#ifndef COLLISIONEFFECT_H_
#define COLLISIONEFFECT_H_
#include <cmath>
#include "Effect.h"
class Collidable;
class CollisionEffect : public Effect{
public:
	CollisionEffect(Collidable *colli_obj);
	virtual ~CollisionEffect();
	virtual int Effect_type();
	virtual void collision(Collidable* obj);
protected:
	Collidable *colli_obj;
};

#endif /* COLLISIONEFFECT_H_ */
