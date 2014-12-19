#ifndef LISTBUTTON_H_
#define LISTBUTTON_H_

#include "Bmplist.h"

class ListButton : public Bmplist{
struct button{
GLuint normal,selected,pressed;
double width,height;
};
public:
	ListButton(double size=0.02);
	virtual ~ListButton();
	std::vector<button> Buttons;
protected:
	void creat_all_list();
	double size;
};

#endif /* LISTBUTTON_H_ */
