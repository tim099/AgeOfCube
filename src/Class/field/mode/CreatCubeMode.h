#ifndef CREATCUBEMODE_H_
#define CREATCUBEMODE_H_
#include "CubeTextureDefine.h"
#include "map/Map.h"
#include "Mouse.h"
#include "Mode.h"
class CreatCubeMode : public Mode{
public:
	CreatCubeMode(Mouse *mou,Map *map,int cube_type);
	virtual ~CreatCubeMode();

	virtual void dp_mode();
	virtual int get_mode()const;
protected:
	void creat_cube();
	Mouse *mou;
	Map *map;
	int c_type;
	bool drag;
	int start_x,start_y,start_z;

	virtual void timer_tic();
};

#endif /* CREATCUBEMODE_H_ */
