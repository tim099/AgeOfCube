#ifndef SIGNAL_H_
#define SIGNAL_H_
#include <string>
#include "signalsdefine.h"
class Signal {
public:
	Signal(int signal,std::string s);
	Signal(int signal,int extra=0);
	Signal();

	virtual ~Signal();
	void set_signal(int signal);
	int sig();
	int typ();
	int layer();
	virtual int extra_sig();
	virtual std::string str();

protected:
	int signal;
	int extra;
	std::string s;
};

#endif /* SIGNAL_H_ */
