#include "DeletableCube.h"

DeletableCube::DeletableCube() {
	_exist=true;
	_terminate=false;
	terminate_timer=0;
}
DeletableCube::~DeletableCube() {

}
void DeletableCube::terminate_timer_tic(){
	if(_exist)return;
	if(terminate_timer>0)terminate_timer--;
	else _terminate=true;
}
void DeletableCube::delete_cube(int timer){
	_exist=false;
	terminate_timer=timer;
}
bool DeletableCube::exist()const{
	return _exist;
}
bool DeletableCube::terminate()const{
	return _terminate;
}
