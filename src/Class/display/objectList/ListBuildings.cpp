#include "ListBuildings.h"

ListBuildings::ListBuildings() {
	creat_all_list();

}
ListBuildings::~ListBuildings() {
	/*glDeleteLists(DP_P0_BUILDING,1);
	glDeleteLists(DP_P1_BUILDING,1);
	glDeleteLists(DP_P2_BUILDING,1);
	glDeleteLists(DP_P3_BUILDING,1);
	glDeleteLists(DP_P4_BUILDING,1);
	glDeleteLists(DP_P5_BUILDING,1);
	glDeleteLists(DP_P6_BUILDING,1);
	glDeleteLists(DP_P7_BUILDING,1);
	glDeleteLists(DP_BASE,1);
	glDeleteLists(DP_BASE_CORE,1);
	glDeleteLists(DP_ELEVATOR,1);
	glDeleteLists(DP_ELEVATOR_PLANE,1);
	glDeleteLists(DP_ONE_WAY,1);
	glDeleteLists(DP_ONE_WAY_WALL,1);
	glDeleteLists(DP_ONE_WAY_NOUT,1);*/
}
void ListBuildings::creat_all_list(){
	creat_obj_list((char*)"files/obj/players/playersbuilding/P0.obj",DP_P0_BUILDING,0.051,0,-0.0499,0);
	creat_obj_list((char*)"files/obj/players/playersbuilding/P1.obj",DP_P1_BUILDING,0.051,0,-0.0499,0);
	creat_obj_list((char*)"files/obj/players/playersbuilding/P2.obj",DP_P2_BUILDING,0.051,0,-0.0499,0);
	creat_obj_list((char*)"files/obj/players/playersbuilding/P3.obj",DP_P3_BUILDING,0.051,0,-0.0499,0);
	creat_obj_list((char*)"files/obj/players/playersbuilding/P4.obj",DP_P4_BUILDING,0.051,0,-0.0499,0);
	creat_obj_list((char*)"files/obj/players/playersbuilding/P5.obj",DP_P5_BUILDING,0.051,0,-0.0499,0);
	creat_obj_list((char*)"files/obj/players/playersbuilding/P6.obj",DP_P6_BUILDING,0.051,0,-0.0499,0);
	creat_obj_list((char*)"files/obj/players/playersbuilding/P7.obj",DP_P7_BUILDING,0.051,0,-0.0499,0);
	creat_obj_list((char*)"files/obj/buildings/basic/Base/Base.obj",DP_BASE,0.05,0,-0.025,0);
	creat_obj_list((char*)"files/obj/buildings/basic/Base/BaseCore.obj",DP_BASE_CORE,0.05,0,0,0);
	creat_obj_list((char*)"files/obj/buildings/basic/Elevator/Elevator.obj",DP_ELEVATOR,0.052,0,0,0);
	creat_obj_list((char*)"files/obj/buildings/basic/Elevator/ElevatorPlane.obj",DP_ELEVATOR_PLANE,0.032,0,0,0);
	creat_obj_list((char*)"files/obj/buildings/basic/OneWay/OneWay.obj",DP_ONE_WAY,0.052,0,-0.04,0);
	creat_obj_list((char*)"files/obj/buildings/basic/OneWay/OneWayWall.obj",DP_ONE_WAY_WALL,0.04,0,-0.035,0.047);
	creat_obj_list((char*)"files/obj/buildings/basic/OneWay/OneWayOUT.obj",DP_ONE_WAY_NOUT,0.03,0,-0.046,0.04);
}
