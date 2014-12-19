#include <BasicButList.h>

BasicButList::BasicButList(Mouse *mou,double _size) : ButtonList(mou){
	size=_size;
	fonts= new ListFonts(0.0016*size);
	l_buts = new ListButton(0.02*size);
	basic_button_w=l_buts->Buttons.at(0).width;
	basic_button_h=l_buts->Buttons.at(0).height;
	short_button_w=l_buts->Buttons.at(1).width;
	short_button_h=l_buts->Buttons.at(1).height;
	medium_button_w=l_buts->Buttons.at(2).width;
	medium_button_h=l_buts->Buttons.at(2).height;
	_cur_uni_group=0;
}
BasicButList::~BasicButList() {
	delete fonts;
	delete l_buts;
	clear_all_but_group();
}
void BasicButList::clear_all_but_group(){
	for(unsigned i=0;i<all_but_group.size();i++){
		delete all_but_group.at(i);
	}
}
void BasicButList::timer_tic(){
	but_group_tic();
}
void BasicButList::but_group_tic(){
	for(unsigned i=0;i<unique_group.size();i++){
		if(unique_group.at(i)->END()){
			unique_group.at(i)=unique_group.back();
			unique_group.pop_back();
		}
	}
	for(unsigned i=0;i<all_but_group.size();i++){
		if(all_but_group.at(i)->END()){
			delete all_but_group.at(i);
			all_but_group.at(i)=all_but_group.back();
			all_but_group.pop_back();
		}
		if(i<all_but_group.size()){
			all_but_group.at(i)->tic();
		}
	}
}
void BasicButList::dp_all_buttons(){
	int _size=buts.size();
	Button *b;
	glEnable(GL_LIGHT2);
	glPushMatrix();
	glTranslatef(0,0,-0.1);
	for(int i=0;i<_size;i++){
		b=buts.front();
		buts.pop();
		buts.push(b);
		if(!b->active())continue;
		glPushMatrix();
		glTranslatef(b->x,b->y,0);
		fonts->call_string(b->name.c_str());
		glPushMatrix();
		glTranslatef(0,0,-0.000001);
		switch(b->get_state()){
			case 0:glCallList(l_buts->Buttons.at(b->type()).normal);break;
			case 1:glCallList(l_buts->Buttons.at(b->type()).selected);break;
			case 2:glCallList(l_buts->Buttons.at(b->type()).pressed);break;
		}
		glPopMatrix();
		glPopMatrix();
	}
	glPopMatrix();
	glDisable(GL_LIGHT2);
}
void BasicButList::clear_uni_group(){
	unique_group.clear();
}
BasicButGroup* BasicButList::push_but_group(BasicButGroup *group){
	all_but_group.push_back(group);
	return group;
}
BasicButGroup* BasicButList::push_unique_but_group(BasicButGroup *group){
	group->set_state(false);
	all_but_group.push_back(group);
	unique_group.push_back(group);
	return group;
}
void BasicButList::show_unique_but_group(BasicButGroup* group){
	for(unsigned i=0;i<unique_group.size();i++){
		if(group==unique_group.at(i)){//find!!
			_cur_uni_group=unique_group.at(i);
			_cur_uni_group->set_state(true);
		}else{
			unique_group.at(i)->set_state(false);
		}
	}
}
BasicButGroup* BasicButList::cur_uni_group(){
	return _cur_uni_group;
}
unsigned BasicButList::uni_group_size()const{
	return unique_group.size();
}
BuildButton* BasicButList::creat_build_button(int building_type,bool unfinished,double x,double y){
	BuildButton *buff=new BuildButton(building_type,unfinished);
	buff->x=x;
	buff->y=y;

	buts.push(buff);
	return buff;
}
ShowButGroupButton* BasicButList::creat_ShowButGroup_button
(std::string name,Signal signal,BasicButGroup* group,bool uni_but_group,int type,double x,double y){
	double width,height;
	switch(type){
		case BASCI_BUTTON:
			width=basic_button_w,height=basic_button_h;
			break;
		case SHORT_BUTTON:
			width=short_button_w,height=short_button_h;
			break;
		case MEDIUM_BUTTON:
			width=medium_button_w,height=medium_button_h;
			break;
	}
	ShowButGroupButton *buff= new ShowButGroupButton(group,this,uni_but_group,name,width,height,type);
	buff->signal=signal;
	buff->x=x;
	buff->y=y;
	buts.push(buff);
	return buff;
}
ExecuteButton* BasicButList::creat_SignalButton(ButSignal *_obj,std::string name,Signal signal,int type,double x,double y){
	double width,height;
	switch(type){
		case BASCI_BUTTON:
			width=basic_button_w,height=basic_button_h;
			break;
		case SHORT_BUTTON:
			width=short_button_w,height=short_button_h;
			break;
		case MEDIUM_BUTTON:
			width=medium_button_w,height=medium_button_h;
			break;
	}
	ExecuteButton *buff;
	buff= new ExecuteButton(name,width,height,type);
	buff->push_execute(new ESentSignal(_obj,signal));
	buff->x=x;
	buff->y=y;
	buts.push(buff);
	return buff;
}
BasicButton* BasicButList::creat_basic_button(std::string name,Signal signal,double x,double y){
	BasicButton *buff;
	buff= new BasicButton(name,basic_button_w,basic_button_h,BASCI_BUTTON);
	buff->signal=signal;
	buff->x=x;
	buff->y=y;
	buts.push(buff);
	return buff;
}
BasicButton* BasicButList::creat_short_button(std::string name,Signal signal,double x,double y){
	BasicButton *buff;
	buff= new BasicButton(name,short_button_w,short_button_h,SHORT_BUTTON);
	buff->signal=signal;
	buff->x=x;
	buff->y=y;
	buts.push(buff);
	return buff;
}
BasicButton* BasicButList::creat_medium_button(std::string name,Signal signal,double x,double y){
	BasicButton *buff;
	buff= new BasicButton(name,medium_button_w,medium_button_h,MEDIUM_BUTTON);
	buff->signal=signal;
	buff->x=x;
	buff->y=y;
	buts.push(buff);
	return buff;
}
