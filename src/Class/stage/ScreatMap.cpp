#include "ScreatMap.h"

ScreatMap::ScreatMap() {
	SLB = new CreatMapButList(&mou,0.6);
	dp_map = new DPcreatMap(SLB,0,&mou);

	MSB = dp_map->MSB;
	cur_dp = dp_map;

	field = new FcreatMap(&mou,&k_b,SLB,MSB);
	dp_map->set_field(field);
	field->generate_map();
	//printf("size of field =%d\n",sizeof(field));
}
ScreatMap::~ScreatMap() {
	//std::cout<<"dtor_creat_Stage"<<std::endl;
	delete SLB;
	delete field;
}
Display* ScreatMap::cur_dis(){
	return dp_map;//cur_dp
}
void ScreatMap::timer_tick(){
	field->tic();
	view_control();
}
void ScreatMap::save_field(std::string file_name){
	field->save_field(file_name.c_str());
}
void ScreatMap::load_field(std::string file_name){
	delete field;
	field = new FcreatMap(&mou,&k_b,SLB,MSB);
	field->load_field(file_name.c_str());
	dp_map->set_field(field);
}
void ScreatMap::signal_under_stage(Signal s){
	switch(s.layer()){
		case FIELD_SIGNAL:
			field->sent_signal(s);
			break;
		default:
		printf("cant sent this signal %d by creatmap stage",s.sig());
	}
}
void ScreatMap::Stage_signal_process(Signal s){
	switch(s.sig()){
		case S_SAVE_MAP:
			save_field(s.str());
			break;
		case S_LOAD_MAP:
			load_field(s.str());
			break;
		default:
			printf("unknown signal to menu stage %d\n",s.sig());
	}
}

