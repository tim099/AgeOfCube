#include <ListTank.h>

ListTank::ListTank() {
creat_all_list();

}

ListTank::~ListTank() {
}

void ListTank::creat_all_list(){
	Tanktex t,et;
		t.hull=creat_list((char*) "files/obj/tank/tank00/tankbody00.obj", .05);
		et.hull=creat_list((char*) "files/obj/tank/tank00/enemytankbody00.obj", .05);
		t.turrent=creat_list((char*) "files/obj/tank/tank00/tankturrent00.obj", .04);
		et.turrent=creat_list((char*) "files/obj/tank/tank00/enemytankturrent00.obj", .04);
		l_t.push_back(t);
		l_et.push_back(et);

		t.hull=creat_list((char*) "files/obj/tank/tank01/tankbody01.obj", .07);
		et.hull=creat_list((char*) "files/obj/tank/tank01/enemytankbody01.obj", .07);
		t.turrent=creat_list((char*) "files/obj/tank/tank01/tankturrent01.obj", .09);
		et.turrent=creat_list((char*) "files/obj/tank/tank01/enemytankturrent01.obj", .09);
		l_t.push_back(t);
		l_et.push_back(et);

		t.hull=creat_list((char*) "files/obj/tank/tank02/tankbody02.obj", .085);
		et.hull=creat_list((char*) "files/obj/tank/tank02/enemytankbody02.obj", .085);
		t.turrent=creat_list((char*) "files/obj/tank/tank02/tankturrent02.obj", .12);
		et.turrent=creat_list((char*) "files/obj/tank/tank02/enemytankturrent02.obj", .12);
		l_t.push_back(t);
		l_et.push_back(et);

		t.hull=creat_list((char*) "files/obj/tank/tank06/tankbody06.obj", .11);
		et.hull=creat_list((char*) "files/obj/tank/tank06/enemytankbody06.obj", .11);
		t.turrent=creat_list((char*)"files/obj/tank/tank06/tankturrent06.obj", .12);
		et.turrent=creat_list((char*) "files/obj/tank/tank06/enemytankturrent06.obj", .12);
		l_t.push_back(t);
		l_et.push_back(et);

		t.hull=creat_list((char*) "files/obj/tank/tank07/tankbody07.obj", .09);
		et.hull=creat_list((char*) "files/obj/tank/tank07/enemytankbody07.obj", .09);
		t.turrent=creat_list((char*) "files/obj/tank/tank07/tankturrent07.obj", .09);
		et.turrent=creat_list((char*) "files/obj/tank/tank07/enemytankturrent07.obj", .09);
		l_t.push_back(t);
		l_et.push_back(et);
}
