#ifndef SMENU_H_
#define SMENU_H_
#include "Stage.h"
#include "DPstart.h"
#include "SButtonList.h"
class Smenu : public Stage{
public:
	Smenu();
	virtual ~Smenu();

protected:
	virtual void Stage_signal_process(Signal s);
	virtual void timer_tick();

};

#endif
