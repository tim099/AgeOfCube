#include "StateIdle.h"

StateIdle::StateIdle(CubeCreature *creature) : State(creature){

}
StateIdle::~StateIdle() {

}
int StateIdle::get_state(){
	return STATE_IDLE;
}
void StateIdle::timer_tic(){

}
