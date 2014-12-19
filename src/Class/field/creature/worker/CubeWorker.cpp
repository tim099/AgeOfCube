#include "CubeWorker.h"
#include "WorkerCore.h"
#include "map/Map.h"
#include "AllOrder.h"
CubeWorker::CubeWorker(double _pos_x,double _pos_y,double _pos_z,int _player,Map *map
,std::vector<Collidable*>*_colli_v,std::vector<CubeCreature*>*_f_units,std::queue<Building*>*_f_buildings)
: CubeCreature(_pos_x,_pos_y,_pos_z,_player,map,_colli_v,_f_units,_f_buildings){
	cube_type=C_CUBE_WORKER;
	size=0.7;
	core = new WorkerCore(this);
	work_at=0;
	CJB=new CreatWork(map,this);
}
CubeWorker::~CubeWorker() {
	if(work_at!=0)delete work_at;
	delete CJB;
	delete core;
}
void CubeWorker::creature_load_finished(LoadAddress* LAD){
	if(work_at)work_at->load_finished(LAD);
}
unsigned CubeWorker::max_health()const{
	return 200;
}
std::string CubeWorker::name(){
	return std::string("CubeWorker");
}
void CubeWorker::creat_building_buts(BasicButGroup *Build,BasicButList *SLB){
	Build->push_button(SLB->creat_medium_button("Base",Signal(S_BUILD_UNFINISHED,C_BASE)));
	Build->push_button(SLB->creat_medium_button("Elevator",Signal(S_BUILD_UNFINISHED,C_ELEVATOR)));
	Build->push_button(SLB->creat_medium_button("OneWay",Signal(S_BUILD_UNFINISHED,C_ONE_WAY)));
}
WorkableBuilding* CubeWorker::work_in_building(){
	if(cur_work()!=0&&cur_work()->work_at()
			&&stay_in_building()->workablebuilding()==cur_work()->work_at()){
		return stay_in_building()->workablebuilding();
	}
	return 0;
}
void CubeWorker::save_work(FILE *file){
	if(work_at!=0)work_at->save_work(file);
	else fprintf(file,"%d ",WORK_NULL);
}
void CubeWorker::load_work(FILE *file){
	int job;
	fscanf(file,"%d ",&job);
	if(job!=0){
		work_at=CJB->creat_work(0,job);
		work_at->load_work(file);
	}
}
void CubeWorker::save_creature(FILE *file){
	save_work(file);
	save_worker(file);
}
void CubeWorker::load_creature(FILE *file){
	load_work(file);
	load_worker(file);
}
void CubeWorker::save_worker(FILE *file){
	fprintf(file,"\n");
}
void CubeWorker::load_worker(FILE *file){
	fscanf(file,"\n");
}
unsigned CubeWorker::get_work(){
	//comsume energy!!
	return work_per_tic();
}
unsigned CubeWorker::work_per_tic()const{
	return 1;
}
void CubeWorker::timer_tic(){
	if(cur_work()!=0){
		cur_work()->tic();
		if(cur_work()->End())work_lost();
	}
	worker_timer_tic();
}
void CubeWorker::worker_timer_tic(){

}
CubeWorker* CubeWorker::worker(){
	return this;
}
void CubeWorker::find_job(){
	orders->find_job();
}
Work *CubeWorker::cur_work()const{
	return work_at;
}
double CubeWorker::max_v()const{
	return 0.01;
}
double CubeWorker::max_a()const{
	return 0.003;
}
unsigned CubeWorker::max_energy()const{
	return 1000;
}
void CubeWorker::work_lost(){
	if(work_at)delete work_at;
	work_at=0;
}
void CubeWorker::set_work(WorkableBuilding* w_b,int type){
	if(work_at)delete work_at;
	work_at=CJB->creat_work(w_b,type);
	work_at->work_rigister();
}
unsigned CubeWorker::require_work()const{
	return 500;
}
Resource CubeWorker::require_resources(){
	Resource res;
	res.set_res(R_CUBE,10);
	res.set_res(R_CORE,1);
	return res;
}
void CubeWorker::dp_creature(){
	glCallList(TEX_CUBEWORKER);
}
