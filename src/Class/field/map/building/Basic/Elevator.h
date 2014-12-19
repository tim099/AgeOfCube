#ifndef ELEVATOR_H_
#define ELEVATOR_H_
#include "Building.h"
class Elevator : public Building{
public:
	Elevator(int x,int y,int z,Player *cur_player,int player=MOTHER_EARTH);
	virtual ~Elevator();
	virtual std::string name();
	virtual bool selectable()const;
	virtual unsigned require_work()const;
	virtual Resource require_resources();
protected:
	virtual void timer_tic();
	virtual std::vector<Building::But_type>& Upgrade_button(std::vector<Building::But_type> &_Upgrade_but);
	virtual std::vector<Building::But_type>& Recruit_button(std::vector<Building::But_type> &_Recruit_but);
	virtual std::vector<Building::But_type>& Research_button(std::vector<Building::But_type> &_Research_but);
	virtual std::vector<Building::But_type>& Info_button(std::vector<Building::But_type> &_Info_but);
	virtual void dp_building();
	float plane_h;
	bool plane_up;
};

#endif /* ELEVATOR_H_ */
