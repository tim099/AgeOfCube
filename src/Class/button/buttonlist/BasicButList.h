#ifndef BASICBUTLIST_H_
#define BASICBUTLIST_H_

#include <vector>
#include <string>
#include "ButtonList.h"
#include "BasicButton.h"
#include "BasicButGroup.h"
#include "BuildButton.h"
//#include "SignalButton.h"
#include "ExecuteButton.h"
#include "ShowButGroupButton.h"

class BasicButList : public ButtonList{
public:
	BasicButList(Mouse *mou,double size=1.0);
	virtual ~BasicButList();
	virtual void dp_all_buttons();

	BasicButGroup* push_but_group(BasicButGroup* group);
	BasicButGroup* push_unique_but_group(BasicButGroup* group);
	void show_unique_but_group(BasicButGroup* group);
	unsigned uni_group_size()const;
	void clear_uni_group();
	BasicButGroup* cur_uni_group();


	BuildButton* creat_build_button(int building_type,bool unfinished,double x=0.0,double y=0.0);
	ShowButGroupButton* creat_ShowButGroup_button(std::string name,Signal signal,BasicButGroup* group,bool uni_but_group,int type,double x=0.0,double y=0.0);
	ExecuteButton* creat_SignalButton(ButSignal *_obj,std::string name,Signal signal,int type=0,double x=0.0,double y=0.0);
	BasicButton* creat_basic_button(std::string name,Signal signal,double x=0.0,double y=0.0);
	BasicButton* creat_short_button(std::string name,Signal signal,double x=0.0,double y=0.0);
	BasicButton* creat_medium_button(std::string name,Signal signal,double x=0.0,double y=0.0);
protected:
	virtual void timer_tic();
	void but_group_tic();
	void clear_all_but_group();
	BasicButGroup* _cur_uni_group;
	std::vector<BasicButGroup*>unique_group;
	std::vector<BasicButGroup*>all_but_group;

	ListFonts *fonts;
	ListButton *l_buts;
	double size;
	double basic_button_w,basic_button_h;
	double short_button_w,short_button_h;
	double medium_button_w,medium_button_h;
};

#endif /* BASICBUTLIST_H_ */
