#ifndef CALL_BACK
#define CALL_BACK

void display(){
	//clock_t start_time=clock(),time_cost;

	game->display->display();

	//time_cost=(clock()-start_time);
	//printf("render_time_cost=%lfsec\n",(double)time_cost/(double)(CLOCKS_PER_SEC));
}
void keyboard(unsigned char key, int x, int y){
	game->stages.top()->k_b.keyboard(key,x,y);
}
void keyboard_up(unsigned char key, int x, int y){
	game->stages.top()->k_b.keyboard_up(key,x,y);
}
void Specialkeyboard(int key, int x, int y){
	game->stages.top()->k_b.Specialkeyboard(key,x,y);
}
void Specialkeyboard_up(int key, int x, int y){
	game->stages.top()->k_b.Specialkeyboard_up(key,x,y);
}
void mouse(int button, int state, int x, int y){
	game->stages.top()->mou.mouse(button,state,x,y);
}
void mouseWheel(int button, int dir, int x, int y){
	game->stages.top()->mou.mouseWheel(button,dir,x,y);
}
void glutPassiveMotionFunc(int x, int y){
	game->stages.top()->mou.glutPassiveMotionFunc(x,y);
}
void glutMotionFunc(int x, int y){
	game->stages.top()->mou.glutPassiveMotionFunc(x,y);
}
void timer(int t){
	glutTimerFunc(16, timer, 0);
	game->timer_tick();
}
void resize(int w,int h){
	w=w>1?w:1;h=h>1?h:1;
	game->display->window_resize(w,h);
	game->s_width=w;
	game->s_height=h;
}
void callbackrigister(){
glutDisplayFunc (display);//call display function
glutReshapeFunc(resize);
glutKeyboardFunc(keyboard);
glutKeyboardUpFunc(keyboard_up);
glutSpecialFunc(Specialkeyboard);
glutSpecialUpFunc(Specialkeyboard_up);
glutMouseFunc(mouse);
glutMouseWheelFunc(mouseWheel);
glutPassiveMotionFunc(glutPassiveMotionFunc);
glutMotionFunc(glutMotionFunc);
glutTimerFunc(20,timer,0);//timer_start
glutMainLoop();
}
#endif
