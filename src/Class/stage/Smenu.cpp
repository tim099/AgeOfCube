#include "Smenu.h"

Smenu::Smenu() {
	SLB=new SButtonList(&mou);
	cur_dp = new DPstart(SLB,&mou);
}
Smenu::~Smenu() {
	delete SLB;
}
void Smenu::Stage_signal_process(Signal s){
	switch(s.sig()){
		default:
			printf("unknown signal to menu stage %d\n",s.sig());
	}
}
void Smenu::timer_tick(){
	view_control();
}


