#ifndef STATE_H_
#define STATE_H_
#include "StateDefine.h"
class CubeCreature;
class State {
public:
	State(CubeCreature *creature);
	virtual ~State();
	virtual int get_state();
	int state_type();
	void tic();
	bool END()const;
protected:
	virtual void timer_tic();
	CubeCreature *creature;
	bool end;
};

#endif /* STATE_H_ */
