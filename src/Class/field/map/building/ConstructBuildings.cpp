#include "ConstructBuildings.h"
#include "Player.h"
ConstructBuildings::ConstructBuildings(std::vector<Player>*_players,Map *_map) {
	players=_players;
	map=_map;
}
ConstructBuildings::~ConstructBuildings() {

}
Building* ConstructBuildings::building(int type){
	return build(0,0,0,type,0,false);
}
Building* ConstructBuildings::build(int x,int y,int z,int type,int player,bool unfinished){
	Building *b;
	int player_num=players->at(0).player_num(player);//convert!!
	Player *cur_player=&(players->at(player_num));
	switch(type){
		case C_BASE:
			b=new Base(x,y,z,cur_player,player);
			break;
		case C_ELEVATOR:
			b=new Elevator(x,y,z,cur_player,player);
			break;
		case C_ONE_WAY:
			b=new OneWay(x,y,z,cur_player,map,player);
			break;
		case C_UNFINISHED_BUILDING:
			b=new UnfinishedBuilding(x,y,z,cur_player,0,this,player);
			break;
		default:
			printf("unknow building type %d\n",type);
			return 0;
	}
	if(unfinished){
		Building *unfinished=new UnfinishedBuilding(x,y,z,cur_player,b,this,player);
		cur_player->push_unfinished_building(b);
		unfinished->construct_now();
		return unfinished;
	}else{
		b->construct_now();
		return b;
	}
}
