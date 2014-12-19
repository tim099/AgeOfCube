#include <LoadAddress.h>

LoadAddress::LoadAddress() {

}
LoadAddress::~LoadAddress() {

}
void LoadAddress::push_building_address(Building* address,Building* building){
	b_address.insert(std::pair<Building*,Building*>(address,building));
}
Building* LoadAddress::get_building(Building* address){
	std::map<Building*,Building*>::iterator mc_it;
	mc_it=b_address.find(address);
	if(mc_it!=b_address.end()){
		return (*mc_it).second;
	}else return 0;
}
void LoadAddress::push_creature_address(CubeCreature* address,CubeCreature* creature){
	c_address.insert(std::pair<CubeCreature*,CubeCreature*>(address,creature));
}
CubeCreature* LoadAddress::get_creature(CubeCreature* address){
	std::map<CubeCreature*,CubeCreature*>::iterator mc_it;
	mc_it=c_address.find(address);
	if(mc_it!=c_address.end()){
		return (*mc_it).second;
	}else return 0;
}
