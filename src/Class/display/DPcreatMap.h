#ifndef DPCREATMAP_H_
#define DPCREATMAP_H_
#include <ctime>
#include "DPfield.h"
#include "ListBasicCubes.h"
#include "Field.h"
class DPcreatMap : public DPfield{
public:
	DPcreatMap(ButtonList* SLB,Field *field,Mouse *mou);
	virtual ~DPcreatMap();
	virtual void display();
protected:
	virtual void prepare_list();
	void dp_field();
};

#endif /* DPCREATMAP_H_ */
