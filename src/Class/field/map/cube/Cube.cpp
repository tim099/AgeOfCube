#include <Cube.h>

Cube::Cube(int _cube_type) {
	cube_type=_cube_type;
	hp=10000;
}
Cube::~Cube() {

}
void Cube::save(FILE *file){
	fprintf(file,"%d ",cube_type);
	save_cube(file);
}
void Cube::load(FILE *file){
	load_cube(file);
}
void Cube::save_cube(FILE *file){
	fprintf(file,"\n");
}
void Cube::load_cube(FILE *file){
	fscanf(file,"\n");
}
int Cube::typ()const{
	return cube_type;
}
int Cube::C_TYP()const{
	return cube_type-(cube_type%10000);
}
