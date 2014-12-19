#ifndef WORKERCORE_H_
#define WORKERCORE_H_
#include "Core.h"
class CubeWorker;
class WorkerCore : public Core{
public:
	WorkerCore(CubeWorker *worker,unsigned IQ=100);
	virtual ~WorkerCore();
protected:
	void handle_idle();
	void timer_tic();
	CubeWorker *worker;
};

#endif /* WORKERCORE_H_ */
