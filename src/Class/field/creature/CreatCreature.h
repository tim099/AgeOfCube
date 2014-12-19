#ifndef CREATCREATURE_H_
#define CREATCREATURE_H_
#include "map/Map.h"
#include "CubeWorker.h"
class Player;
class CreatCreature {
public:
	CreatCreature(Map* map,std::vector<Collidable*>*colli_v,std::vector<Player>*players);
	virtual ~CreatCreature();
	CubeCreature *creat_creature(int type,double pos_x,double pos_y,double pos_z,int player);
protected:
	Map* map;
	std::vector<Collidable*>*colli_v;
	std::vector<Player>*players;
};

#endif /* CREATCREATURE_H_ */
