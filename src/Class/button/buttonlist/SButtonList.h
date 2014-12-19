#ifndef SBUTTONLIST_H_
#define SBUTTONLIST_H_
#include "BasicButList.h"

class SButtonList : public BasicButList{
public:
	SButtonList(Mouse *mou,double size=1.0);
	virtual ~SButtonList();
protected:
	virtual void creat_all_buttons();
	BasicButGroup *but_group;
};

#endif /* SBUTTONLIST_H_ */
