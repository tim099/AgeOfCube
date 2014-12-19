#ifndef BUILDINGMODE_H_
#define BUILDINGMODE_H_

#include "Mode.h"
#include "Mouse.h"
#include "PlayerDefine.h"
#include "Player.h"
class BuildingMode : public Mode{
public:
	BuildingMode(ConstructBuildings *CBL,Mouse *mou,Player *cur_player,int building,bool unfinished=true);
	virtual ~BuildingMode();
	virtual void dp_mode();
	virtual int get_mode()const;
protected:
	void build();
	virtual void timer_tic();
	Mouse *mou;
	Player *cur_player;
	ConstructBuildings *CBL;
	Building *building;
	int b_type;
	bool unfinished;
};

#endif /* BUILDINGMODE_H_ */
