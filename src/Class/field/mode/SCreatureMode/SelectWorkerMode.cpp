#include <SelectWorkerMode.h>
#include "CubeWorker.h"
SelectWorkerMode::SelectWorkerMode(Mouse *mou,BasicButList *SLB,CubeWorker *_s_worker,Keyboard *keyboard)
: SelectCreatureMode(mou,SLB,_s_worker,keyboard){
	s_worker=_s_worker;
	Build=SLB->push_but_group(new BasicButGroup());
	Build->set_state(false);

	BBG->push_button(SLB->creat_ShowButGroup_button("Build",Signal(S_NULL),Build,false,2,posx,posy));
	Build->set_auto_pos(posx+0.013,posy,0.0,-0.003,5);
	_s_worker->creat_building_buts(Build,SLB);
    //S_BUILD_UNFINISHED
}
SelectWorkerMode::~SelectWorkerMode() {
	Build->delete_group();
}
int SelectWorkerMode::get_mode()const{
	return SELECT_WORKER_MODE;
}
void SelectWorkerMode::dp_mode(){
	if(control_mode)return;
	list->dp_list();
	glPushMatrix();//just test
	glLoadIdentity();
		//glTranslatef(0,-0.01,-0.1);
		//LBR->dp_bar(s_creature->idle_time(),5000,0.00001,100.0,ListBar::color(0,1,0,0));
	glPopMatrix();
}
