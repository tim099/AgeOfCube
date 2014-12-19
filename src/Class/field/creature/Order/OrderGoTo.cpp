#include "OrderGoTo.h"

OrderGoTo::OrderGoTo(unsigned x,unsigned y,unsigned z,Map *_map,CubeCreature *_creature
		,unsigned _max_time,unsigned _min_time) : Order(_creature){
	max_time=_max_time;
	min_time=_min_time;
	des.x=x;des.y=y;des.z=z;
	map=_map;

	state=S_NOT_START_FIND_YET;
	r=0;
	time_consume_per_move=0;
	total_time_used=0;
	move_state=0;
}
OrderGoTo::~OrderGoTo() {
	Pause();
	clear_route();
}
OrderGoTo* OrderGoTo::o_go_to(){
	return this;
}
UnsignedPos OrderGoTo::get_des()const{
	return des;
}
void OrderGoTo::Pause(){
	if(move_state!=0)move_state->end_state();
	move_state=0;
}
void OrderGoTo::save_order(FILE *fop){
	des.save(fop);
	fprintf(fop,"%u %u ",max_time,min_time);
}
void OrderGoTo::load_order(FILE *fop){
	des.load(fop);
	fscanf(fop,"%u %u ",&max_time,&min_time);
}
int OrderGoTo::get_order(){
	return O_GO_TO;
}
void OrderGoTo::find_path(){
	if(r!=0)clear_route();
	r=map->get_path()->push_find_route(creature->in_x(),creature->in_y(),creature->in_z()
			,des.x,des.y,des.z,max_time,min_time);
	state=S_FINDING_PATH;
}
void OrderGoTo::handle_cant_find_path(){
	r->end_route();
	end=true;//cant goto target!!
}
void OrderGoTo::wait_finding_path(){
	//Do something?
}
void OrderGoTo::go_to_target(){
	if(move_state==0){
		move_state=new StateMoveTo(creature,map,(0.1*(r->route.back().x)+0.05)
		,(0.1*(r->route.back().y)),(0.1*(r->route.back().z)+0.05));
	}
	if(r->route.empty()){//reach target
		state=S_REACH_DESTINATION;
		move_state->end_state();
		end=true;
	}
	if(!r->route.empty()){
		time_consume_per_move++;
		if(creature->cur_move_state()!=move_state){
			creature->switch_move_state(move_state);
		}
		move_state->move_to((0.1*(r->route.back().x)+0.05)
				,(0.1*(r->route.back().y)),(0.1*(r->route.back().z)+0.05));
		if(creature->in_x()==(int)r->route.back().x&&creature->in_y()==(int)r->route.back().y
				&&creature->in_z()==(int)r->route.back().z){
			r->route.pop_back();
			time_consume_per_move=0;
		}
	}
}
void OrderGoTo::clear_route(){
	if(r==0)return;
	r->end_route();
	r=0;
	time_consume_per_move=0;
	state=S_NOT_START_FIND_YET;
}
void OrderGoTo::check_route_state(){
	if(r==0){//no path
		state=S_NOT_START_FIND_YET;
		return;
	}
	if(time_consume_per_move>200){//
		clear_route();
		return;
	}
	//if(total_time_used>60000){
		//handle_cant_find_path();
		//return;
	//}
	switch(r->find()){
		case R_CANT_FIND:
			state=S_CANT_FIND_PATH;
			break;
		case R_NOT_YET_FIND:
			state=S_FINDING_PATH;
			break;
		case R_FIND:
			state=S_FIND_PATH;
			break;
	}
}
void OrderGoTo::execute_state(){
	switch(state){
		case S_NOT_START_FIND_YET:
			find_path();
			break;
		case S_CANT_FIND_PATH:
			handle_cant_find_path();
			break;
		case S_FINDING_PATH:
			wait_finding_path();
			break;
		case S_FIND_PATH:
			go_to_target();
			break;
		default:
			printf("unknow state!!\n");
	}
}
void OrderGoTo::timer_tic(){
	total_time_used++;
	check_route_state();
	execute_state();
	if(S_NOT_START_FIND_YET){
		find_path();
	}

}
