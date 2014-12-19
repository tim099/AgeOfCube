#ifndef CUBE_H_
#define CUBE_H_
#include "cube_define.h"
#include "stdio.h"
class Cube {
public:
	Cube(int cube_type=C_NULL);
	virtual ~Cube();
	virtual void save(FILE *file);
	virtual void load(FILE *file);

	int typ()const;
	int C_TYP()const;
protected:
	virtual void save_cube(FILE *file);
	virtual void load_cube(FILE *file);
	int cube_type;
	int hp;
};

#endif /* CUBE_H_ */
