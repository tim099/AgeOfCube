#ifndef SIGNALBUTTON_H_
#define SIGNALBUTTON_H_

#include "BasicButton.h"
class ButSignal;
class SignalButton : public BasicButton{
public:
	SignalButton(int test,ButSignal *obj,Signal s,std::string name,double width=0.02,double height=0.0025,int type=0);
	virtual ~SignalButton();

	virtual void pressed();
protected:
	Signal sig;
	ButSignal *obj;
};

#endif /* SIGNALBUTTON_H_ */
