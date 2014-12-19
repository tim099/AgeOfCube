#ifndef BUTSIGNAL_H_
#define BUTSIGNAL_H_
#include "Signal.h"
class ButSignal {
public:
	ButSignal();
	virtual ~ButSignal();
	virtual void handle_signal(Signal sig)=0;
protected:

};

#endif /* BUTSIGNAL_H_ */
