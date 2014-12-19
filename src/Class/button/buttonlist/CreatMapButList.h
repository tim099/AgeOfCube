#ifndef CREATMAPBUTLIST_H_
#define CREATMAPBUTLIST_H_
#include "BasicButList.h"
#include "BasicButGroup.h"
#include "Signal.h"
#include "Cube_define.h"
class CreatMapButList :public BasicButList{
public:
	CreatMapButList(Mouse *mou,double size=1.0);
	virtual ~CreatMapButList();
protected:
	BasicButGroup *options;
	BasicButGroup *Buildings;
	BasicButGroup *Basics;
	BasicButGroup *Cubes;
	virtual void creat_all_buttons();
	virtual void handle_button_group_signal(Signal s);
};

#endif /* CREATMAPBUTLIST_H_ */
