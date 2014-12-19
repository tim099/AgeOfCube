#ifndef POS_H_
#define POS_H_

class Pos {
public:
	Pos();
	Pos(int x,int y,int z);
	virtual ~Pos();
	int x,y,z;
};

#endif /* POS_H_ */
