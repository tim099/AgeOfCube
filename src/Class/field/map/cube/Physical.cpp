#include "Physical.h"

Physical::Physical(double _x,double _y,double _z) {
set_pos(_x,_y,_z);
ry=0;
size=1.0;
density=1.0;
}
Physical::~Physical() {

}
void Physical::save_physical(FILE* fop){
	fprintf(fop,"%lf %lf %lf ",pos.x,pos.y,pos.z);
	fprintf(fop,"%lf %lf %lf ",v.x,v.y,v.z);
	fprintf(fop,"%lf %lf ",ry,size);
}
void Physical::load_physical(FILE* fop){
	fscanf(fop,"%lf %lf %lf ",&pos.x,&pos.y,&pos.z);
	fscanf(fop,"%lf %lf %lf ",&v.x,&v.y,&v.z);
	fscanf(fop,"%lf %lf ",&ry,&size);
}
void Physical::accelerate_by_a(double dvx,double dvy,double dvz){
	double dv=sqrt(dvx*dvx+dvy*dvy+dvz*dvz);
	if(fabs(dv)<0.0001)return;
	accelerate(max_a()*dvx/dv,max_a()*dvy/dv,max_a()*dvz/dv);
}
void Physical::freeze(){
	v.x=0;
	v.y=0;
	v.z=0;
}
void Physical::accelerate(double dvx,double dvy,double dvz){
	set_v(v.x+dvx,v.y+dvy,v.z+dvz);
}
void Physical::set_v(double _vx,double _vy,double _vz){
	v.x=_vx;
	v.y=_vy;
	v.z=_vz;
	double vel=sqrt(v.x*v.x+v.y*v.y+v.z*v.z);
	if(vel>max_v()){
		v.x*=(max_v()/vel);
		v.y*=(max_v()/vel);
		v.z*=(max_v()/vel);
	}
}
void Physical::set_pos(double _x,double _y,double _z){
		prev.x=pos.x;prev.y=pos.y;prev.z=pos.z;
		pos.x=_x;pos.y=_y;pos.z=_z;
}
void Physical::set_ry(double _ry){ry=_ry;}
PosDouble Physical::get_pos()const{
	return pos;
}
int Physical::convert_pos_x(double x)const{if(x>=0.0)return (10*x);else return -1;}
int Physical::convert_pos_y(double y)const{if(y>=0.0)return (10*y);else return -1;}
int Physical::convert_pos_z(double z)const{if(z>=0.0)return (10*z);else return -1;}
double Physical::get_size()const{return 0.02*size;}
double Physical::get_mass()const{return density*size*size*size;}
double Physical::max_v()const{return 0.01;}
double Physical::max_a()const{return 0.002;}
double Physical::get_v()const{return sqrt(v.x*v.x+v.y*v.y+v.z*v.z);}
double Physical::get_vx()const{return v.x;}
double Physical::get_vy()const{return v.y;}
double Physical::get_vz()const{return v.z;}
double Physical::get_x()const{return pos.x;}
double Physical::get_y()const{return pos.y;}
double Physical::get_z()const{return pos.z;}
double Physical::get_ry()const{return ry;}
int Physical::prev_in_x()const{return convert_pos_x(prev.x);}
int Physical::prev_in_y()const{return convert_pos_y(prev.y);}
int Physical::prev_in_z()const{return convert_pos_z(prev.z);}
int Physical::in_x()const{return convert_pos_x(pos.x);}
int Physical::in_y()const{return convert_pos_y(pos.y);}
int Physical::in_z()const{return convert_pos_z(pos.z);}
int Physical::on_x()const{return in_x();}
int Physical::on_y()const{return (in_y()-1);}
int Physical::on_z()const{return in_z();}
