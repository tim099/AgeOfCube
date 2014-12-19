#ifndef LISTRESOURCES_H_
#define LISTRESOURCES_H_
#include "ResourcesTexDefine.h"
#include "Bmplist.h"
class ListResources : public Bmplist{
public:
	ListResources(double size=1.0);
	virtual ~ListResources();
protected:
	void creat_all_list();
	double size;
};

#endif /* LISTRESOURCES_H_ */
