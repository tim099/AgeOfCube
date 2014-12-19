#include <PlayerOwnObject.h>

PlayerOwnObject::PlayerOwnObject(int _player) {
	player=_player;

}
PlayerOwnObject::~PlayerOwnObject() {

}
void PlayerOwnObject::save_player(FILE *file){
	fprintf(file,"%d ",player);
}
void PlayerOwnObject::load_player(FILE *file){
	fscanf(file,"%d ",&player);
}
int PlayerOwnObject::player_num()const{
	int num=0,buff=player;
	while(buff>1){
		buff>>=1;
		num++;
	}
	return num;
}
int PlayerOwnObject::belong_to()const{
	return player;
}
