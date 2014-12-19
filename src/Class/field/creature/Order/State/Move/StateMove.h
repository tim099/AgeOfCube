#ifndef STATEMOVE_H_
#define STATEMOVE_H_
#include "State.h"

const int MS_NOT_MOVING=0;
const int MS_AVOID_COLLISION=1;
const int MS_NORMAL=2;

class Collidable;
class StateMove : public State{
public:
	StateMove(CubeCreature *creature);
	virtual ~StateMove();
	virtual int get_state();
	int get_move_state()const;
	virtual void avoid_collision(Collidable *cube);

protected:
	void timer_tic();
	virtual void move_timer_tic();
	int move_state;

};

#endif /* STATEMOVE_H_ */
