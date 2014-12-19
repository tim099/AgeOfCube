#ifndef ORDERFINDJOB_H_
#define ORDERFINDJOB_H_
#include "Order.h"
#include "map/map.h"
#include "WorkableBuilding.h"
#include "Work.h"
#include "SearchJob.h"

class CubeWorker;
class StaticCube;

class OrderFindJob : public Order{
public:
	OrderFindJob(CubeWorker *worker,Map *map);
	virtual ~OrderFindJob();
	virtual int get_order();
	virtual void Pause();//while new order being push in stack
protected:
	void search_job();
	unsigned compute_work_value(Work* work);
	virtual void timer_tic();
	Map *map;
	CubeWorker *worker;
};

#endif /* ORDERFINDJOB_H_ */
