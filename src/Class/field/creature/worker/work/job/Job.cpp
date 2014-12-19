#include "job/Job.h"

Job::Job() {
	_end=false;
}
Job::~Job() {

}
int Job::job_type()const{
	return JOB_NULL;
}
bool Job::END()const{
	return _end;
}
void Job::save(FILE *file){
	fprintf(file,"%d ",job_type());
	save_job(file);
}
void Job::load(FILE *file){
	load_job(file);
}
void Job::load_finished(LoadAddress* LAD){

}
void Job::save_job(FILE *file){
	fprintf(file,"\n");
}
void Job::load_job(FILE *file){
	fscanf(file,"\n");
}
void Job::tic(){
	timer_tic();
}
