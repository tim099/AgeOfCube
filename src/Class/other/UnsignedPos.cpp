#include <UnsignedPos.h>

UnsignedPos::UnsignedPos() {
	x=0,y=0,z=0;
}
UnsignedPos::UnsignedPos(unsigned _x,unsigned _y,unsigned _z){
	x=_x;y=_y;z=_z;
}
UnsignedPos::~UnsignedPos() {

}
void UnsignedPos::save(FILE *file){
	fprintf(file,"%u %u %u ",x,y,z);
}
void UnsignedPos::load(FILE *file){
	fscanf(file,"%u %u %u ",&x,&y,&z);
}
UnsignedPos& UnsignedPos::operator=(const UnsignedPos &pos){
	x=pos.x;
	y=pos.y;
	z=pos.z;
	return (*this);
}
bool UnsignedPos::operator==(const UnsignedPos &pos)const{
	if(pos.x==x&&pos.y==y&&pos.z==z)return true;
	return false;
}
bool UnsignedPos::operator!=(const UnsignedPos &pos)const{
	if(pos.x==x&&pos.y==y&&pos.z==z)return false;
	return true;
}
