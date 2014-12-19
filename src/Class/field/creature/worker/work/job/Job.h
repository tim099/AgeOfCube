#ifndef JOB_H_
#define JOB_H_
#include <cstdio>
#include "JobDefine.h"
#include "LoadAddress.h"
class Job {
public:
	Job();
	virtual ~Job();
	virtual int job_type()const;
	virtual void load_finished(LoadAddress* LAD);
	void tic();
	void save(FILE *file);
	void load(FILE *file);
	bool END()const;
protected:
	virtual void  timer_tic()=0;
	virtual void save_job(FILE *file);
	virtual void load_job(FILE *file);
	bool _end;
};

#endif /* JOB_H_ */
