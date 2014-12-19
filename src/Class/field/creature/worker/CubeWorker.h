#ifndef CUBEWORKER_H_
#define CUBEWORKER_H_
#include "CubeCreature.h"
#include "CubeTextureDefine.h"
#include "CreatWork.h"
#include "BasicButGroup.h"
#include "BasicButList.h"
class WorkerCore;
class WorkableBuilding;

class CubeWorker : public CubeCreature{
public:
	CubeWorker(double pos_x,double pos_y,double pos_z,int player,Map *map,std::vector<Collidable*>*colli_v
	,std::vector<CubeCreature*>*f_units,std::queue<Building*>*f_buildings);
	virtual ~CubeWorker();
	virtual Resource require_resources();
	virtual unsigned require_work()const;
	virtual std::string name();
	virtual CubeWorker* worker();
	virtual double max_v()const;
	virtual double max_a()const;
	virtual unsigned max_energy()const;
	virtual unsigned max_health()const;
	unsigned get_work();

	void find_job();
	Work *cur_work()const;
	void set_work(WorkableBuilding* w_b,int type);
	void work_lost();

	WorkableBuilding* work_in_building();

	virtual void creat_building_buts(BasicButGroup *building,BasicButList *SLB);
protected:
	virtual void creature_load_finished(LoadAddress* LAD);
	virtual void save_creature(FILE *file);
	virtual void load_creature(FILE *file);
	virtual void save_worker(FILE *file);
	virtual void load_worker(FILE *file);
	virtual void dp_creature();

	virtual void timer_tic();
	virtual void worker_timer_tic();

	virtual unsigned work_per_tic()const;

	void save_work(FILE *file);
	void load_work(FILE *file);
	CreatWork *CJB;
	Work *work_at;
};

#endif /* CUBEWORKER_H_ */
