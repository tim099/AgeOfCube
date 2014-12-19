#include "SelectWorkableBuildingMode.h"

SelectWorkableBuildingMode::SelectWorkableBuildingMode(Mouse *mou,Map *map,BasicButList *SLB,Messagebox *MSB
		,Player *player,CreatCreature *CCT,WorkableBuilding *_workable_building)
: SelectBuildingMode(mou,map,SLB,MSB,player,CCT,_workable_building){

	workable_building=_workable_building;
}
SelectWorkableBuildingMode::~SelectWorkableBuildingMode() {

}
int SelectWorkableBuildingMode::get_mode()const{
	return SELECT_WORKABLE_BUILDING_MODE;
}
void SelectWorkableBuildingMode::timer_tic(){
	if(mou->get_but(0))end=true;
	if(mou->get_but(2)){
		workable_building->set_rally_point(mou->select_x,mou->select_y+1,mou->select_z);
	}
}
void SelectWorkableBuildingMode::dp_building_mode(){
	workable_building->dp_rally_point();
	glPushMatrix();//just test
	glLoadIdentity();
	glTranslatef(0.04,-0.01,-0.1);
	ListBar::dp_bar(workable_building->recruit_process()*100,100,0.0001,10.0,ListBar::color(0,1,0,0));
	glPopMatrix();
}
