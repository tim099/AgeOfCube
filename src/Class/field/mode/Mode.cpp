#include "Mode.h"

Mode::Mode() {
end=false;
}
Mode::~Mode() {

}
void Mode::display_alter(Display* display){

}
int Mode::get_mode()const{
	return MODE_BASIC;
}
void Mode::dp_mode(){

}
void Mode::tic(){
	while(!signal_q.empty()){
		handle_signal(signal_q.front());
		signal_q.pop();
	}
	timer_tic();
}
void Mode::timer_tic(){

}
void Mode::sent_signal(Signal sig){
	signal_q.push(sig);
}
void Mode::handle_signal(Signal sig){
	switch(sig.typ()){
		case T_MODE_SIGNAL:
			if(sig.extra_sig()==MODE_SIG_BACK)end=true;
			else	handle_mode_signal(sig);
			break;
		default:
			printf("cant handle this sig %d by mode\n",sig.sig());
	}
}
void Mode::handle_mode_signal(Signal sig){
	printf("cant handle mode signal by original mode\n");
}
bool Mode::END(){
	return end;
}
