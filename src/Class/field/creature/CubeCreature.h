#ifndef CUBECREATURE_H_
#define CUBECREATURE_H_
#include <cstdio>
#include <string>
#include <cmath>

#include "resources/Resource.h"
#include "Cube.h"
#include "CreatureTexDefine.h"
#include "SelectableCube.h"
#include "PlayerOwnObject.h"
#include "Collidable.h"
#include "StateMove.h"

#include "Health.h"
#include "Constructable.h"
#include "LoadAddress.h"

class AllOrder;
class Order;
class Building;
class Core;
class CubeWorker;
class CubeCreature : public Cube,public PlayerOwnObject,public SelectableCube,public Collidable,
public Constructable,public Health{

public:
	CubeCreature(double pos_x,double pos_y,double pos_z,int player,Map *map,std::vector<Collidable*>*colli_v
	,std::vector<CubeCreature*>*f_units,std::queue<Building*>*f_buildings);
	virtual ~CubeCreature();

	virtual void avoid_collision(Collidable* cube);
	virtual int colli_state()const;
	virtual unsigned max_energy()const=0;

	virtual CubeWorker* worker();

	void dp_players_creature();
	void tic();

	void clean_order();
	void go_to(unsigned x,unsigned y,unsigned z);

	Order *cur_order()const;
	StateMove *cur_move_state()const;
	void switch_move_state(StateMove* s_move);
	State *cur_state()const;
	unsigned idle_time()const;

	unsigned cur_energy()const;
	unsigned consume_energy(unsigned num);
	void restore_energy(unsigned num);

	void set_address(LoadAddress* LAD);
	void load_finished(LoadAddress* LAD);

	bool get_in_building();
	void get_out_building();
	Building* in_building()const;
	Building* stay_in_building()const;
protected:

	virtual void timer_tic();
	void move_state_tic();
	void avoid_collision();
	void detect_at();

	virtual void save_cube(FILE *file);
	virtual void load_cube(FILE *file);
	virtual void creature_load_finished(LoadAddress* LAD);

	virtual void save_creature(FILE *file);
	virtual void load_creature(FILE *file);

	void save_address(FILE *file);
	void load_address(FILE *file);

	void dp_players_color();
	virtual void dp_creature()=0;

	CubeCreature* address;
	std::vector<CubeCreature*>*f_units;
	std::queue<Building*>*f_buildings;

	StateMove *move_state;
	Resource carry_res;
	AllOrder *orders;
	Building *_in_building;
	Core *core;

	bool _stay_in_building;
	unsigned timer;
	unsigned energy;
};

#endif /* CUBECREATURE_H_ */
