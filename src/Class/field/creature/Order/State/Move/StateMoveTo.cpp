#include "StateMoveTo.h"
#include "CubeCreature.h"
#include "map/Map.h"
StateMoveTo::StateMoveTo(CubeCreature *creature,Map *_map,double x,double y,double z) : StateMove(creature){
px=x;py=y;pz=z;
map=_map;
}
StateMoveTo::~StateMoveTo() {

}
int StateMoveTo::get_state(){
	return STATE_MOVE_TO;
}
void StateMoveTo::move_timer_tic(){
	double dx=px-creature->get_x();
	double dy=py-creature->get_y();
	double dz=pz-creature->get_z();

	creature->accelerate_by_a(dx,0,dz);
	if(map->get_path()->get_path(creature->in_x(),creature->in_y(),creature->in_z())&&M_LIFTABLE){
		creature->accelerate(0,(0.1*dy+0.001),0);
	}
}
void StateMoveTo::end_state(){
	end=true;
}
void StateMoveTo::move_to(double x,double y,double z){
	px=x;py=y;pz=z;

}
