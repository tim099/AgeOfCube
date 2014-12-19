#ifndef STAGE_H_
#define STAGE_H_
#include <queue>
#include <ctime>
#include <iostream>
#include "Display.h"
#include "keyboard.h"
#include "mouse.h"
#include "Signal.h"
#include "BasicButList.h"
class Stage {
public:
	Stage();
	virtual ~Stage();
	virtual Display* cur_dis();
	void sent_signal(Signal s);
	void tic();

	bool END();
	Keyboard k_b;
	Mouse mou;
	std::queue<Signal>out_signal_q;
protected:
	void get_signals();
	void handle_signals();

	virtual void timer_tick()=0;
	virtual void view_control();

	virtual void signal_process(Signal s);
	virtual void Stage_signal_process(Signal s);
	virtual void signal_under_stage(Signal s);
	std::queue<Signal>signal_q;
	Display *cur_dp;
	BasicButList *SLB;
	bool end;
	long long unsigned timer;
};

#endif
