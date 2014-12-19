#ifndef JOBWORKING_H_
#define JOBWORKING_H_
#include "Job.h"
#include "UnsignedPos.h"
#include "OrderGoTo.h"
const int JSW_NULL=0;
const int JSW_FIND_WORK_AT=1;
const int JSW_GO_TO_WORK=2;
const int JSW_GOING_TO_WORK=3;
const int JSW_WORKING=4;
class Map;
class WorkableBuilding;
class CubeWorker;
class JobWorking : public Job{
public:
	JobWorking(WorkableBuilding *w_b,Map *map,CubeWorker *worker);
	virtual ~JobWorking();
	virtual int job_type()const;
	virtual void load_finished(LoadAddress* LAD);
protected:
	virtual void save_job(FILE *file);
	virtual void load_job(FILE *file);
	virtual void  timer_tic();
	void handle_state();
	void go_to_work();
	void going_to_work();
	void working();

	//UnsignedPos work_at;
	WorkableBuilding *w_b;
	Map *map;
	CubeWorker *worker;
	int state;
};
#endif /* JOBWORKING_H_ */
