#include <FcreatMap.h>

FcreatMap::FcreatMap(Mouse *_mou,Keyboard *_k_b,BasicButList *_SLB,Messagebox *_MSB)
: Field( _mou,_k_b,_SLB,_MSB){
	creat_building_button();
	dp_height=30;
}
FcreatMap::~FcreatMap() {

}
void FcreatMap::generate_map(){
	map->creat_map_flat(250,10,250,C_BASIC,0,10,0);
	map->creat_map_flat(250,10,250,C_DARK,0,0,0);
	srand(time(NULL));
	map->generate_map(rand());
}
void FcreatMap::timer_tick(){

}
void FcreatMap::creat_building_button(){

}
