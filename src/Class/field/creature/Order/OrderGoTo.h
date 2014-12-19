#ifndef ORDERGOTO_H_
#define ORDERGOTO_H_
#include "Order.h"
#include "map/Map.h"
#include "StateMoveTo.h"
#include "UnsignedPos.h"
const int S_CANT_FIND_PATH=-1;
const int S_NOT_START_FIND_YET=0;
const int S_FINDING_PATH=1;
const int S_FIND_PATH=2;
const int S_REACH_DESTINATION=3;
class CubeCreature;
class OrderGoTo : public Order{
public:
	OrderGoTo(unsigned x,unsigned y,unsigned z,Map *map,CubeCreature *creature
			,unsigned max_time=10000,unsigned min_time=5000);
	virtual void Pause();//while new order being push in stack
	virtual ~OrderGoTo();
	virtual int get_order();
	virtual OrderGoTo* o_go_to();

	UnsignedPos get_des()const;
protected:
	virtual void save_order(FILE *fop);
	virtual void load_order(FILE *fop);
	virtual void timer_tic();
	void find_path();
	void handle_cant_find_path();
	void check_route_state();
	void wait_finding_path();
	void execute_state();
	void clear_route();
	void go_to_target();
	unsigned max_time,min_time;
	UnsignedPos des;
	int state;
	unsigned time_consume_per_move,total_time_used;
	Map *map;
	Route *r;
	StateMoveTo *move_state;
};

#endif /* ORDERGOTO_H_ */
