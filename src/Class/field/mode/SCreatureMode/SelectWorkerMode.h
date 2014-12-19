#ifndef SELECTWORKERMODE_H_
#define SELECTWORKERMODE_H_
#include "SelectCreatureMode.h"

class CubeWorker;
class SelectWorkerMode : public SelectCreatureMode{
public:
	SelectWorkerMode(Mouse *mou,BasicButList *SLB,CubeWorker *s_creature,Keyboard *keyboard);
	virtual ~SelectWorkerMode();
	virtual void dp_mode();
	virtual int get_mode()const;
protected:
	CubeWorker *s_worker;
	BasicButGroup *Build;
};

#endif /* SELECTWORKERMODE_H_ */
