#include "State.h"
#include "CubeCreature.h"
State::State(CubeCreature *_creature) {
creature=_creature;
end=false;
}
State::~State() {

}
int State::get_state(){
	return STATE_STATE;
}
int State::state_type(){
	return get_state()-(get_state()%100);
}
bool State::END()const{
	return end;
}
void State::tic(){
	timer_tic();
}
void State::timer_tic(){

}
