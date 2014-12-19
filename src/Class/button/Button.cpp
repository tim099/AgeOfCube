#include <Button.h>

Button::Button() {
x=0,y=0,width=0.02,height=0.0025;
state=0;
pressed_timer=0;
_active=true;
_exist=true;
}
Button::~Button() {

}
void Button::set_active(bool active){
	_active=active;
}
bool Button::active()const{
	return _active;
}
int Button::type()const{
	return 0;
}
bool Button::exist()const{
	return _exist;
}
void Button::delete_but(){
	_exist=false;
}
void Button::set_state(int _state){
	if(pressed_timer>0)return;
	state=_state;
}
int Button::get_state(){
	return state;
}
void Button::tic(){
	if(state==2){
		pressed_timer++;
	}
}
void Button::pressed(){

}
