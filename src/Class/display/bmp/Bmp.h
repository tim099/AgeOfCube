#ifndef BMP_H_
#define BMP_H_
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <cmath>
#include "GL/freeglut.h"

class Bmp {
public:
	Bmp(GLuint tex=0);
	virtual ~Bmp();
    void load(const char *path );
    void load( int width, int height);
    void prepare_tex(const char *path);
    int w,h;
    double pw,ph;
    unsigned char *rgb;
    GLuint tex;
private:
    void rb_swap();
};

#endif /* BMP_H_ */
