#ifndef FCREATMAP_H_
#define FCREATMAP_H_
#include "Field.h"

class FcreatMap : public Field{
public:
	FcreatMap(Mouse *mou,Keyboard *k_b,BasicButList *SLB,Messagebox *_MSB);
	virtual ~FcreatMap();
	virtual void generate_map();
protected:
	virtual void timer_tick();
	void creat_building_button();
};

#endif /* FCREATMAP_H_ */
