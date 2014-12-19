#ifndef ORDERWORK_H_
#define ORDERWORK_H_
#include "Order.h"
class CubeWorker;

class OrderWork : public Order{
public:
	OrderWork(CubeWorker *worker);
	virtual ~OrderWork();
	virtual int get_order();
	virtual void Pause();//while new order being push in stack
protected:
	virtual void timer_tic();
	void detect_worker_state();
	CubeWorker *worker;
};

#endif /* ORDERWORK_H_ */
