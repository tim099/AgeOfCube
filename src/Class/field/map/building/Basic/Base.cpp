#include "Base.h"
#include "Player.h"
Base::Base(int x,int y,int z,Player *cur_player,int player)
:WorkableBuilding(x,y,z,cur_player,player){
cube_type=C_BASE;
resources->push_res(R_CUBE,100);
resources->push_res(R_CORE,10);
}
Base::~Base() {

}
std::string Base::name(){
	return std::string("Base");
}
unsigned Base::building_produce_work(){
	return 1;
}
unsigned Base::require_work()const{
	return 5000;
}
Resource Base::require_resources(){
	Resource res;
	res.set_res(R_CUBE,2000);
	res.set_res(R_CORE,100);
	return res;
}
unsigned Base::max_worker_num()const{
	return 5;
}
bool Base::have_job()const{
	if(workers.size()<max_worker_num()&&cur_constructing())return true;
	else return false;
}
void Base::work_timer_tic(){
	if(!res_link())merge_res(&(cur_player->player_res));
	DP_core.tic();
}
std::vector<Building::But_type>& Base::Upgrade_button(std::vector<Building::But_type> &_Upgrade_but){
	_Upgrade_but.push_back(Building::But_type("BigBase",Signal(S_NULL)));
	return _Upgrade_but;
}
std::vector<Building::But_type>& Base::Recruit_button(std::vector<Building::But_type> &_Recruit_but){
	_Recruit_but.push_back(Building::But_type("CubeWorker",Signal(S_DP_RECRUIT_INFO,C_CUBE_WORKER)));
	return _Recruit_but;
}
std::vector<Building::But_type>& Base::Research_button(std::vector<Building::But_type> &_Research_but){
	_Research_but.push_back(Building::But_type("DarkCube",Signal(S_NULL)));
	return _Research_but;
}
std::vector<Building::But_type>& Base::Info_button(std::vector<Building::But_type> &_Info_but){
	return _Info_but;
}
void Base::dp_building(){
	glCallList(DP_BASE);
	glPushMatrix();
	glTranslatef(0,DP_core.h,0);
	glRotatef(DP_core.ry,0,1,0);
	glCallList(DP_BASE_CORE);
	glPopMatrix();
}
