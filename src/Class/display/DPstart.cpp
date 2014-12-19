
#include "DPstart.h"

DPstart::DPstart(ButtonList *_SLB,Mouse *mou) : Display(mou){
prepare_list();//
SLB=_SLB;

zoom=1.0f;
s_width=1280,s_height=720;
}
void DPstart::prepare_list(){
fonts= new ListFonts();
}
DPstart::~DPstart() {
delete fonts;
}
void DPstart::dp_texture(){
	glPushMatrix();
	glTranslatef(0,0,-0.1);
	glPushMatrix();
	glTranslatef(0,-0.01,0);
	glPopMatrix();
	glPopMatrix();
}

void DPstart::display(){
	dp_prepare();
	//glPolygonMode (GL_FRONT,GL_LINE  );//GL_POINT //GL_FILL
	dp_button();
	dp_texture();

	glutSwapBuffers();
}


