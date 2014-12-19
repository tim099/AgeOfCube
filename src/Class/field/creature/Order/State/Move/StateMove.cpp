#include "StateMove.h"
#include "Collidable.h"
#include "CubeCreature.h"
StateMove::StateMove(CubeCreature *creature) : State (creature){
move_state=MS_NOT_MOVING;

}
StateMove::~StateMove() {

}
int StateMove::get_state(){
	return STATE_MOVE;
}
int StateMove::get_move_state()const{
	return move_state;
}
void StateMove::avoid_collision(Collidable *cube){
	if(move_state==MS_AVOID_COLLISION)return;
	move_state=MS_AVOID_COLLISION;
	double vx=cube->get_vx(),vy=cube->get_vy(),vz=cube->get_vz();
	double vec_x=-0.1,vec_y=1.0,vec_z=0.1;
	double acx=vy*vec_z-vz*vec_y;
	double dx=cube->get_x()-creature->get_x(),dz=cube->get_z()-creature->get_z();
	//double acy=vz*vec_x-vx*vec_z;
	double acz=vx*vec_y-vy*vec_x;

	if((dx*acx+dz*acz)>=0)creature->accelerate_by_a(-acx,0,-acz);
	else creature->accelerate_by_a(acx,0,acz);
}
void StateMove::timer_tic(){
	if(move_state==MS_AVOID_COLLISION){
		move_state=MS_NORMAL;
	}else move_timer_tic();//control accelerate of creature
}
void StateMove::move_timer_tic(){

}
