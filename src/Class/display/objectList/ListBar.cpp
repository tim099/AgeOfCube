#include "ListBar.h"

ListBar::ListBar() {

}
ListBar::~ListBar() {

}
void ListBar::dp_bar(unsigned numerator,unsigned denominator,double size,double height,color color){
	ListBar::color dark;
	if(numerator>denominator)denominator=numerator;
	if(denominator<=0)denominator=1;
	glMaterialfv(GL_FRONT,GL_AMBIENT_AND_DIFFUSE,dark.col);
	glBegin(GL_QUADS);
	glVertex3f(size*(numerator-0.5*denominator),size*height,0.0);
	glVertex3f(size*(numerator-0.5*denominator),-size*height,0.0);
	glVertex3f(0.5*size*denominator,-size*height,0.0);
	glVertex3f(0.5*size*denominator,size*height,0.0);
	glEnd();

	glMaterialfv(GL_FRONT,GL_AMBIENT_AND_DIFFUSE,color.col);
	glBegin(GL_QUADS);
	glVertex3f(-0.5*size*denominator,size*height,0);
	glVertex3f(-0.5*size*denominator,-size*height,0);
	glVertex3f(size*(numerator-0.5*denominator),-size*height,0);
	glVertex3f(size*(numerator-0.5*denominator),size*height,0);
	glEnd();

	glMaterialfv(GL_FRONT,GL_AMBIENT_AND_DIFFUSE,ListBar::color(1.0,1.0,1.0,1.0).col);
}
void ListBar::dp_3D_bar(unsigned numerator,unsigned denominator,double size,double height,color color){
	ListBar::color dark;
	if(numerator>denominator)denominator=numerator;
	if(denominator<=0)denominator=1;
	glMaterialfv(GL_FRONT,GL_AMBIENT_AND_DIFFUSE,dark.col);
	glBegin(GL_QUADS);
	glVertex3f(size*(numerator-0.5*denominator),size*height,0.0);
	glVertex3f(size*(numerator-0.5*denominator),-size*height,0.0);
	glVertex3f(0.5*size*denominator,-size*height,0.0);
	glVertex3f(0.5*size*denominator,size*height,0.0);
	glEnd();
	glBegin(GL_QUADS);
	glColor3f(1.0f,0.0f,0.0f);
	glVertex3f(size*(numerator-0.5*denominator),size*height,0.0);
	glVertex3f(size*(numerator-0.5*denominator),-size*height,0.0);
	glVertex3f(-0.5*size*denominator,size*height,0.0);
	glVertex3f(-0.5*size*denominator,-size*height,0.0);
	glEnd();


	glMaterialfv(GL_FRONT,GL_AMBIENT_AND_DIFFUSE,color.col);
	glBegin(GL_QUADS);
	glVertex3f(-0.5*size*denominator,size*height,0);
	glVertex3f(-0.5*size*denominator,-size*height,0);
	glVertex3f(size*(numerator-0.5*denominator),-size*height,0);
	glVertex3f(size*(numerator-0.5*denominator),size*height,0);
	glEnd();
	glMaterialfv(GL_FRONT,GL_AMBIENT_AND_DIFFUSE,ListBar::color(1.0,1.0,1.0,1.0).col);
}
