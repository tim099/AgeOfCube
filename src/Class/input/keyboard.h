#ifndef KEYBOARD
#define KEYBOARD
#include "GL/freeglut.h"

class Keyboard{
public:
Keyboard();
void keyboard(unsigned char key, int x, int y);
void keyboard_up(unsigned char key, int x, int y);
void Specialkeyboard(int key, int x, int y);
void Specialkeyboard_up(int key, int x, int y);
void clear();
bool get(unsigned char key);

bool w,a,s,d,q,e,r,f,z,x,v,c,esc,enter,space;
bool t,g,n,shift,b,p,o;
bool up,down,left,right,backspace,plus,minus;
bool input[300];
private:

int input_times[300];

};
#endif
