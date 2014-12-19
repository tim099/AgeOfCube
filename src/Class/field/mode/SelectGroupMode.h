#ifndef SELECTGROUPMODE_H_
#define SELECTGROUPMODE_H_
const int STATE_SELECT=0;
const int STATE_SELECTED=1;
#include <cmath>
#include <vector>
#include "Mode.h"
#include "Mouse.h"
#include "CubeCreature.h"
#include "Player.h"
class SelectGroupMode : public Mode{
public:
	SelectGroupMode(Mouse *mou,Player *cur_player);
	virtual ~SelectGroupMode();
	virtual void dp_mode();
	virtual int get_mode()const;
protected:
	virtual void timer_tic();
	void find_select_creatures();
	void group_commend_goto();
	Mouse *mou;
	Player *cur_player;
	std::vector<CubeCreature*>s_creatures;
	double sx,sy,sz;
	int state;
};

#endif /* SELECTGROUPMODE_H_ */
