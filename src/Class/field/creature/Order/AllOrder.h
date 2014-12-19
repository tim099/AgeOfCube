#ifndef ALLORDER_H_
#define ALLORDER_H_

#include <cstdio>
#include <vector>
#include "CreatOrder.h"
#include "LoadAddress.h"
class Building;
class CubeCreature;
class Map;
class AllOrder {
public:
	AllOrder(CubeCreature* c_creature,Map *map,std::queue<Building*>*f_buildings);
	virtual ~AllOrder();

	void save_orders(FILE *fop);
	void load_orders(FILE *fop);

	void go_to(unsigned x,unsigned y,unsigned z);
	void find_job();

	Order* cur_order();
	void clean_order();

	unsigned idle_time()const;
	void tic();
	void load_finished(LoadAddress* LAD);
protected:
	void clear_all_orders();
	void push_order(Order* order);
	void pop_order();
	void execute_order();
	std::vector<Order*>order_stack;
	CreatOrder *COD;
	CubeCreature* c_creature;
	std::queue<Building*>*f_buildings;
	Map *map;
};

#endif /* ALLORDER_H_ */
