#include <UnfinishedBuilding.h>
#include "Player.h"
UnfinishedBuilding::UnfinishedBuilding(int x,int y,int z,Player *cur_player,Building *_constructing_building
,ConstructBuildings *_CBL,int player) : WorkableBuilding(x,y,z,cur_player,player){
	cube_type=C_UNFINISHED_BUILDING;
	set_construct(_constructing_building);
	CBL=_CBL;
	path|=M_STANDABLE;
	extra_path|=M_EX_DOWN_STANDABLE;
	extra_path|=M_EX_NOT_DOWN;
}
UnfinishedBuilding::~UnfinishedBuilding() {
	if(constructing_building->unfinished())constructing_building->delete_cube(3);
}
std::string UnfinishedBuilding::name(){
	return constructing_building->name();
}
void UnfinishedBuilding::save_construct(FILE *file){
	constructing_building->save(file);
}
void UnfinishedBuilding::load_construct(FILE *file){
	int type;
	fscanf(file,"%d ",&type);
	set_construct(CBL->build(0,0,0,type,player));
	constructing_building->load(file);
	cur_player->push_unfinished_building(constructing_building);
}
void UnfinishedBuilding::set_construct(Building *_constructing_building){
	constructing_building=_constructing_building;
	if(constructing_building)cb_on=constructing_building->can_build_on();
}
void UnfinishedBuilding::save_workablebuilding(FILE *file){
	save_construct(file);
	save_unfinishbuilding(file);
}
void UnfinishedBuilding::load_workablebuilding(FILE *file){
	load_construct(file);
	load_unfinishbuilding(file);
}
void UnfinishedBuilding::save_unfinishbuilding(FILE *file){
	fprintf(file,"\n");
}
void UnfinishedBuilding::load_unfinishbuilding(FILE *file){
	fscanf(file,"\n");
}
bool UnfinishedBuilding::selectable()const{return false;}
unsigned UnfinishedBuilding::require_work()const{
	return 5000;
}
Resource UnfinishedBuilding::require_resources(){
	Resource res;
	res.set_res(R_CUBE,2000);
	res.set_res(R_CORE,100);
	return res;
}
unsigned UnfinishedBuilding::max_worker_num()const{
	return 5;
}
bool UnfinishedBuilding::have_job()const{
	if(workers.size()<max_worker_num())return true;
	else return false;
}
void UnfinishedBuilding::work_timer_tic(){

}
void UnfinishedBuilding::construct_finished(){//build done!!
	cur_player->map->delete_cube(get_x(),get_y(),get_z());//delete this unfinished building
}
Constructable* UnfinishedBuilding::cur_constructing()const{
	return constructing_building;
}
std::vector<Building::But_type>& UnfinishedBuilding::Upgrade_button(std::vector<Building::But_type> &_Upgrade_but){
	_Upgrade_but.push_back(Building::But_type("None",Signal(S_NULL)));
	return _Upgrade_but;
}
std::vector<Building::But_type>& UnfinishedBuilding::Recruit_button(std::vector<Building::But_type> &_Recruit_but){
	_Recruit_but.push_back(Building::But_type("None",Signal(S_NULL)));
	return _Recruit_but;
}
std::vector<Building::But_type>& UnfinishedBuilding::Research_button(std::vector<Building::But_type> &_Research_but){
	_Research_but.push_back(Building::But_type("None",Signal(S_NULL)));
	return _Research_but;
}
std::vector<Building::But_type>& UnfinishedBuilding::Info_button(std::vector<Building::But_type> &_Info_but){
	return _Info_but;
}
void UnfinishedBuilding::dp_building(){
	//glCallList(DP_BASE);
	glPushMatrix();
	glPushMatrix();
	glTranslatef(0,0.06,0);
	ListBar::dp_bar(this->recruit_process()*100,100,0.001,10.0,ListBar::color(0,1,0,0));
	glPopMatrix();
	glPolygonMode (GL_FRONT,GL_POINT);
	glPolygonMode (GL_BACK,GL_LINE);
	constructing_building->dp_players_building();
	glPolygonMode (GL_FRONT_AND_BACK,GL_FILL);//GL_POINT //
	glPopMatrix();
}
