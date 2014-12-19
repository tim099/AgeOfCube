#ifndef SLOADMAP_H_
#define SLOADMAP_H_
#include "Stage.h"
#include "List.h"
#include "DPinput.h"
#include "BasicButList.h"
#include "BasicButGroup.h"
#include "ListTank.h"
#include <dirent.h>
#include <vector>
class SloadMap : public Stage{
public:
	SloadMap();
	virtual ~SloadMap();
protected:
	List *list;
	std::string *select_but;
	virtual void Stage_signal_process(Signal s);
	virtual void timer_tick();
	BasicButGroup *but_group;
};

#endif /* SLOADMAP_H_ */
