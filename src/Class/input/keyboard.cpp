#include"keyboard.h"
Keyboard::Keyboard(){
	clear();
}
bool Keyboard::get(unsigned char key){
	int c=key;
	if(input_times[c]>0){
		input_times[c]--;
		return true;
	}
return false;
}
void Keyboard::clear(){
	w=false,a=false,s=false,d=false,q=false,e=false,r=false,f=false,esc=false,enter=false;
	t=false;g=false;space=false;shift=false;
	up=false,down=false,left=false,right=false;v=false;z=false;x=false;c=false;n=false;b=false;
	p=false;o=false;backspace=false;plus=false;minus=false;
	for(int i=0;i<300;i++)input_times[i]=0;
	for(int i=0;i<300;i++)input[i]=0;
}
void Keyboard::keyboard(unsigned char key, int _x, int _y) {
	int c=key;
	if(input_times[c]<10)input_times[c]++;
	input[key]=true;
	switch (key) {
		case 'w':
			w = true;
			break;
		case 'a':
			a = true;
			break;
		case 's':
			s = true;
			break;
		case 'd':
			d = true;
			break;
		case 'q':
			q = true;
			break;
		case 'e':
			e = true;
			break;
		case 'r':
			r = true;
			break;
		case 'f':
			f = true;
			break;
		case 't':
			t = true;
			break;
		case 'g':
			g = true;
			break;
		case 'z':
			z =true;
			break;
		case 'x':
			x =true;
			break;
		case 'c':
			c =true;
			break;
		case 'v':
			v =true;
			break;
		case 'n':
			n =true;
			break;
		case 'b':
			b =true;
			break;
		case 'p':
			p =true;
			break;
		case 'o':
			o =true;
			break;
		case '+':
			plus=true;
			break;
		case '-':
			minus=true;
			break;
		case 8:
			backspace=true;
			break;
		case 13: //ENTER
			enter = true;
			break;
		case 27: //esc
			esc = true;
			break;
		case' ':
			space =true;
			break;
		}
}
void Keyboard::keyboard_up(unsigned char key, int _x, int _y) {
	input[key]=false;
	switch (key) {
	case 'w':
		w = false;
		break;
	case 'a':
		a = false;
		break;
	case 's':
		s = false;
		break;
	case 'd':
		d = false;
		break;
	case 'q':
		q = false;
		break;
	case 'e':
		e = false;
		break;
	case 'r':
		r = false;
		break;
	case 'f':
		f = false;
		break;
	case 't':
		t = false;
		break;
	case 'g':
		g = false;
		break;
	case 'z':
		z = false;
		break;
	case 'x':
		x = false;
		break;
	case 'c':
		c = false;
		break;
	case 'v':
		v =false;
		break;
	case 'n':
		n =false;
		break;
	case 'b':
		b =false;
		break;
	case 'p':
		p =false;
		break;
	case 'o':
		o =false;
		break;
	case '+':
		plus=false;
		break;
	case '-':
		minus=false;
		break;
	case 8:
		backspace=false;
		break;
	case 13: //ENTER
		enter = false;
		break;
	case 27: //esc
		esc = false;
		break;
	case' ':
		space =false;
		break;
	}
}
void Keyboard::Specialkeyboard(int key, int x, int y){
	switch(key){
	case GLUT_KEY_UP:
		up=true;
		break;
	case GLUT_KEY_DOWN:
		down=true;
		break;
	case GLUT_KEY_LEFT:
		left=true;
		break;
	case GLUT_KEY_RIGHT:
		right=true;
		break;
	}
}
void Keyboard::Specialkeyboard_up(int key, int x, int y){
	switch(key){
	case GLUT_KEY_UP:
		up=false;
		break;
	case GLUT_KEY_DOWN:
		down=false;
		break;
	case GLUT_KEY_LEFT:
		left=false;
		break;
	case GLUT_KEY_RIGHT:
		right=false;
		break;

	}
}
