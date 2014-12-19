#include <SelectableCube.h>
SelectableCube::SelectableCube() {
	_selected=false;
}
SelectableCube::~SelectableCube() {

}
bool SelectableCube::selected()const{
	return _selected;
}
void SelectableCube::select(){
	_selected=true;
}
bool SelectableCube::selectable()const{
	return true;
}
void SelectableCube::deselect(){
	_selected=false;
}
void SelectableCube::dp_selected(){
	if(selected()){
		glCallList(MISC_SELECTED);
	}
}
