#include <ButtonList.h>

ButtonList::ButtonList(Mouse *_mou) {
prev_pressed_but=0;
prepre_but=0;
mou=_mou;
}
ButtonList::~ButtonList() {
	while(!buts.empty()){
		delete buts.front();
		buts.pop();
	}
}
Signal ButtonList::get_signal(){
	if(!signal_out.empty()){
		Signal s=signal_out.front();
		signal_out.pop();
		return s;
	}
	return Signal();
}
void ButtonList::check_button_pressed(){
	int _size=buts.size();
	Button *b;
	for(int i=0;i<_size;i++){
		b=buts.front();
		buts.pop();
		if(b->get_state()==2&&b->pressed_timer>10){//pressed
			b->pressed_timer=0;
			b->set_state(0);
			prepre_but=prev_pressed_but;
			prev_pressed_but=b;
			signal_q.push(b->signal);
			b->pressed();
		}
		buts.push(b);
	}
}
void ButtonList::handle_signal(Signal s){
	if(s.sig()==S_NULL)return;
	if(s.layer()!=BUTTON_SIGNAL){
		signal_out.push(s);
		return;
	}else switch(s.typ()){
		case BUTTON_GROUP_SIGNAL:
			handle_button_group_signal(s);
			break;
		default:
			printf("unknow button signal %d\n",s.sig());
	}
}
void ButtonList::handle_button_group_signal(Signal s){
	printf("cant handle button group signal %d by button list\n",s.sig());
}
void ButtonList::remove_button(){
	Button *b;
	int size=buts.size();
	for(int i=0;i<size;i++){
		b=buts.front();
		buts.pop();
		if(b->exist()){
			buts.push(b);
		}else{
			delete b;
		}
	}
}
void ButtonList::tic(){
	crusor_button_collision();
	check_button_pressed();
	while(!signal_q.empty()){
		handle_signal(signal_q.front());
		signal_q.pop();
	}
	timer_tic();
	remove_button();
}

void ButtonList::crusor_button_collision(){
	double dx,dy;
	Button *b;
	int _size=buts.size();
	for(int i=0;i<_size;i++){
		b=buts.front();
		buts.pop();
		if(b->active()){
			dx=fabs((b->x)-mou->fx);
			dy=fabs((b->y)-mou->fy);
			if(dx<b->width&&dy<b->height){//colli
				if(mou->get_but(0)){
					if(b->pressed_timer==0)b->set_state(2);//click on
				}else{
					b->set_state(1);//on button
				}
			}else if(b->get_state()!=2){
				b->set_state(0);
			}
		}
		b->tic();
		buts.push(b);
	}
}


