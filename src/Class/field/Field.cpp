#include "Field.h"
#include "CreatureMap.h"
Field::Field(Mouse *_mou,Keyboard *_k_b,BasicButList *_SLB,Messagebox *_MSB) {
	mode = new Mode();
	map = new Map(&delete_q,&creatures,250,100,250);

	CBL = new ConstructBuildings(&players,map);
	CCT = new CreatCreature(map,&colli_v,&players);
	LAD = new LoadAddress();
	dp_height=0;

	mou=_mou;
	k_b=_k_b;
	SLB=_SLB;
	MSB=_MSB;
	mou->selected_cube=0;
	mou->selected_building=0;
	mou->selected_creature=0;
	//look=_look;look_v=_look_v;
	for(int i=0;i<3;i++){
		players.push_back(Player(1<<i,CBL,CCT,map,&creatures,&colli_v,&delete_q,LAD));
	}
	cur_player=1;
}
Field::~Field() {
	delete mode;
	delete CBL;
	delete CCT;
	delete LAD;
	while(!delete_q.empty()){
		if(!delete_q.front()->exist())delete delete_q.front();
		delete_q.pop();
	}
	while(!creatures.empty()){
		delete creatures.front();//must delete before path delete
		creatures.pop();
	}
	delete map;//path delete and order find path will have problem
	clear_field();
}
void Field::clear_field(){
	while(!creatures.empty())creatures.pop();
	while(!colli_v.empty())colli_v.clear();
	while(!delete_q.empty())delete_q.pop();
}
void Field::save_players(FILE *fop){
	fprintf(fop,"%d\n",players.size());
	for(unsigned i=0;i<players.size();i++){
		players.at(i).save(fop);
	}
}
void Field::load_players(FILE *fop){
	unsigned size;
	fscanf(fop,"%d\n",&size);
	for(unsigned i=0;i<size;i++){
		players.at(i).load(fop);
	}
}
void Field::save_field(const char *filename){
	FILE *fop=fopen(filename,"w+t");
	map->Save_Map(fop);
	save_players(fop);
	fclose(fop);
}
void Field::load_finish(){

	for(unsigned i=0;i<players.size();i++){
		players.at(i).load_finished();
	}
}
void Field::load_field(const char *filename){
	FILE *fop=fopen(filename,"r");
	if(fop==0){
		printf("No save map:%s\n",filename);
		return;
	}
	map->Load_Map(fop);
	load_players(fop);
	load_finish();
	fclose(fop);
}
void Field::generate_map(){
	map->creat_map_flat(250,8,250,C_BASIC,0,8,0);
	map->creat_map_flat(250,8,250,C_DARK,0,0,0);
	srand(time(NULL));
	map->generate_map(rand());
}
void Field::find_selected_cube(){
	mou->selected_cube=map->get_map(mou->select_x,mou->select_y,mou->select_z);
}
void Field::switch_mode(Mode *_mode){
	if(mode!=0)delete mode;
	mode=_mode;
}
void Field::switch_building_mode(int building_type,bool unfinished){
	switch_mode(new BuildingMode(CBL,mou,&players.at(cur_player),building_type,unfinished));
}
void Field::building_signal(Signal s){
	switch(s.sig()){
		case S_BUILD:
			switch_building_mode(s.extra_sig(),false);
			break;
		case S_BUILD_UNFINISHED:
			switch_building_mode(s.extra_sig(),true);
			break;
		case S_CREAT_CUBE:
			switch_mode(new CreatCubeMode(mou,map,s.extra_sig()));
			break;
		case S_DESTRUCT:
			switch_mode(new DestructMode(mou,map));
			break;
		default:
		printf("unknow building signal\n");
	}
}
void Field::handle_signal(){
	while(!signal_q.empty()){
		signal_process(signal_q.front());
		signal_q.pop();
	}
}
void Field::signal_process(Signal sig){
	switch(sig.typ()){
		case T_FIELD_BUILDING:
			building_signal(sig);
			break;
		case T_MODE_SIGNAL:
			if(mode!=0)mode->sent_signal(sig);
			else printf("mode is empty !! cant handle mode signal!!\n");//pipe signal into mode!!
			break;
		default:
		printf("cant process signal %d by original field\n",sig.sig());
	}
}
void Field::sent_signal(Signal sig){
	signal_q.push(sig);
}
Building* Field::s_building()const{
	return mou->selected_building;
}
CubeCreature* Field::s_creature()const{
	return mou->selected_creature;
}
void Field::find_selected_building(){
	int size=map->buildings.size();
	bool find=false;
	Building *buff;
	for(int i=0;i<size;i++){
		buff=map->buildings.front();
		map->buildings.pop();
		if(!find&&buff->exist()&&buff->belong_to()==players.at(cur_player).which_player()
				&&buff->get_x()==mou->select_x&&buff->get_y()==mou->select_y&&buff->get_z()==mou->select_z){
			mou->selected_building=buff;
			find=true;
		}
		map->buildings.push(buff);
	}
	if(!find)mou->selected_building=0;
}
void Field::find_selected_creature(){
	int size=creatures.size();
	bool find=false;
	double dx,dy,dz,dis;
	CubeCreature *buff;
	for(int i=0;i<size;i++){
		buff=creatures.front();
		creatures.pop();
		dx=(fabs(mou->px-buff->get_x()));
		dy=(fabs(mou->py-buff->get_y()));
		dz=(fabs(mou->pz-buff->get_z()));
		dis=sqrt(dx*dx+dz*dz);
		if(!find&&buff->exist()&&buff->belong_to()==players.at(cur_player).which_player()&&
				dis<buff->get_size()&&dy<2*buff->get_size()){
			mou->selected_creature=buff;
			find=true;
		}
		creatures.push(buff);
	}
	if(!find)mou->selected_creature=0;
}
void Field::selected_pos_compute(){
	double dx=10*mou->px-floor(10*mou->px);
	double dy=10*mou->py-floor(10*mou->py);
	double dz=10*mou->pz-floor(10*mou->pz);
	mou->select_x=(unsigned)floor(10*mou->px);
	mou->select_y=(unsigned)floor(10*mou->py);
	mou->select_z=(unsigned)floor(10*mou->pz);
	if(mou->select_x>=map->MSX())mou->select_x=(map->MSX()-1);
	if(mou->select_y>=map->MSY())mou->select_y=(map->MSY()-1);
	if(mou->select_z>=map->MSZ())mou->select_z=(map->MSZ()-1);
		//map->discover(select_x,select_y,select_z,P2);
	if(dx>0.95){
		mou->surface_x=1;
	}else if(dx<0.05){
		mou->surface_x=-1;
	}else{
		mou->surface_x=0;
	}
	if(dy>0.95){
		mou->surface_y=1;
	}else if(dy<0.05){
		mou->surface_y=-1;
	}else{
		mou->surface_y=0;
	}
	if(dz>0.95){
		mou->surface_z=1;
	}else if(dz<0.05){
		mou->surface_z=-1;
	}else{
		mou->surface_z=0;
	}
	if(mou->surface_y!=0){
		mou->surface_x=0;
		mou->surface_z=0;
	}else if(fabs(dz-0.5)>fabs(dx-0.5)){
		mou->surface_x=0;
	}else{
		mou->surface_z=0;
	}
}
void Field::control(){
	if(k_b->get('w')){
		if(dp_height<map->MSY())dp_height++;
	}
	if(k_b->get('s')){
		if(dp_height>0)dp_height--;
	}
	if(k_b->get('t')){
		if(cur_player<(int)(players.size()-1))cur_player++;
		else cur_player=0;
	}
	if(k_b->get('g')){
		if(cur_player>0)cur_player--;
		else cur_player=(players.size()-1);
	}
}
void Field::creatures_timer_tic(){
	unsigned size=creatures.size();
	CubeCreature *buff;
	for(unsigned i=0;i<size;i++){
		buff=creatures.front();
		creatures.pop();
		if(buff->exist())creatures.push(buff);
	}
}
void Field::colli_q_timer_tic(){
	//printf("colli_size=%u,creatures=%u\n",colli_q.size(),creatures.size());
	for(unsigned i=0;i<colli_v.size();i++){
		if(!colli_v.at(i)->exist()){
			colli_v.at(i)=colli_v.back();
			colli_v.pop_back();
		}
	}
}
void Field::terminate_timer_tic(){
	unsigned size=delete_q.size();
	DeletableCube *buff;
	for(unsigned i=0;i<size;i++){
		buff=delete_q.front();
		delete_q.pop();
		buff->terminate_timer_tic();
		if(buff->terminate())delete buff;
		else delete_q.push(buff);
	}
}
void Field::mode_timer_tick(){
	mode->tic();
	if(mode->END()){
		Mode *m = new Mode();
		switch_mode(m);
	}
}
void Field::selected_creature(){
	CubeCreature *s_creature=mou->selected_creature;
	if(s_creature){
		CubeWorker *s_worker=s_creature->worker();
		if(s_worker){
			switch_mode(new SelectWorkerMode(mou,SLB,s_worker,k_b));
		}else{
			switch_mode(new SelectCreatureMode(mou,SLB,s_creature,k_b));
		}
	}

}
void Field::tic(){
	//clock_t start_time=clock(),time_cost;
	selected_pos_compute();
	find_selected_cube();

	mode_timer_tick();

	handle_signal();
	timer_tick();

	map->creature_map->tic();
	for(unsigned i=0;i<players.size();i++)players.at(i).timer_tic();

	map->tic();//pop delete obj
	colli_q_timer_tic();//pop delete obj
	creatures_timer_tic();//pop delete obj
	terminate_timer_tic();//remove delete things!!buildings and creature

	find_selected_building();
	find_selected_creature();
	if(mou->selected_creature!=0&&!(mou->selected_creature->in_building())&&
			mode->get_mode()==MODE_BASIC&&mou->get_but(0)){//
		selected_creature();
	}else if(mou->selected_building!=0&&mou->selected_building->selectable()&&
			mode->get_mode()==MODE_BASIC&&mou->get_but(0)){//
		if(mou->selected_building->workablebuilding()){
			switch_mode(new SelectWorkableBuildingMode(mou,map,SLB,MSB,&players.at(cur_player),CCT,
					mou->selected_building->workablebuilding()));
		}else switch_mode(new SelectBuildingMode(mou,map,SLB,MSB,&players.at(cur_player),CCT,mou->selected_building));
	}else if(mode->get_mode()==MODE_BASIC&&mou->get_but(0)){//select nothing
		switch_mode(new SelectGroupMode(mou,&players.at(cur_player)));
	}
	control();
	//time_cost=(clock()-start_time);
	//printf("field_time_cost=%lfsec\n",(double)time_cost/(double)(CLOCKS_PER_SEC));
}
