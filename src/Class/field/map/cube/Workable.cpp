#include <Workable.h>
#include "CubeWorker.h"
#include "Constructable.h"
Workable::Workable() {

}
Workable::~Workable() {

}
void Workable::get_work(CubeWorker *worker){
	Constructable* constructing_obj=cur_constructing();
	if(constructing_obj){//if need work
		construct(worker->get_work());
	}
}
