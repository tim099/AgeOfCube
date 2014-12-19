#include <ExecuteButton.h>

ExecuteButton::ExecuteButton(std::string name,double width,double height,int type)
: BasicButton(name,width,height,type){

}
ExecuteButton::~ExecuteButton() {
	while(!executes.empty()){
		delete executes.back();
		executes.pop_back();
	}
}
void ExecuteButton::push_execute(Execute* execute){
	executes.push_back(execute);
}
void ExecuteButton::pressed(){
	for(unsigned i=0;i<executes.size();i++){
		executes.at(i)->execute();
	}
}
