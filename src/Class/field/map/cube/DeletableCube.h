#ifndef DELETABLECUBE_H_
#define DELETABLECUBE_H_

class DeletableCube {
public:
	DeletableCube();
	virtual ~DeletableCube();
	void terminate_timer_tic();
	void delete_cube(int timer=10);
	bool exist()const;
	bool terminate()const;
protected:
	int terminate_timer;
	bool _exist;
	bool _terminate;
};

#endif /* DELETABLECUBE_H_ */
