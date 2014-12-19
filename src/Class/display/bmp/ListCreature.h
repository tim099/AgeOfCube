#ifndef LISTCREATURE_H_
#define LISTCREATURE_H_
#include "Bmplist.h"
#include "Objlist.h"
#include "CreatureTexDefine.h"
class ListCreature : public Bmplist,public Objlist{
public:
	ListCreature(double size=1.0);
	virtual ~ListCreature();
protected:
	void creat_all_list();
	double size;
};

#endif /* LISTCREATURE_H_ */
