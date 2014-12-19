#include "CreatCreature.h"
#include "Player.h"
CreatCreature::CreatCreature(Map* _map,std::vector<Collidable*>*_colli_v,std::vector<Player>*_players) {
map=_map;
colli_v=_colli_v;
players=_players;
}
CreatCreature::~CreatCreature() {

}
CubeCreature* CreatCreature::creat_creature(int type,double pos_x,double pos_y,double pos_z,int player){
	CubeCreature *c;
	int player_num=players->at(0).player_num(player);//convert!!
	switch(type){
		case C_CUBE_WORKER:
			c=new CubeWorker(pos_x,pos_y,pos_z,player,map,colli_v,&(players->at(player_num).creatures)
					,&(players->at(player_num).buildings));
			break;
		default:
			printf("cant creat unknow type creature %d \n",type);
	}
	c->set_health(c->max_health());
return c;
}
