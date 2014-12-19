#include "map/Path.h"
#include "map/Map.h"
#include "CreatureMap.h"
#include "StaticCube.h"
#include "Search.h"
#include "SearchCreature.h"
#include "CubeCreature.h"
Path::Path(int _msx,int _msy,int _msz,Map *_map) {
	initialize(_msx,_msy,_msz,_map);
	memset(path,0,msx*msy*msz*sizeof(unsigned char));
}
Path::Path(Path &p,Map *_map){
	initialize(p.msx,p.msy,p.msz,_map);
	memcpy(path,p.path,msx*msy*msz*sizeof(unsigned char));
}
void Path::initialize(int _msx,int _msy,int _msz,Map *_map){
	time_used=0;
	msx=_msx;msy=_msy;msz=_msz;
	map=_map;
	path=new unsigned char[msx*msy*msz];
	route_map=0;
	route_dis=0;
	search_map=0;
}
Path::~Path() {
	delete[] path;
	if(route_map!=0)delete[] route_map;
	if(route_dis!=0)delete[] route_dis;
	if(search_map!=0)delete[]search_map;
	while(!route_v.empty()){
		delete route_v.back();
		route_v.pop_back();
	}
}
void Path::tic(){
	time_used=0;
	F_R* fr;
	while(!find_route_q.empty()&&time_used<MAX_TIME_USED){
		fr=find_route_q.front();
		find_route_q.pop();
		if(fr->r->find()==R_NOT_YET_FIND){
			find_route(fr->r,fr->start,fr->destination,fr->max_time,fr->min_time);
		}else{//stop finding!!
			fr->r->delete_route();
		}
		delete fr;
	}
	for(unsigned i=0;i<route_v.size();i++){
		if(!route_v.at(i)->exits()){
			delete route_v.at(i);
			route_v.at(i)=route_v.back();
			route_v.pop_back();
		}
	}
}
bool Path::time_out()const{
	if(time_used>MAX_TIME_USED)return true;
	else return false;
}
void Path::creat_route_map(){
	if(route_map==0)route_map=new unsigned[msx*msy*msz];
	if(route_dis==0)route_dis=new unsigned[msx*msy*msz];
	memset(route_dis,255,msx*msy*msz*sizeof(unsigned));//max!!
}
void Path::creat_search_map(){
	if(search_map==0)search_map=new bool[msx*msy*msz];
	memset(search_map,0,msx*msy*msz*sizeof(bool));
}
Route* Path::push_find_route(int s_x,int s_y,int s_z,int d_x,int d_y,int d_z
		,unsigned max_time,unsigned min_time){
	F_R* f_r=new F_R(convert_pos(s_x,s_y,s_z),convert_pos(d_x,d_y,d_z),max_time,min_time);
	find_route_q.push(f_r);
	route_v.push_back(f_r->r);
	return f_r->r;
}
void Path::search(int s_x,int s_y,int s_z,Search* check
		,std::vector<StaticCube*> &find_v,unsigned num,unsigned max_time,std::vector<Route::point>*find_p){
	clock_t start_time=clock(),time_cost;
	creat_search_map();
	std::queue<unsigned>search_q;
	bool end=false;
	unsigned start=convert_pos(s_x,s_y,s_z),cur_at,times=0;
	unsigned next_arr[6],in_arr;
	search_q.push(start);
	search_map[start]=true;
	StaticCube* cube;
	while(!end){
		cur_at=search_q.front();
		search_q.pop();
		cube=map->get_map(cur_at);
		if(check->check_search(cube)){//find
			find_v.push_back(cube);
			if(find_p){//if need to get find pos!!
				find_p->push_back(convert_pos(cur_at));
			}
		}
		in_arr=0;
		if(path[cur_at]&M_RIGHT)next_arr[in_arr++]=(cur_at+msy*msz);
		if(path[cur_at]&M_LEFT)next_arr[in_arr++]=(cur_at-msy*msz);
		if(path[cur_at]&M_UP)next_arr[in_arr++]=(cur_at+msz);
		if(path[cur_at]&M_DOWN)next_arr[in_arr++]=(cur_at-msz);
		if(path[cur_at]&M_FRONT)next_arr[in_arr++]=(cur_at+1);
		if(path[cur_at]&M_BACK)next_arr[in_arr++]=(cur_at-1);
		for(unsigned i=0;i<in_arr;i++){
			unsigned next=next_arr[i];
			if(!search_map[next]){//not search yet
				search_map[next]=true;
				search_q.push(next);
			}
		}
		times++;
	//	printf("search times=%u\n",times);
		if(find_v.size()>=num)end=true;
		if(times>max_time)end=true;
		if(search_q.empty())end=true;
	}
	time_cost=(clock()-start_time);
	time_used+=(time_cost+1);
	delete check;
}
void Path::search(int s_x,int s_y,int s_z,SearchCreature* check,std::vector<CubeCreature*> &find_v
		,unsigned num,unsigned max_time){
		clock_t start_time=clock(),time_cost;
		creat_search_map();
		std::queue<unsigned>search_q;
		std::vector<CubeCreature*>*c_v;
		bool end=false;
		unsigned start=convert_pos(s_x,s_y,s_z),cur_at,times=0;
		unsigned next_arr[6],in_arr;
		search_q.push(start);
		search_map[start]=true;
		while(!end){
			cur_at=search_q.front();
			search_q.pop();
			//cube=map->get_map(cur_at);
			c_v=map->creature_map->get_creature_map(cur_at);
			for(unsigned i=0;i<c_v->size();i++){
				if(check->check_creature(c_v->at(i))){
					find_v.push_back(c_v->at(i));
				}
			}
			in_arr=0;
			if(path[cur_at]&M_RIGHT)next_arr[in_arr++]=(cur_at+msy*msz);
			if(path[cur_at]&M_LEFT)next_arr[in_arr++]=(cur_at-msy*msz);
			if(path[cur_at]&M_UP)next_arr[in_arr++]=(cur_at+msz);
			if(path[cur_at]&M_DOWN)next_arr[in_arr++]=(cur_at-msz);
			if(path[cur_at]&M_FRONT)next_arr[in_arr++]=(cur_at+1);
			if(path[cur_at]&M_BACK)next_arr[in_arr++]=(cur_at-1);
			for(unsigned i=0;i<in_arr;i++){
				unsigned next=next_arr[i];
				if(!search_map[next]){//not search yet
					search_map[next]=true;
					search_q.push(next);
				}
			}
			times++;
		//	printf("search times=%u\n",times);
			if(find_v.size()>=num)end=true;
			if(times>max_time)end=true;
			if(search_q.empty())end=true;
		}
		time_cost=(clock()-start_time);
		time_used+=(time_cost+1);
		delete check;
}
void Path::find_route(Route* route,unsigned start,unsigned destination,
		unsigned max_time,unsigned min_time){
	clock_t start_time=clock(),time_cost;
	creat_route_map();
	std::priority_queue<Point,std::vector<Point>,Compare> update_q;
	unsigned times=0;
	unsigned next_arr[6],in_arr;

	bool find=false,end_finding=false;
	update_q.push(Point(start,compute_dis_value(start,start,destination)));
	route_dis[start]=0;
	unsigned cur_at;

	while(!end_finding){
		cur_at=update_q.top().pos;
		update_q.pop();
		if(cur_at==destination){
			find=true;//printf("find!!but not shortest!!\n");
		}
		if(find){
			if(times>=min_time)end_finding=true;
		}
		in_arr=0;
		if(path[cur_at]&M_RIGHT)next_arr[in_arr++]=(cur_at+msy*msz);
		if(path[cur_at]&M_LEFT)next_arr[in_arr++]=(cur_at-msy*msz);
		if(path[cur_at]&M_UP)next_arr[in_arr++]=(cur_at+msz);
		if(path[cur_at]&M_DOWN)next_arr[in_arr++]=(cur_at-msz);
		if(path[cur_at]&M_FRONT)next_arr[in_arr++]=(cur_at+1);
		if(path[cur_at]&M_BACK)next_arr[in_arr++]=(cur_at-1);
		for(unsigned i=0;i<in_arr;i++){
			unsigned next=next_arr[i];
			if((route_dis[cur_at]+1)<route_dis[next]){
				route_dis[next]=(route_dis[cur_at]+1);
				route_map[next]=cur_at;
				if(!find||(route_dis[destination]>(route_dis[next]+compute_dis(next,destination)))){
					update_q.push(Point(next,compute_dis_value(next,route_dis[next],destination)));
				}
			}
		}
		if(update_q.empty()){
			end_finding=true;
			if(route_dis[destination]<99999){
				find=true;//printf("empty_q!!shortest find\n");
			}//else printf("empty_q!!no path find\n");
		}
		times++;
		if(times>=max_time){
			end_finding=true;//printf("cant find!!time out!!\n");
		}
	}
	time_cost=(clock()-start_time);
	time_used+=(time_cost+1);
	//printf("times=%d,time_cost=%lfsec\n",times,(double)time_cost/(double)(CLOCKS_PER_SEC));
	if(find){
		unsigned x,y,z;
		for(unsigned i=destination;i!=start;i=route_map[i]){
			convert_pos(i,x,y,z);
			route->route.push_back(Route::point(x,y,z));
		}
		convert_pos(start,x,y,z);
		route->route.push_back(Route::point(x,y,z));
		route->set_find();
	}else route->set_not_find();
}

unsigned char Path::get_path(int x,int y,int z)const{
	if(x<0||x>=msx||y<0||y>=msy||z<0||z>=msz)return 0;
	else return path[convert_pos(x,y,z)];
}
void Path::set_path(int x,int y,int z,unsigned char _path){
	if(x<0||x>=msx||y<0||y>=msy||z<0||z>=msz)return;
	path[convert_pos(x,y,z)]=_path;
}
unsigned Path::compute_dis_value(unsigned pos,unsigned cur_dis,unsigned end){
	unsigned p_x,p_y,p_z,e_x,e_y,e_z;
	convert_pos(pos,p_x,p_y,p_z);
	convert_pos(end,e_x,e_y,e_z);
	int d_ex=(p_x-e_x),d_ey=(p_y-e_y),d_ez=(p_z-e_z);
	return (cur_dis+(3*abs(d_ex)+10*abs(d_ey)+3*abs(d_ez)+abs(abs(d_ex)-abs(d_ez))));
}
unsigned Path::compute_dis(unsigned start,unsigned end){
	unsigned s_x,s_y,s_z,e_x,e_y,e_z;
	convert_pos(start,s_x,s_y,s_z);
	convert_pos(end,e_x,e_y,e_z);
	return (abs(s_x-e_x)+abs(s_y-e_y)+abs(s_z-e_z));
}
unsigned Path::convert_pos(unsigned x,unsigned y,unsigned z)const{
	return (x*msy*msz+y*msz+z);
}
Route::point Path::convert_pos(unsigned pos){
	unsigned x,y,z;
	convert_pos(pos,x,y,z);
	return Route::point(x,y,z);
}
void Path::convert_pos(const unsigned &pos,unsigned &x,unsigned &y,unsigned &z){
	unsigned re,num=pos;
	re=num%(msy*msz);
	x=(num-re)/(msy*msz);
	num=re;
	re=num%msz;
	y=(num-re)/msz;
	z=re;
}
