#include "OrderIdle.h"

OrderIdle::OrderIdle(CubeCreature *creature) : Order (creature){
	idle_timer=0;
}
OrderIdle::~OrderIdle() {

}
void OrderIdle::Pause(){
	idle_timer=0;
}
unsigned OrderIdle::idle_time()const{
	return idle_timer;
}
void OrderIdle::save_order(FILE *fop){
	fprintf(fop,"%u ",idle_timer);
}
void OrderIdle::load_order(FILE *fop){
	fscanf(fop,"%u ",&idle_timer);
}
int OrderIdle::get_order(){
	return O_IDLE;
}
void OrderIdle::timer_tic(){
	if(idle_timer<10000000)idle_timer++;
	else idle_timer=0;
	//printf("idle time=%u\n",idle_timer);
}
