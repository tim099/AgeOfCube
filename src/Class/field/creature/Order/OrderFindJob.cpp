#include "OrderFindJob.h"
#include "CubeWorker.h"
#include "StaticCube.h"
#include "WorkableBuilding.h"

OrderFindJob::OrderFindJob(CubeWorker *_worker,Map *_map) : Order(_worker){
	map=_map;
	worker=_worker;
}
OrderFindJob::~OrderFindJob() {

}
int OrderFindJob::get_order(){
	return O_FIND_JOB;
}
void OrderFindJob::Pause(){

}
void OrderFindJob::search_job(){
	if(map->get_path()->time_out())return;
	std::vector<StaticCube*>find_v;
	WorkableBuilding *b;
	map->get_path()->search(worker->in_x(),worker->in_y(),worker->in_z(),new SearchJob(worker->belong_to()),find_v,1,20000);
	for(unsigned i=0;i<find_v.size();i++){
		if(true){//will only find one so...,if more than one then choose the best job
			b=find_v.at(i)->get_building()->workablebuilding();
			worker->set_work(b,b->work_type());
			break;
		}
	}
	end=true;//nomatter find or cant find
}
void OrderFindJob::timer_tic(){
	if(!end)search_job();
}
unsigned OrderFindJob::compute_work_value(Work* work){
	return 0;
}
