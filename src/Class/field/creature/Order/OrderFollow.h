#ifndef ORDERFOLLOW_H_
#define ORDERFOLLOW_H_
#include "Order.h"
class OrderFollow : public Order{
public:
	OrderFollow();
	virtual ~OrderFollow();
	virtual int get_order()=0;
	virtual void Pause();//while new order being push in stack
private:

};

#endif /* ORDERFOLLOW_H_ */
