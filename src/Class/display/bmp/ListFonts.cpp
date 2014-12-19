#include <ListFonts.h>

ListFonts::ListFonts(double _size) {
size = _size;
creat_all_list();
}
ListFonts::~ListFonts() {

}
void ListFonts::call_string(int num){
	char s[50]={0};
	sprintf(s,"%d",num);
	call_string(s);
}
void ListFonts::creat_all_list(){
	char c[40]="files/texture/fonts/capital/A.bmp";
	GLuint list;
	for(char i='A';i<='Z';i++){
		c[28]=i;
		list=creat_texture(c,size,270,0);
		cap_fonts.push_back(list);
	}
	char b[40]="files/texture/fonts/lowercase/a.bmp";
	for(char i='a';i<='z';i++){
		b[30]=i;
		list=creat_texture(b,size,270,0);
		fonts.push_back(list);
	}
	char n[40]="files/texture/fonts/numbers/0.bmp";
	for(char i='0';i<='9';i++){
		n[28]=i;
		list=creat_texture(n,size,270,0);
		numbs.push_back(list);
	}
}
void ListFonts::call_string(const char *str){
	int len=strlen(str);
	double dis=1.375*size;
	for(int i=0;i<len;i++){
		//a=97,A=65
		glPushMatrix();
		glTranslatef((i-0.5*(len-1))*dis,0,0);
		if(str[i]==' '){
		}else if(str[i]>='a'){
			glCallList(fonts.at(str[i]-'a'));
		}else if(str[i]>='A'){
			glCallList(cap_fonts.at(str[i]-'A'));
		}else if(str[i]>='0'){
			glCallList(numbs.at(str[i]-'0'));
		}
		glPopMatrix();
	}

}

