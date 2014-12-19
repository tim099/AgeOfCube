#include "Map.h"
#include "CreatureMap.h"
Map::Map(std::queue<DeletableCube*>*_delete_q,std::queue<CubeCreature*>*_creatures,unsigned _msx,unsigned _msy,unsigned _msz) {
	delete_q=_delete_q;
	creatures=_creatures;
	seed=0;
	set_map_size(_msx,_msy,_msz);
	path=new Path(_msx,_msy,_msz,this);
	for(int i=0;i<MAX_X;i++){
		for(int j=0;j<MAX_Y;j++){
			for(int k=0;k<MAX_Z;k++){
				map[i][j][k]=0;
			}
		}
	}
	CubeNull=new BasicCube(C_NULL);
	CubeOutOfEdge =new BasicCube(C_OUT_OF_EDGE);
	creature_map=new CreatureMap(creatures,this);
}
Map::~Map() {
	delete CubeNull;
	delete CubeOutOfEdge;
	clear_map();
}
void Map::clear_map(){
	delete path;
	for(unsigned i=0;i<MSX();i++){
		for(unsigned j=0;j<MSY();j++){
			for(unsigned k=0;k<MSZ();k++){
				if(map[i][j][k]!=0){
					if(map[i][j][k]->C_TYP()==C_CUBE){
						delete map[i][j][k];//except buildings?
					}
				}
				map[i][j][k]=0;
			}
		}
	}
	while(!buildings.empty()){
		delete buildings.front();
		buildings.pop();
	}
	delete creature_map;
}
void Map::update_all_path(){
	for(unsigned i=0;i<MSX();i++){
		for(unsigned j=0;j<MSY();j++){
			for(unsigned k=0;k<MSZ();k++){
				update_path(i,j,k);
			}
		}
	}
}
void Map::update_path(int x,int y,int z){
	unsigned char this_path=get_map(x,y,z)->get_path();
	unsigned char extra_path=get_map(x,y,z)->get_extra_path();
	unsigned char _path=0;
	if(get_map(x,y-1,z)->get_path()&M_STANDABLE){//can stand on so can move horizontal
		if((get_map(x+1,y,z)->get_path()&M_LEFT)&&((get_map(x+1,y,z)->get_extra_path()&M_EX_DOWN_STANDABLE)||
				(get_map(x+1,y-1,z)->get_path()&M_STANDABLE))){
			if(!(extra_path&M_EX_NOT_RIGHT))_path|=M_RIGHT;//move right = right cube left side
		}
		if((get_map(x-1,y,z)->get_path()&M_RIGHT)&&((get_map(x-1,y,z)->get_extra_path()&M_EX_DOWN_STANDABLE)||
				(get_map(x-1,y-1,z)->get_path()&M_STANDABLE))){
			if(!(extra_path&M_EX_NOT_LEFT))_path|=M_LEFT;
		}
		if((get_map(x,y,z+1)->get_path()&M_BACK)&&((get_map(x,y,z+1)->get_extra_path()&M_EX_DOWN_STANDABLE)||
				(get_map(x,y-1,z+1)->get_path()&M_STANDABLE))){
			if(!(extra_path&M_EX_NOT_FRONT))_path|=M_FRONT;
		}
		if((get_map(x,y,z-1)->get_path()&M_FRONT)&&((get_map(x,y,z-1)->get_extra_path()&M_EX_DOWN_STANDABLE)||
				(get_map(x,y-1,z-1)->get_path()&M_STANDABLE))){
			if(!(extra_path&M_EX_NOT_BACK))_path|=M_BACK;
		}
	}
	if((get_map(x,y+1,z)->get_path()&M_DOWN)&&(this_path&M_LIFTABLE)){
		if(!(extra_path&M_EX_NOT_UP))_path|=M_UP;
		_path|=M_LIFTABLE;
	}
	if((get_map(x,y-1,z)->get_path()&M_UP)){
		if(!(extra_path&M_EX_NOT_DOWN))_path|=M_DOWN;
	}
	if((M_STANDABLE&this_path)||((get_map(x,y+1,z)->get_extra_path()&M_EX_DOWN_STANDABLE))){
		_path|=M_STANDABLE;
	}
	path->set_path(x,y,z,(_path&this_path));
}
void Map::update_pos(int x,int y,int z){
	Building *b=get_map(x,y,z)->get_building();
	if(b){
		if(!can_build_on(b)){
			delete_cube(x,y,z);
		}
	}
	update_path(x,y,z);
}
void Map::update_cube(int x,int y,int z){
	for(int i=-1;i<=1;i++){
		for(int j=-1;j<=1;j++){
			for(int k=-1;k<=1;k++){
				update_pos(x+i,y+j,z+k);
			}
		}
	}
}
void Map::push_building(Building *building){
	buildings.push(building);
	delete_q->push(building);
}
void Map::tic(){
	unsigned size=buildings.size();
	Building *b_p;
	for(unsigned i=0;i<size;i++){
		b_p=buildings.front();
		buildings.pop();
		if(b_p->exist())buildings.push(b_p);
	}
	path->tic();
}
void Map::set_map_size(unsigned _msx,unsigned _msy,unsigned _msz){
	msx=_msx<MAX_X?_msx:MAX_X;
	msy=_msy<MAX_Y?_msy:MAX_Y;
	msz=_msz<MAX_Z?_msz:MAX_Z;
}
bool Map::build(Building *building){
	int at=0,buff=building->belong_to();
	while(buff>1){
		buff>>=1;
		at++;
	}
	if(!buildable(building))return false;
	map[building->get_x()][building->get_y()][building->get_z()]=building;
	push_building(building);

	update_cube(building->get_x(),building->get_y(),building->get_z());
	return true;
}
bool Map::can_build_on(Building *building){
	int b_x=building->get_x(),b_y=building->get_y(),b_z=building->get_z();
	if(building->can_build_on()&ON_BUT)if(get_map(b_x,b_y-1,b_z)->buildable())return true;
	if(building->can_build_on()&ON_TOP)if(get_map(b_x,b_y+1,b_z)->buildable())return true;
	if(building->can_build_on()&ON_LEFT)if(get_map(b_x-1,b_y,b_z)->buildable())return true;
	if(building->can_build_on()&ON_RIGHT)if(get_map(b_x+1,b_y,b_z)->buildable())return true;
	if(building->can_build_on()&ON_FRONT)if(get_map(b_x,b_y,b_z+1)->buildable())return true;
	if(building->can_build_on()&ON_BACK)if(get_map(b_x,b_y,b_z-1)->buildable())return true;
	return false;
}
bool Map::buildable(Building *building){
	if(get_map(building->get_x(),building->get_y(),building->get_z())->typ()!=C_NULL)return false;
	return can_build_on(building);
}
void Map::Save_Map(FILE *fop){
	fprintf(fop,"%d %d %d\n",msx,msy,msz);
	fprintf(fop,"%u\n",seed);
	for(unsigned i=0;i<msx;i++){
		for(unsigned j=0;j<msy;j++){
			for(unsigned k=0;k<msz;k++){
				if(get_map(i,j,k)->C_TYP()==C_BASIC_CUBE)get_map(i,j,k)->save(fop);
				else fprintf(fop,"0\n");
			}
		}
	}
}
void Map::Load_Map(FILE *fop){
	clear_map();

	int type;
	fscanf(fop,"%d %d %d\n",&msx,&msy,&msz);
	fscanf(fop,"%u\n",&seed);
	path=new Path(msx,msy,msz,this);
	creature_map=new CreatureMap(creatures,this);
	for(unsigned i=0;i<msx;i++){
		for(unsigned j=0;j<msy;j++){
			for(unsigned k=0;k<msz;k++){
				fscanf(fop,"%d",&type);
				if(type==0)map[i][j][k]=0;
				if(type>=C_CUBE&&type<C_BUILDING){
					map[i][j][k]=new BasicCube(type);
					map[i][j][k]->load(fop);
				}
			}
		}
	}
	update_all_path();
}
unsigned Map::MSX()const{return msx;}
unsigned Map::MSY()const{return msy;}
unsigned Map::MSZ()const{return msz;}

void Map::generate_mountain(){
	int max_m_n=100;
	int m_n=rand()%max_m_n+280;
	for(int i=0;i<m_n;i++)creat_mountain(Pos(rand()%msx,rand()%msy,rand()%msz));
}
void Map::creat_mountain(Pos pos){
	bool but=false;
	StaticCube* cube;
	int m_size=30;
	for(unsigned y=0;y<msy;y++){
		cube=get_map(pos.x,y,pos.z);
		if(cube->typ()==C_NULL&&but){//start
			pos.y=y;

			creat_flate_circle(pos,rand()%m_size+1,C_BASIC);
			break;
		}
		if(cube->C_TYP()==C_CUBE)but=true;
		else but=false;

	}
}
void Map::generate_map(unsigned _seed){
	seed=_seed;
	srand(seed);

	generate_mountain();
	for(int i=0;i<15;i++){
		creat_ball(Pos(rand()%msx,rand()%(msy-20)+10,rand()%msz),rand()%30+5,C_DARK);
	}
}
void Map::creat_flate_circle(Pos o,unsigned r,int type){
	for(int i=-r;i<=(int)r;i++){
		for(int j=-r;j<=(int)r;j++){
			if(sqrt(i*i+j*j)<=(double)r){
				if(get_map(o.x+i,o.y-1,o.z+j)->C_TYP()==C_BASIC_CUBE)
				creat_cube(o.x+i,o.y,o.z+j,type);
			}
		}
	}
}
void Map::creat_ball(Pos o,unsigned r,int type){
	for(int i=-r;i<=(int)r;i++){
		for(int j=-r;j<=(int)r;j++){
			for(int k=-r;k<(int)r;k++){
				if(sqrt(i*i+j*j+k*k)<(double)r){
					delete_cube(o.x+i,o.y+j,o.z+k);
					creat_cube(o.x+i,o.y+j,o.z+k,type);
				}
			}
		}
	}
}
void Map::creat_map_flat(unsigned sx,unsigned sy,unsigned sz,int type,unsigned spx,unsigned spy,unsigned spz){
	if(spx>=msx||spy>=msy||spz>=msz)return ;
	sx=sx<(msx-spx)?sx:(msx-spx);
	sy=sy<(msy-spy)?sy:(msy-spy);
	sz=sz<(msz-spz)?sz:(msz-spz);
	for(unsigned i=0;i<sx;i++){
		for(unsigned j=0;j<sy;j++){
			for(unsigned k=0;k<sz;k++){
				if(map[i+spx][j+spy][k+spz]==0)map[i+spx][j+spy][k+spz]=new BasicCube(type);
			}
		}
	}
	update_all_path();
}
StaticCube* Map::get_map(int x,int y,int z){
	if(x<0||y<0||z<0)return CubeOutOfEdge;
	if(x>=(int)msx||y>=(int)msy||z>=(int)msz)return CubeOutOfEdge;
	if(map[x][y][z]!=0)return map[x][y][z];
	else return CubeNull;
}
StaticCube* Map::get_map(unsigned pos){
	unsigned x,y,z;
	path->convert_pos(pos,x,y,z);
	return get_map(x,y,z);
}
bool Map::see_map(int x,int y,int z,int player){
	StaticCube *c=get_map(x,y,z);
	if(c->typ()>C_CUBE){
		return c->see(player);
	}else return false;
}
void Map::discover(int x,int y,int z,int player){
	StaticCube *c=get_map(x,y,z);
	if(c->typ()>C_CUBE){
		c->discover(player);
	}
}
void Map::delete_cube(int x,int y,int z){
	StaticCube *c=get_map(x,y,z);
	if(c->typ()<C_CUBE)return;//not cube
	switch(c->C_TYP()){
		case C_CUBE:
			delete map[x][y][z];
			break;
		case C_BUILDING:
			c->delete_cube(3);//in 3 tics
			break;
		default:;
	}
	map[x][y][z]=0;
	update_cube(x,y,z);
}
bool Map::creatable(int x,int y,int z){
	if(get_map(x,y,z)->typ()!=C_NULL)return false;
	return true;
}
void Map::creat_cube(int x,int y,int z,int c_type){
	if(!creatable(x,y,z))return;
	map[x][y][z]=new BasicCube(c_type);
	update_cube(x,y,z);
}
Path *Map::get_path()const{
	return path;
}
