#include <SelectGroupMode.h>
SelectGroupMode::SelectGroupMode(Mouse *_mou,Player *_cur_player) {
mou=_mou;
cur_player=_cur_player;
state=STATE_SELECT;
sx=mou->px;
sy=mou->py;
sz=mou->pz;
}
SelectGroupMode::~SelectGroupMode() {
	for(unsigned i=0;i<s_creatures.size();i++){
		s_creatures.at(i)->deselect();
	}
	s_creatures.clear();
}
void SelectGroupMode::dp_mode(){
	if(state==STATE_SELECT){
		glPushMatrix();
		GLfloat blue[] = {0.0f, 0.0f, 1.0f, 0.3333f};
		glDepthMask(GL_FALSE);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, blue);
		glBegin(GL_QUADS);
		glVertex3f(sx,sy+0.003,sz);
		glVertex3f(sx,sy+0.003,mou->pz);
		glVertex3f(mou->px,sy+0.003,mou->pz);
		glVertex3f(mou->px,sy+0.003,sz);
		glEnd();
		glDepthMask(GL_TRUE);
		glDisable(GL_BLEND);
		glPopMatrix();
	}
}
void SelectGroupMode::find_select_creatures(){
	double min_x,max_x,min_z,max_z;
	if(sx<mou->px){
		min_x=sx;max_x=mou->px;
	}else{
		min_x=mou->px;max_x=sx;
	}
	if(sz<mou->pz){
		min_z=sz;max_z=mou->pz;
	}else{
		min_z=mou->pz;max_z=sz;
	}
	CubeCreature *buff;
	for(unsigned i=0;i<cur_player->creatures.size();i++){
		buff=cur_player->creatures.at(i);
		if(buff->get_x()<=max_x+0.01&&buff->get_x()>=min_x-0.01){
			if(buff->get_z()<=max_z+0.01&&buff->get_z()>=min_z-0.01){
				if(buff->get_y()-sy<0.09&&buff->get_y()-sy>-0.15){
					s_creatures.push_back(buff);
					buff->select();
				}
			}
		}
	}
}
void SelectGroupMode::group_commend_goto(){
	for(unsigned i=0;i<s_creatures.size();i++){
		s_creatures.at(i)->clean_order();
		s_creatures.at(i)->go_to(mou->select_x,mou->select_y+1,mou->select_z);
		//else s_creatures.at(i)->go_to(mou->select_x,mou->select_y,mou->select_z);
	}
}
void SelectGroupMode::timer_tic(){
	if(state==STATE_SELECT){
		if(mou->button[0]==true){//stay select state!!
			for(unsigned i=0;i<s_creatures.size();i++){
				s_creatures.at(i)->deselect();
			}
			s_creatures.clear();
			find_select_creatures();
		}else{//release
			if(!s_creatures.empty())state=STATE_SELECTED;
			else end=true;
		}
	}
	if(state==STATE_SELECTED){
		if(mou->get_but(2)){
			group_commend_goto();
		}
		if(mou->get_but(0)){
			end=true;
		}
	}
}
int SelectGroupMode::get_mode()const{
	return SELECT_GROUP_MODE;
}
