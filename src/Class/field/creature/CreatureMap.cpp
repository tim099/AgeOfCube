#include "CreatureMap.h"
#include "CubeCreature.h"
#include "map/Map.h"
CreatureMap::CreatureMap(std::queue<CubeCreature*>*_creatures,Map *_map) {
	creatures=_creatures;
	map=_map;
}
CreatureMap::~CreatureMap() {

}
std::vector<CubeCreature*>* CreatureMap::get_creature_map(int x,int y,int z){
	if(x<0||y<0||z<0)return (&no_creature);

	unsigned pos=map->get_path()->convert_pos(x,y,z);
	return get_creature_map(pos);
}
std::vector<CubeCreature*>* CreatureMap::get_creature_map(unsigned pos){
	std::map<unsigned,std::vector<CubeCreature*> >::iterator mc_it;
	mc_it=creatures_map.find(pos);
	if(mc_it!=creatures_map.end()){
		return &((*mc_it).second);
	}else return (&no_creature);//not find
}
void CreatureMap::push_creature_map(CubeCreature* creature){
	unsigned pos;
	std::map<unsigned,std::vector<CubeCreature*> >::iterator mc_it;
	pos=map->get_path()->convert_pos(creature->in_x(),creature->in_y(),creature->in_z());
	mc_it=creatures_map.find(pos);
	if(mc_it!=creatures_map.end()){//already exist
		(*mc_it).second.push_back(creature);
	}else{
		std::vector<CubeCreature*>buff_v;
		buff_v.push_back(creature);
		creatures_map.insert(std::pair<unsigned,std::vector<CubeCreature*> >(pos,buff_v));
	}
}
void CreatureMap::creat_creature_map(){
	//clock_t start_time=clock(),time_cost;
	unsigned size=creatures->size();

	creatures_map.clear();
	CubeCreature *creature;
	for(unsigned i=0;i<size;i++){
		creature=creatures->front();
		creatures->pop();
		creatures->push(creature);
		push_creature_map(creature);
	}
	//time_cost=clock()-start_time;
	//printf("time_cost=%lfsec\n",(double)time_cost/(double)(CLOCKS_PER_SEC));
}
void CreatureMap::tic(){
	creat_creature_map();
}


