#include <ShowButGroupButton.h>
#include "BasicButList.h"
#include "BasicButGroup.h"
ShowButGroupButton::ShowButGroupButton(BasicButGroup *_but_group,BasicButList *_SLB,bool _uni_but_group
		,std::string name,double width,double height,int type):BasicButton(name,width,height,type){
	but_group=_but_group;
	SLB=_SLB;
	uni_but_group=_uni_but_group;
}
ShowButGroupButton::~ShowButGroupButton() {

}
ShowButGroupButton* ShowButGroupButton::ShowButGroupBut(){
	return this;
}
void ShowButGroupButton::set_active(bool active){
	_active=active;
	if(!active){
		//but_group->set_state(false);
	}
}
void ShowButGroupButton::pressed(){
	show_but_group();
}
void ShowButGroupButton::show_but_group(){
	if(uni_but_group)SLB->show_unique_but_group(but_group);
	else{
		if(but_group->get_state()){
			but_group->set_state(false);
		}else{
			but_group->set_state(true);
		}
	}
}
