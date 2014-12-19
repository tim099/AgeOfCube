#include <DPinput.h>

DPinput::DPinput(List *_list,ButtonList *_SLB,Mouse *mou) : Display(mou){
//prepare_list();
	SLB=_SLB;
	list=_list;
}
DPinput::~DPinput() {

}
void DPinput::prepare_list(){

}
void DPinput::display(){
	dp_prepare();
	dp_button();
	list->dp_list();
	glutSwapBuffers();
	//printf("dpinput!!\n");
}
