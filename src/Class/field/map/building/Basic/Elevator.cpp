#include "Elevator.h"

Elevator::Elevator(int x,int y,int z,Player *cur_player,int player) : Building(x,y,z,cur_player,player) {
	cube_type=C_ELEVATOR;
	plane_h=0;
	plane_up=true;
	_buildable=true;
	cb_on|=ON_LEFT;
	cb_on|=ON_RIGHT;
	cb_on|=ON_FRONT;
	cb_on|=ON_BACK;
	path|=M_UP;
	path|=M_STANDABLE;
	path|=M_LIFTABLE;
	//extra_path|=M_EX_NOT_LEFT;
	//extra_path|=M_EX_NOT_RIGHT;
	//extra_path|=M_EX_NOT_FRONT;
}
Elevator::~Elevator() {

}
std::string Elevator::name(){
	return std::string("Elevator");
}
unsigned Elevator::require_work()const{
	return 2000;
}
Resource Elevator::require_resources(){
	Resource res;
	res.set_res(R_CUBE,500);
	res.set_res(R_CORE,1);
	return res;
}
bool Elevator::selectable()const{
	return false;
}
std::vector<Building::But_type>& Elevator::Upgrade_button(std::vector<Building::But_type> &_Upgrade_but){
	_Upgrade_but.push_back(Building::But_type("None",Signal(S_NULL)));
	return _Upgrade_but;
}
std::vector<Building::But_type>& Elevator::Recruit_button(std::vector<Building::But_type> &_Recruit_but){
	_Recruit_but.push_back(Building::But_type("None",Signal(S_NULL)));
	return _Recruit_but;
}
std::vector<Building::But_type>& Elevator::Research_button(std::vector<Building::But_type> &_Research_but){
	_Research_but.push_back(Building::But_type("None",Signal(S_NULL)));
	return _Research_but;

}
std::vector<Building::But_type>& Elevator::Info_button(std::vector<Building::But_type> &_Info_but){

	return _Info_but;
}
void Elevator::dp_building(){
	glCallList(DP_ELEVATOR);
	glPushMatrix();
	glTranslatef(0,-0.05+0.1*plane_h,0);
	glCallList(DP_ELEVATOR_PLANE);
	glPopMatrix();
}
void Elevator::timer_tic(){
	if(plane_up){
		if(plane_h<0.95)plane_h+=0.01;
		else plane_up=false;
	}else{
		if(plane_h>0.0)plane_h-=0.01;
		else plane_up=true;
	}
}
