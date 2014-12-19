#ifndef CREATORDER_H_
#define CREATORDER_H_
#include "OrderIdle.h"
#include "OrderGoTo.h"
#include "OrderFindJob.h"
#include "OrderWork.h"
class CubeCreature;
class Map;
class Building;
class CreatOrder {
public:
	CreatOrder(CubeCreature* c_creature,Map *map,std::queue<Building*>*f_buildings);
	virtual ~CreatOrder();
	Order *creat_order(int type);
protected:
	CubeCreature* c_creature;
	Map *map;
	std::queue<Building*>*f_buildings;
};

#endif /* CREATORDER_H_ */
