#include "Signal.h"

Signal::Signal(int _signal,std::string _s){
set_signal(_signal);
s=_s;
}
Signal::Signal(int _signal,int _extra){//auto signal type
set_signal(_signal);
extra=_extra;
}
Signal::Signal(){
set_signal(S_NULL);
}
Signal::~Signal() {

}
std::string Signal::str(){
	return (s);
}
int Signal::extra_sig(){
	return extra;
}
void Signal::set_signal(int _signal){
signal=_signal;
}
int Signal::sig(){
	return signal;
}
int Signal::typ(){
	return (signal-(signal%100));
}
int Signal::layer(){
	return (signal-(signal%1000));
}


