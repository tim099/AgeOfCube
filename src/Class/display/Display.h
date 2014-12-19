#ifndef DISPLAY_H_
#define DISPLAY_H_

#define PI 3.14159265359
#include <cstdio>
#include <vector>
#include <ctime>
#include "GL/freeglut.h"
#include "glm.h"
#include "math.h"
#include "ButtonList.h"
#include "Mouse.h"
#include "PosDouble.h"
#include "MessageBox.h"

class Display {
public:
	Display(Mouse *mou);
	virtual void display()=0;
	virtual void dp_prepare();
	virtual ~Display();
	virtual void tic();

	bool render_finished()const;
	void window_resize(int w,int h);
	float distance,horizontal,vertical;
	PosDouble look_v,look;
	float look_minx,look_miny,look_minz,look_maxx,look_maxy,look_maxz;
	float v_hori,v_ver,v_dis;

	int s_width,s_height;
	float zoom,light_hori,light_ver,light_dis;
	int dp_range;
	Messagebox *MSB;
protected:
	void compute_mouse_location();
	void compute_mouse_flat_pos();
	virtual void timer_tic();
	virtual void prepare_list()=0;
	virtual void dp_button();
	virtual void dp_message_box();
	void look_at_func();
	void prepare_lighting();
	void light_off();
	void light_on();
	void Materialfv();
	void lighting0();
	void lighting1();
	void lighting2();
	void lighting3();
	void lighting4();
	void lighting5();
	void lighting6();
	ButtonList *SLB;
	Mouse *mou;

	float look_dy;
	bool r_finished;
};

#endif
