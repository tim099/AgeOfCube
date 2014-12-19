#ifndef ONEWAY_H_
#define ONEWAY_H_
#include "Building.h"
#include "ButSignal.h"
#include "map/Map.h"
const int ONEWAY_FRONT_WALL = 0;
const int ONEWAY_BACK_WALL = 1;
const int ONEWAY_LEFT_WALL = 2;
const int ONEWAY_RIGHT_WALL = 3;
const int ONEWAY_FRONT_NOUT = 4;
const int ONEWAY_BACK_NOUT = 5;
const int ONEWAY_LEFT_NOUT = 6;
const int ONEWAY_RIGHT_NOUT = 7;
const unsigned char W_NULL=0;
const unsigned char W_LEFT_WALL=1<<0;
const unsigned char W_RIGHT_WALL=1<<1;
const unsigned char W_FRONT_WALL=1<<2;
const unsigned char W_BACK_WALL=1<<3;
const unsigned char W_LEFT_NOUT=1<<4;
const unsigned char W_RIGHT_NOUT=1<<5;
const unsigned char W_FRONT_NOUT=1<<6;
const unsigned char W_BACK_NOUT=1<<7;
class OneWay : public Building,ButSignal{
public:
	OneWay(int x,int y,int z,Player *cur_player,Map *map,int player=MOTHER_EARTH);
	virtual ~OneWay();
	virtual std::string name();
	virtual unsigned require_work()const;
	virtual Resource require_resources();
	virtual unsigned char get_path()const;
	virtual unsigned char get_extra_path()const;
	virtual void creat_button(BasicButList *SLB,std::vector<BasicButGroup*>*but_groups);
	virtual void handle_signal(Signal sig);
protected:
	virtual void save_building(FILE *file);
	virtual void load_building(FILE *file);

	virtual void timer_tic();
	virtual std::vector<Building::But_type>& Upgrade_button(std::vector<Building::But_type> &_Upgrade_but);
	virtual std::vector<Building::But_type>& Recruit_button(std::vector<Building::But_type> &_Recruit_but);
	virtual std::vector<Building::But_type>& Research_button(std::vector<Building::But_type> &_Research_but);
	virtual std::vector<Building::But_type>& Info_button(std::vector<Building::But_type> &_Info_but);
	virtual void dp_building();

	void creat_alter_but(BasicButList *SLB,std::vector<BasicButGroup*>*but_groups);
	Map *map;
	unsigned char way;
};

#endif /* ONEWAY_H_ */
