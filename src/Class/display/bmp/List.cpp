#include "List.h"

List::List(double size,int _list_type,double _lpx,double _lpy,double _list_size) : ListFonts(size){
	creat_all_list();
	list_type=_list_type;
	list_size=_list_size;
	lpx=_lpx;lpy=_lpy;
	resource=0;
	tmp_res=false;
	res_x=0.0;res_y=0.0;
}
List::~List() {
	clear_dp_resources();
	clear_temp_str();
	while(!Lstrs.empty()){
		delete Lstrs.front();
		Lstrs.pop();
	}
}
void List::creat_all_list(){
	GLuint list;
	list=creat_texture_bysize("files/texture/lists/List.bmp",0.029,270,0);
	Lists.push_back(list);
	list=creat_texture_bysize("files/texture/lists/List01.bmp",0.058,270,0);
	Lists.push_back(list);
}
void List::push_str(std::string str,double px,double py){
	Lstr *l = new Lstr();
	l->str = new std::string(str);
	l->pos_x=px;
	l->pos_y=py;
	Lstrs.push(l);
}
void List::push_str(std::string *str,double px,double py){
	Lstr *l = new Lstr();
	l->str = str;
	l->pos_x=px;
	l->pos_y=py;
	Lstrs.push(l);
}
void List::push_temp_str(std::string str,double px,double py){
	Lstr *l = new Lstr();
	l->str = new std::string(str);
	l->pos_x=px;
	l->pos_y=py;
	temp_strs.push(l);
}
void List::push_temp_str(std::string *str,double px,double py){
	Lstr *l = new Lstr();
	l->str = str;
	l->pos_x=px;
	l->pos_y=py;
	temp_strs.push(l);
}
void List::clear_dp_resources(){
	if(resource!=0&&tmp_res)delete resource;
	resource=0;
	tmp_res=false;
}
void List::clear(){
	clear_dp_resources();
	clear_temp_str();
}
void List::push_resources(Resource *_resource,double _res_x,double _res_y){
	clear_dp_resources();
	res_x=_res_x;res_y=_res_y;
	resource=_resource;
}
void List::push_resources(Resource _resource,double _res_x,double _res_y){
	clear_dp_resources();
	res_x=_res_x;res_y=_res_y;
	tmp_res=true;
	resource = new Resource(_resource);
}
void List::dp_resources(){
	double dis_x=0.016;
	double dis_y=-0.003;
	int dx=0,dy=0,mdy=3;
	if(resource==0)return;
	glPushMatrix();
	glTranslatef(res_x,res_y,0);
	for(int i=0;i<TOTAL_RESOURCES;i++){
		if(resource->res_num(i)!=0){
			glPushMatrix();
			glTranslatef(dis_x*(double)dx,dis_y*(double)dy,0);
			glCallList(TEX_R_CUBE+i);
			glTranslatef(0.5*dis_x,0,0);
			call_string(resource->res_num(i));
			glPopMatrix();
			dy++;
			if(dy>mdy){
				dy=0;
				dx++;
			}
		}
	}
	glPopMatrix();
}
void List::clear_temp_str(){
	while(!temp_strs.empty()){
		delete temp_strs.front();
		temp_strs.pop();
	}
}
void List::dp_list(){
	glEnable(GL_LIGHT2);
	glPushMatrix();
	glLoadIdentity();
	glTranslatef(lpx,lpy,-0.1);
	unsigned size;
	Lstr *l;
	size=Lstrs.size();
	for(unsigned i=0;i<size;i++){
		l=Lstrs.front();
		Lstrs.pop();
		glPushMatrix();
		glTranslatef(l->pos_x,l->pos_y,0);
		call_string(l->str->c_str());
		glPopMatrix();
		Lstrs.push(l);
	}
	size=temp_strs.size();
	for(unsigned i=0;i<size;i++){
		l=temp_strs.front();
		temp_strs.pop();
		glPushMatrix();
		glTranslatef(l->pos_x,l->pos_y,0);
		call_string(l->str->c_str());
		glPopMatrix();
		temp_strs.push(l);

	}
	dp_resources();
	glPushMatrix();
	glTranslatef(0,0,-0.01);
	glCallList(Lists.at(list_type));
	glPopMatrix();

	glPopMatrix();
	glDisable(GL_LIGHT2);
}
