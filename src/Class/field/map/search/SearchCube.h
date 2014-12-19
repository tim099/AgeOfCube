#ifndef SEARCHCUBE_H_
#define SEARCHCUBE_H_
#include "Search.h"
class SearchCube : public Search{
public:
	SearchCube(int cube_type);
	virtual ~SearchCube();
	virtual bool check_search(StaticCube* cube);
protected:
	int cube_type;
};

#endif /* SEARCHCUBE_H_ */
