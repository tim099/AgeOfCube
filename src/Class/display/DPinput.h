#ifndef DPINPUT_H_
#define DPINPUT_H_
#include "List.h"
#include "Display.h"

class DPinput : public Display{
public:
	DPinput(List *list,ButtonList *SLB,Mouse *mou);
	virtual ~DPinput();
	virtual void display();
protected:
	virtual void prepare_list();
	List *list;
};

#endif /* DPINPUT_H_ */
