#include <think/Think.h>

Think::Think() {
	_end=false;

}
Think::~Think() {

}
unsigned Think::think_type(){
	return THINK_THINK;
}
void Think::timer_tic(){
	printf("think timer tic\n");
}
void Think::tic(){
	timer_tic();
}
bool Think::end()const{
	return _end;
}
