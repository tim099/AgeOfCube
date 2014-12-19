#ifndef MESSAGEBOX_H_
#define MESSAGEBOX_H_
#include <queue>
#include "Message.h"
#include "ListFonts.h"
class Messagebox {
public:
	Messagebox();
	virtual ~Messagebox();
	void push_message(Message *message);
	void tic();
	void dp_message_box();
protected:
	void dp_message(Message *message);
	ListFonts *lf;
	std::queue<Message*> messages;
	int cur_dp_message;
};

#endif /* MESSAGEBOX_H_ */
