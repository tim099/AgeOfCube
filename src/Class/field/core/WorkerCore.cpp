#include "WorkerCore.h"
#include "CubeWorker.h"

WorkerCore::WorkerCore(CubeWorker *_worker,unsigned IQ) : Core(IQ){
	worker=_worker;
	creature=worker;
}
WorkerCore::~WorkerCore() {

}
void WorkerCore::handle_idle(){
	if(worker->cur_work()==0){
		worker->find_job();
	}
}
void WorkerCore::timer_tic(){
	if(creature->idle_time()>500){
		handle_idle();
	}
}
