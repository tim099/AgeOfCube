#ifndef WORKABLE_H_
#define WORKABLE_H_
class CubeWorker;
class Constructable;
class Workable {
public:
	Workable();
	virtual ~Workable();
protected:
	virtual void construct(unsigned work)=0;
	virtual Constructable* cur_constructing()const=0;
	void get_work(CubeWorker *worker);
};

#endif /* WORKABLE_H_ */
