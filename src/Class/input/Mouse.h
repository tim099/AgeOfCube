#ifndef MOUSE_H_
#define MOUSE_H_

#include <cstdio>
#include <GL/freeglut.h>

class Cube;
class Building;
class CubeCreature;
class Mouse {
public:
	Mouse();
	virtual ~Mouse();
	void mouse(int button, int state, int x, int y);
	void mouseWheel(int button, int dir, int x, int y);
	void glutPassiveMotionFunc(int x, int y);
	int get_dir();
	bool get_but(int but);
	void clear();
	unsigned select_x,select_y,select_z;
	int surface_x,surface_y,surface_z;
	int x,y,prev_x,prev_y;
	bool dir[2],state;
	bool button[6];
	double px,py,pz;
	double fx,fy;
	Cube *selected_cube;
	Building *selected_building;
	CubeCreature *selected_creature;
protected:
	bool but_in[6];
	void set_pos(int x,int y);

};

#endif /* MOUSE_H_ */
