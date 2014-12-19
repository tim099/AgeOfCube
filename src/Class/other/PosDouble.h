#ifndef POSDOUBLE_H_
#define POSDOUBLE_H_

class PosDouble {
public:
	PosDouble();
	PosDouble(double x,double y,double z);
	virtual ~PosDouble();
	double x,y,z;
};

#endif /* POSDOUBLE_H_ */
