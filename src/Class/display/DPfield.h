#ifndef DPFIELD_H_
#define DPFIELD_H_
#include "Display.h"
#include "ListBasicCubes.h"
#include "Field.h"
#include "playerdefine.h"
#include "ListBuildings.h"
#include "ListCreature.h"
#include "ListResources.h"
#include "ListMisc.h"
#include "ListBar.h"
class DPfield : public Display{
public:
	DPfield(Mouse *mou);
	virtual ~DPfield();
	void set_field(Field* field);
protected:
	void read_file();
	void save_file();
	void dp_field_mode();
	void dp_Cube(unsigned i,unsigned j,unsigned k);
	void dp_building(unsigned min_x,unsigned min_z,unsigned max_x,unsigned max_z);
	void dp_creature(int min_x,int min_z,int max_x,int max_z);
	void dp_map();
	Field *field;
	ListBasicCubes *LBC;
	ListBuildings *LBD;
	ListCreature *LCT;
	ListResources *LRC;
	ListMisc *LMC;
	ListBar *LBR;
};

#endif /* DPFIELD_H_ */
