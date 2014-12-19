#ifndef SELECTBUILDINGMODE_H_
#define SELECTBUILDINGMODE_H_
#include "cube_define.h"
#include "Mode.h"
#include "Mouse.h"
#include "map/Map.h"
#include "Player.h"
#include "BasicButList.h"
#include "List.h"
#include "CreatCreature.h"
#include "BasicButGroup.h"
#include "ResourcesTexDefine.h"
#include "Messagebox.h"
#include "ListBar.h"
#include <vector>
class SelectBuildingMode : public Mode{
public:
	SelectBuildingMode(Mouse *mou,Map *map,BasicButList *SLB,Messagebox *MSB,Player *player,CreatCreature *CCT,
			Building* s_building);
	virtual ~SelectBuildingMode();
	virtual void dp_mode();
	virtual int get_mode()const;
protected:
	virtual void handle_mode_signal(Signal sig);
	virtual void timer_tic();
	virtual void dp_building_mode();
	void handle_signal(Signal sig);
	void handle_DP_signal(Signal sig);
	void dp_recruit_info(int type);
	void dp_building_resources();
	void creat_button();

	void creat_creature();
	Mouse *mou;
	Map *map;
	BasicButList *SLB;
	List *list;
	Building* s_building;

	Player *player;
	CreatCreature *CCT;
	CubeCreature* creature;

	BasicButGroup *BBG;
	Messagebox *MSB;

	std::vector<BasicButGroup*> but_groups;

	double disy;
	double posx,posy;
};

#endif /* SELECTBUILDINGMODE_H_ */
