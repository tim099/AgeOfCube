#ifndef BMPLIST_H_
#define BMPLIST_H_

#include <queue>
#include <vector>
#include "Bmp.h"

class Bmplist {
public:
	Bmplist();
	virtual ~Bmplist();
	static void dp_tex(Bmp* bmp,double w=0.05,double h=0.05,double rx=0,double ry=0);
protected:
	GLuint creat_texture_bysize(const char *path,double size,double rx=0,double ry=0);
	void creat_texture_bysize(const char *path,GLuint list,double size,double rx=0,double ry=0);
	void creat_cube_bysize(const char *path,GLuint list,double size);
	GLuint creat_texture(const char *path,double size,double rx=0,double ry=0);
	GLuint creat_texture(const char *path,double size,double &width,double &height,double rx=0,double ry=0);

	Bmp* creat_tex(const char *path);



	virtual void creat_all_list()=0;

	std::queue<GLuint>all_tex;
	std::queue<GLuint>all_texture;
};

#endif
