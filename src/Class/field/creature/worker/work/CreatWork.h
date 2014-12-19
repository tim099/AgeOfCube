#ifndef CREATWORK_H_
#define CREATWORK_H_
#include "Work.h"
class WorkableBuilding;
class Map;
class CubeWorker;
class CreatWork {
public:
	CreatWork(Map *map,CubeWorker *worker);
	virtual ~CreatWork();
	Work *creat_work(WorkableBuilding* w_b,int job_type);
protected:
	Map *map;
	CubeWorker *worker;
};

#endif /* CREATWORK_H_ */
