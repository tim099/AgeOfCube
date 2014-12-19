#include "WorkableBuilding.h"
#include "CubeWorker.h"
#include "WorkDefine.h"
#include "Player.h"
#include "SearchCube.h"
#include "Job/JobWorking.h"
WorkableBuilding::WorkableBuilding(unsigned x,unsigned y,unsigned z,Player *cur_player,int player)
:Building(x,y,z,cur_player,player){
	_job_type=WORK_NORMAL;
	rally_point_find=false;
}
WorkableBuilding::~WorkableBuilding() {
	clear_workers();
	while(!construct_q.empty()){
		construct_q.front()->delete_cube(3);
		construct_q.pop();
	}
}
void WorkableBuilding::save_workers(FILE* file){
	fprintf(file,"%u\n",workers.size());
	for(unsigned i=0;i<workers.size();i++){
		fprintf(file,"%x ",(unsigned)workers.at(i));
	}
}
void WorkableBuilding::load_workers(FILE* file){
	unsigned w_size;
	CubeWorker *buff;
	fscanf(file,"%u\n",&w_size);
	for(unsigned i=0;i<w_size;i++){
		fscanf(file,"%x ",(unsigned*)&buff);
		workers.push_back(buff);
	}
}
void WorkableBuilding::save_building(FILE *file){
	save_construct_q(file);
	save_workablebuilding(file);
	save_rally_point(file);
	save_workers(file);
}
void WorkableBuilding::load_building(FILE *file){
	load_construct_q(file);
	load_workablebuilding(file);
	load_rally_point(file);
	load_workers(file);
}
void WorkableBuilding::load_finished(LoadAddress* LAD){
	for(unsigned i=0;i<workers.size();i++){
		workers.at(i)=LAD->get_creature(workers.at(i))->worker();
	}
}
void WorkableBuilding::save_workablebuilding(FILE *file){
	fprintf(file,"\n");
}
void WorkableBuilding::load_workablebuilding(FILE *file){
	fscanf(file,"\n");
}
void WorkableBuilding::save_rally_point(FILE* file){
	fprintf(file,"%d ",rally_point_find);
	rally_point.save(file);
}
void WorkableBuilding::load_rally_point(FILE* file){
	int _find;
	fscanf(file,"%d ",&_find);
	rally_point.load(file);
	if(_find)rally_point_find=true;
}
void WorkableBuilding::save_construct_q(FILE *file){
	unsigned size=construct_q.size();
	fprintf(file,"%u ",size);
	CubeCreature* c;
	for(unsigned i=0;i<size;i++){
		c=construct_q.front();
		construct_q.pop();
		c->save(file);
		construct_q.push(c);
	}
}
void WorkableBuilding::load_construct_q(FILE *file){
	unsigned size;
	int type;
	fscanf(file,"%u ",&size);
	for(unsigned i=0;i<size;i++){
		fscanf(file,"%d ",&type);
		push_construct(cur_player->load_unfinished_creature(type,file));
	}
}
bool WorkableBuilding::check_workers(CubeWorker* worker){
	if(worker){
		for(unsigned i=0;i<workers.size();i++)if(worker==workers.at(i))return true;
	}
	return false;
}
bool WorkableBuilding::get_in(CubeCreature *creature){
	if(creature->belong_to()==belong_to()){
		if(check_workers(creature->worker())){
			in_b_creatures.push_back(creature);
			return true;//have space
		}
	}
	return false;
}
unsigned WorkableBuilding::building_produce_work(){
	return 0;
}
void WorkableBuilding::push_construct(CubeCreature* creature){
	construct_q.push(creature);
}
bool WorkableBuilding::worker_rigister(CubeWorker* worker){
	if(have_job()){//if still need worker
		workers.push_back(worker);
		Work* w_work=worker->cur_work();
		if(!w_work->cur_job()){//no job
			w_work->set_job(new JobWorking(this,cur_player->map,worker));
		}
		return true;
	}
	return false;
}
int WorkableBuilding::job_type(){
	return _job_type;
}
int WorkableBuilding::work_type(){
	return WORK_NORMAL;
}
double WorkableBuilding::recruit_process()const{
	Constructable* c=cur_constructing();
	if(c){
		return ((double)c->cur_work()/(double)c->require_work());
	}
	return 0;
}
Constructable* WorkableBuilding::cur_constructing()const{
	if(construct_q.empty())return 0;
	return construct_q.front();
}
void WorkableBuilding::clear_workers(){
	for(unsigned i=0;i<workers.size();i++){
		workers.at(i)->work_lost();
		workers.at(i)->get_out_building();
		if(find_rally_point())workers.at(i)->go_to(rally_point.x,rally_point.y,rally_point.z);
	}
	workers.clear();
}
void WorkableBuilding::dp_rally_point(){
	glPushMatrix();
	glEnable(GL_LIGHT2);
	glTranslatef(0.1*rally_point.x+0.05,0.1*rally_point.y,0.1*rally_point.z+0.05);
	glCallList(MISC_RALLY_POINT);
	glDisable(GL_LIGHT2);
	glPopMatrix();
}
void WorkableBuilding::set_rally_point(unsigned x,unsigned y,unsigned z){
	if(cur_player->map->get_map(x,y,z)->typ()!=C_NULL)return;
	rally_point_find=true;
	rally_point.x=x;
	rally_point.y=y;
	rally_point.z=z;
}
bool WorkableBuilding::find_rally_point(){
	if(rally_point_find){
		if(cur_player->map->get_map(rally_point.x,rally_point.y,rally_point.z)->typ()==C_NULL)return true;
	}
	std::vector<StaticCube*>find_v;
	std::vector<Route::point>find_p;
	cur_player->map->get_path()->search(get_x(),get_y(),get_z()
	,new SearchCube(C_NULL),find_v,10,100,&find_p);
	if(!find_p.empty()){
		set_rally_point(find_p.back().x,find_p.back().y,find_p.back().z);
		return true;
	}
	return false;
}
void WorkableBuilding::construct_finished(){
	CubeCreature *finished_creature=construct_q.front();
	construct_q.pop();
	if(find_rally_point()){
		finished_creature->go_to(rally_point.x,rally_point.y,rally_point.z);
	}
}
void WorkableBuilding::construct(unsigned work){
	Constructable* constructing_obj=cur_constructing();
	if(constructing_obj){
		if(constructing_obj->construct(work)){//finished
			construct_finished();
		}
	}
}

bool WorkableBuilding::recruit_creature(int type){
	CubeCreature* creature=cur_player->recruit_creature(this,type);
	if(creature){
		creature->restore_energy(creature->max_energy());
		push_construct(creature);
		return true;
	}else return false;
}
void WorkableBuilding::timer_tic(){
	CubeWorker *worker;
	//printf("cur_worker num=%u\n",workers.size());
	//printf("construct size=%u\n",construct_q.size());
	for(unsigned i=0;i<workers.size();i++){
		worker=workers.at(i);
		if(!worker->exist()||worker->cur_work()==0//check worker not exist
		||worker->cur_work()->get_pos()!=get_pos()){//not work at this building
			workers.at(i)=workers.back();
			worker=workers.at(i);
			workers.pop_back();
		}
		if(i<workers.size()){//tic?get work from worker
			if(worker->stay_in_building()==this){
				if(cur_constructing()){get_work(worker);}
				else {clear_workers();}//test
			}
		}
	}
	construct(building_produce_work());//construct by building produce work

	work_timer_tic();
}
void WorkableBuilding::work_timer_tic(){
	printf("undefine work timer tic of building %d\n",cube_type);
}
WorkableBuilding* WorkableBuilding::workablebuilding(){
	return this;
}
