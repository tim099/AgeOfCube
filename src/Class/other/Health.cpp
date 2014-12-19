#include <Health.h>

Health::Health(int ini_health) {
	_health=ini_health;
}
Health::~Health() {

}
void Health::health_alter(int delta){
	set_health(_health+=delta);
}
void Health::set_health(int health){
	_health=health;
	if(_health>(int)max_health())_health=max_health();
	if(_health<0)health=0;
}
void Health::save_health(FILE *file){
	fprintf(file,"%d ",_health);
}
void Health::load_health(FILE *file){
	fscanf(file,"%d ",&_health);
}
