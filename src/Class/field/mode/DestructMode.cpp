#include "DestructMode.h"

DestructMode::DestructMode(Mouse *_mou,Map *_map) {
mou=_mou;
map=_map;
}
DestructMode::~DestructMode() {

}
int DestructMode::get_mode()const{
	return DESTRUCTED_MODE;
}
void DestructMode::dp_mode(){

}
void DestructMode::timer_tic(){
	if(mou->get_but(0))map->delete_cube(mou->select_x,mou->select_y,mou->select_z);
	if(mou->get_but(2))end=true;
}
