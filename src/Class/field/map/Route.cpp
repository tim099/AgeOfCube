#include "map/Route.h"

Route::Route() {
	_find=R_NOT_YET_FIND;
	_exist=true;
}
Route::~Route() {

}
signed char Route::find()const{
	return _find;
}
void Route::set_find(){
	_find=R_FIND;
}
void Route::set_not_find(){
	_find=R_CANT_FIND;
}
void Route::end_route(){
	if(_find==R_NOT_YET_FIND)_find=R_STOP_FIND;//not find yet so stop finding
	else delete_route();//find so delete!!
}
void Route::delete_route(){
	_exist=false;
}
bool Route::exits()const{
	return _exist;
}
