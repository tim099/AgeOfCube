#include "Building.h"
#include "CubeCreature.h"
#include "Player.h"
#include "BasicButList.h"
Building::Building(unsigned _x,unsigned _y,unsigned _z,Player *_cur_player,int _player) : PlayerOwnObject(_player){
	cube_type=C_BUILDING;
	pos.x=_x;pos.y=_y;pos.z=_z;
	CubeCapacity=0;
	b_function=0;
	discovered|=_player;
	cb_on=ON_BUT;
	b_on=0;
	path|=M_UP;
	path|=M_DOWN;
	path|=M_LEFT;
	path|=M_RIGHT;
	path|=M_FRONT;
	path|=M_BACK;
	extra_path=0;
	cur_player=_cur_player;
	address=this;
}
Building::~Building() {

}
void Building::set_address(LoadAddress* LAD){
	LAD->push_building_address(address,this);
}
void Building::load_finished(LoadAddress* LAD){

}
unsigned char Building::get_path()const{
	return path;
}
unsigned char Building::get_extra_path()const{
	return extra_path;
}
Building* Building::get_building(){
	return this;
}
WorkableBuilding *Building::workablebuilding(){
	return 0;
}
void Building::in_building_creature_check(){
	for(unsigned i=0;i<in_b_creatures.size();i++){
		if(in_b_creatures.at(i)->stay_in_building()!=this){//get_out
			in_b_creatures.at(i)=in_b_creatures.back();
			in_b_creatures.pop_back();
		}
	}
}
void Building::tic(){
	//printf("in_b_creatures num=%u\n",in_b_creatures.size());
	timer_tic();
	in_building_creature_check();
}
void Building::creat_button(BasicButList *SLB,std::vector<BasicButGroup*>*but_groups){
	creat_recruit_button(SLB,but_groups);
	creat_upgrade_button(SLB,but_groups);
	creat_research_button(SLB,but_groups);
	creat_info_button(SLB,but_groups);
}
void Building::creat_button_group(BasicButList *SLB,std::vector<Building::But_type>&buff,BasicButGroup *group){
	double disy=0.003,posx=-0.026,posy=-0.0075;
	for(unsigned i=0;i<buff.size();i++){
		group->push_button(SLB->creat_basic_button(buff.at(i).name.c_str(),buff.at(i).sig));
	}
	group->set_auto_pos(posx,posy,0,-disy,4);
}
void Building::creat_recruit_button(BasicButList *SLB,std::vector<BasicButGroup*>*but_groups){
	double disy=0.003,posx=-0.026,posy=-0.0075;
	BasicButGroup *Recruit=SLB->push_unique_but_group(new BasicButGroup());
	but_groups->push_back(Recruit);
	but_groups->at(0)->push_button(SLB->creat_ShowButGroup_button("Recruit",Signal(T_MODE_SIGNAL,DP_GROUP_RECRUIT),Recruit,true,2));
	Recruit->push_indie_button(SLB->creat_medium_button("Recruit",Signal(S_MODE_RECRUIT),posx+0.02,posy-5.3*disy));
	std::vector<Building::But_type>buff=Recruit_but();
	creat_button_group(SLB,buff,Recruit);
}
void Building::creat_upgrade_button(BasicButList *SLB,std::vector<BasicButGroup*>*but_groups){
	BasicButGroup *Upgrade=SLB->push_unique_but_group(new BasicButGroup());
	but_groups->push_back(Upgrade);
	but_groups->at(0)->push_button(SLB->creat_ShowButGroup_button("Upgrade",Signal(T_MODE_SIGNAL,DP_GROUP_RECRUIT),Upgrade,true,2));
	std::vector<Building::But_type>buff=Upgrade_but();
	creat_button_group(SLB,buff,Upgrade);
}
void Building::creat_info_button(BasicButList *SLB,std::vector<BasicButGroup*>*but_groups){
	BasicButGroup *Info=SLB->push_unique_but_group(new BasicButGroup());
	but_groups->push_back(Info);
	but_groups->at(0)->push_button(SLB->creat_ShowButGroup_button("Info",Signal(T_MODE_SIGNAL,DP_GROUP_BUILDING_INFO),Info,true,2));
	std::vector<Building::But_type>buff=Info_but();
	creat_button_group(SLB,buff,Info);
}
void Building::creat_research_button(BasicButList *SLB,std::vector<BasicButGroup*>*but_groups){
	BasicButGroup *Research=SLB->push_unique_but_group(new BasicButGroup());
	but_groups->push_back(Research);
	but_groups->at(0)->push_button(SLB->creat_ShowButGroup_button("Research",Signal(T_MODE_SIGNAL,DP_GROUP_RESEARCH),Research,true,2));
	std::vector<Building::But_type>buff=Research_but();
	creat_button_group(SLB,buff,Research);
}
std::vector<Building::But_type> Building::Upgrade_but(){
	std::vector<Building::But_type> _Upgrade_but;
	return Upgrade_button(_Upgrade_but);
}
std::vector<Building::But_type> Building::Recruit_but(){
	std::vector<Building::But_type> _Recruit_but;
	return Recruit_button(_Recruit_but);
}
std::vector<Building::But_type> Building::Research_but(){
	std::vector<But_type> _Research_but;
	return Research_button(_Research_but);
}
std::vector<Building::But_type> Building::Info_but(){
	std::vector<But_type> _Info_but;
	_Info_but.push_back(Building::But_type("Resources",Signal(S_MODE_DP,DP_BUILDING_RESOURCE)));
	return Info_button(_Info_but);
}
bool Building::get_in(CubeCreature *creature){
	if(creature->belong_to()==belong_to()){
		in_b_creatures.push_back(creature);
		return true;//have space
	}
	return false;
}
int Building::can_build_on()const{
	return cb_on;
}
int Building::build_on()const{
	return b_on;
}
bool Building::set_build_on(int build_on){
	if(build_on&can_build_on()){
		b_on=build_on;
		return true;
	}else return false;
}
void Building::dp_player_color(){
	switch(player){
		case MOTHER_EARTH:
			glCallList(DP_P0_BUILDING);
			break;
		case P1:
			glCallList(DP_P1_BUILDING);
			break;
		case P2:
			glCallList(DP_P2_BUILDING);
			break;
		case P3:
			glCallList(DP_P3_BUILDING);
			break;
		case P4:
			glCallList(DP_P4_BUILDING);
			break;
		case P5:
			glCallList(DP_P5_BUILDING);
			break;
		case P6:
			glCallList(DP_P6_BUILDING);
			break;
		case P7:
			glCallList(DP_P7_BUILDING);
			break;
	}
}
void Building::dp_players_building(){
	glPushMatrix();
	dp_player_color();
	dp_building();
	glPopMatrix();
}
void Building::save_address(FILE *file){
	fprintf(file,"%x ",(unsigned)this);//save address
}
void Building::load_address(FILE *file){
	fscanf(file,"%x ",(unsigned*)&address);
}
void Building::save_static_cube(FILE *file){
	pos.save(file);
	fprintf(file,"%d %d %u ",CubeCapacity,b_on,b_function);
	save_address(file);
	save_res(file);
	save_player(file);
	save_building(file);
	save_constructable(file);
}
void Building::load_static_cube(FILE *file){
	pos.load(file);
	fscanf(file,"%d %d %u ",&CubeCapacity,&b_on,&b_function);
	load_address(file);
	load_res(file);
	load_player(file);
	load_building(file);
	load_constructable(file);
}
bool Building::recruit_creature(int type){
	//return cur_player->recruit_creature(this,type);
	printf("cant recruit by original building\n");
	return false;//
}
void Building::save_building(FILE *file){
	fprintf(file,"\n");
}
void Building::load_building(FILE *file){
	fscanf(file,"\n");
}
void Building::set_pos(int _x,int _y,int _z){
	pos.x=_x;pos.y=_y;pos.z=_z;
}
UnsignedPos Building::get_pos()const{
	return pos;
}
unsigned Building::get_x()const{
	return pos.x;
}
unsigned Building::get_y()const{
	return pos.y;
}
unsigned Building::get_z()const{
	return pos.z;
}

