#ifndef EXECUTEBUTTON_H_
#define EXECUTEBUTTON_H_
#include <vector>
#include "BasicButton.h"
#include "ESentSignal.h"
class ExecuteButton : public BasicButton{
public:
	ExecuteButton(std::string name=0,double width=0.02,double height=0.0025,int type=0);
	virtual ~ExecuteButton();
	virtual void pressed();
	void push_execute(Execute* execute);
protected:
	std::vector<Execute*> executes;
};

#endif /* EXECUTEBUTTON_H_ */
