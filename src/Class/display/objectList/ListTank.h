#ifndef LISTTANK_H_
#define LISTTANK_H_
#include"Objlist.h"

class ListTank : public Objlist{
struct Tanktex{
	GLuint turrent;
	GLuint hull;
};
public:
	ListTank();
	virtual ~ListTank();
	std::vector<Tanktex>l_t;
	std::vector<Tanktex>l_et;
protected:
	virtual void creat_all_list();
};

#endif
