#include "AllOrder.h"

#include "map/Map.h"
#include "CubeCreature.h"
AllOrder::AllOrder(CubeCreature* _c_creature,Map *_map,std::queue<Building*>*_f_buildings) {
c_creature=_c_creature;
map=_map;
f_buildings=_f_buildings;
order_stack.push_back(new OrderIdle(c_creature));
COD=new CreatOrder(c_creature,map,f_buildings);
}
AllOrder::~AllOrder() {
	clear_all_orders();
	delete COD;
}
void AllOrder::save_orders(FILE *fop){
	fprintf(fop,"%u ",order_stack.size());//some orders are unsaveable!!
	for(unsigned i=0;i<order_stack.size();i++){
		order_stack.at(i)->save(fop);
	}
}
void AllOrder::load_orders(FILE *fop){
	clear_all_orders();
	unsigned size;
	int type;
	Order *buff;
	fscanf(fop,"%u ",&size);
	for(unsigned i=0;i<size;i++){
		fscanf(fop,"%d ",&type);
		buff=COD->creat_order(type);
		if(buff){
			buff->load(fop);
			order_stack.push_back(buff);
		}
	}
}
void AllOrder::load_finished(LoadAddress* LAD){
	for(unsigned i=0;i<order_stack.size();i++)order_stack.at(i)->load_finished(LAD);
}
void AllOrder::go_to(unsigned x,unsigned y,unsigned z){
	push_order(new OrderGoTo(x,y,z,map,c_creature));
}
void AllOrder::find_job(){
	CubeWorker *c_worker=c_creature->worker();
	if(c_worker)push_order(new OrderFindJob(c_worker,map));
}
Order* AllOrder::cur_order(){
	if(order_stack.empty())return 0;
	return order_stack.back();
}
void AllOrder::clean_order(){
	while(order_stack.size()>1){
		pop_order();
	}
}
void AllOrder::push_order(Order* order){
	order_stack.back()->Pause();
	order_stack.push_back(order);
}
void AllOrder::pop_order(){
	if(order_stack.back()->get_order()==O_IDLE)return;
	delete order_stack.back();
	order_stack.pop_back();
}
void AllOrder::clear_all_orders(){
	while(!order_stack.empty()){
		delete order_stack.back();
		order_stack.pop_back();
	}
}
void AllOrder::tic(){
	execute_order();
	if(order_stack.back()->END())pop_order();
}
unsigned AllOrder::idle_time()const{
	return order_stack.back()->idle_time();
}
void AllOrder::execute_order(){
	if(order_stack.empty())return;
	order_stack.back()->tic();
}
