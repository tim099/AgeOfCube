#ifndef SEARCHWORKER_H_
#define SEARCHWORKER_H_
#include "SearchCreature.h"
class SearchWorker : public SearchCreature{
public:
	SearchWorker(int which_player);
	virtual ~SearchWorker();
	virtual bool check_creature(CubeCreature* creature);
protected:
	int which_player;
};

#endif /* SEARCHWORKER_H_ */
