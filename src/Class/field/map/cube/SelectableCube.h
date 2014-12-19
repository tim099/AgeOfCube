#ifndef SELECTABLECUBE_H_
#define SELECTABLECUBE_H_
#include "MiscTexDefine.h"
class SelectableCube {
public:
	SelectableCube();
	virtual ~SelectableCube();
	virtual bool selectable()const;

	void select();
	void deselect();
	bool selected()const;

protected:
	void dp_selected();
	bool _selected;
};

#endif /* SELECTABLECUBE_H_ */
