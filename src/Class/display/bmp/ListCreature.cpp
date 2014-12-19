#include "ListCreature.h"

ListCreature::ListCreature(double _size) {
	size=_size;
	creat_all_list();
}
ListCreature::~ListCreature() {

}
void ListCreature::creat_all_list(){
	creat_obj_list((char*)"files/obj/players/playersCreature/P0C.obj",DP_P0_CREATURE,0.02*size,0,0.0005,0);
	creat_obj_list((char*)"files/obj/players/playersCreature/P1C.obj",DP_P1_CREATURE,0.02*size,0,0.0005,0);
	creat_obj_list((char*)"files/obj/players/playersCreature/P2C.obj",DP_P2_CREATURE,0.02*size,0,0.0005,0);
	creat_obj_list((char*)"files/obj/creature/CubeWorker.obj",TEX_CUBEWORKER,0.01*size,0,0.01*size,0);
	//creat_cube_bysize("files/texture/creature/CubeWorker/CubeWorker.BMP",TEX_CUBEWORKER,0.01*size);
}
