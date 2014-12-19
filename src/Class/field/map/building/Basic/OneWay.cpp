#include <OneWay.h>
#include "BasicButList.h"
OneWay::OneWay(int x,int y,int z,Player *cur_player,Map *_map,int player) : Building(x,y,z,cur_player,player){
	cube_type=C_ONE_WAY;
	_buildable=true;
	map=_map;
	way=W_NULL;
}
OneWay::~OneWay() {

}
void OneWay::save_building(FILE *file){
	fprintf(file,"%u",(unsigned)way);
	fprintf(file,"\n");
}
void OneWay::load_building(FILE *file){
	fscanf(file,"%u ",(unsigned*)&way);

	fscanf(file,"\n");
}
std::string OneWay::name(){
	return std::string("OneWay");
}
unsigned OneWay::require_work()const{
	return 2000;
}
Resource OneWay::require_resources(){
	Resource res;
	res.set_res(R_CUBE,500);
	res.set_res(R_CORE,1);
	return res;
}
unsigned char OneWay::get_extra_path()const{
	unsigned char extra_path=0;
	if(way&W_LEFT_NOUT)extra_path|=M_EX_NOT_LEFT;
	else extra_path&=(~M_EX_NOT_LEFT);
	if(way&W_RIGHT_NOUT)extra_path|=M_EX_NOT_RIGHT;
	else extra_path&=(~M_EX_NOT_RIGHT);
	if(way&W_FRONT_NOUT)extra_path|=M_EX_NOT_FRONT;
	else extra_path&=(~M_EX_NOT_FRONT);
	if(way&W_BACK_NOUT)extra_path|=M_EX_NOT_BACK;
	else extra_path&=(~M_EX_NOT_BACK);
	return extra_path;
}
unsigned char OneWay::get_path()const{
	int _path=path;
	if(way&W_LEFT_WALL)_path&=(~M_LEFT);
	else _path|=M_LEFT;
	if(way&W_RIGHT_WALL)_path&=(~M_RIGHT);
	else _path|=M_RIGHT;
	if(way&W_FRONT_WALL)_path&=(~M_FRONT);
	else _path|=M_FRONT;
	if(way&W_BACK_WALL)_path&=(~M_BACK);
	else _path|=M_BACK;
	return _path;
}
void OneWay::dp_building(){
	glCallList(DP_ONE_WAY);
	glPushMatrix();
	if(way&W_FRONT_WALL){
		glCallList(DP_ONE_WAY_WALL);
	}
	if(way&W_BACK_WALL){
		glPushMatrix();
		glRotatef(180,0,1,0);
		glCallList(DP_ONE_WAY_WALL);
		glPopMatrix();
	}
	if(way&W_LEFT_WALL){
		glPushMatrix();
		glRotatef(270,0,1,0);
		glCallList(DP_ONE_WAY_WALL);
		glPopMatrix();
	}
	if(way&W_RIGHT_WALL){
		glPushMatrix();
		glRotatef(90,0,1,0);
		glCallList(DP_ONE_WAY_WALL);
		glPopMatrix();
	}
	if(way&W_FRONT_NOUT){
		glCallList(DP_ONE_WAY_NOUT);
	}
	if(way&W_BACK_NOUT){
		glPushMatrix();
		glRotatef(180,0,1,0);
		glCallList(DP_ONE_WAY_NOUT);
		glPopMatrix();
	}
	if(way&W_LEFT_NOUT){
		glPushMatrix();
		glRotatef(270,0,1,0);
		glCallList(DP_ONE_WAY_NOUT);
		glPopMatrix();
	}
	if(way&W_RIGHT_NOUT){
		glPushMatrix();
		glRotatef(90,0,1,0);
		glCallList(DP_ONE_WAY_NOUT);
		glPopMatrix();
	}
	glPopMatrix();
}
void OneWay::timer_tic(){

}
void OneWay::creat_button(BasicButList *SLB,std::vector<BasicButGroup*>*but_groups){
	creat_alter_but(SLB,but_groups);
}
void OneWay::handle_signal(Signal sig){
	switch(sig.sig()){
		case ONEWAY_FRONT_WALL:
			if(way&W_FRONT_WALL){
				way&=(~W_FRONT_WALL);
			}else way|=W_FRONT_WALL;
			map->update_cube(get_x(),get_y(),get_z());
			break;
		case ONEWAY_BACK_WALL:
			if(way&W_BACK_WALL){
				way&=(~W_BACK_WALL);
			}else way|=W_BACK_WALL;
			map->update_cube(get_x(),get_y(),get_z());
			break;
		case ONEWAY_LEFT_WALL:
			if(way&W_LEFT_WALL){
				way&=(~W_LEFT_WALL);
			}else way|=W_LEFT_WALL;
			map->update_cube(get_x(),get_y(),get_z());
			break;
		case ONEWAY_RIGHT_WALL:
			if(way&W_RIGHT_WALL){
				way&=(~W_RIGHT_WALL);
			}else way|=W_RIGHT_WALL;
			map->update_cube(get_x(),get_y(),get_z());
			break;
		case ONEWAY_FRONT_NOUT:
			if(way&W_FRONT_NOUT){
				way&=(~W_FRONT_NOUT);
			}else way|=W_FRONT_NOUT;
			map->update_cube(get_x(),get_y(),get_z());
			break;
		case ONEWAY_BACK_NOUT:
			if(way&W_BACK_NOUT){
				way&=(~W_BACK_NOUT);
			}else way|=W_BACK_NOUT;
			map->update_cube(get_x(),get_y(),get_z());
			break;
		case ONEWAY_LEFT_NOUT:
			if(way&W_LEFT_NOUT){
				way&=(~W_LEFT_NOUT);
			}else way|=W_LEFT_NOUT;
			map->update_cube(get_x(),get_y(),get_z());
			break;
		case ONEWAY_RIGHT_NOUT:
			if(way&W_RIGHT_NOUT){
				way&=(~W_RIGHT_NOUT);
			}else way|=W_RIGHT_NOUT;
			map->update_cube(get_x(),get_y(),get_z());
			break;
	}
}
void OneWay::creat_alter_but(BasicButList *SLB,std::vector<BasicButGroup*>*but_groups){
	BasicButGroup *Gate=SLB->push_unique_but_group(new BasicButGroup());
	but_groups->push_back(Gate);
	but_groups->at(0)->push_button(SLB->creat_ShowButGroup_button("Gate",Signal(S_NULL),Gate,true,2));

	Gate->push_button(SLB->creat_SignalButton(this,std::string("Front"),Signal(ONEWAY_FRONT_WALL),MEDIUM_BUTTON));
	Gate->push_button(SLB->creat_SignalButton(this,std::string("Back"),Signal(ONEWAY_BACK_WALL),MEDIUM_BUTTON));
	Gate->push_button(SLB->creat_SignalButton(this,std::string("Left"),Signal(ONEWAY_LEFT_WALL),MEDIUM_BUTTON));
	Gate->push_button(SLB->creat_SignalButton(this,std::string("Right"),Signal(ONEWAY_RIGHT_WALL),MEDIUM_BUTTON));


	std::vector<Building::But_type>buff;
	creat_button_group(SLB,buff,Gate);

	BasicButGroup *NotOut=SLB->push_unique_but_group(new BasicButGroup());
	but_groups->at(0)->push_button(SLB->creat_ShowButGroup_button("OneWay",Signal(S_NULL),NotOut,true,2));
	but_groups->push_back(NotOut);
	NotOut->push_button(SLB->creat_SignalButton(this,std::string("Front"),Signal(ONEWAY_FRONT_NOUT),MEDIUM_BUTTON));
	NotOut->push_button(SLB->creat_SignalButton(this,std::string("Back"),Signal(ONEWAY_BACK_NOUT),MEDIUM_BUTTON));
	NotOut->push_button(SLB->creat_SignalButton(this,std::string("Left"),Signal(ONEWAY_LEFT_NOUT),MEDIUM_BUTTON));
	NotOut->push_button(SLB->creat_SignalButton(this,std::string("Right"),Signal(ONEWAY_RIGHT_NOUT),MEDIUM_BUTTON));
	creat_button_group(SLB,buff,NotOut);
}
std::vector<Building::But_type>& OneWay::Upgrade_button(std::vector<Building::But_type> &_Upgrade_but){
	return _Upgrade_but;
}
std::vector<Building::But_type>& OneWay::Recruit_button(std::vector<Building::But_type> &_Recruit_but){
	return _Recruit_but;
}
std::vector<Building::But_type>& OneWay::Research_button(std::vector<Building::But_type> &_Research_but){
	return _Research_but;
}
std::vector<Building::But_type>& OneWay::Info_button(std::vector<Building::But_type> &_Info_but){
	return _Info_but;
}
