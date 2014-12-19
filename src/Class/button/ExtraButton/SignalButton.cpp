#include <SignalButton.h>
#include "ButSignal.h"
SignalButton::SignalButton(int test,ButSignal *_obj,Signal s,std::string name,double width,double height,int type)
: BasicButton(name,width,height,type){
	sig=s;
	obj=_obj;
}
SignalButton::~SignalButton() {

}
void SignalButton::pressed(){
	obj->handle_signal(sig);
}
