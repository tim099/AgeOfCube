#ifndef SCREATMAP_H_
#define SCREATMAP_H_
#include "Stage.h"
#include "DPcreatMap.h"
#include "CreatMapButList.h"
#include "FcreatMap.h"
class ScreatMap : public Stage{
public:
	ScreatMap();
	virtual ~ScreatMap();
	virtual Display* cur_dis();//could have multiple display object
protected:
	virtual void timer_tick();

	virtual void signal_under_stage(Signal s);
	virtual void Stage_signal_process(Signal s);

	void save_field(std::string file_name);
	void load_field(std::string file_name);
	FcreatMap *field;
	DPcreatMap *dp_map;
	Messagebox *MSB;
};

#endif /* SCREATMAP_H_ */
