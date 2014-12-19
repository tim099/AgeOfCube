#include <BasicButton.h>

BasicButton::BasicButton(std::string _name,double _width,double _height,int type) {
	name=_name;
	height=_height;
	width=_width;
	_type=type;
}
BasicButton::~BasicButton() {

}
ShowButGroupButton* BasicButton::ShowButGroupBut(){
	return 0;
}
int BasicButton::type()const{
	return _type;
}
void BasicButton::set_name(std::string _name){
	name =_name;
}


