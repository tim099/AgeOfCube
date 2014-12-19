#include "Sinput.h"

Sinput::Sinput() {
list=new List();
SLB=new BasicButList(&mou);
cur_dp=new DPinput(list,SLB,&mou);//delete by stage
input_str=0;

}
Sinput::~Sinput() {
delete list;
delete SLB;
}
void Sinput::Stage_signal_process(Signal s){
	switch(s.sig()){
		default:
			printf("unknown signal to input stage %d\n",s.sig());
	}
}
void Sinput::get_input(){
	for(char i='A';i<'z';i++){
		if(k_b.get(i)&&input_str->size()<20)input_str->push_back(i);
	}
	for(char i='0';i<='9';i++){
		if(k_b.get(i)&&input_str->size()<20)input_str->push_back(i);
	}
	if(k_b.get(8)){
		if(input_str->size()>0)input_str->resize(input_str->size()-1);
	}
}
void Sinput::timer_tick(){
	get_input();
}
