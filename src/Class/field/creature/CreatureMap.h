#ifndef CREATUREMAP_H_
#define CREATUREMAP_H_
#include <map>
#include <vector>
#include <queue>
class CubeCreature;
class Map;
class CreatureMap {
public:
	CreatureMap(std::queue<CubeCreature*>*creatures,Map *map);
	virtual ~CreatureMap();

	std::vector<CubeCreature*>* get_creature_map(int x,int y,int z);
	std::vector<CubeCreature*>* get_creature_map(unsigned pos);
	void tic();
protected:
	void creat_creature_map();
	void push_creature_map(CubeCreature* creature);
	std::queue<CubeCreature*>*creatures;
	std::map<unsigned,std::vector<CubeCreature*> >creatures_map;
	Map *map;
	std::vector<CubeCreature*> no_creature;
};

#endif /* CREATUREMAP_H_ */
