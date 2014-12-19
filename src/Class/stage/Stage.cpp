#include "Stage.h"

Stage::Stage() {
SLB=0;
cur_dp=0;timer=0;
end=false;
}
Stage::~Stage() {
//std::cout<<"dtor_Stage"<<std::endl;
if(cur_dp!=0)delete cur_dp;
}
bool Stage::END(){
	return end;
}
Display* Stage::cur_dis(){
	return cur_dp;
}
void Stage::sent_signal(Signal s){
	signal_q.push(s);
}
void Stage::get_signals(){
	if(SLB==0)return;
	Signal signals=SLB->get_signal();
	if(signals.sig()!=S_NULL){
		if(signals.layer()>=GAME_SIGNAL){
			out_signal_q.push(signals);
		}else{//under stage signal
			signal_q.push(signals);
		}
	}
}
void Stage::handle_signals(){
	while(!signal_q.empty()){
		if(signal_q.front().sig()>=GAME_SIGNAL){
			out_signal_q.push(signal_q.front());
		}else{
			signal_process(signal_q.front());
		}
		signal_q.pop();
	}
}
void Stage::signal_under_stage(Signal s){
	printf("cant sent this signal under stage %d by original stage\n",s.sig());
}
void Stage::signal_process(Signal s){
	if(s.layer()<STAGE_SIGNAL){
		signal_under_stage(s);
		return;
	}
	switch(s.typ()){
		case T_STAGE_MENU:
		case T_STAGE_CREAT_MAP:
		case T_STAGE_LOAD_MAP:
			Stage_signal_process(s);
			break;
		default:
		printf("cant process this signal %d by original stage\n",s.sig());
	}

}
void Stage::Stage_signal_process(Signal s){
	printf("cant process this signal %d by original stage\n",s.sig());
};
void Stage::view_control(){
	if(k_b.get('+')&&cur_dp->dp_range<100){
		(cur_dp->dp_range)++;
	}
	if(k_b.get('-')&&cur_dp->dp_range>2){
		(cur_dp->dp_range)--;
	}
	if(k_b.input['y']){
		cur_dp->look_v.y+=0.005;
	}
	if(k_b.input['h']){
		cur_dp->look_v.y-=0.005;
	}
	int dir=mou.get_dir();
	if(dir==1){
		cur_dp->v_dis+=0.02*sqrt(cur_dp->distance);
	}
	if(dir==-1){
		cur_dp->v_dis-=0.02*sqrt(cur_dp->distance);
	}
	if(mou.button[1]){
		int dx=mou.x-mou.prev_x;
		int dy=mou.y-mou.prev_y;
		mou.prev_x=mou.x;
		mou.prev_y=mou.y;
		cur_dp->v_hori+=0.001*dx;
		cur_dp->v_ver-=0.0003*dy;
	}
	double dx=cur_dp->s_width-mou.x;
	double dy=cur_dp->s_height-mou.y;
	if(dx<0.05*cur_dp->s_width){
		double speed;
		if(dx>0.03*cur_dp->s_width)speed=0.001;
		else if(dx>0.02*cur_dp->s_width)speed=0.002;
		else speed=0.003;
		speed*=sqrt(cur_dp->distance);
		cur_dp->look_v.x+=speed*sinf(cur_dp->horizontal);
		cur_dp->look_v.z-=speed*cosf(cur_dp->horizontal);
	}
	if(dx>0.95*cur_dp->s_width){
		double speed;
		if(dx<0.97*cur_dp->s_width)speed=0.001;
		else if(dx<0.98*cur_dp->s_width)speed=0.002;
		else speed=0.003;
		speed*=sqrt(cur_dp->distance);
		cur_dp->look_v.x-=speed*sinf(cur_dp->horizontal);
		cur_dp->look_v.z+=speed*cosf(cur_dp->horizontal);
	}
	if(dy<0.05*cur_dp->s_height){
		double speed;
		if(dy>0.03*cur_dp->s_height)speed=0.001;
		else if(dy>0.02*cur_dp->s_height)speed=0.002;
		else speed=0.003;
		speed*=sqrt(cur_dp->distance);
		cur_dp->look_v.x+=speed*cosf(cur_dp->horizontal);
		cur_dp->look_v.z+=speed*sinf(cur_dp->horizontal);
	}
	if(dy>0.95*cur_dp->s_height){
		double speed;
		if(dy<0.98*cur_dp->s_height)speed=0.001;
		else if(dy<0.97*cur_dp->s_height)speed=0.002;
		else speed=0.003;
		speed*=sqrt(cur_dp->distance);
		cur_dp->look_v.x-=speed*cosf(cur_dp->horizontal);
		cur_dp->look_v.z-=speed*sinf(cur_dp->horizontal);
	}
}
void Stage::tic(){
	cur_dp->tic();
	if(SLB!=0)SLB->tic();
	get_signals();
	handle_signals();
	timer_tick();
	timer++;
	//clock_t start_time=clock(),time_cost;
	glutPostRedisplay();
	//time_cost=(clock()-start_time);
	//printf("time_cost=%lfsec\n",(double)time_cost/(double)(CLOCKS_PER_SEC));
}



