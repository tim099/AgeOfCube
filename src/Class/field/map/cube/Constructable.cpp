#include "Constructable.h"
#include "resources\Resource.h"
Constructable::Constructable() {
	_unfinished=true;
	_cur_work=0;
}
Constructable::~Constructable() {

}
void Constructable::save_constructable(FILE *file){
	fprintf(file,"%u ",_cur_work);
}
void Constructable::load_constructable(FILE *file){
	fscanf(file,"%u ",&_cur_work);
	detect_finished();
}
void Constructable::construct_now(){
	_cur_work=require_work();
	_unfinished=false;//finished!!
}
bool Constructable::unfinished()const{
	return _unfinished;
}
unsigned Constructable::cur_work()const{
	return _cur_work;
}
bool Constructable::detect_finished(){
	if(_cur_work>=require_work()){
		_unfinished=false;//finished!!
		return true;
	}
	_unfinished=true;
	return false;
}
bool Constructable::construct(unsigned work){
	_cur_work+=work;
	return detect_finished();
}
