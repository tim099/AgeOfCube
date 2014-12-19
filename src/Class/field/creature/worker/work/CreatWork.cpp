#include "CreatWork.h"

CreatWork::CreatWork(Map *_map,CubeWorker *_worker) {
	map=_map;
	worker=_worker;
}
CreatWork::~CreatWork() {

}
Work *CreatWork::creat_work(WorkableBuilding* w_b,int job_type){
	Work *job=0;
	switch(job_type){
		case WORK_NORMAL:
			job=new Work(w_b,map,worker);
			break;
		default:
			printf("unknow job %d\n",job_type);
	}
	return job;
}
