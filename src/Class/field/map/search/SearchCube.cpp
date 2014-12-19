#include "SearchCube.h"
#include "StaticCube.h"
#include "cstdio"
SearchCube::SearchCube(int _cube_type) {
cube_type=_cube_type;
}
SearchCube::~SearchCube() {

}
bool SearchCube::check_search(StaticCube* cube){
	if(cube->typ()==cube_type){
		return true;
	}else{
		return false;
	}
}
