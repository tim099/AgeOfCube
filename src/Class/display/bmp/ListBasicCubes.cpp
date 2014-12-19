#include "ListBasicCubes.h"

ListBasicCubes::ListBasicCubes(double _size) {
	size=_size;
	creat_all_list();
}
ListBasicCubes::~ListBasicCubes() {
	while(!cube_tex.empty()){
		delete cube_tex.back();
		cube_tex.pop_back();
	}
}
void ListBasicCubes::creat_all_list(){
	creat_texture_bysize("files/texture/cubes/BasicCube/BasicCubeTop01.BMP",TEXT_BASIC_CUBE_TOP,size,0,0);
	creat_texture_bysize("files/texture/cubes/BasicCube/BasicCubeSide01.BMP",TEXT_BASIC_CUBE_SIDE,size,90,0);
	creat_texture_bysize("files/texture/cubes/DarkCube/DarkCubeTop.BMP",TEXT_DARK_CUBE_TOP,size,0,0);
	creat_texture_bysize("files/texture/cubes/DarkCube/DarkCubeSide.BMP",TEXT_DARK_CUBE_SIDE,size,90,0);
	creat_texture_bysize("files/texture/cubes/DarkCube/RedCore/RedCoreTop.BMP",TEXT_RED_CORE_TOP,size,0,0);
	creat_texture_bysize("files/texture/cubes/DarkCube/RedCore/RedCoreTop.BMP",TEXT_RED_CORE_SIDE,size,90,0);
	creat_texture_bysize("files/texture/cubes/BasicCube/WhiteBrickTop.BMP",TEXT_WHITE_BRICK_TOP,size,0,0);
	creat_texture_bysize("files/texture/cubes/BasicCube/WhiteBrickSide.BMP",TEXT_WHITE_BRICK_SIDE,size,90,0);

	cube_tex.push_back(creat_tex("files/texture/cubes/BasicCube/BasicCubeTop01.BMP"));
	cube_tex.push_back(creat_tex("files/texture/cubes/BasicCube/BasicCubeSide01.BMP"));
	cube_tex.push_back(creat_tex("files/texture/cubes/DarkCube/DarkCubeTop.BMP"));
	cube_tex.push_back(creat_tex("files/texture/cubes/DarkCube/DarkCubeSide.BMP"));
	cube_tex.push_back(creat_tex("files/texture/cubes/DarkCube/RedCore/RedCoreTop.BMP"));
	cube_tex.push_back(creat_tex("files/texture/cubes/DarkCube/RedCore/RedCoreSide.BMP"));
	cube_tex.push_back(creat_tex("files/texture/cubes/BasicCube/WhiteBrickTop.BMP"));
	cube_tex.push_back(creat_tex("files/texture/cubes/BasicCube/WhiteBrickSide.BMP"));
}
