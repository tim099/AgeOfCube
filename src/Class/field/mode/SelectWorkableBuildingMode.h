#ifndef SELECTWORKABLEBUILDINGMODE_H_
#define SELECTWORKABLEBUILDINGMODE_H_
#include "SelectBuildingMode.h"
#include "WorkableBuilding.h"
class SelectWorkableBuildingMode : public SelectBuildingMode{
public:
	SelectWorkableBuildingMode(Mouse *mou,Map *map,BasicButList *SLB,Messagebox *MSB,Player *player,CreatCreature *CCT,
			WorkableBuilding *workable_building);
	virtual ~SelectWorkableBuildingMode();
	virtual int get_mode()const;
protected:
	virtual void dp_building_mode();
	virtual void timer_tic();
	WorkableBuilding *workable_building;
};

#endif /* SELECTWORKABLEBUILDINGMODE_H_ */
