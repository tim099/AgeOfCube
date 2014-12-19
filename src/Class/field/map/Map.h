#ifndef MAP_H_
#define MAP_H_

#include <cstring>
#include <ctime>
#include <queue>
#include <iostream>
#include "BasicCube.h"
#include "building/Building.h"
#include "Building.h"
#include "Path.h"
#include "Pos.h"
const int MAX_X=300,MAX_Y=100,MAX_Z=300;
class CreatureMap;
class CubeCreature;
class Map {
public:
	Map(std::queue<DeletableCube*>*delete_q,std::queue<CubeCreature*>*creatures,unsigned msx=MAX_X,unsigned msy=MAX_Y,unsigned msz=MAX_Z);
	virtual ~Map();

	StaticCube* get_map(int x,int y,int z);
	StaticCube* get_map(unsigned pos);
	bool see_map(int x,int y,int z,int player);
	void discover(int x,int y,int z,int player);
	void delete_cube(int x,int y,int z);
	void creat_cube(int x,int y,int z,int c_type=C_BASIC);
	bool creatable(int x,int y,int z);

	void update_all_path();
	void update_cube(int x,int y,int z);

	void tic();
	bool build(Building *building);
	bool buildable(Building *building);
	void destruct_building(int x,int y,int z);
	void creat_map_flat(unsigned sx,unsigned sy,unsigned sz,int type=C_BASIC,unsigned spx=0,unsigned spy=0,unsigned spz=0);
	void generate_map(unsigned seed);
	void creat_flate_circle(Pos o,unsigned r,int type);
	void creat_ball(Pos o,unsigned r,int type);
	void Save_Map(FILE *fop);
	void Load_Map(FILE *fop);
	unsigned MSX()const;
	unsigned MSY()const;
	unsigned MSZ()const;

	Path *get_path()const;

	std::queue<Building*>buildings;
	CreatureMap *creature_map;
protected:
	bool can_build_on(Building *building);
	void generate_mountain();
	void creat_mountain(Pos pos);
	void push_building(Building *building);
	void update_pos(int x,int y,int z);
	void update_path(int x,int y,int z);
	void set_map_size(unsigned msx,unsigned msy,unsigned msz);
	void clear_map();
	unsigned msx,msy,msz;
	unsigned seed;
	StaticCube* map[MAX_X][MAX_Y][MAX_Z];
	StaticCube* CubeNull;
	StaticCube* CubeOutOfEdge;
	std::queue<DeletableCube*>*delete_q;
	std::queue<CubeCreature*>*creatures;
	Path *path;
};

#endif /* MAP_H_ */
