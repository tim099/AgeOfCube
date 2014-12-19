#ifndef ESENTSIGNAL_H_
#define ESENTSIGNAL_H_
#include <vector>
#include "Signal.h"
#include "Execute.h"
class ButSignal;

class ESentSignal : public Execute{
public:
	ESentSignal(ButSignal *obj,Signal sig);
	virtual ~ESentSignal();
	virtual void execute();
protected:
	ButSignal *obj;
	Signal sig;

};

#endif /* ESENTSIGNAL_H_ */
