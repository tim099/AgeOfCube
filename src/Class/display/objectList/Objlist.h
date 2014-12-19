#ifndef OBJLIST_H_
#define OBJLIST_H_
#include <cstdio>
#include "GL/glut.h"
#include "glm.h"
#include <queue>
class Objlist {

public:
	Objlist();
	virtual ~Objlist();

protected:
	void creat_list(GLuint&,char*,float);
	GLuint creat_list(char*file_name,float size,float x=0,float y=0,float z=0);
	void creat_obj_list(char*file_name,GLuint list,float size,float x=0,float y=0,float z=0);
	std::queue<GLuint>all_obj;
};

#endif
