#include "Order.h"

Order::Order(CubeCreature *_creature) {
end=false;
creature=_creature;
push_state(new StateIdle(creature));
}
Order::~Order() {
	clear_state();
}
OrderGoTo* Order::o_go_to(){
	return 0;
}
unsigned Order::idle_time()const{
	return 0;
}
void Order::Pause(){

}
void Order::load_finished(LoadAddress* LAD){

}
void Order::save(FILE *fop){
	fprintf(fop,"%d ",get_order());//save order type
	save_order(fop);
}
void Order::load(FILE *fop){
	load_order(fop);
}
void Order::save_order(FILE *fop){

}
void Order::load_order(FILE *fop){

}
State* Order::cur_state()const{
	return states.top();
}
void Order::push_state(State *state){
	states.push(state);
}
void Order::pop_state(){
	if(states.empty())return;
	delete states.top();
	states.pop();
}
void Order::tic(){
	if(cur_state()->END())pop_state();
	cur_state()->tic();
	timer_tic();
}
void Order::clear_state(){
	while(!states.empty()){
		delete states.top();
		states.pop();
	}
}
bool Order::END()const{
	return end;
}
