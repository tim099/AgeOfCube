#ifndef CONSTRUCTABLE_H_
#define CONSTRUCTABLE_H_
class Resource;
#include <cstdio>
#include <string>
class Constructable {
public:
	Constructable();
	virtual ~Constructable();
	virtual unsigned require_work()const=0;
	virtual Resource require_resources()=0;
	virtual std::string name()=0;

	void save_constructable(FILE *file);
	void load_constructable(FILE *file);

	void construct_now();//cheat

	bool unfinished()const;
	bool construct(unsigned work);
	unsigned cur_work()const;

protected:
	bool detect_finished();
	bool _unfinished;
	unsigned _cur_work;
};

#endif /* CONSTRUCTABLE_H_ */
