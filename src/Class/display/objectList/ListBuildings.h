#ifndef LISTBUILDINGS_H_
#define LISTBUILDINGS_H_
#include "building_obj_define.h"
#include "Objlist.h"
class ListBuildings : public Objlist{
public:
	ListBuildings();
	virtual ~ListBuildings();
protected:
	virtual void creat_all_list();

};

#endif /* LISTBUILDINGS_H_ */
