#include "Collidable.h"
#include "CubeCreature.h"
#include "map/Map.h"
#include "CollisionEffect.h"
#include "CreatureMap.h"
Collidable::Collidable(double _x,double _y,double _z,std::vector<Collidable*>*_colli_v,Map *_map)
:Physical(_x,_y,_z){
	colli_v=_colli_v;
	map=_map;
}
Collidable::~Collidable() {

}
int Collidable::colli_state()const{
	return C_STATE_COLLI_ON;
}
void Collidable::set_pos(double _x,double _y,double _z){
		prev.x=pos.x;prev.y=pos.y;prev.z=pos.z;
		pos.x=_x;pos.y=_y;pos.z=_z;
}
void Collidable::save_colli(FILE *fop){
	save_physical(fop);
}
void Collidable::load_colli(FILE *fop){
	load_physical(fop);
}
bool Collidable::collide(Collidable* cube_b)const{
	double dx,dy,dz,dis;

	if(this!=cube_b&&(colli_state()!=C_STATE_COLLI_OFF)&&(cube_b->colli_state()!=C_STATE_COLLI_OFF)){
		double total_size=cube_b->get_size()+get_size();
		dx=get_x()-cube_b->get_x();
		dz=get_z()-cube_b->get_z();
		dy=get_y()-cube_b->get_y();
		dis=sqrt(dx*dx+dy*dy+dz*dz);
		if(dis<total_size)return true;
	}
	return false;
}
bool Collidable::pre_collide(Collidable* cube_b)const{
	double dx,dy,dz,dis;
	if(this!=cube_b&&cube_b->colli_state()!=C_STATE_COLLI_OFF){
		double size=cube_b->get_size()+get_size();
		dx=(get_x()+get_vx())-(cube_b->get_x()+cube_b->get_vx());
		if(fabs(dx)<size){
			dz=(get_z()+get_vz())-(cube_b->get_z()+cube_b->get_vz());
			if(fabs(dz)<size){
				dy=(get_y()+get_vy())-(cube_b->get_y()+cube_b->get_vy());
				if(fabs(dy)<size){
					dis=sqrt(dx*dx+dy*dy+dz*dz);
					if(dis<size){
						return true;
					}
				}
			}
		}
	}
	return false;
}
Collidable* Collidable::detect_colli_creature()const{
	std::vector<CubeCreature*>*creature_v;
	int x=in_x(),y=in_y(),z=in_z();
	for(int i=-(1+floor(10*get_size()));i<=(1+floor(10*get_size()));i++){
		for(int j=-(1+floor(10*get_size()));j<=(1+floor(10*get_size()));j++){
			for(int k=-(1+floor(10*get_size()));k<=(1+floor(10*get_size()));k++){
				creature_v=map->creature_map->get_creature_map(x+i,y+j,z+k);
				for(unsigned i=0;i<creature_v->size();i++){
					if(collide(creature_v->at(i))){
						return creature_v->at(i);
					}
				}
			}
		}
	}/*
	for(unsigned i=0;i<colli_v->size();i++){
		if(collide(colli_v->at(i),cube)){
			return colli_v->at(i);
		}
	}*/
	return 0;
}
unsigned Collidable::detect_colli_map(Collidable* cube)const{
	unsigned colli_type=COLLI_NULL;
	unsigned char path=map->get_path()->get_path(cube->prev_in_x(),cube->prev_in_y(),cube->prev_in_z());
	unsigned char path_on=map->get_map(cube->prev_in_x(),cube->prev_in_y()-1,cube->prev_in_z())->get_path();
	int dx=cube->in_x()-cube->prev_in_x();
	int dy=cube->in_y()-cube->prev_in_y();
	int dz=cube->in_z()-cube->prev_in_z();
	if(dx!=0&&dz!=0){
		unsigned char path_next=map->get_path()->get_path(cube->in_x(),cube->in_y(),cube->in_z());
		if(dx>0&&dz>0){
			if(!(path_next&M_LEFT)||!(path_next&M_BACK)){
				colli_type|=COLLI_RIGHT;
				colli_type|=COLLI_FRONT;
			}
		}
		if(dx>0&&dz<0){
			if(!(path_next&M_LEFT)||!(path_next&M_FRONT)){
				colli_type|=COLLI_RIGHT;
				colli_type|=COLLI_BACK;
			}
		}
		if(dx<0&&dz>0){
			if(!(path_next&M_RIGHT)||!(path_next&M_BACK)){
				colli_type|=COLLI_LEFT;
				colli_type|=COLLI_FRONT;
			}
		}
		if(dx<0&&dz<0){
			if(!(path_next&M_RIGHT)||!(path_next&M_FRONT)){
				colli_type|=COLLI_LEFT;
				colli_type|=COLLI_BACK;
			}
		}
	}

	if(dx>0){
		if(!(path&M_RIGHT))colli_type|=COLLI_RIGHT;
	}
	if(dx<0){
		if(!(path&M_LEFT))colli_type|=COLLI_LEFT;
	}
	if(dy>0){
		if(!(path&M_UP))colli_type|=COLLI_UP;
	}
	if(dy<0){
		if(!(path&M_DOWN))colli_type|=COLLI_DOWN;
	}
	if(dz>0){
		if(!(path&M_FRONT))colli_type|=COLLI_FRONT;
	}
	if(dz<0){
		if(!(path&M_BACK))colli_type|=COLLI_BACK;
	}

	if(!(path&M_LIFTABLE)){
		if(!(path_on&M_LIFTABLE)&&(10*pos.y-floor(10*pos.y)>0.1))colli_type|=COLLI_DROP;
		else if((10*pos.y-floor(10*pos.y)>0.5))colli_type|=COLLI_DROP;
		if(!(path_on&M_STANDABLE))colli_type|=COLLI_DROP;
	}


	return colli_type;
}
void Collidable::handle_stuck(){
	if(detect_stuck(in_x(),in_y(),in_z())){
		if(10*pos.x-floor(10*pos.x)>0.5){
			if(!detect_stuck(in_x()+1,in_y(),in_z())){//success!!
				set_pos(0.1*(in_x()+1),pos.y,pos.z);
				return;
			}
		}else{
			if(!detect_stuck(in_x()-1,in_y(),in_z())){//success!!
				set_pos(0.1*(in_x()-1),pos.y,pos.z);
				return;
			}
		}
		if(10*pos.y-floor(10*pos.y)>0.5){
			if(!detect_stuck(in_x(),in_y()+1,in_z())){//success!!
				set_pos(pos.x,0.1*(in_y()+1),pos.z);
				return;
			}
		}else{
			if(!detect_stuck(in_x(),in_y()-1,in_z())){//success!!
				set_pos(pos.x,0.1*(in_y()-1),pos.z);
				return;
			}
		}
		if(10*pos.z-floor(10*pos.z)>0.5){
			if(!detect_stuck(in_x(),in_y(),in_z()+1)){//success!!
				set_pos(pos.x,pos.y,0.1*(in_z()+1));
				return;
			}
		}else{
			if(!detect_stuck(in_x(),in_y(),in_z()-1)){//success!!
				set_pos(pos.x,pos.y,0.1*(in_z()-1));
				return;
			}
		}
		for(int i=-4;i<=4;i++){
			for(int j=-4;j<=4;j++){
				for(int k=-4;k<=4;k++){
					if(!detect_stuck(in_x()+i,in_y()+j,in_z()+k)){
						set_pos(0.1*(in_x()+i),0.1*(in_y()+j),0.1*(in_z()+k));
						return;
					}
				}
			}
		}
		printf("stuck %lf,%lf,%lf",pos.x,pos.y,pos.z);
		printf("cant handle this stuck,%u,%u,%u!!\n",in_x(),in_y(),in_z());
		delete_cube(3);//test
	}
}
bool Collidable::detect_stuck(int x,int y,int z){
	if(map->get_map(x,y,z)->C_TYP()==C_CUBE)return true;
	if(map->get_map(x,y,z)->typ()==C_OUT_OF_EDGE){
		return true;
	}
	return false;
}
bool Collidable::colli_map(){
	unsigned colli_type=detect_colli_map(this);
	if(colli_type){
		if(colli_type&COLLI_DROP){
			accelerate(0,GRAVITY,0);
		}
		if((colli_type&COLLI_RIGHT)||(colli_type&COLLI_LEFT)){
			pos.x=prev.x;
			v.x*=-0.9;
		}
		if((colli_type&COLLI_UP)||(colli_type&COLLI_DOWN)){
			pos.y=prev.y;
			v.y*=-0.2;
		}
		if((colli_type&COLLI_FRONT)||(colli_type&COLLI_BACK)){
			pos.z=prev.z;
			v.z*=-0.9;
		}
		return true;
	}
	return false;
}
bool Collidable::colli_creature(){
	Collidable* colli_obj=detect_colli_creature();
	if(colli_obj){
		pos.x=prev.x;
		pos.y=prev.y;
		pos.z=prev.z;
		colli_obj->be_collide(this->get_colli_effect());//set other object colli by this
		return true;
	}
	return false;
}
bool Collidable::collision(){//collide other
	bool colli=false;
	if(colli_map())colli=true;
	if(colli_creature())colli=true;
	handle_stuck();
	return colli;
}
Effect *Collidable::get_colli_effect(){
	return new CollisionEffect(this);
}
void Collidable::be_collide(Effect *effect){//being collide by cube
	if(effect!=0){
		effect->collision(this);
		delete effect;
	}
}
void Collidable::move_timer_tic(){
	set_pos(pos.x+v.x,pos.y+v.y,pos.z+v.z);
	if(colli_state()!=C_STATE_COLLI_OFF)collision();//do collision
	v.x*=0.8;
	v.y*=0.8;
	v.z*=0.8;
	double vry=(57.2957795*atan2(v.x,v.z)),vel=sqrt(v.x*v.x+v.z*v.z),dry=(vry-ry);
	if(dry>180.0){
		dry-=360;
	}else if(dry<-180.0){
		dry+=360;
	}
	ry+=(vel/(0.04+vel))*dry;
	if(ry>180)ry-=360;
	if(ry<-180)ry+=360;
}
