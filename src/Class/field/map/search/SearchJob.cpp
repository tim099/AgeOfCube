#include "SearchJob.h"
#include "WorkableBuilding.h"
SearchJob::SearchJob(int _which_player) {
	which_player=_which_player;

}
SearchJob::~SearchJob() {

}
bool SearchJob::check_search(StaticCube* cube){
	Building *building=cube->get_building();
	if(building&&building->belong_to()==which_player){
		WorkableBuilding *w_b=building->workablebuilding();
		if(w_b){
			if(w_b->have_job())return true;
		}
	}
	return false;
}
