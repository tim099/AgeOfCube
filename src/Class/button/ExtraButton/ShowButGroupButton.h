#ifndef SHOWBUTGROUPBUTTON_H_
#define SHOWBUTGROUPBUTTON_H_
#include "BasicButton.h"
class BasicButGroup;
class BasicButList;
class ShowButGroupButton : public BasicButton{
public:
	ShowButGroupButton(BasicButGroup *but_group,BasicButList *SLB,bool uni_but_group=true
			,std::string name=0,double width=0.02,double height=0.0025,int type=0);
	virtual ~ShowButGroupButton();
	virtual void pressed();
	virtual ShowButGroupButton* ShowButGroupBut();
	virtual void set_active(bool active);
	BasicButGroup *but_group;
protected:
	void show_but_group();
	bool uni_but_group;

	BasicButList *SLB;
};

#endif /* SHOWBUTGROUPBUTTON_H_ */
