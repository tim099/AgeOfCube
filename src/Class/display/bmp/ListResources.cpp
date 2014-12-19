#include "ListResources.h"

ListResources::ListResources(double _size) {
	size=_size;
	creat_all_list();
}
ListResources::~ListResources() {

}
void ListResources::creat_all_list(){
	creat_texture_bysize("files/texture/resources/Cube.bmp",TEX_R_CUBE,0.001*size,270,0);
	creat_texture_bysize("files/texture/resources/DarkCube.bmp",TEX_R_DARK_CUBE,0.001*size,270,0);
	creat_texture_bysize("files/texture/resources/core.bmp",TEX_R_CORE,0.001*size,270,0);
	creat_texture_bysize("files/texture/resources/RedCore.bmp",TEX_R_RED_CORE,0.001*size,270,0);
}
