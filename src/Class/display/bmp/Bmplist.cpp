#include <Bmplist.h>

Bmplist::Bmplist() {

}
Bmplist::~Bmplist() {
	while(!all_tex.empty()){
		glDeleteTextures(1,&all_tex.front());
		all_tex.pop();
	}
	while(!all_texture.empty()){
		glDeleteLists(all_texture.front(),1);
		all_texture.pop();
	}
}
Bmp* Bmplist::creat_tex(const char *path){
	Bmp *bmp=new Bmp();
	bmp->prepare_tex(path);
	all_tex.push((bmp->tex));
	return bmp;
}
void Bmplist::dp_tex(Bmp* bmp,double w,double h,double rx,double ry){
	//glPushMatrix();
	glRotatef(ry,0,1,0);
	glRotatef(rx,1,0,0);
	glBindTexture(GL_TEXTURE_2D,bmp->tex);
	glEnable(GL_TEXTURE_2D);
	glBegin(GL_QUADS);
	glTexCoord3f( 0,0,0); glVertex3f(-w,0,-h);
	glTexCoord3f( bmp->pw,0,0); glVertex3f(w,0,-h);
	glTexCoord3f( bmp->pw,bmp->ph,0); glVertex3f(w,0,h);
	glTexCoord3f( 0,bmp->ph,0); glVertex3f(-w,0,h);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	//glPopMatrix();
}
GLuint Bmplist::creat_texture_bysize(const char *path,double size,double rx,double ry){
	Bmp bmp;
	bmp.prepare_tex(path);
	all_tex.push((bmp.tex));
	double w=bmp.pw;
	double h=bmp.ph;
	size/=(w>h?w:h);
	GLuint list;
	list = glGenLists(1);
	glNewList(list,GL_COMPILE);
	glPushMatrix();
	glRotatef(rx,1,0,0);
	glRotatef(ry,0,1,0);
	glBindTexture(GL_TEXTURE_2D,bmp.tex);
	glEnable(GL_TEXTURE_2D);
	glBegin(GL_QUADS);
	glTexCoord3f( 0,0,0); glVertex3f(-size*w,0,-size*h);
	glTexCoord3f( w,0,0); glVertex3f(size*w,0,-size*h);
	glTexCoord3f( w,h,0); glVertex3f(size*w,0,size*h);
	glTexCoord3f( 0,h,0); glVertex3f(-size*w,0,size*h);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	glEndList();
	all_texture.push(list);
	return list;
}
void Bmplist::creat_cube_bysize(const char *path,GLuint list,double size){
	Bmp bmp;
	bmp.prepare_tex(path);
	all_tex.push((bmp.tex));
	double w=bmp.pw;
	double h=bmp.ph;
	size/=(w>h?w:h);
	glNewList(list,GL_COMPILE);
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D,bmp.tex);
	glEnable(GL_TEXTURE_2D);
	glBegin(GL_QUADS);
	glTexCoord3f( 0,0,0); glVertex3f(-size,0,-size);
	glTexCoord3f( w,0,0); glVertex3f(size,0,-size);
	glTexCoord3f( w,h,0); glVertex3f(size,0,size);
	glTexCoord3f( 0,h,0); glVertex3f(-size,0,size);
	glEnd();

	glBindTexture(GL_TEXTURE_2D,bmp.tex);
	glBegin(GL_QUADS);
	glTexCoord3f( 0,0,0); glVertex3f(-size,2*size,-size);
	glTexCoord3f( w,0,0); glVertex3f(size,2*size,-size);
	glTexCoord3f( w,h,0); glVertex3f(size,2*size,size);
	glTexCoord3f( 0,h,0); glVertex3f(-size,2*size,size);
	glEnd();

	glBindTexture(GL_TEXTURE_2D,bmp.tex);
	glBegin(GL_QUADS);
	glTexCoord3f( 0,0,0); glVertex3f(-size,2*size,-size);
	glTexCoord3f( w,0,0); glVertex3f(size,2*size,-size);
	glTexCoord3f( w,h,0); glVertex3f(size,0,-size);
	glTexCoord3f( 0,h,0); glVertex3f(-size,0,-size);
	glEnd();

	glBindTexture(GL_TEXTURE_2D,bmp.tex);
	glBegin(GL_QUADS);
	glTexCoord3f( 0,0,0); glVertex3f(size,2*size,size);
	glTexCoord3f( w,0,0); glVertex3f(-size,2*size,size);
	glTexCoord3f( w,h,0); glVertex3f(-size,0,size);
	glTexCoord3f( 0,h,0); glVertex3f(size,0,size);
	glEnd();

	glBindTexture(GL_TEXTURE_2D,bmp.tex);
	glBegin(GL_QUADS);
	glTexCoord3f( 0,0,0); glVertex3f(-size,2*size,size);
	glTexCoord3f( w,0,0); glVertex3f(-size,2*size,-size);
	glTexCoord3f( w,h,0); glVertex3f(-size,0,-size);
	glTexCoord3f( 0,h,0); glVertex3f(-size,0,size);
	glEnd();

	glBindTexture(GL_TEXTURE_2D,bmp.tex);
	glBegin(GL_QUADS);
	glTexCoord3f( 0,0,0); glVertex3f(size,2*size,-size);
	glTexCoord3f( w,0,0); glVertex3f(size,2*size,size);
	glTexCoord3f( w,h,0); glVertex3f(size,0,size);
	glTexCoord3f( 0,h,0); glVertex3f(size,0,-size);
	glEnd();

	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
	glEndList();
	all_texture.push(list);
	return;
}
void Bmplist::creat_texture_bysize(const char *path,GLuint list,double size,double rx,double ry){
	Bmp bmp;
	bmp.prepare_tex(path);
	all_tex.push((bmp.tex));
	double w=bmp.pw;
	double h=bmp.ph;
	size/=(w>h?w:h);
	glNewList(list,GL_COMPILE);
	glPushMatrix();
	glRotatef(rx,1,0,0);
	glRotatef(ry,0,1,0);
	glBindTexture(GL_TEXTURE_2D,bmp.tex);
	glEnable(GL_TEXTURE_2D);
	glBegin(GL_QUADS);
	glTexCoord3f( 0,0,0); glVertex3f(-size*w,0,-size*h);
	glTexCoord3f( w,0,0); glVertex3f(size*w,0,-size*h);
	glTexCoord3f( w,h,0); glVertex3f(size*w,0,size*h);
	glTexCoord3f( 0,h,0); glVertex3f(-size*w,0,size*h);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	glEndList();
	all_texture.push(list);
	return;
}
GLuint Bmplist::creat_texture(const char *path,double size,double rx,double ry){
	Bmp bmp;
	bmp.prepare_tex(path);
	all_tex.push((bmp.tex));
	GLuint list;
	list = glGenLists(1);
	double w=bmp.pw;
	double h=bmp.ph;

	//printf("%s :w=%lf,h=%lf,list=%d\n",path,w,h,list);
	glNewList(list,GL_COMPILE);
	glPushMatrix();
	glRotatef(rx,1,0,0);
	glRotatef(ry,0,1,0);
	glBindTexture(GL_TEXTURE_2D,bmp.tex);

	glEnable(GL_TEXTURE_2D);
	glBegin(GL_QUADS);
	glTexCoord3f( 0,0,0); glVertex3f(-size*w,0,-size*h);
	glTexCoord3f( w,0,0); glVertex3f(size*w,0,-size*h);
	glTexCoord3f( w,h,0); glVertex3f(size*w,0,size*h);
	glTexCoord3f( 0,h,0); glVertex3f(-size*w,0,size*h);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	glEndList();
	all_texture.push(list);
	return list;
}
GLuint Bmplist::creat_texture(const char *path,double size,double &width,double &height,double rx,double ry){
	Bmp bmp;
	bmp.prepare_tex(path);
	all_tex.push((bmp.tex));
	double w=bmp.pw;
	double h=bmp.ph;

	GLuint list;
	list = glGenLists(1);
	//printf("%s :w=%lf,h=%lf,list=%d\n",path,w,h,list);
	glNewList(list,GL_COMPILE);
	glPushMatrix();
	glRotatef(rx,1,0,0);
	glRotatef(ry,0,1,0);
	glBindTexture(GL_TEXTURE_2D,bmp.tex);
	glEnable(GL_TEXTURE_2D);
	glBegin(GL_QUADS);
	glTexCoord3f( 0,0,0); glVertex3f(-size*w,0,-size*h);
	glTexCoord3f( w,0,0); glVertex3f(size*w,0,-size*h);
	glTexCoord3f( w,h,0); glVertex3f(size*w,0,size*h);
	glTexCoord3f( 0,h,0); glVertex3f(-size*w,0,size*h);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	glEndList();

	width=size*w;
	height=size*h;

	all_texture.push(list);
	return list;
}


