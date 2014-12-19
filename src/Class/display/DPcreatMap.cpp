#include <DPcreatMap.h>

DPcreatMap::DPcreatMap(ButtonList* _SLB,Field *_field,Mouse *_mou) : DPfield(_mou){
prepare_list();
SLB=_SLB;
look.y=0.5;look.x=0.5;look.z=0.5;
zoom=1.0f;
set_field(_field);
}
DPcreatMap::~DPcreatMap() {

}
void DPcreatMap::prepare_list(){

}

void DPcreatMap::dp_field(){
	dp_map();
}


void DPcreatMap::display(){

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(30*zoom, ((float)s_width/(float)s_height), 0.03, 50);
	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity();
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	//glPolygonMode (GL_FRONT,GL_LINE  );//GL_POINT //GL_FILL

	glLoadIdentity();
	prepare_lighting();

	//look_y=0.1*field->map->MSY();
	dp_button();

	dp_message_box();

	dp_field();

	glutSwapBuffers();


}

