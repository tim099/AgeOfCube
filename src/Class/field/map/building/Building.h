#ifndef BUILDING_H_
#define BUILDING_H_
#include <cstdio>
#include <string>
#include <vector>
#include "BuildingResource.h"
#include "Signal.h"
#include "ModeSignalDefine.h"
#include "StaticCube.h"
#include "SelectableCube.h"
#include "CubeCreature.h"
#include "building_define.h"
#include "building_obj_define.h"
#include "PlayerOwnObject.h"
#include "Constructable.h"
#include "UnsignedPos.h"
#include "LoadAddress.h"
class BasicButGroup;
class BasicButList;
class Player;
class CubeCreature;
class WorkableBuilding;
class Building : public StaticCube,public PlayerOwnObject,public SelectableCube,public BuildingResource,
public Constructable{
public:
	struct But_type{
		But_type(std::string _name,Signal _sig){
			name=_name;
			sig=_sig;
		}
		std::string name;
		Signal sig;
	};
	Building(unsigned x,unsigned y,unsigned z,Player *cur_player,int player=MOTHER_EARTH);
	virtual ~Building();

	virtual std::vector<Building::But_type> Upgrade_but();
	virtual std::vector<Building::But_type> Recruit_but();
	virtual std::vector<Building::But_type> Research_but();
	virtual std::vector<Building::But_type> Info_but();
	virtual void creat_button(BasicButList *SLB,std::vector<BasicButGroup*>*butgroups);

	virtual Building *get_building();
	virtual WorkableBuilding *workablebuilding();

	virtual bool get_in(CubeCreature *creature);

	virtual unsigned char get_extra_path()const;
	virtual unsigned char get_path()const;

	virtual bool recruit_creature(int type);

	unsigned get_x()const;
	unsigned get_y()const;
	unsigned get_z()const;
	UnsignedPos get_pos()const;

	void tic();
	int can_build_on()const;
	int build_on()const;
	bool set_build_on(int build_on);
	void set_pos(int x,int y,int z);

	void dp_players_building();

	void set_address(LoadAddress* LAD);
	virtual void load_finished(LoadAddress* LAD);
protected:
	virtual void timer_tic()=0;
	virtual std::vector<Building::But_type>& Upgrade_button(std::vector<Building::But_type> &_Upgrade_but)=0;
	virtual std::vector<Building::But_type>& Recruit_button(std::vector<Building::But_type> &_Recruit_but)=0;
	virtual std::vector<Building::But_type>& Research_button(std::vector<Building::But_type> &_Research_but)=0;
	virtual std::vector<Building::But_type>& Info_button(std::vector<Building::But_type> &_Info_but)=0;
	virtual void dp_building()=0;

	void creat_recruit_button(BasicButList *SLB,std::vector<BasicButGroup*>*but_groups);
	void creat_upgrade_button(BasicButList *SLB,std::vector<BasicButGroup*>*but_groups);
	void creat_info_button(BasicButList *SLB,std::vector<BasicButGroup*>*but_groups);
	void creat_research_button(BasicButList *SLB,std::vector<BasicButGroup*>*but_groups);
	void creat_button_group(BasicButList *SLB,std::vector<Building::But_type>&buff,BasicButGroup *group);


	void in_building_creature_check();
	void dp_player_color();
	virtual void save_static_cube(FILE *file);
	virtual void load_static_cube(FILE *file);
	virtual void save_building(FILE *file);
	virtual void load_building(FILE *file);
	void save_address(FILE *file);
	void load_address(FILE *file);

	Building *address;
	UnsignedPos pos;
	int CubeCapacity;
	int cb_on,b_on;
	unsigned b_function;
	Player *cur_player;
	unsigned char extra_path;
	std::vector<CubeCreature*>in_b_creatures;
};

#endif
