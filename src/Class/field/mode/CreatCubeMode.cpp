#include "CreatCubeMode.h"

CreatCubeMode::CreatCubeMode(Mouse *_mou,Map *_map,int cube_type) {
	mou=_mou;
	map=_map;
	c_type=cube_type;
	drag=false;
	start_x=0;start_y=0;start_z=0;
}
CreatCubeMode::~CreatCubeMode() {

}
int CreatCubeMode::get_mode()const{
	return CREAT_CUBE_MODE;
}
void CreatCubeMode::dp_mode(){
	if(!drag)return;
	int cur_x=mou->select_x+mou->surface_x;
	int cur_z=mou->select_z+mou->surface_z;
	unsigned max_x=cur_x>start_x?cur_x:start_x;
	unsigned min_x=cur_x<start_x?cur_x:start_x;
	unsigned max_z=cur_z>start_z?cur_z:start_z;
	unsigned min_z=cur_z<start_z?cur_z:start_z;
	if(max_x>map->MSX())max_x=map->MSX();
	if(max_z>map->MSZ())max_z=map->MSZ();
	if(min_x<0)min_x=0;
	if(min_z<0)min_z=0;
	for(unsigned i=min_x;i<=max_x;i++){
		for(unsigned k=min_z;k<=max_z;k++){
			glPushMatrix();
			if(map->creatable(i,start_y,k))glEnable(GL_LIGHT6);
			else glEnable(GL_LIGHT5);
			glTranslatef(0.1*(i)+0.05,0.1*(start_y)+0.05,0.1*(k)+0.05);
			glPushMatrix();
			glTranslatef(0,0.0485,0);
			glCallList(TEXT_BASIC_CUBE_TOP+2*(c_type-C_BASIC));
			glPopMatrix();

			glPushMatrix();
			glTranslatef(0,-0.0485,0);
			glCallList(TEXT_BASIC_CUBE_TOP+2*(c_type-C_BASIC));
			glPopMatrix();

			glPushMatrix();
			glTranslatef(0.0485,0,0);
			glRotatef(90,0,1,0);
			glCallList(TEXT_BASIC_CUBE_SIDE+2*(c_type-C_BASIC));
			glPopMatrix();

			glPushMatrix();
			glTranslatef(-0.0485,0,0);
			glRotatef(90,0,1,0);
			glCallList(TEXT_BASIC_CUBE_SIDE+2*(c_type-C_BASIC));
			glPopMatrix();

			glPushMatrix();
			glTranslatef(0,0,0.0485);
			glCallList(TEXT_BASIC_CUBE_SIDE+2*(c_type-C_BASIC));
			glPopMatrix();

			glPushMatrix();
			glTranslatef(0,0,-0.0485);
			glCallList(TEXT_BASIC_CUBE_SIDE+2*(c_type-C_BASIC));
			glPopMatrix();

			glPopMatrix();

			glDisable(GL_LIGHT5);
			glDisable(GL_LIGHT6);
		}
	}
}
void CreatCubeMode::creat_cube(){
	int cur_x=mou->select_x+mou->surface_x;
	int cur_z=mou->select_z+mou->surface_z;
	unsigned max_x=cur_x>start_x?cur_x:start_x;
	unsigned min_x=cur_x<start_x?cur_x:start_x;
	unsigned max_z=cur_z>start_z?cur_z:start_z;
	unsigned min_z=cur_z<start_z?cur_z:start_z;
	if(max_x>map->MSX())max_x=map->MSX();
	if(max_z>map->MSZ())max_z=map->MSZ();
	if(min_x<0)min_x=0;
	if(min_z<0)min_z=0;
	for(unsigned i=min_x;i<=max_x;i++){
		for(unsigned k=min_z;k<=max_z;k++){
			map->creat_cube(i,start_y,k,c_type);
		}
	}
}
void CreatCubeMode::timer_tic(){
	if(mou->get_but(0)&&!drag){
		drag=true;
		start_x=mou->select_x+mou->surface_x;
		start_y=mou->select_y+mou->surface_y;
		start_z=mou->select_z+mou->surface_z;
	}
	if(!mou->button[0]&&drag){
		drag=false;
		creat_cube();
	}
	if(mou->get_but(2))end=true;
}
