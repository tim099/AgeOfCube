#include <Mouse.h>

Mouse::Mouse(){
	clear();
}
void Mouse::clear(){
	fx=0;fy=0;
	prev_x=0;prev_y=0;
	x=0;y=0;
	px=0,py=0,pz=0;
	state=0;
	dir[0]=0;dir[1]=0;
	select_x=0;select_y=0;select_z=0;
	surface_x=0,surface_y=0,surface_z=0;
	for(int i=0;i<6;i++){
		button[i]=false;
		but_in[i]=false;
	}
}
int Mouse::get_dir(){
	if(dir[1]){
		dir[1]=false;
		return 1;
	}
	if(dir[0]){
		dir[0]=false;
		return -1;
	}
	return 0;
}
bool Mouse::get_but(int but){
	if(but_in[but]){
		but_in[but]=false;
		return true;
	}
	return false;
}
void Mouse::set_pos(int _x,int _y){
	prev_x=x;prev_y=y;
	x=_x;y=_y;
}
void Mouse::mouse(int _button, int _state, int _x, int _y){
	set_pos(_x,_y);
	if(_state==0){//press
		button[_button]=true;
		but_in[_button]=true;
	}else if(_state==1){//release
		button[_button]=false;
		but_in[_button]=false;
	}
	state=_state;
}
void Mouse::mouseWheel(int _button, int _dir, int _x, int _y){
	set_pos(_x,_y);
	if(_dir==1){
		dir[1]=true;
		dir[0]=false;
	}
	if(_dir==-1){
		dir[0]=true;
		dir[1]=false;
	}
}
void Mouse::glutPassiveMotionFunc(int _x, int _y){
	set_pos(_x,_y);
}
Mouse::~Mouse() {

}

