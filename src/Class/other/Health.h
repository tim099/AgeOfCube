#ifndef HEALTH_H_
#define HEALTH_H_
#include<cstdio>
class Health {
public:
	Health(int ini_health=0);
	virtual ~Health();
	virtual unsigned max_health()const=0;
	int health()const;
	void health_alter(int delta);
	void set_health(int health);

	void save_health(FILE *file);
	void load_health(FILE *file);
protected:

	int _health;
};

#endif /* HEALTH_H_ */
