#include "CollisionEffect.h"
#include "Collidable.h"
CollisionEffect::CollisionEffect(Collidable *_colli_obj) {
	colli_obj=_colli_obj;
}
CollisionEffect::~CollisionEffect() {

}
int CollisionEffect::Effect_type(){
	return E_COLLISION_EFFECT;
}
void CollisionEffect::collision(Collidable* be_colli){
	double x1=colli_obj->get_x(),x2=be_colli->get_x();
	double y1=colli_obj->get_y(),y2=be_colli->get_y();
	double z1=colli_obj->get_z(),z2=be_colli->get_z();
	double dx=x1-x2,dy=y1-y2,dz=z1-z2;
	double dis=sqrt(dx*dx+dy*dy+dz*dz);
	double m1=colli_obj->get_mass(),m2=be_colli->get_mass();
	if(dis<(colli_obj->get_size()+be_colli->get_size())){//in others!!
		if(dis<0.0001){
			colli_obj->set_pos(x1+0.3*colli_obj->get_size(),y1,z1+0.3*colli_obj->get_size());
			be_colli->set_pos(x2-0.3*be_colli->get_size(),y2,z2-0.3*be_colli->get_size());
			return;
		}else{
			double mx=(m1*x1+m2*x2)/(m1+m2);
			double my=(m1*y1+m2*y2)/(m1+m2);
			double mz=(m1*z1+m2*z2)/(m1+m2);
			double dmx1=x1-mx,dmx2=x2-mx;
			double dmy1=y1-my,dmy2=y2-my;
			double dmz1=z1-mz,dmz2=z2-mz;
			double dis_m1=sqrt(dmx1*dmx1+dmy1*dmy1+dmz1*dmz1);
			double dis_m2=sqrt(dmx2*dmx2+dmy2*dmy2+dmz2*dmz2);
			double size1=1.2*colli_obj->get_size(),size2=1.2*be_colli->get_size();
			colli_obj->set_pos(mx+(size1*dmx1/dis_m1),my+(size1*dmy1/dis_m1),mz+(size1*dmz1/dis_m1));
			be_colli->set_pos(mx+(size2*dmx2/dis_m2),my+(size2*dmy2/dis_m2),mz+(size2*dmz2/dis_m2));
			return;
		}
	}
	double vx1=colli_obj->get_vx(),vx2=be_colli->get_vx();
	double vy1=colli_obj->get_vy(),vy2=be_colli->get_vy();
	double vz1=colli_obj->get_vz(),vz2=be_colli->get_vz();
	double mvx=(m1*vx1+m2*vx2)/(m1+m2);//systemic velocity
	double mvy=(m1*vy1+m2*vy2)/(m1+m2);
	double mvz=(m1*vz1+m2*vz2)/(m1+m2);

	double dvx1=vx1-mvx,dvx2=vx2-mvx;
	double dvy1=vy1-mvy,dvy2=vy2-mvy;
	double dvz1=vz1-mvz,dvz2=vz2-mvz;
	double dv1=sqrt(dvx1*dvx1+dvy1*dvy1+dvz1*dvz1);
	double dv2=sqrt(dvx2*dvx2+dvy2*dvy2+dvz2*dvz2);

	double v1_cos=fabs(dvx1*dx+dvy1*dy+dvz1*dz)/(dis*dv1);
	double v2_cos=fabs(dvx2*dx+dvy2*dy+dvz2*dz)/(dis*dv2);

	double value=1.95;
	colli_obj->set_v(mvx-value*dvx1*v1_cos,mvy-value*dvy1*v1_cos,mvz-value*dvz1*v1_cos);
	be_colli->set_v(mvx-value*dvx2*v2_cos,mvy-value*dvy2*v2_cos,mvz-value*dvz2*v2_cos);
}
