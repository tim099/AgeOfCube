#include <BuildingMode.h>

BuildingMode::BuildingMode(ConstructBuildings *_CBL,Mouse *_mou,Player *_cur_player,int _building,bool _unfinished) {
	CBL=_CBL;
	mou=_mou;
	cur_player=_cur_player;
	building=_CBL->build(mou->select_x,mou->select_y,mou->select_z,_building,_cur_player->which_player());
	b_type=_building;
	unfinished=_unfinished;
}
BuildingMode::~BuildingMode() {
	delete building;
}
int BuildingMode::get_mode()const{
	return BUILDING_MODE;
}
void BuildingMode::dp_mode(){
	unsigned s_x=(mou->select_x+mou->surface_x),s_y=(mou->select_y+mou->surface_y),s_z=(mou->select_z+mou->surface_z);
	if(s_x>cur_player->map->MSX()||s_x<0||s_y>cur_player->map->MSY()||s_y<0
			||s_z>cur_player->map->MSZ()||s_z<0)return;
	glPushMatrix();
	glTranslatef(0.1*s_x+0.05,0.1*s_y+0.05,0.1*s_z+0.05);
	if(cur_player->buildable(mou->select_x+mou->surface_x,mou->select_y+mou->surface_y,
			mou->select_z+mou->surface_z,b_type))glEnable(GL_LIGHT6);
	else glEnable(GL_LIGHT5);
	building->dp_players_building();
	glDisable(GL_LIGHT5);
	glDisable(GL_LIGHT6);
	glPopMatrix();


}
void BuildingMode::build(){
	cur_player->build(mou->select_x+mou->surface_x,mou->select_y+mou->surface_y,
			mou->select_z+mou->surface_z,b_type,unfinished);
}
void BuildingMode::timer_tic(){
	if(mou->get_but(0))build();
	if(mou->get_but(2))end=true;
}
