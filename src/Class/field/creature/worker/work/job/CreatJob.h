#ifndef CREATJOB_H_
#define CREATJOB_H_
#include "Job.h"
#include "JobWorking.h"
#include <cstdio>
class Map;
class CubeWorker;
class CreatJob {
public:
	CreatJob(Map *map,CubeWorker *worker);
	virtual ~CreatJob();
	Job* creat_job(int job_type);
protected:
	Map *map;
	CubeWorker *worker;
};

#endif /* CREATJOB_H_ */
