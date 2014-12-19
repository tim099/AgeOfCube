#include "SsaveMap.h"

SsaveMap::SsaveMap() {
	input_str=new std::string("Map01");//delete by list
	list->push_str(input_str,0,0);//->call_string();
	list->push_str(std::string("Enter Map Name"),0,0.006);
	SLB->creat_short_button("Save",Signal(S_SAVE_MAP),-0.01,-0.006);
	SLB->creat_short_button("Back",Signal(S_BACK),0.01,-0.006);
}
SsaveMap::~SsaveMap() {
	//delete input_str;
}
void SsaveMap::Stage_signal_process(Signal s){
	char file[100]="files/maps/";
	switch(s.sig()){
		case S_SAVE_MAP:
			for(unsigned i=0;i<input_str->size();i++){
				file[i+11]=input_str->at(i);
			}
			file[input_str->size()+11]='\0';
			sent_signal(Signal(S_SAVE_MAP_NAME,std::string(file)));
			end=true;
			break;
		default:
			printf("unknown signal to savemap stage %d\n",s.sig());
	}
}
void SsaveMap::timer_tick(){
	get_input();
}
