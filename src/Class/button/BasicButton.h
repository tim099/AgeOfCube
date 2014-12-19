#ifndef BASICBUTTON_H_
#define BASICBUTTON_H_
#include "Button.h"
#include <string>
class ShowButGroupButton;
class BasicButton : public Button{
public:
	BasicButton(std::string name=0,double width=0.02,double height=0.0025,int type=0);
	virtual ~BasicButton();
	virtual int type()const;
	virtual ShowButGroupButton* ShowButGroupBut();

	void set_name(std::string name);
protected:
	int _type;
};

#endif /* BASICBUTTON_H_ */
