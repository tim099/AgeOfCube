#ifndef CONSTRUCTBUILDINGS_H_
#define CONSTRUCTBUILDINGS_H_
#include "PlayerDefine.h"
#include "AllBuildingInclude.h"
class Player;
class Map;
class ConstructBuildings{
public:
	ConstructBuildings(std::vector<Player>*players,Map *map);
	virtual ~ConstructBuildings();
	Building* build(int x,int y,int z,int type,int player=MOTHER_EARTH,bool unfinished=false);
	Building* building(int type);
protected:
	std::vector<Player>*players;
	Map *map;
};

#endif /* CONSTRUCTBUILDINGS_H_ */
