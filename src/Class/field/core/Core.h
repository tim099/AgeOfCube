#ifndef CORE_H_
#define CORE_H_
#include <queue>
#include "think/Think.h"
class CubeCreature;
class Core {
public:
	Core(unsigned IQ=100);
	virtual ~Core();

	Think* cur_thinking()const;
	void pop_thinking();
	void push_thinking(Think* think);
	void tic();
	//virtual void save(FILE *file);
	//virtual void load(FILE *file);
protected:
	class Compare{
		public:
			bool operator() (Think* a, Think* b){
				if(a->think_type()<b->think_type())return true;
				return false;
			}
	};
	virtual void timer_tic()=0;
	void think_timer_tic();
	//virtual void think();
	CubeCreature *creature;
	unsigned think_timer;
	unsigned IQ;
	bool in_think_q[MAX_THINK_NUM];
	std::priority_queue<Think*,std::vector<Think*>,Compare> thinking_q;

};

#endif /* CORE_H_ */
