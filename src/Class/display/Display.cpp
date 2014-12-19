#include "Display.h"

Display::Display(Mouse *_mou) {
	mou=_mou;
	light_dis=4.0,light_ver=0.1,light_hori=0.0;
	distance=3.0,horizontal=-1.9,vertical=0.9f;
	look.x=0;look.y=0;look_dy=0.0;look.z=0;look_v.x=0,look_v.y=0,look_v.z=0;
	v_hori=0.0,v_ver=0.0;v_dis=0;
	zoom=1.0f;
	s_width=1280,s_height=720;
	look_minx=-0.5,look_miny=-400.0,look_minz=-0.5,look_maxx=999.0,look_maxy=999.0,look_maxz=999.0;
	SLB=0;
	dp_range=0;
	r_finished=true;
	MSB=new Messagebox();
}
Display::~Display() {
	delete MSB;
}
void Display::timer_tic(){

}
void Display::tic(){
	horizontal+=v_hori;
	vertical+=v_ver;
	if((v_dis>0&&distance<10)||(v_dis<0&&distance>0.1))distance+=v_dis;

	if((look_v.x<0&&look.x>look_minx)||(look_v.x>0&&look.x<look_maxx))look.x+=look_v.x;
	else look_v.x*=-0.9;
	if((look_v.y<0&&look_dy>look_miny)||(look_v.y>0&&look_dy<look_maxy))look_dy+=look_v.y;
	else look_v.y*=-0.9;
	if((look_v.z<0&&look.z>look_minz)||(look_v.z>0&&look.z<look_maxz))look.z+=look_v.z;
	else look_v.z*=-0.9;
	if(distance<0.1)distance=0.1;
	if(horizontal>PI)horizontal-=2*PI;
	if(horizontal<-PI)horizontal+=2*PI;

	if(vertical>0.79*PI)vertical=0.79*PI;
	if(vertical<0.0001)vertical=0.0001*PI;

	look_v.x*=0.9;
	look_v.y*=0.9;
	look_v.z*=0.9;

	v_hori*=0.9;
	v_ver*=0.9;
	v_dis*=0.9;

	MSB->tic();
}
bool Display::render_finished()const{
	return r_finished;
}
void Display::dp_message_box(){
	MSB->dp_message_box();
}
void Display::dp_button(){

	SLB->dp_all_buttons();
	//clock_t start_time=clock(),time_cost;
	compute_mouse_flat_pos();
	//time_cost=(clock()-start_time);
	//printf("render_but_time_cost=%lfsec\n",(double)time_cost/(double)(CLOCKS_PER_SEC));

}
void Display::compute_mouse_location(){
	GLint viewport[4];
	GLdouble modelview[16];
	GLdouble projection[16];
	GLfloat winX, winY, winZ;
	GLdouble posX, posY, posZ;

	glGetIntegerv(GL_VIEWPORT, viewport);
	glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
	glGetDoublev(GL_PROJECTION_MATRIX, projection);
	winX = (float)mou->x;
	winY = (float)viewport[3]-mou->y;
	glReadPixels(winX, (int)winY, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ);
	gluUnProject(winX, winY, winZ, modelview, projection, viewport, &posX, &posY, &posZ);

	mou->px=posX;
	mou->py=posY;
	mou->pz=posZ;
	if(mou->px<0)mou->px=0;
	if(mou->py<0)mou->py=0;
	if(mou->pz<0)mou->pz=0;
	//printf("x=%f y=%f z=%f\n",mdx,mdy,mdz);
}
void Display::compute_mouse_flat_pos(){
	GLint viewport[4];
	GLdouble modelview[16];
	GLdouble projection[16];
	GLfloat winX, winY, winZ;
	GLdouble posX, posY, posZ;
	glGetIntegerv(GL_VIEWPORT, viewport);
	glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
	glGetDoublev(GL_PROJECTION_MATRIX, projection);
	winX = (float)mou->x;
	winY = (float)viewport[3]-mou->y;

	glReadPixels(winX, (int)winY, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ);
	gluUnProject(winX, winY, winZ, modelview, projection, viewport, &posX, &posY, &posZ);
	if(fabs(posZ)<0.101&&fabs(posZ)>0.0999){
		mou->fx=posX;
		mou->fy=posY;
	}else{
		mou->fx=99999999.0;
		mou->fy=99999999.0;
	}
	//printf("posZ=%f\n",posZ);
}
void Display::dp_prepare(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(30*zoom, ((float)s_width/(float)s_height), 0.1, 50);
	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity();
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	glLoadIdentity();
	prepare_lighting();
}
void Display::Materialfv(){
	GLfloat mat_ambient[] = {1.0, 1.0, 1.0, 1.0};
	GLfloat mat_diffuse[] = {1.0, 1.0, 1.0, 1.0};
	GLfloat mat_specular[] =  {1.0, 1.0, 1.0, 1.0};
	GLfloat hig_shininess[] = {100.0};
	GLfloat mat_emission[] = {0.01,0.01, 0.01, 1.0};

	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT,GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT,GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT,GL_SHININESS, hig_shininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
}
void Display::lighting0(){
	GLfloat light_diffuse[4] = { 0.3, 0.25, 0.25, 1.0 };
	GLfloat light_ambient[4]  = { 0.03, 0.0, 0.0, 1.0};
	GLfloat light_specular[4] = { 0.63, 0.58, 0.58, 1.0};

	GLfloat light_position[4] = { light_dis*sinf(light_ver+vertical)*cosf(light_hori+horizontal),
			light_dis*cosf(light_ver+vertical),
			light_dis*sinf(light_ver+vertical)*sinf(light_hori+horizontal), 0 };
	//glPolygonMode ( GL_FRONT ,GL_LINE  );//GL_POINT //GL_FILL

	glLightfv( GL_LIGHT0, GL_AMBIENT, light_ambient);//(Ambient Light)
	glLightfv( GL_LIGHT0, GL_SPECULAR,light_specular);//(Specular Light)
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glEnable (GL_LIGHT0);
}
void Display::lighting1(){
	GLfloat light_diffuse[4] = { 0.07, 0.1, 0.1, 1.0 };
	GLfloat light_ambient[4]  = { 0.03, 0.03, 0.03, 1.0};
	GLfloat light_specular[4] = { 0.03, 0.03, 0.03, 1.0};

	GLfloat light_pos[4] = { 10,10,10,0};
	glLightfv( GL_LIGHT1, GL_DIFFUSE, light_ambient);//(Ambient Light)
	glLightfv( GL_LIGHT1, GL_SPECULAR,light_specular);//(Specular Light)
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT1, GL_POSITION, light_pos);
	glEnable(GL_LIGHT1);
}
void Display::lighting2(){
	GLfloat light_diffuse[4] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_ambient[4]  = { 1.0, 1.0, 1.0, 1.0};
	GLfloat light_specular[4] = { 1.0, 1.0, 1.0, 1.0};
	GLfloat light_pos[4] = { light_dis*sinf(light_ver)*cosf(light_hori),
				light_dis*cosf(light_ver),
				light_dis*sinf(light_ver)*sinf(light_hori), 0 };
	glLightfv( GL_LIGHT2, GL_AMBIENT, light_ambient);//(Ambient Light)
	glLightfv( GL_LIGHT2, GL_SPECULAR,light_specular);//(Specular Light)
	glLightfv(GL_LIGHT2, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT2, GL_POSITION, light_pos);
	glDisable(GL_LIGHT2);
}
void Display::lighting3(){
	GLfloat light_diffuse[4] = { 0.05, 0.08, 0.08, 1.0 };
	GLfloat light_ambient[4]  = { 0.02, 0.03, 0.03, 1.0};
	GLfloat light_specular[4] = { 0.02, 0.03, 0.03, 1.0};

	GLfloat light_pos[4] = { -light_dis*sinf(light_ver+vertical)*cosf(light_hori+horizontal),
			light_dis*cosf(light_ver+vertical),
			light_dis*sinf(light_ver+vertical)*sinf(light_hori+horizontal), 0 };
	glLightfv( GL_LIGHT3, GL_AMBIENT, light_ambient);//(Ambient Light)
	glLightfv( GL_LIGHT3, GL_SPECULAR,light_specular);//(Specular Light)
	glLightfv(GL_LIGHT3, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT3, GL_POSITION, light_pos);
	glEnable(GL_LIGHT3);
}
void Display::lighting4(){
	GLfloat light_diffuse[4] = { 0.07, 0.1, 0.1, 1.0 };
	GLfloat light_ambient[4]  = { 0.1, 0.1, 0.1, 1.0};
	GLfloat light_specular[4] = { 0.1, 0.1, 0.1, 1.0};

	GLfloat light_pos[4] = { -light_dis*sinf(light_ver)*cosf(light_hori),
				light_dis*cosf(light_ver),
				-light_dis*sinf(light_ver)*sinf(light_hori), 0 };
	glLightfv( GL_LIGHT4, GL_AMBIENT, light_ambient);//(Ambient Light)
	glLightfv( GL_LIGHT4, GL_SPECULAR,light_specular);//(Specular Light)
	glLightfv(GL_LIGHT4, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT4, GL_POSITION, light_pos);
	glEnable(GL_LIGHT4);
}
void Display::lighting5(){
	GLfloat light_diffuse[4] = { 0.9, 0, 0, 1.0 };
	GLfloat light_ambient[4]  = { 0.9, 0, 0, 1.0};
	GLfloat light_specular[4] = { 0.9, 0, 0, 1.0};

	GLfloat light_pos[4] = { light_dis*sinf(light_ver)*cosf(light_hori),
				light_dis*cosf(light_ver),
				light_dis*sinf(light_ver)*sinf(light_hori), 0 };
	glLightfv( GL_LIGHT5, GL_AMBIENT, light_ambient);//(Ambient Light)
	glLightfv( GL_LIGHT5, GL_SPECULAR,light_specular);//(Specular Light)
	glLightfv(GL_LIGHT5, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT5, GL_POSITION, light_pos);
}
void Display::lighting6(){
	GLfloat light_diffuse[4] = { 0, 0.9, 0, 1.0 };
	GLfloat light_ambient[4]  = { 0, 0.9, 0, 1.0};
	GLfloat light_specular[4] = { 0, 0.9, 0, 1.0};

	GLfloat light_pos[4] = { light_dis*sinf(light_ver)*cosf(light_hori),
				light_dis*cosf(light_ver),
				light_dis*sinf(light_ver)*sinf(light_hori), 0 };
	glLightfv( GL_LIGHT6, GL_AMBIENT, light_ambient);//(Ambient Light)
	glLightfv( GL_LIGHT6, GL_SPECULAR,light_specular);//(Specular Light)
	glLightfv(GL_LIGHT6, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT6, GL_POSITION, light_pos);

}
void Display::prepare_lighting() {
	glLoadIdentity();
	const GLfloat glfLightSperef[4]={1,1,1,1};
	GLfloat normalVector[]={1,1,1};
	glMaterialfv(GL_FRONT,GL_SPECULAR,glfLightSperef) ;
	glNormal3fv(normalVector);

	lighting0();
	lighting1();
	lighting2();
	lighting3();
	//lighting4();
	lighting5();
	lighting6();
	Materialfv();
}
void Display::light_off(){
	glDisable(GL_LIGHT0);
	glDisable(GL_LIGHT1);
	glDisable(GL_LIGHT3);
	//glDisable(GL_LIGHT4);
}
void Display::light_on(){
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHT3);
	//glEnable(GL_LIGHT4);
}
void Display::window_resize(int w,int h){
	s_width=w;s_height=h;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0,0,s_width,s_height);
	gluPerspective(30*zoom, ((float)s_width/(float)s_height), 0.1, 50);
	glMatrixMode(GL_MODELVIEW);
}
void Display::look_at_func(){
	gluLookAt(distance*sinf(vertical)*cosf(horizontal),
			  distance*cosf(vertical),
			  distance*sinf(vertical)*sinf(horizontal),
			  0.0,0.0,0.0,
			  0.0,1.0,0.0);
	glTranslatef(-look.x,-look.y,-look.z);
}


