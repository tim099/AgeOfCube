#ifndef DPSTART_H_
#define DPSTART_H_
#include "Display.h"
#include "bmp/ListFonts.h"
#include "SButtonList.h"
class DPstart : public Display{
public:
	DPstart(ButtonList* SLB,Mouse *mou);
	virtual ~DPstart();
	virtual void display();

protected:
	virtual void prepare_list();
	void dp_texture();
	ListFonts *fonts;

};

#endif
