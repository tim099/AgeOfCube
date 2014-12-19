#ifndef GAME_H_
#define GAME_H_
#include <queue>
#include <stack>
#include "display/Display.h"
#include "display/DPstart.h"
#include "stage/Smenu.h"
#include "stage/ScreatMap.h"

#include "stage/SsaveMap.h"
#include "stage/SloadMap.h"

#include "Signal.h"
class Game {
public:
	Game();
	virtual ~Game();


	void timer_tick();

	std::stack<Stage*>stages;
	Display* display;
	int s_width,s_height;
private:
	bool strcm(char *,const char *);
	void start();
	void read_in_settings();
	void process_settings(char c[101]);
	void save_sittings();
	void push_stage(Stage*);
	void pop_stage();
	void get_signal();
	void handle_signal(Signal s);
	void stage_control(Signal s);
	void game_operation(Signal s);
	std::queue<Signal>signal_q;
};

#endif
