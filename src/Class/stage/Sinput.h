#ifndef SINPUT_H_
#define SINPUT_H_

#include <string>
#include "Stage.h"
#include "List.h"
#include "DPinput.h"
#include "BasicButList.h"
class Sinput : public Stage{
public:
	Sinput();
	virtual ~Sinput();
protected:
	virtual void Stage_signal_process(Signal s);
	virtual void timer_tick();
	void get_input();
	List *list;
	std::string *input_str;
};

#endif /* SINPUT_H_ */
