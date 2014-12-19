#ifndef STATICCUBE_H_
#define STATICCUBE_H_
#include "DeletableCube.h"
#include "Cube.h"
class Building;
class StaticCube : public Cube ,public DeletableCube{
public:
	StaticCube(int type=C_STATIC_CUBE);
	virtual ~StaticCube();

	bool buildable()const;
	void discover(int player);
	bool see(int player);
	virtual unsigned char get_path()const;
	virtual unsigned char get_extra_path()const;
	virtual Building *get_building();
protected:
	virtual void save_cube(FILE *file);
	virtual void load_cube(FILE *file);
	virtual void save_static_cube(FILE *file);
	virtual void load_static_cube(FILE *file);
	int discovered;
	bool _buildable;
	unsigned char path;
};

#endif /* STATICCUBE_H_ */
