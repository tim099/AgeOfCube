#ifndef LISTBASICCUBES_H_
#define LISTBASICCUBES_H_

#include "Bmplist.h"
#include "CubeTextureDefine.h"

class ListBasicCubes : public Bmplist{
public:
	ListBasicCubes(double size=0.05);
	virtual ~ListBasicCubes();
	std::vector<Bmp*>cube_tex;
protected:
	void creat_all_list();
	double size;

};

#endif /* LISTBASICCUBES_H_ */
