#include <SButtonList.h>

SButtonList::SButtonList(Mouse *mou,double size) : BasicButList(mou,size){
	creat_all_buttons();
}
SButtonList::~SButtonList() {

}
void SButtonList::creat_all_buttons(){
	double dis=0.007;
	but_group=push_but_group(new BasicButGroup());
	but_group->push_button(creat_basic_button("Start",Signal(S_START),0,0));
	but_group->push_button(creat_basic_button("Creat Map",Signal(S_CREAT_MAP),0,0));
	but_group->push_button(creat_basic_button("Load",Signal(S_LOAD_GAME),0,0));
	but_group->push_button(creat_basic_button("Option",Signal(S_OPTION),0,0));
	but_group->set_auto_pos(0,1.1*dis,0,-dis,10);
}
