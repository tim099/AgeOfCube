#include <Work.h>
#include "map/Map.h"
#include "CubeWorker.h"
#include "WorkableBuilding.h"
Work::Work(WorkableBuilding *w_b,Map *_map,CubeWorker *_worker) {
	map=_map;
	worker=_worker;
	_work_rigistered=false;
	_end=false;
	w_building=w_b;
	_cur_job=0;
	creat_job=new CreatJob(map,worker);
}
Work::~Work() {
	delete creat_job;
	job_lost();
}
void Work::load_finished(LoadAddress* LAD){
	w_building=LAD->get_building(w_building)->workablebuilding();
	if(w_building){
		_work_rigistered=true;
		if(_cur_job)_cur_job->load_finished(LAD);
	}
	else _end = true;
}
UnsignedPos Work::get_pos()const{
	return w_building->get_pos();
}
WorkableBuilding* Work::work_at()const{
	return w_building;
}
bool Work::End()const{
	return _end;
}
int Work::work_type()const{
	return WORK_NORMAL;
}
void Work::save_workbuilding(FILE *file){
	fprintf(file,"%x ",(unsigned)w_building);
}
void Work::load_workbuilding(FILE *file){
	fscanf(file,"%x ",(unsigned*)&w_building);
}
void Work::save_work(FILE *file){
	fprintf(file,"%d ",work_type());
	save_workbuilding(file);
	save_job(file);
}
void Work::load_work(FILE *file){
	load_workbuilding(file);
	load_job(file);
}
void Work::save_job(FILE *file){
	if(_cur_job!=0){//have job
		_cur_job->save(file);
	}else{
		fprintf(file,"%d ",JOB_NULL);
	}
}
void Work::load_job(FILE *file){
	int job_type;
	fscanf(file,"%d ",&job_type);
	_cur_job=creat_job->creat_job(job_type);
	if(_cur_job)_cur_job->load(file);
}
void Work::tic(){
	if(!work_rigistered())work_rigister();
	if(w_building!=0){
		if(!w_building->exist())work_lost();
	}
	job_timer_tic();
	timer_tic();
}
Job* Work::cur_job()const{
	return _cur_job;
}
void Work::job_lost(){
	if(_cur_job)delete _cur_job;
	_cur_job=0;
}
void Work::job_timer_tic(){
	if(!cur_job())return;
	cur_job()->tic();
	if(cur_job()->END())job_lost();
}
void Work::set_job(Job *job){
	if(_cur_job)delete _cur_job;
	_cur_job=job;
}
void Work::timer_tic(){

}
bool Work::work_rigistered()const{
	return _work_rigistered;
}
void Work::work_lost(){
	_end=true;
}
void Work::work_rigister(){
	if(w_building){
		if(w_building->worker_rigister(worker)){
			_work_rigistered=true;
			return;
		}else _end=true;
	}
}
