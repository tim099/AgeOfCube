#include <MessageBox.h>

Messagebox::Messagebox() {
	lf=new ListFonts(0.0009);
	cur_dp_message=0;
}
Messagebox::~Messagebox() {
	delete lf;
}
void Messagebox::push_message(Message *message){
	messages.push(message);
}
void Messagebox::tic(){
	int num=messages.size();
	Message *buff;
	for(int i=0;i<num;i++){
		buff=messages.front();
		messages.pop();
		buff->tic();
		if(buff->end()){
			delete buff;
		}else messages.push(buff);
	}
}
void Messagebox::dp_message_box(){
	glPushMatrix();
	glLoadIdentity();
	cur_dp_message=0;
	int num=messages.size();
		Message *buff;
		for(int i=0;i<num;i++){
			buff=messages.front();
			messages.pop();
			dp_message(buff);
			messages.push(buff);
		}
	glPopMatrix();
}
void Messagebox::dp_message(Message *message){
	if(message->show()){
		glPushMatrix();
		glTranslatef(-0.04,0.005-0.0023*cur_dp_message,-0.099);
		lf->call_string(message->message.c_str());
		glPopMatrix();
	}
	cur_dp_message++;
}
