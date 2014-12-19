#include <BasicButGroup.h>
#include "ShowButGroupButton.h"
BasicButGroup::BasicButGroup(unsigned _but_per_page) {
	active=true;
	auto_pos=false;
	g_px=0.0,g_py=0.0,disy=0.0,disx=0.0;
	but_per_page=_but_per_page;
	cur_page_at=0;
	_end=false;
}
BasicButGroup::~BasicButGroup() {
//delete is handle by button list
}
void BasicButGroup::handle_signal(Signal sig){
	switch(sig.sig()){
		case S_NEXT_PAGE:
			break;
		case S_PREV_PAGE:
			break;
	}
}
bool BasicButGroup::END()const{
	return _end;
}
void BasicButGroup::clear_delete_but(){
	for(unsigned i=0;i<sort_buts.size();i++){
		if(!sort_buts.at(i)->exist()){
			remove_but(i);
		}
	}
	for(unsigned i=0;i<indie_buts.size();i++){
		if(!indie_buts.at(i)->exist()){
			indie_buts.at(i)=indie_buts.back();
		}
	}
	for(unsigned i=0;i<all_buts.size();i++){
		if(!all_buts.at(i)->exist()){
			all_buts.at(i)=all_buts.back();
		}
	}
}
void BasicButGroup::remove_but(unsigned i){
	if(sort_buts.size()<=i)return;
	for(;i<(sort_buts.size()-1);i++){
		sort_buts.at(i)=sort_buts.at(i+1);
	}
	sort_buts.pop_back();
}
void BasicButGroup::construct_cur_page(){
	cur_page.clear();
	for(unsigned i=cur_page_at*but_per_page;(i<sort_buts.size())&&(i<(cur_page_at+1)*but_per_page);i++){
		cur_page.push_back(sort_buts.at(i));
	}
}
void BasicButGroup::prev_page(){
	if(cur_page_at==0)return;
	cur_page_at--;
	construct_cur_page();
}
void BasicButGroup::next_page(){
	if(((cur_page_at+1)*but_per_page)>=sort_buts.size())return;
	cur_page_at++;
	construct_cur_page();
}
void BasicButGroup::dp_cur_page(){
	construct_cur_page();
	for(unsigned i=0;i<all_buts.size();i++){
		all_buts.at(i)->set_active(false);
	}
	if(!active)return;
	for(unsigned i=0;i<cur_page.size();i++){
		cur_page.at(i)->set_active(true);
	}
	for(unsigned i=0;i<indie_buts.size();i++){
		indie_buts.at(i)->set_active(true);
	}
}
void BasicButGroup::tic(){
	clear_delete_but();
	dp_cur_page();
	auto_position();

	timer_tic();
}
void BasicButGroup::auto_position(){
	if(!auto_pos)return;
	for(unsigned i=0;i<cur_page.size();i++){
		cur_page.at(i)->x=g_px+i*disx;
		cur_page.at(i)->y=g_py+i*disy;
	}
}
void BasicButGroup::set_auto_pos(double _g_px,double _g_py,double _disx,double _disy,unsigned _but_per_page){
	auto_pos=true;
	g_px=_g_px,g_py=_g_py,disy=_disy;disx=_disx;
	but_per_page=_but_per_page;
	construct_cur_page();
	auto_position();
}
void BasicButGroup::turn_off_auto_pos(){
	auto_pos=false;
}
void BasicButGroup::timer_tic(){

}
unsigned BasicButGroup::size(){
	return sort_buts.size();
}
void BasicButGroup::delete_group(){
	for(unsigned i=0;i<all_buts.size();i++){
		all_buts.at(i)->delete_but();
	}
	_end=true;
}
void BasicButGroup::push_button(BasicButton* but){
	but->set_active(active);
	sort_buts.push_back(but);
	all_buts.push_back(but);
}
void BasicButGroup::push_indie_button(BasicButton* but){
	but->set_active(active);
	indie_buts.push_back(but);
	all_buts.push_back(but);
}
void BasicButGroup::push_sub_group(BasicButGroup* group){
	sub_group.push_back(group);
}
bool BasicButGroup::get_state(){
	return active;
}
void BasicButGroup::set_state(bool _active){
	if(active==_active)return;
	active=_active;
	if(!active){
		for(unsigned i=0;i<sub_group.size();i++)sub_group.at(i)->set_state(false);
	}
	dp_cur_page();
}
