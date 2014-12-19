#ifndef LOADADDRESS_H_
#define LOADADDRESS_H_
#include <map>
#include <cstdio>
class CubeCreature;
class Building;
class LoadAddress {
public:
	LoadAddress();
	virtual ~LoadAddress();
	void push_building_address(Building* address,Building* building);
	Building* get_building(Building* address);

	void push_creature_address(CubeCreature* address,CubeCreature* creature);
	CubeCreature* get_creature(CubeCreature* address);
protected:
	std::map<CubeCreature*,CubeCreature*>c_address;
	std::map<Building*,Building*>b_address;
};

#endif /* LOADADDRESS_H_ */
