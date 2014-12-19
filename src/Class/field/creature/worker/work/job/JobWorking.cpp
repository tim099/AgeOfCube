#include <job/JobWorking.h>
#include "WorkableBuilding.h"
#include "CubeWorker.h"
#include "map/Map.h"

JobWorking::JobWorking(WorkableBuilding *_w_b,Map *_map,CubeWorker *_worker) {
	map=_map;
	state=JSW_NULL;
	w_b=_w_b;
	worker=_worker;
}
JobWorking::~JobWorking() {

}
int JobWorking::job_type()const{
	return JOB_WORKING;
}
void JobWorking::save_job(FILE *file){
	fprintf(file,"%x ",(unsigned)w_b);
	fprintf(file,"\n");
}
void JobWorking::load_finished(LoadAddress* LAD){
	w_b=LAD->get_building(w_b)->workablebuilding();
}
void JobWorking::load_job(FILE *file){
	fscanf(file,"%x ",(unsigned*)&w_b);
	fscanf(file,"\n");
}
void JobWorking::go_to_work(){
	worker->clean_order();
	worker->go_to(w_b->get_x(),w_b->get_y(),w_b->get_z());
	state=JSW_GOING_TO_WORK;
}
void JobWorking::going_to_work(){
	if(worker->in_building()==w_b){
		if(worker->get_in_building())state=JSW_WORKING;
	}
	Order *o=worker->cur_order();
	if(!(o->o_go_to()))state=JSW_GO_TO_WORK;//not going to work!!return to prev state
}
void JobWorking::working(){
	if(worker->stay_in_building()!=w_b){
		state=JSW_GO_TO_WORK;
	}
}
void JobWorking::handle_state(){
	if(!w_b){
		state=JSW_FIND_WORK_AT;
	}
	switch(state){
		case JSW_NULL:
			state=JSW_GO_TO_WORK;
			break;
		case JSW_GO_TO_WORK:
			go_to_work();
			break;
		case JSW_GOING_TO_WORK:
			going_to_work();
			break;
		case JSW_WORKING:
			working();
			break;
	}
}
void JobWorking::timer_tic(){
	handle_state();
}
