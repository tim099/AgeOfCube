#ifndef BUTTON_H_
#define BUTTON_H_
#include "ButtonDefine.h"
#include "Bmp.h"
#include "bmp/ListFonts.h"
#include "Signal.h"
#include <string>
class Button {
public:
	Button();
	virtual ~Button();
	virtual void pressed();
	virtual int type()const;
	virtual void set_active(bool active);

	bool active()const;

	void tic();
	void set_state(int state);
	int get_state();

	void delete_but();
	bool exist()const;

	double x,y,width,height;
	int pressed_timer;
	std::string name;
	Signal signal;
protected:
	bool _active;
	bool _exist;
	int state;
};

#endif /* BUTTON_H_ */
