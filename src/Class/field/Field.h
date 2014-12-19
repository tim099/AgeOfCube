#ifndef FIELD_H_
#define FIELD_H_
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <cmath>
#include <ctime>

#include <map>
#include "Signal.h"
#include "map/Map.h"

#include "CubeCreature.h"
#include "CreatCreature.h"
#include "Mouse.h"
#include "Keyboard.h"
#include "Player.h"

#include "BasicButList.h"
#include "BuildingMode.h"
#include "CreatCubeMode.h"
#include "DestructMode.h"
#include "SelectWorkableBuildingMode.h"
#include "SelectCreatureMode.h"
#include "SelectWorkerMode.h"
#include "SelectGroupMode.h"

#include "LoadAddress.h"
#include "ConstructBuildings.h"
#include "PosDouble.h"
#include "MessageBox.h"
class Field {
public:
	Field(Mouse *mou,Keyboard *k_b,BasicButList *SLB,Messagebox *MSB);
	virtual ~Field();
	virtual void generate_map();
	void tic();
	void sent_signal(Signal sig);
	void switch_mode(Mode *mode);
	void switch_building_mode(int building_type,bool unfinished=false);
	void save_field(const char *filename);
	void load_field(const char *filename);
	void load_finish();
	Building *s_building()const;
	CubeCreature *s_creature()const;

	Mode *mode;
	Map *map;
	Mouse *mou;
	unsigned dp_height;
	std::queue<CubeCreature*>creatures;
	std::vector<Collidable*>colli_v;
	std::queue<DeletableCube*>delete_q;
protected:
	void clear_field();

	void save_players(FILE *fop);
	void load_players(FILE *fop);

	void mode_timer_tick();

	virtual void timer_tick()=0;
	void terminate_timer_tic();
	void colli_q_timer_tic();
	void creatures_timer_tic();
	void handle_signal();
	void signal_process(Signal sig);
	virtual void building_signal(Signal sig);

	void find_selected_cube();
	void find_selected_building();
	void find_selected_creature();
	void selected_pos_compute();
	void control();

	void selected_creature();

    CreatCreature *CCT;
	BasicButList *SLB;
	Keyboard *k_b;
	LoadAddress *LAD;

	ConstructBuildings *CBL;
	std::queue<Signal>signal_q;
	std::vector<Player>players;
	int cur_player;
	Messagebox *MSB;
//	PosDouble *look,*look_v;
};

#endif /* FIELD_H_ */
