#ifndef UNFINISHEDBUILDING_H_
#define UNFINISHEDBUILDING_H_
#include "WorkableBuilding.h"
#include "ListBar.h"
class ConstructBuildings;
class UnfinishedBuilding : public WorkableBuilding{
public:
	UnfinishedBuilding(int x,int y,int z,Player *cur_player,Building *constructing_building,
			ConstructBuildings *CBL,int player=MOTHER_EARTH);
	virtual ~UnfinishedBuilding();
	virtual std::string name();
	virtual unsigned max_worker_num()const;
	virtual bool have_job()const;
	virtual unsigned require_work()const;
	virtual Resource require_resources();
	virtual Constructable* cur_constructing()const;

	virtual bool selectable()const;
protected:
	virtual void save_workablebuilding(FILE *file);
	virtual void load_workablebuilding(FILE *file);
	virtual void save_unfinishbuilding(FILE *file);
	virtual void load_unfinishbuilding(FILE *file);
	void save_construct(FILE *file);
	void load_construct(FILE *file);

	virtual void construct_finished();
	virtual void work_timer_tic();
	virtual std::vector<Building::But_type>& Upgrade_button(std::vector<Building::But_type> &_Upgrade_but);
	virtual std::vector<Building::But_type>& Recruit_button(std::vector<Building::But_type> &_Recruit_but);
	virtual std::vector<Building::But_type>& Research_button(std::vector<Building::But_type> &_Research_but);
	virtual std::vector<Building::But_type>& Info_button(std::vector<Building::But_type> &_Info_but);
	virtual void dp_building();

	void set_construct(Building *constructing_building);
	Building *constructing_building;
	ConstructBuildings *CBL;
	//ListBar *LBR;
};

#endif /* UNFINISHEDBUILDING_H_ */
