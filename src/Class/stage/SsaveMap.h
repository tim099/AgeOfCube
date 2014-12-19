#ifndef SSAVEMAP_H_
#define SSAVEMAP_H_
#include "Sinput.h"
class SsaveMap : public Sinput{
public:
	SsaveMap();
	virtual ~SsaveMap();
protected:
	virtual void Stage_signal_process(Signal s);
	virtual void timer_tick();
};

#endif /* SLOADMAP_H_ */
