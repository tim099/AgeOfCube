#ifndef PHYSICAL_H_
#define PHYSICAL_H_
#include <cmath>
#include <cstdio>
#include "PosDouble.h"
const double GRAVITY=-0.004;
class Physical {
public:
	Physical(double x,double y,double z);
	virtual ~Physical();

	double get_mass()const;
	double get_size()const;

	virtual double max_v()const;
	virtual double max_a()const;


	double get_x()const;
	double get_y()const;
	double get_z()const;
	double get_v()const;
	PosDouble get_pos()const;
	double get_vx()const;
	double get_vy()const;
	double get_vz()const;
	double get_ry()const;
	int in_x()const;
	int in_y()const;
	int in_z()const;
	int prev_in_x()const;
	int prev_in_y()const;
	int prev_in_z()const;
	int on_x()const;
	int on_y()const;
	int on_z()const;

	void freeze();
	void accelerate(double dvx,double dvy,double dvz);
	void accelerate_by_a(double dvx,double dvy,double dvz);

	void set_v(double vx,double vy,double vz);
	virtual void set_pos(double pos_x,double pos_y,double pos_z);
protected:
	void save_physical(FILE* fop);
	void load_physical(FILE* fop);
	void set_ry(double ry);
	int convert_pos_x(double x)const;
	int convert_pos_y(double y)const;
	int convert_pos_z(double z)const;

	PosDouble pos,prev,v;

	double ry;
	double size;
	double density;
};

#endif /* PHYSICAL_H_ */
