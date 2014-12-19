#include <Core.h>
#include "CubeCreature.h"
Core::Core(unsigned _IQ) {
	creature=0;
	think_timer=0;
	IQ=_IQ;
	for(unsigned i=0;i<MAX_THINK_NUM;i++)in_think_q[i]=false;
}
Core::~Core() {
	while(!thinking_q.empty())pop_thinking();
}
void Core::think_timer_tic(){
	if(cur_thinking()){
		cur_thinking()->tic();
		if(cur_thinking()->end()){
			pop_thinking();
			think_timer=0;//end cur thinking
		}
	}else{//cur_thinking timer tic!!
		think_timer++;
	}
}
void Core::tic(){
	think_timer_tic();
	timer_tic();
}
Think* Core::cur_thinking()const{
	if(!thinking_q.empty())return thinking_q.top();
	else return 0;
}
void Core::push_thinking(Think* think){
	if(!(in_think_q[think->think_type()])){
		thinking_q.push(think);//not in think q
		in_think_q[think->think_type()]=true;
	}else delete think;
}
void Core::pop_thinking(){
	if(!thinking_q.empty()){
		in_think_q[thinking_q.top()->think_type()]=false;
		delete thinking_q.top();
		thinking_q.pop();
	}
}
