#ifndef SELECTCREATUREMODE_H_
#define SELECTCREATUREMODE_H_
#include "Mode.h"
#include "Mouse.h"
#include "Keyboard.h"
#include "BasicButList.h"
#include "List.h"
#include "ListBar.h"
#include "CubeCreature.h"
class SelectCreatureMode : public Mode{
public:
	SelectCreatureMode(Mouse *mou,BasicButList *SLB,CubeCreature *s_creature,Keyboard *keyboard);
	virtual ~SelectCreatureMode();
	virtual void dp_mode();
	virtual int get_mode()const;
	virtual void display_alter(Display* display);
protected:
	virtual void timer_tic();
	double posx,posy;
	Mouse *mou;
	Keyboard *k_b;
	BasicButList *SLB;
	List *list;
	CubeCreature *s_creature;
	ListBar *LBR;
	BasicButGroup *BBG;
	bool control_mode;
	int jump;
};

#endif /* SELECTCREATUREMODE_H_ */
