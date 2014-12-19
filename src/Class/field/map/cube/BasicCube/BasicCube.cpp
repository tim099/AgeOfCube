#include <BasicCube.h>

BasicCube::BasicCube(int _type){
	cube_type=_type;
	if(C_TYP()==C_CUBE)_buildable=true;
	if(typ()==C_NULL){
		path|=M_LEFT;
		path|=M_RIGHT;
		path|=M_FRONT;
		path|=M_BACK;
		path|=M_UP;
		path|=M_DOWN;
	}else if(C_TYP()==C_CUBE){
		path|=M_STANDABLE;
	}
}
BasicCube::~BasicCube() {

}
