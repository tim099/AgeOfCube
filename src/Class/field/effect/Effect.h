#ifndef EFFECT_H_
#define EFFECT_H_
#include <cstdio>
#include "EffectDefine.h"
class Collidable;
class Effect {
public:
	Effect();
	virtual ~Effect();
	virtual int Effect_type();
	virtual void collision(Collidable* obj);
protected:
};

#endif /* EFFECT_H_ */
