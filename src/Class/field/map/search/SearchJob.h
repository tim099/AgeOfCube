#ifndef SEARCHJOB_H_
#define SEARCHJOB_H_

#include "Search.h"
class SearchJob : public Search{
public:
	SearchJob(int which_player);
	virtual ~SearchJob();
	virtual bool check_search(StaticCube* cube);
protected:
	int which_player;
};

#endif /* SEARCHJOB_H_ */
