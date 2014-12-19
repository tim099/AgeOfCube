#include "OrderWork.h"
#include "CubeWorker.h"
OrderWork::OrderWork(CubeWorker *_worker) : Order(_worker){
	worker=_worker;
}
OrderWork::~OrderWork() {

}
int OrderWork::get_order(){
	return O_WORK;
}
void OrderWork::Pause(){

}
void OrderWork::detect_worker_state(){
	if(worker->cur_work()==0){//no job
		end = true;
	}else{
		//if(worker->stay_in_building()==worker->cur_job()->work_at()){//at working place

		//}
	}
}
void OrderWork::timer_tic(){
	detect_worker_state();
}
