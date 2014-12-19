#ifndef BUTTONLIST_H_
#define BUTTONLIST_H_
#include <queue>
#include "Button.h"
#include "Signal.h"
#include "ListButton.h"
#include "ListFonts.h"
#include "Mouse.h"
class ButtonList {
public:
	ButtonList(Mouse *mou);
	virtual ~ButtonList();
	virtual void dp_all_buttons()=0;
	virtual Signal get_signal();
	void remove_button();

	void tic();

	std::queue<Button*>buts;
	Button *prev_pressed_but,*prepre_but;
protected:
	virtual void crusor_button_collision();
	virtual void handle_button_group_signal(Signal s);
	virtual void timer_tic()=0;
	void check_button_pressed();
	void handle_signal(Signal s);

	std::queue<Signal>signal_q;
	std::queue<Signal>signal_out;

	Mouse *mou;
};

#endif
