#ifndef THINK_H_
#define THINK_H_
#include <cstdio>
#include "ThinkDefine.h"
class Think {
public:
	Think();
	virtual ~Think();
	virtual unsigned think_type();

	void tic();
	bool end()const;
protected:
	virtual void timer_tic();
	bool _end;
};

#endif /* THINK_H_ */
