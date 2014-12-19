#ifndef BASE_H_
#define BASE_H_
#include "WorkableBuilding.h"
class Player;
class Map;
class Base : public WorkableBuilding{
public:
	struct BaseCore{
		BaseCore(){
			h=0.01;vy=0;ry=0;up=true;
		}
		void tic(){
			vy*=0.9;
			if(up){
				vy+=0.0002;
				h+=vy;
				if(h>0.02){
					up=false;
				}
			}else{
				vy-=0.0002;
				h+=vy;
				if(h<0.01){
					up=true;
				}
			}
			if(ry<180)ry+=1.0;
			else ry-=360.0;
		}
		bool up;
		double h,vy;
		double ry;
	};
	Base(int x,int y,int z,Player *cur_player,int player=MOTHER_EARTH);
	virtual ~Base();
	virtual std::string name();
	virtual bool have_job()const;
	virtual unsigned max_worker_num()const;
	virtual unsigned require_work()const;
	virtual Resource require_resources();

	virtual unsigned building_produce_work();
protected:
	virtual void work_timer_tic();
	virtual std::vector<Building::But_type>& Upgrade_button(std::vector<Building::But_type> &_Upgrade_but);
	virtual std::vector<Building::But_type>& Recruit_button(std::vector<Building::But_type> &_Recruit_but);
	virtual std::vector<Building::But_type>& Research_button(std::vector<Building::But_type> &_Research_but);
	virtual std::vector<Building::But_type>& Info_button(std::vector<Building::But_type> &_Info_but);
	virtual void dp_building();
	BaseCore DP_core;
};

#endif /* BASE_H_ */
