#include "SearchWorker.h"
#include "CubeWorker.h"
SearchWorker::SearchWorker(int _which_player) {
	which_player=_which_player;
}
SearchWorker::~SearchWorker() {

}
bool SearchWorker::check_creature(CubeCreature* creature){
	CubeWorker *worker;
	if(creature->belong_to()==which_player){
		worker=creature->worker();
		if(worker){
			if(worker->cur_work()==0)return true;//no job
		}
	}
	return false;
}
