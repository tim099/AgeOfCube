#include "ListMisc.h"

ListMisc::ListMisc() {
	creat_all_list();

}
ListMisc::~ListMisc() {
	//glDeleteLists(MISC_SELECTED,1);
	//glDeleteLists(MISC_RALLY_POINT,1);handle by all_obj
}
void ListMisc::creat_all_list(){
	creat_obj_list((char*)"files/obj/Misc/selected.obj",MISC_SELECTED,0.015,0,0.05,0);
	creat_obj_list((char*)"files/obj/Misc/RallyPoint.obj",MISC_RALLY_POINT,0.04,0,0.01,0);
}
