#ifndef BASICBUTGROUP_H_
#define BASICBUTGROUP_H_

#include <vector>
#include "button_group_signal_define.h"
#include "BasicButton.h"
#include "ButSignal.h"

const int S_NEXT_PAGE = 0;
const int S_PREV_PAGE = 1;
class BasicButGroup : public ButSignal{
public:
	BasicButGroup(unsigned but_per_page=1000);
	virtual ~BasicButGroup();
	virtual void handle_signal(Signal sig);

	void push_button(BasicButton* but);
	void push_indie_button(BasicButton* but);
    void push_sub_group(BasicButGroup* group);

	void tic();
	unsigned size();
	void delete_group();

	bool END()const;
	void set_state(bool active);
	bool get_state();

	void prev_page();
	void next_page();

	void set_auto_pos(double g_px,double g_py,double disx,double disy,unsigned but_per_page);
	void turn_off_auto_pos();

protected:
	virtual void timer_tic();
	void clear_delete_but();
	void construct_cur_page();
	void remove_but(unsigned i);
	void auto_position();
	void dp_cur_page();
	std::vector<BasicButton*>all_buts;
	std::vector<BasicButton*>sort_buts;
	std::vector<BasicButton*>indie_buts;
	std::vector<BasicButton*>cur_page;
	std::vector<BasicButGroup*> sub_group;

	bool active;
	bool auto_pos;
	bool _end;
	double g_px,g_py,disx,disy;
	unsigned but_per_page;
	unsigned cur_page_at;
};

#endif
