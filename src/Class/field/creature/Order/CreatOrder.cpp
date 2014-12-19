#include "CreatOrder.h"
#include "map/MAP.h"
#include "CubeCreature.h"
CreatOrder::CreatOrder(CubeCreature* _c_creature,Map *_map,std::queue<Building*>*_f_buildings) {
	c_creature=_c_creature;
	map=_map;
	f_buildings=_f_buildings;
}
CreatOrder::~CreatOrder() {

}
Order *CreatOrder::creat_order(int type){
	Order *order=0;
	switch(type){
		case O_IDLE:
			order=new OrderIdle(c_creature);
			break;
		case O_GO_TO:
			order=new OrderGoTo(0,0,0,map,c_creature);
			break;
		case O_FIND_JOB:
			if(c_creature->worker())order=new OrderFindJob(c_creature->worker(),map);
			break;
		case O_WORK:
			if(c_creature->worker())order=new OrderWork(c_creature->worker());
			break;
		default:
			printf("unknow type %d order to creat\n",type);
	}
	return order;
}
