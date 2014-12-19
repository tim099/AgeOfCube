#include "SloadMap.h"

SloadMap::SloadMap() {
	select_but=new std::string("Not selected yet");
	list=new List(0.001,0);
	SLB=new BasicButList(&mou,0.7);
	cur_dp=new DPinput(list,SLB,&mou);//delete by stage

	SLB->creat_short_button("Prev",Signal(S_S_L_PREV),-0.02,-0.018);
	SLB->creat_short_button("Next",Signal(S_S_L_NEXT),-0.0125,-0.018);
	SLB->creat_short_button("Back",Signal(S_BACK),-0.02,-0.022);
	SLB->creat_medium_button("Load",Signal(S_LOAD_MAP),0.01,-0.022);//S_LOAD_MAP
	SLB->creat_medium_button("Delete",Signal(S_DELETE_MAP_NAME),-0.009,-0.022);
	list->push_str(select_but,0.01,-0.018);
	DIR *dp;
	dirent *dirp;
	dp = opendir("files/maps");
	readdir(dp);readdir(dp);
	double dis=0.0037;
	std::vector<std::string> filenames;
	but_group=SLB->push_but_group(new BasicButGroup());
	while((dirp=readdir(dp))!= NULL){
		filenames.push_back(dirp->d_name);
	}
	for(unsigned i=0;i<filenames.size();i++){
		but_group->push_button(SLB->creat_basic_button(filenames.at(i).c_str(),
					Signal(S_SELECTED_MAP_NAME,filenames.at(i))));
	}
	but_group->set_auto_pos(0,6*dis,0,-dis,10);
	closedir(dp);
}
SloadMap::~SloadMap() {
	delete list;
	delete SLB;
}
void SloadMap::Stage_signal_process(Signal s){
	char c[50]="files/maps/";
	switch(s.sig()){
		case S_SELECTED_MAP_NAME:
			(*select_but)=s.str().c_str();
			break;
		case S_DELETE_MAP_NAME:
			if(SLB->prepre_but!=0&&SLB->prepre_but->signal.sig()!=S_DELETE_MAP_NAME){
				for(unsigned i=0;i<(*select_but).size();i++){
					c[11+i]=(*select_but).at(i);
				}
				c[11+(*select_but).size()]='\0';
				remove(c);
				SLB->prepre_but->delete_but();
			}
			break;
		case S_LOAD_MAP:
			for(unsigned i=0;i<(*select_but).size();i++){
				c[11+i]=(*select_but).at(i);
			}
			c[11+(*select_but).size()]='\0';
			sent_signal(Signal(S_LOAD_MAP_NAME,std::string(c)));
			end=true;
			break;
		case S_S_L_PREV:
			but_group->prev_page();
			break;
		case S_S_L_NEXT:
			but_group->next_page();
			break;
		default:
			printf("unknown signal to input stage %d\n",s.sig());
	}
}
void SloadMap::timer_tick(){

}
