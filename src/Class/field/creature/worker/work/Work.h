#ifndef WORK_H_
#define WORK_H_
#include <cstdio>
#include "WorkDefine.h"
#include "job/CreatJob.h"
#include "UnsignedPos.h"
#include "LoadAddress.h"

class Map;
class CubeWorker;
class WorkableBuilding;
class Work {
public:
	Work(WorkableBuilding *w_b,Map *map,CubeWorker *worker);
	virtual ~Work();
	virtual int work_type()const;
	virtual void load_finished(LoadAddress* LAD);

	void tic();

	void save_work(FILE *file);
	void load_work(FILE *file);

	bool work_rigistered()const;
	void work_rigister();
	bool End()const;

	UnsignedPos get_pos()const;

	WorkableBuilding* work_at()const;
	void set_job(Job *job);
	Job* cur_job()const;
protected:
	virtual void timer_tic();
	void job_timer_tic();

	void work_lost();
	void job_lost();

	void save_job(FILE *file);
	void load_job(FILE *file);
	void save_workbuilding(FILE *file);
	void load_workbuilding(FILE *file);

	bool _work_rigistered;
	Map *map;
	CubeWorker *worker;
	WorkableBuilding *w_building;
	Job *_cur_job;
	CreatJob *creat_job;
	bool _end;
};

#endif /* WORK_H_ */
