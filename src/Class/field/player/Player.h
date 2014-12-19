#ifndef PLAYER_H_
#define PLAYER_H_

#include <cstring>
#include <cstdio>
#include <queue>
#include "playerdefine.h"
#include "Building.h"
#include "ConstructBuildings.h"
#include "CreatCreature.h"
#include "map/Map.h"
#include "resources/Resource.h"
#include "LoadAddress.h"
class Player {
public:
	Player(int player,ConstructBuildings *CBL,CreatCreature *CCT,Map *map
	,std::queue<CubeCreature*>*all_creatures,std::vector<Collidable*>*colli_v
	,std::queue<DeletableCube*>*delete_q,LoadAddress *LAD);
	virtual ~Player();
	Building* build(int x,int y,int z,int building,bool unfinished=true);
	Building* build(Building *b);
	bool buildable(int x,int y,int z,int building);

	CubeCreature* recruit_creature(Building *b,int type);
	void save(FILE *fop);
	void load(FILE *fop);
	void load_finished();

	void timer_tic();

	void push_unfinished_building(Building *b);
	void push_unfinished_creature(CubeCreature* creature);

	CubeCreature* load_unfinished_creature(int type,FILE *fop);

	int which_player()const;
	int player_num()const;
	int player_num(int player)const;

	Map *map;
	std::vector<CubeCreature*>creatures;
	std::queue<Building*>buildings;
	Resource player_res;
	ConstructBuildings *CBL;
protected:
	void clear_player();

	void push_building(Building *b);
	void push_creature(CubeCreature* creature);
	void save_buildings(FILE *fop);
	void load_buildings(FILE *fop);
	void clear_building();
	void clear_unfinished();

	void save_creatures(FILE *fop);
	void load_creatures(FILE *fop);


	void clear_creatures();

	void unfinished_tic();

	int player;

	std::queue<CubeCreature*>enemies_in_sight;
	std::queue<CubeCreature*>*all_creatures;

	CreatCreature *CCT;
	LoadAddress *LAD;
	std::vector<Collidable*>*colli_v;
	std::queue<DeletableCube*>*delete_q;
	std::vector<CubeCreature*>unfinished_creature;
	std::vector<Building*>unfinished_building;
};

#endif /* PLAYER_H_ */
