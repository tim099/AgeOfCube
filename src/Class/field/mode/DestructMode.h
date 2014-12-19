#ifndef DESTRUCTMODE_H_
#define DESTRUCTMODE_H_
#include "Mode.h"
#include "map/Map.h"
#include "Mouse.h"
class DestructMode : public Mode{
public:
	DestructMode(Mouse *mou,Map *map);
	virtual ~DestructMode();
	virtual void dp_mode();
	virtual int get_mode()const;
protected:
	virtual void timer_tic();
	Mouse *mou;
	Map *map;
};

#endif /* DESTRUCTMODE_H_ */
