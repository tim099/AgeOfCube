#ifndef BUILDBUTTON_H_
#define BUILDBUTTON_H_
#include "BasicButton.h"

class Building;
class BuildButton : public BasicButton{
public:
	BuildButton(int building,bool unfinished=true);
	virtual ~BuildButton();
	virtual void pressed();

protected:
	void build();
	int building;
	bool unfinished;
};

#endif /* BUILDBUTTON_H_ */
