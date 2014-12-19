#include <job/CreatJob.h>

CreatJob::CreatJob(Map *_map,CubeWorker *_worker) {
	map=_map;
	worker=_worker;
}
CreatJob::~CreatJob() {

}
Job* CreatJob::creat_job(int job_type){
	Job* job=0;
	switch(job_type){
		case JOB_NULL:
			break;
		case JOB_WORKING:
			job=new JobWorking(0,map,worker);
			break;
		default:
		printf("unknow type of job\n");
	}

	return job;
}
