#ifndef COLLIDABLE_H_
#define COLLIDABLE_H_
#include <cstdio>
#include <cmath>
#include <queue>
#include "DeletableCube.h"
#include "Effect.h"
#include "Physical.h"

const unsigned COLLI_NULL=0;
const unsigned COLLI_DROP=1<<1;
const unsigned COLLI_LEFT=1<<2;
const unsigned COLLI_RIGHT=1<<3;
const unsigned COLLI_UP=1<<4;
const unsigned COLLI_DOWN=1<<5;
const unsigned COLLI_FRONT=1<<6;
const unsigned COLLI_BACK=1<<7;

const int C_STATE_COLLI_OFF=-1;
const int C_STATE_COLLI_ON=0;
class Map;
class Collidable : virtual public DeletableCube,public Physical{
public:
	Collidable(double x,double y,double z,std::vector<Collidable*>*colli_v,Map *map);
	virtual ~Collidable();

	virtual Effect *get_colli_effect();//can do someother thing
	virtual void set_pos(double pos_x,double pos_y,double pos_z);

	virtual int colli_state()const;
protected:
	virtual bool collision();//collide other
	virtual void be_collide(Effect *effect);//being collide

	Collidable* detect_colli_creature()const;
	unsigned detect_colli_map(Collidable* cube)const;
	bool detect_stuck(int x,int y,int z);

	bool colli_creature();
	bool colli_map();
	void handle_stuck();

	bool collide(Collidable* cube)const;
	bool pre_collide(Collidable* cube_b)const;

	void save_colli(FILE *fop);
	void load_colli(FILE *fop);
	void move_timer_tic();
	std::vector<Collidable*>*colli_v;
	Map *map;
};

#endif /* COLLIDABLE_H_ */
