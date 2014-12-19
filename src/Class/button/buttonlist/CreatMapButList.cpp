#include <CreatMapButList.h>
#include <iostream>
CreatMapButList::CreatMapButList(Mouse *mou,double size) : BasicButList(mou,size){
	options=push_but_group(new BasicButGroup());
	Buildings=push_but_group(new BasicButGroup());
	Basics=push_but_group(new BasicButGroup());
	Cubes=push_but_group(new BasicButGroup());
	creat_all_buttons();
}
CreatMapButList::~CreatMapButList() {
//handle by buttons list
}
void CreatMapButList::creat_all_buttons(){
	double disy=0.005*size,disx=0.021*size;
	double posx=-0.043,posy=0.02;

	creat_ShowButGroup_button("Option",Signal(S_NULL),options,false,2,posx,posy+1*disy);
	options->push_button(creat_medium_button("Save Map",Signal(S_PREPARE_SAVE_MAP)));
	options->push_button(creat_medium_button("Load Map",Signal(S_PREPARE_LOAD_MAP)));
	options->push_button(creat_medium_button("Back",Signal(S_BACK)));
	options->set_auto_pos(posx,posy,0,-disy,5);
	options->set_state(false);

	creat_ShowButGroup_button("Building",Signal(S_NULL),Buildings,false,2,posx+1*disx,posy+1*disy);
	Buildings->push_indie_button(creat_medium_button("Destruct",Signal(S_DESTRUCT),posx+1*disx,posy+0*disy));
	Buildings->push_button(creat_ShowButGroup_button("Cubes",Signal(S_NULL),Cubes,false,2));
	Buildings->push_button(creat_ShowButGroup_button("Basic",Signal(S_NULL),Basics,false,2));

	Buildings->push_sub_group(Basics);
	Buildings->push_sub_group(Cubes);
	Buildings->set_auto_pos(posx+2*disx,posy+1*disy,disx,0,10);
	Buildings->set_state(false);

	Basics->push_button(creat_medium_button("Base",Signal(S_BUILD,C_BASE)));
	Basics->push_button(creat_medium_button("Elevator",Signal(S_BUILD,C_ELEVATOR)));
	Basics->push_button(creat_medium_button("OneWay",Signal(S_BUILD,C_ONE_WAY)));
	Basics->set_auto_pos(posx+3*disx,posy,0,-disy,5);
	Basics->set_state(false);

	Cubes->push_button(creat_medium_button("CubeBasic",Signal(S_CREAT_CUBE,C_BASIC)));
	Cubes->push_button(creat_medium_button("CubeDark",Signal(S_CREAT_CUBE,C_DARK)));
	Cubes->push_button(creat_medium_button("RedCore",Signal(S_CREAT_CUBE,C_RED_CORE)));
	Cubes->push_button(creat_medium_button("WBrick",Signal(S_CREAT_CUBE,C_WHITE_BRICK)));
	Cubes->set_auto_pos(posx+2*disx,posy,0,-disy,5);
	Cubes->set_state(false);
}
void CreatMapButList::handle_button_group_signal(Signal s){
	switch(s.extra_sig()){
		case DP_GROUP_MENU:
			if(options->get_state())options->set_state(false);
			else options->set_state(true);
			break;
		case DP_GROUP_BUILDING:
			if(Buildings->get_state()){
				Buildings->set_state(false);
				Basics->set_state(false);
				Cubes->set_state(false);
			}else Buildings->set_state(true);
			break;
		case DP_GROUP_BASIC:
			if(Basics->get_state())Basics->set_state(false);
			else Basics->set_state(true);
			break;
		case DP_GROUP_CUBE:
			if(Cubes->get_state())Cubes->set_state(false);
			else Cubes->set_state(true);
			break;
		default:
			printf("unknow signal %d to CreatMapButList\n",s.sig());
	}
}
