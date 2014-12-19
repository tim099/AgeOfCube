#include "StaticCube.h"

StaticCube::StaticCube(int type) {
	cube_type=type;
	discovered=0;
	_exist=true;
	_buildable=false;
	path=0;
}
StaticCube::~StaticCube() {

}
Building* StaticCube::get_building(){
	return 0;
}
unsigned char StaticCube::get_extra_path()const{
	return 0;
}
unsigned char StaticCube::get_path()const{
	return path;
}
bool StaticCube::buildable()const{
	return _buildable;
}
void StaticCube::save_cube(FILE *file){
	fprintf(file,"%d ",discovered);
	save_static_cube(file);
}
void StaticCube::load_cube(FILE *file){
	fscanf(file,"%d ",&discovered);
	load_static_cube(file);
}
void StaticCube::save_static_cube(FILE *file){
	fprintf(file,"\n");
}
void StaticCube::load_static_cube(FILE *file){
	fscanf(file,"\n");
}
void StaticCube::discover(int player){
	discovered|=player;
	return;
}
bool StaticCube::see(int player){
	if(discovered&player)return true;
	else return false;
}
