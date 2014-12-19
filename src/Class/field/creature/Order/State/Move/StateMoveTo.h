#ifndef STATEMOVETO_H_
#define STATEMOVETO_H_
#include "StateMove.h"

class Map;
class StateMoveTo : public StateMove{
public:
	StateMoveTo(CubeCreature *creature,Map *map,double x,double y,double z);
	virtual ~StateMoveTo();
	virtual int get_state();
	void move_to(double x,double y,double z);
	void end_state();
protected:
	virtual void move_timer_tic();
	Map *map;
	double px,py,pz;
};

#endif /* STATEMOVETO_H_ */
