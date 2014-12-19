#ifndef STATEIDLE_H_
#define STATEIDLE_H_
#include "State.h"
class StateIdle : public State{
public:
	StateIdle(CubeCreature *creature);
	virtual ~StateIdle();
	virtual int get_state();
protected:
	virtual void timer_tic();

};

#endif /* STATEIDLE_H_ */
