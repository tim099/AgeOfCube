#ifndef ORDERIDLE_H_
#define ORDERIDLE_H_
#include "Order.h"
class OrderIdle : public Order{
public:
	OrderIdle(CubeCreature *creature);
	virtual ~OrderIdle();
	virtual int get_order();
	virtual void Pause();//while new order being push in stack
	virtual unsigned idle_time()const;
protected:
	virtual void save_order(FILE *fop);
	virtual void load_order(FILE *fop);
	virtual void timer_tic();
	unsigned idle_timer;
};

#endif /* ORDERIDLE_H_ */
