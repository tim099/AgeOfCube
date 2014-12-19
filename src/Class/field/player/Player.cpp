#include "Player.h"

Player::Player(int _player,ConstructBuildings *_CBL,CreatCreature *_CCT,Map *_map
,std::queue<CubeCreature*>*_all_creatures,std::vector<Collidable*>*_colli_v
,std::queue<DeletableCube*>*_delete_q,LoadAddress *_LAD) {
	player=_player;
	all_creatures=_all_creatures;
	colli_v=_colli_v;
	delete_q=_delete_q;
	CBL=_CBL;
	CCT=_CCT;
	LAD=_LAD;
	map=_map;
}
Player::~Player() {
	clear_player();
}
void Player::clear_player(){
	clear_building();
	clear_creatures();
	clear_unfinished();
}
void Player::timer_tic(){
	Building *buff;
	int size=buildings.size();

	for(unsigned i=0;i<creatures.size();i++){//creature tic first,to enter building
		if(!creatures.at(i)->exist()){
			creatures.at(i)=creatures.back();
			creatures.pop_back();
		}
		if(i<creatures.size())creatures.at(i)->tic();
	}
	for(int i=0;i<size;i++){
		buff = buildings.front();
		buildings.pop();
		buff->tic();
		if(buff->exist())buildings.push(buff);
	}
	unfinished_tic();
}
void Player::save(FILE *fop){
	player_res.save(fop);
	save_buildings(fop);
	save_creatures(fop);
}
void Player::load(FILE *fop){
	clear_player();
	player_res.load(fop);
	load_buildings(fop);
	load_creatures(fop);
}
void Player::save_creatures(FILE *fop){
	fprintf(fop,"%d\n",creatures.size());
	for(unsigned i=0;i<creatures.size();i++){
		creatures.at(i)->save(fop);
	}
}
void Player::load_creatures(FILE *fop){
	clear_creatures();
	CubeCreature *c;
	int size,type;
	fscanf(fop,"%d\n",&size);
	for(int i=0;i<size;i++){
		fscanf(fop,"%d ",&type);
		c=CCT->creat_creature(type,0,0,0,player);
		c->load(fop);
		c->set_address(LAD);
		push_creature(c);
	}
}
CubeCreature* Player::load_unfinished_creature(int type,FILE *fop){
	CubeCreature *c;
	c=CCT->creat_creature(type,0,0,0,player);
	c->load(fop);
	push_unfinished_creature(c);
	return c;
}
void Player::load_finished(){
	for(unsigned i=0;i<creatures.size();i++){
		creatures.at(i)->load_finished(LAD);
	}
	unsigned b_size=buildings.size();
	Building *buff;
	for(unsigned i=0;i<b_size;i++){
		buff=buildings.front();
		buildings.pop();
		buff->load_finished(LAD);
		buildings.push(buff);
	}
	//finished rigister!!?
}
void Player::clear_creatures(){
	creatures.clear();
}
void Player::clear_unfinished(){
	for(unsigned i=0;i<unfinished_creature.size();i++){//creature tic first,to enter building
		delete unfinished_creature.at(i);
	}
	unfinished_creature.clear();
	for(unsigned i=0;i<unfinished_building.size();i++){//creature tic first,to enter building
		delete unfinished_building.at(i);
	}
	unfinished_building.clear();
}
void Player::save_buildings(FILE *fop){
	Building *b;
	int size=buildings.size();
	fprintf(fop,"%d\n",size);
	for(int i=0;i<size;i++){
		b=buildings.front();
		buildings.pop();
		b->save(fop);
		buildings.push(b);
	}
}
void Player::load_buildings(FILE *fop){
	clear_building();
	int size,_building;
	Building *building;
	fscanf(fop,"%d\n",&size);
	for(int i=0;i<size;i++){
		fscanf(fop,"%d ",&_building);
		building=CBL->build(0,0,0,_building,player);
		building->load(fop);
		building->set_address(LAD);
		build(building);
	}
}
void Player::clear_building(){
	while(!buildings.empty()){
		buildings.pop();
	}
}
int Player::player_num()const{
	return player_num(player);
}
int Player::player_num(int _player)const{
	int num=0,buff=_player;
	while(buff>1){
		buff>>=1;
		num++;
	}
	return num;
}
void Player::push_building(Building *b){
	buildings.push(b);
}
void Player::push_unfinished_creature(CubeCreature* creature){
	unfinished_creature.push_back(creature);
}
void Player::push_unfinished_building(Building *b){
	unfinished_building.push_back(b);
}
CubeCreature* Player::recruit_creature(Building *b,int type){
	CubeCreature *c;
	c=CCT->creat_creature(type,0.1*b->get_x()+0.05,0.1*b->get_y(),0.1*b->get_z()+0.05,player);
	if(b->consume_resources(c->require_resources())){
		//push in unfinish_v?already consume resources
		push_unfinished_creature(c);
		//push_creature(c);
		return c;//have enough resources
	}else{
		delete c;
		return 0;
	}
}
void Player::push_creature(CubeCreature* creature){
	creatures.push_back(creature);
	all_creatures->push(creature);
	colli_v->push_back(creature);
	delete_q->push(creature);
}
void Player::unfinished_tic(){
	for(unsigned i=0;i<unfinished_creature.size();i++){//creature tic first,to enter building
		if(!unfinished_creature.at(i)->exist()){
			delete unfinished_creature.at(i);
			unfinished_creature.at(i)=unfinished_creature.back();
			unfinished_creature.pop_back();
		}
		if(i<unfinished_creature.size()){
			if(!unfinished_creature.at(i)->unfinished()){//finished!!
				push_creature(unfinished_creature.at(i));
				unfinished_creature.at(i)=unfinished_creature.back();
				unfinished_creature.pop_back();
			}
		}
	}

	for(unsigned i=0;i<unfinished_building.size();i++){//creature tic first,to enter building
		if(!unfinished_building.at(i)->exist()){
			delete unfinished_building.at(i);
			unfinished_building.at(i)=unfinished_building.back();
			unfinished_building.pop_back();
		}
		if(i<unfinished_building.size()){
			if(!unfinished_building.at(i)->unfinished()){//finished!!
				build(unfinished_building.at(i));
				unfinished_building.at(i)=unfinished_building.back();
				unfinished_building.pop_back();
			}
		}
	}
}
bool Player::buildable(int x,int y,int z,int _building){
	Building *building=CBL->build(x,y,z,_building,player);
	if(map->buildable(building)){
		delete building;
		return true;
	}else{
		delete building;
		return false;
	}
}
Building* Player::build(int x,int y,int z,int _building,bool unfinished){
	Building *building=CBL->build(x,y,z,_building,player,unfinished);//unfinished building
	return build(building);
}
Building* Player::build(Building *building){
	if(map->build(building)){
		push_building(building);
		return building;
	}else{
		delete building;
		return 0;
	}
}
int Player::which_player()const{
	return player;
}
