#include "Game.h"

Game::Game() {
	s_width=1280,s_height=720;
	start();
}
Game::~Game() {
	save_sittings();
}
void Game::start(){
	read_in_settings();
	display=0;
	int c=1;
	char *v[1] = {(char*)" "};
	glutInit(&c,v);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB);
	glutInitWindowSize (s_width,s_height);
	glutInitWindowPosition(0,0);
	glutCreateWindow ("Age Of Cubes");

	push_stage(new Smenu());
}
void Game::read_in_settings(){
	FILE *settings;
	char c[101];
	settings=fopen("files/settings/gamesettings", "r");
	while(fgets(c,101,settings)!=0){
		process_settings(c);
	}
	fclose(settings);
}
bool Game::strcm(char *s1,const char *s2){
	int len1=strlen(s1),len2=strlen(s2);
	int cplen=len1<len2?len1:len2;
	for(int i=0;i<cplen;i++){
		if(s1[i]!=s2[i])return false;
	}
	return true;
}
void Game::process_settings(char c[101]){
	if(c[0]!='#')return;
	if(strcm(c,"#s_width")){
		sscanf(c,"#s_width %d",&s_width);//printf("set width %d\n",s_width);
	}else if(strcm(c,"#s_height")){
		sscanf(c,"#s_height %d",&s_height);//printf("set height %d\n",s_height);
	}else{
		printf("warning!!unknow sitting!!\n");
	}
}
void Game::save_sittings(){
	FILE *settings;
	settings=fopen("files/settings/gamesettings", "r+t");
	fprintf(settings,"#s_width %d\n",s_width);
	fprintf(settings,"#s_height %d\n",s_height);
	fclose(settings);
}
void Game::timer_tick(){
	//std::cout<<"tic1"<<std::endl;
	stages.top()->tic();
	get_signal();//get before stages die
	if(stages.top()->END())pop_stage();
	while(!signal_q.empty()){
		handle_signal(signal_q.front());
		signal_q.pop();
	}
	//std::cout<<"tic2"<<std::endl;
}
void Game::get_signal(){
	while(!(stages.top()->out_signal_q).empty()){
		signal_q.push(stages.top()->out_signal_q.front());
		stages.top()->out_signal_q.pop();
	}
}
void Game::handle_signal(Signal s){
	switch(s.typ()){
		case T_SWITCH_STAGE:
			stage_control(s);
			break;
		case T_GAME_OPERATION:
			game_operation(s);
			break;
		default:
			printf("warning,unknow signal type to game%d\n",s.sig());
	}
}
void Game::stage_control(Signal s){
	switch(s.sig()){
		case S_BACK:
			pop_stage();
			break;
		case S_START:
			printf("Start!!\n");
			break;
		case S_OPTION:
			printf("Option!!\n");
			break;
		case S_CREAT_MAP:
			push_stage(new ScreatMap());
			break;
		case S_PREPARE_SAVE_MAP:
			push_stage(new SsaveMap());
			break;
		case S_PREPARE_LOAD_MAP:
			push_stage(new SloadMap());
			break;
		default:
			printf("warning,unknow stage control signal %d\n",s.sig());
		}
}
void Game::game_operation(Signal s){
	switch(s.sig()){
		case S_LOAD_GAME:
			printf("Load!!\n");
			break;
		case S_SAVE_GAME:
			printf("Save!!\n");
		case S_SAVE_MAP_NAME:
			stages.top()->sent_signal(Signal(S_SAVE_MAP,s.str()));
			break;
		case S_LOAD_MAP_NAME:
			stages.top()->sent_signal(Signal(S_LOAD_MAP,s.str()));
			break;
		default:
			printf("warning,unknow game operation signal %d\n",s.sig());
	}
}
void Game::push_stage(Stage* s){
	stages.push(s);
	display=s->cur_dis();//set_display
	display->window_resize(s_width,s_height);
}
void Game::pop_stage(){
	if(stages.empty())return;
	delete stages.top();
	stages.pop();
	if(!stages.empty())display=stages.top()->cur_dis();
	display->window_resize(s_width,s_height);
}
