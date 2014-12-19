#ifndef LISTBAR_H_
#define LISTBAR_H_
#include "GL/freeglut.h"
class ListBar {
public:
	struct color{
		color(GLfloat R=0.0,GLfloat G=0.0,GLfloat B=0.0,GLfloat A=1.0){
			col[0]=R;col[1]=G;col[2]=B;col[3]=A;
		}
		GLfloat col[4];
	};
	ListBar();
	virtual ~ListBar();
	static void dp_bar(unsigned numerator,unsigned denominator,double size=1.0,double height=0.1
			,color color=color(1.0,0.0,0));
	static void dp_3D_bar(unsigned numerator,unsigned denominator,double size=1.0,double height=0.1
				,color color=color(1.0,0.0,0));
protected:

};
#endif /* LISTBAR_H_ */
