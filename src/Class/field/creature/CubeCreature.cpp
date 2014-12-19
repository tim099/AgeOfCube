#include "CubeCreature.h"
#include "AllOrder.h"
#include "Building.h"
#include "map/Map.h"
#include "Core.h"
#include "CreatureMap.h"
CubeCreature::CubeCreature(double _x,double _y,double _z,int _player,Map *_map
,std::vector<Collidable*>*_colli_v,std::vector<CubeCreature*>*_f_units,std::queue<Building*>*_f_buildings)
:PlayerOwnObject(_player),Collidable(_x,_y,_z,_colli_v,_map){
	cube_type=C_CREATURE;
	f_units=_f_units;
	f_buildings=_f_buildings;

	orders=new AllOrder(this,map,f_buildings);
	move_state=new StateMove(this);

	_selected=false;
	_stay_in_building=false;

	timer=0;
	_in_building=0;
	core=0;
	energy=0;
	address=this;
	//printf("creature=%X\n",(unsigned int)this);
}
CubeCreature::~CubeCreature() {
	delete orders;
	delete move_state;
}
CubeWorker* CubeCreature::worker(){
	return 0;
}
Order *CubeCreature::cur_order()const{
	return orders->cur_order();
}
unsigned CubeCreature::cur_energy()const{
	return energy;
}
unsigned CubeCreature::consume_energy(unsigned num){
	if(num>energy){
		num=energy;//dont have enough energy
		energy=0;
	}else{
		energy-=num;//have enough energy
	}
	return num;
}
void CubeCreature::restore_energy(unsigned num){
	energy+=num;
	if(energy>max_energy())energy=max_energy();
}
unsigned CubeCreature::idle_time()const{
	return orders->idle_time();
}
bool CubeCreature::get_in_building(){
	if(_stay_in_building)return true;
	if(in_building()){
		if(in_building()->get_in(this)){
			_stay_in_building=true;
			freeze();
			return true;
		}
	}
	return false;
}
void CubeCreature::get_out_building(){
	_stay_in_building=false;
}
Building* CubeCreature::in_building()const{
	if(_in_building)return _in_building;
	else return 0;
}
Building* CubeCreature::stay_in_building()const{
	if(_stay_in_building){
		return _in_building;
	}else return 0;
}
void CubeCreature::detect_at(){
	_in_building=map->get_map(in_x(),in_y(),in_z())->get_building();
	if(!_in_building)_stay_in_building=false;
}
int CubeCreature::colli_state()const{
	if(stay_in_building())return C_STATE_COLLI_OFF;
	return C_STATE_COLLI_ON;
}
void CubeCreature::tic(){
	timer++;
	detect_at();
	if(core!=0)core->tic();
	orders->tic();//sent order to state
	move_state_tic();//control creature
	avoid_collision();//avoid friend unit colli
	move_timer_tic();
	timer_tic();
	if(timer>1000000)timer=0;
}
void CubeCreature::timer_tic(){

}
void CubeCreature::clean_order(){
	orders->clean_order();
}
void CubeCreature::go_to(unsigned x,unsigned y,unsigned z){
	orders->go_to(x,y,z);
}
void CubeCreature::dp_players_creature(){
	glPushMatrix();
	glScalef(size,size,size);
	dp_selected();
	dp_players_color();
	glRotatef(ry,0,1,0);
	dp_creature();
	glPopMatrix();
}
void CubeCreature::dp_players_color(){
	switch(player){
		case MOTHER_EARTH:
			glCallList(DP_P0_CREATURE);
			break;
		case P1:
			glCallList(DP_P1_CREATURE);
			break;
		case P2:
			glCallList(DP_P2_CREATURE);
			break;
		case P3:
			glCallList(DP_P3_CREATURE);
			break;
		case P4:
			glCallList(DP_P4_CREATURE);
			break;
		case P5:
			glCallList(DP_P5_CREATURE);
			break;
		case P6:
			glCallList(DP_P6_CREATURE);
			break;
		case P7:
			glCallList(DP_P7_CREATURE);
			break;
	}
}
void CubeCreature::save_address(FILE *file){
	fprintf(file,"%x ",(unsigned)this);//save address
}
void CubeCreature::load_address(FILE *file){
	fscanf(file,"%x ",(unsigned*)&address);
}
void CubeCreature::set_address(LoadAddress* LAD){
	LAD->push_creature_address(address,this);
}
void CubeCreature::load_finished(LoadAddress* LAD){
	orders->load_finished(LAD);
	creature_load_finished(LAD);
}
void CubeCreature::creature_load_finished(LoadAddress* LAD){

}
void CubeCreature::save_cube(FILE *file){
	fprintf(file,"%u ",energy);
	save_address(file);
	carry_res.save(file);
	orders->save_orders(file);
	save_player(file);
	save_colli(file);
	save_creature(file);
	save_constructable(file);
	save_health(file);
}
void CubeCreature::load_cube(FILE *file){
	fscanf(file,"%u ",&energy);
	load_address(file);
	carry_res.load(file);
	orders->load_orders(file);
	load_player(file);
	load_colli(file);
	load_creature(file);
	load_constructable(file);
	load_health(file);
}
void CubeCreature::save_creature(FILE *file){
	fprintf(file,"\n");
}
void CubeCreature::load_creature(FILE *file){
	fscanf(file,"\n");
}
StateMove *CubeCreature::cur_move_state()const{
	return move_state;
}
void CubeCreature::move_state_tic(){
	if(move_state->END())switch_move_state(new StateMove(this));
	move_state->tic();//cant delete
}
void CubeCreature::switch_move_state(StateMove* s_move){
	delete move_state;
	move_state=s_move;
}
void CubeCreature::avoid_collision(Collidable* cube){
	cur_move_state()->avoid_collision(cube);
}
void CubeCreature::avoid_collision(){
	if(cur_move_state()->get_move_state()==MS_AVOID_COLLISION)return;
	if(colli_state()==C_STATE_COLLI_OFF)return;
	if(get_v()<0.00001)return;
	std::vector<CubeCreature*>*creature_v;
	CubeCreature* avoid_creature;
	int x=in_x(),y=in_y(),z=in_z();
	for(int i=-1;i<=1;i++){
		for(int j=-1;j<=1;j++){
			for(int k=-1;k<=1;k++){
				creature_v=map->creature_map->get_creature_map(x+i,y+j,z+k);
				for(unsigned i=0;i<creature_v->size();i++){
					avoid_creature=creature_v->at(i);
					if(avoid_creature!=this&&avoid_creature->colli_state()!=C_STATE_COLLI_OFF
							&&avoid_creature->belong_to()==belong_to())
					if(pre_collide(creature_v->at(i))){
						creature_v->at(i)->avoid_collision(this);
					}
				}
			}
		}
	}
}
State *CubeCreature::cur_state()const{
	return orders->cur_order()->cur_state();
}
