#include "SelectBuildingMode.h"

SelectBuildingMode::SelectBuildingMode(Mouse *_mou,Map *_map,BasicButList *_SLB,Messagebox *_MSB
		,Player *_player,CreatCreature *_CCT,Building* _s_building) {
	mou=_mou;
	map=_map;
	SLB=_SLB;
	CCT=_CCT;
	MSB=_MSB;
	player=_player;
	creature=0;
	s_building=_s_building;
	s_building->select();
	list = new List(0.001,1,0,-0.017,1.0);
	BBG=SLB->push_but_group(new BasicButGroup());

	but_groups.push_back(BBG);//!!!!

	disy=0.003;
	posx=-0.026;
	posy=-0.0075;
	creat_button();
	//MSB->push_message(new Message(std::string("test"),500,7,10));
}
SelectBuildingMode::~SelectBuildingMode() {
	s_building->deselect();

	delete list;
	if(creature!=0)delete creature;
	while(!but_groups.empty()){
		but_groups.back()->delete_group();
		but_groups.pop_back();
	}
}
int SelectBuildingMode::get_mode()const{
	return SELECT_BUILDING_MODE;
}
void SelectBuildingMode::creat_button(){
	double disx=0.019;


	BBG->push_indie_button(SLB->creat_short_button("Back",Signal(T_MODE_SIGNAL,MODE_SIG_BACK),posx+3.7*disx,posy-5.5*disy));
	BBG->push_indie_button(SLB->creat_short_button("Prev",Signal(T_MODE_SIGNAL,DP_GROUP_PREV),posx-0.3*disx,posy-5.3*disy));
	BBG->push_indie_button(SLB->creat_short_button("Next",Signal(T_MODE_SIGNAL,DP_GROUP_NEXT),posx+0.1*disx,posy-5.3*disy));

	s_building->creat_button(SLB,&but_groups);//test
	BBG->set_auto_pos(posx-disx,posy,0,-disy,10);
}
void SelectBuildingMode::dp_building_mode(){

}
void SelectBuildingMode::dp_mode(){
	list->dp_list();
	dp_building_mode();
}
void SelectBuildingMode::dp_building_resources(){
	list->clear();
	list->push_resources(s_building->resource());
}
void SelectBuildingMode::dp_recruit_info(int type){
	list->clear();
	double posx=0.015,posy=0.01;
	if(creature!=0)delete creature;
	creature=CCT->creat_creature(type,0,0,0,0);
	list->push_temp_str(std::string("require resources"),posx,posy);
	list->push_temp_str(std::string(creature->name()),posx+0.0017,posy-0.0166);
	list->push_resources(creature->require_resources());
}
void  SelectBuildingMode::creat_creature(){
	if(creature!=0){
		if(!s_building->recruit_creature(creature->typ())){//no resource
			MSB->push_message(new Message(std::string("no enough resource"),200,15,20));
		}
	}
}
void SelectBuildingMode::handle_mode_signal(Signal sig){
	switch(sig.sig()){
		case T_MODE_SIGNAL:
			handle_signal(sig);
			break;
		case S_DP_RECRUIT_INFO:
			dp_recruit_info(sig.extra_sig());
			break;
		case S_MODE_RECRUIT:
			creat_creature();
			break;
		case S_MODE_DP:
			handle_DP_signal(sig);
			break;
		default:
			printf("unknow sig to mode%d\n",sig.sig());
	}
}
void SelectBuildingMode::handle_DP_signal(Signal sig){
	switch(sig.extra_sig()){
		case DP_BUILDING_RESOURCE:
			dp_building_resources();
			break;
	}
}
void SelectBuildingMode::handle_signal(Signal sig){
	switch(sig.extra_sig()){
		case DP_GROUP_RECRUIT:
			list->clear();
			break;
		case  DP_GROUP_UPGRADE:
			list->clear();
			break;
		case DP_GROUP_BUILDING_INFO:
			list->clear();
			break;
		case DP_GROUP_RESEARCH:
			list->clear();
			break;
		case DP_GROUP_PREV:
			if(SLB->cur_uni_group())SLB->cur_uni_group()->prev_page();
			break;
		case DP_GROUP_NEXT:
			if(SLB->cur_uni_group())SLB->cur_uni_group()->next_page();
			break;
		default:
			printf("cant handle sig %d by select building mode\n",sig.sig());
	}
}
void SelectBuildingMode::timer_tic(){
	if(mou->get_but(0))end=true;
	if(mou->get_but(2))end=true;
}
