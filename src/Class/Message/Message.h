#ifndef MESSAGE_H_
#define MESSAGE_H_
#include<string>

class Message {
public:
	Message(std::string message,int time=50,int blink=0,int interval=0);
	virtual ~Message();
	bool end()const;
	void tic();
	bool show()const;
	std::string message;
private:
	bool _end;
	int blink,interval;
	int time;
};

#endif /* MESSAGE_H_ */
