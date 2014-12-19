#include <Message.h>

Message::Message(std::string _message,int _time,int _blink,int _interval) {
	message=_message;
	_end=false;
	blink=_blink																																																																																												;
	interval=_interval;
	time=_time;
}
Message::~Message() {

}
bool Message::end()const{
	return _end;
}
void Message::tic(){
	if(time)time--;
	else _end=true;
}
bool Message::show()const{
	if((time%interval)<blink){
		return true;
	}
	return false;
}
