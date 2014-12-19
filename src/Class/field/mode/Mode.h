#ifndef MODE_H_
#define MODE_H_
#include <queue>
#include "cstdio"
#include "Signal.h"
#include "GL/freeglut.h"
#include "mode_define.h"
#include "ModeSignalDefine.h"
class Display;
class Mode {
public:
	Mode();
	virtual ~Mode();
	virtual void dp_mode();

	void tic();
	bool END();
	virtual int get_mode()const;
	virtual void display_alter(Display* display);
	void sent_signal(Signal sig);

protected:
	void handle_signal(Signal sig);
	virtual void handle_mode_signal(Signal sig);
	std::queue<Signal>signal_q;
	virtual void timer_tic();
	bool end;
};

#endif /* MODE_H_ */
