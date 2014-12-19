#include <ListButton.h>

ListButton::ListButton(double _size) {
	size=_size;
	creat_all_list();
}
ListButton::~ListButton() {

}
void ListButton::creat_all_list(){
	button b;
	b.normal=creat_texture("files/texture/buttons/BasicButtons/ButtonBasic.bmp",size,b.width,b.height,270,0);
	b.selected=creat_texture("files/texture/buttons/BasicButtons/ButtonSelected.bmp",size,270,0);
	b.pressed=creat_texture("files/texture/buttons/BasicButtons/ButtonPressed.bmp",size,270,0);
	Buttons.push_back(b);

	b.normal=creat_texture("files/texture/buttons/BasicButtons/ButShortnormal.bmp",0.25*size,b.width,b.height,270,0);
	b.selected=creat_texture("files/texture/buttons/BasicButtons/ButShortselected.bmp",0.25*size,270,0);
	b.pressed=creat_texture("files/texture/buttons/BasicButtons/ButShortpressed.bmp",0.25*size,270,0);
	Buttons.push_back(b);

	b.normal=creat_texture("files/texture/buttons/BasicButtons/ButtonMedium.bmp",0.5*size,b.width,b.height,270,0);
	b.selected=creat_texture("files/texture/buttons/BasicButtons/ButtonMediumselected.bmp",0.5*size,270,0);
	b.pressed=creat_texture("files/texture/buttons/BasicButtons/ButtonMediumpressed.bmp",0.5*size,270,0);
	Buttons.push_back(b);
	//printf("button width=%lf,height=%lf\n",b.width,b.height);
}
