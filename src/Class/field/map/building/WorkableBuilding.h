#ifndef WORKABLEBUILDING_H_
#define WORKABLEBUILDING_H_
#include "Building.h"
#include "Workable.h"
#include <vector>
#include <queue>

class CubeWorker;
class CubeCreature;
class Player;
class WorkableBuilding : public Building,public Workable{
public:
	WorkableBuilding(unsigned x,unsigned y,unsigned z,Player *cur_player,int player=MOTHER_EARTH);
	virtual ~WorkableBuilding();
	virtual WorkableBuilding *workablebuilding();

	virtual bool have_job()const=0;
	virtual unsigned max_worker_num()const=0;
	virtual bool worker_rigister(CubeWorker* worker);

	virtual void timer_tic();

	virtual bool recruit_creature(int type);
	virtual double recruit_process()const;
	virtual Constructable* cur_constructing()const;

	virtual unsigned building_produce_work();

	virtual int work_type();
	virtual int job_type();

	virtual void load_finished(LoadAddress* LAD);
	virtual bool get_in(CubeCreature *creature);
	void dp_rally_point();
	void set_rally_point(unsigned x,unsigned y,unsigned z);
protected:
	virtual void construct(unsigned work);
	virtual void construct_finished();

	virtual void save_building(FILE *file);
	virtual void load_building(FILE *file);
	virtual void save_workablebuilding(FILE *file);
	virtual void load_workablebuilding(FILE *file);
	void save_rally_point(FILE* file);
	void load_rally_point(FILE* file);
	void save_workers(FILE* file);
	void load_workers(FILE* file);

	virtual void work_timer_tic();

	bool find_rally_point();

	bool check_workers(CubeWorker* worker);
	void clear_workers();

	void save_construct_q(FILE *file);
	void load_construct_q(FILE *file);

	void push_construct(CubeCreature* creature);


	std::vector<CubeWorker*> workers;
	std::queue<CubeCreature*> construct_q;

	int _job_type;
	UnsignedPos rally_point;//rally_point
	bool rally_point_find;
};

#endif /* WORKABLEBUILDING_H_ */
