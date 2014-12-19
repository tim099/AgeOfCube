#ifndef ORDER_H_
#define ORDER_H_
#include <stack>
#include <cstdio>
#include "OrderDefine.h"
#include "CubeCreature.h"
#include "StateIdle.h"
#include "LoadAddress.h"
class OrderGoTo;
class Order {
public:
	Order(CubeCreature *creature);
	virtual ~Order();
	virtual int get_order()=0;
	virtual void Pause();//while new order being push in stack
	virtual unsigned idle_time()const;
	virtual OrderGoTo* o_go_to();

	bool END()const;
	void tic();
	void save(FILE *fop);
	void load(FILE *fop);
	State* cur_state()const;
	void push_state(State *state);
	void pop_state();
	virtual void load_finished(LoadAddress* LAD);
protected:
	virtual void save_order(FILE *fop);
	virtual void load_order(FILE *fop);
	virtual void timer_tic()=0;

	void clear_state();
	bool end;
	CubeCreature *creature;
	std::stack<State*>states;
};

#endif /* ORDER_H_ */
