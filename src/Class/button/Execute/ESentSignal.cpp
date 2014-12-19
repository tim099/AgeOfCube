#include <ESentSignal.h>
#include "ButSignal.h"
ESentSignal::ESentSignal(ButSignal *_obj,Signal _sig) {
	obj=_obj;
	sig=_sig;
}
ESentSignal::~ESentSignal() {

}
void ESentSignal::execute(){
	obj->handle_signal(sig);
}

