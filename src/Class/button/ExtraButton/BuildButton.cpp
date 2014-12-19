#include <BuildButton.h>
#include "Player.h"
#include "Building.h"

BuildButton::BuildButton(int _building,bool _unfinished){
	building=_building;
	unfinished=_unfinished;
	//c_building=cur_player->CBL->building(building);
	//name.assign(c_building->name());
}
BuildButton::~BuildButton(){

}
void BuildButton::build(){

}
void BuildButton::pressed(){
	build();
}
