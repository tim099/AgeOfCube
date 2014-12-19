#include "SelectCreatureMode.h"
#include "Display.h"
SelectCreatureMode::SelectCreatureMode(Mouse *_mou,BasicButList *_SLB,CubeCreature *_s_creature
,Keyboard *_k_b) {
	posx=-0.045;posy=-0.007;
	jump=0;
	mou=_mou;
	k_b=_k_b;
	SLB=_SLB;
	s_creature=_s_creature;
	s_creature->select();
	list = new List(0.001,1,0,-0.017,1.0);
	LBR = new ListBar();
	control_mode=false;
	BBG=SLB->push_but_group(new BasicButGroup());
}
SelectCreatureMode::~SelectCreatureMode() {
	delete list;
	delete LBR;
	BBG->delete_group();
	s_creature->deselect();
}
void SelectCreatureMode::display_alter(Display* display){
	if(control_mode){
		(display->look)=s_creature->get_pos();
		(display->horizontal)=(s_creature->get_ry()+90)*(-PI/180.0);
	}
}
int SelectCreatureMode::get_mode()const{
	return SELECT_CREATURE_MODE;
}
void SelectCreatureMode::dp_mode(){
	if(control_mode)return;
	list->dp_list();
	glPushMatrix();//just test
	glLoadIdentity();
	//glTranslatef(0,-0.01,-0.1);
	//LBR->dp_bar(s_creature->idle_time(),5000,0.00001,100.0,ListBar::color(0,1,0,0));
	glPopMatrix();
}
void SelectCreatureMode::timer_tic(){
	if(mou->get_but(0))end=true;
	if(mou->get_but(2)){
		s_creature->clean_order();
		if(!mou->selected_building)s_creature->go_to(mou->select_x,mou->select_y+1,mou->select_z);
		else s_creature->go_to(mou->select_x,mou->select_y,mou->select_z);
	}
	//if(k_b->d){
		//s_creature->delete_cube(3);
		//end=true;
//	}
	if(k_b->get('c')){
		if(!control_mode)control_mode=true;
		else control_mode=false;
	}
	if(control_mode){
		k_b->get('d');
		k_b->get('a');
		k_b->get('w');
		k_b->get('s');
		k_b->get('q');
		k_b->get(' ');
		if(k_b->input['d'])s_creature->accelerate(0.001*sinf((s_creature->get_ry()+90)*(-PI/180.0)),0,0.001*cosf((s_creature->get_ry()-90)*(-PI/180.0)));
		if(k_b->input['a'])s_creature->accelerate(0.001*sinf((s_creature->get_ry()-90)*(-PI/180.0)),0,0.001*cosf((s_creature->get_ry()+90)*(-PI/180.0)));
		if(k_b->input['w'])s_creature->accelerate(0.01*sinf((s_creature->get_ry())*(PI/180.0)),0,0.01*cosf((s_creature->get_ry())*(PI/180.0)));
		if(k_b->input['s'])s_creature->accelerate(-0.001*sinf((s_creature->get_ry())*(PI/180.0)),0,-0.001*cosf((s_creature->get_ry())*(PI/180.0)));
		if(k_b->input[' '])s_creature->accelerate(0,0.1,0);
		if(k_b->input['q'])s_creature->accelerate(0,-0.1,0);
	}
}
