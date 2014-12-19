#ifndef PATH_H_
#define PATH_H_
#include "cube_define.h"
#include "cstring"
#include "Route.h"
#include <vector>
#include <cstdlib>
#include <cstdio>
#include <queue>
#include <ctime>

const clock_t MAX_TIME_USED=10;//1000=1sec
class StaticCube;
class Map;
class Search;
class SearchCreature;
class CubeCreature;
class Path {
	friend Map;

public:
	struct Point{
		Point(unsigned _p,unsigned _dis_value){
			pos=_p;
			dis_value=_dis_value;
		}
		unsigned pos,dis_value;
	};
	struct F_R{
		F_R(unsigned _start,unsigned _destination,unsigned _max_time=10000,unsigned _min_time=5000){
			start=_start;
			destination=_destination;
			max_time=_max_time;
			min_time=_min_time;
			r=new Route();
		}
		Route* r;
		unsigned start,destination;
		unsigned max_time,min_time;
	};
	Path(int _msx,int _msy,int _msz,Map *map);
	Path(Path &p,Map *map);
	virtual ~Path();

	void tic();
	unsigned char get_path(int x,int y,int z)const;
	void set_path(int x,int y,int z,unsigned char _path);
	Route* push_find_route(int s_x,int s_y,int s_z,int d_x,int d_y,int d_z,unsigned max_time=10000,unsigned min_time=5000);

	void search(int s_x,int s_y,int s_z,Search* check,std::vector<StaticCube*> &find_v
			,unsigned num=1,unsigned max_time=5000,std::vector<Route::point>*find_p=0);
	void search(int s_x,int s_y,int s_z,SearchCreature* check,std::vector<CubeCreature*> &find_v
			,unsigned num=1,unsigned max_time=5000);
	bool time_out()const;

	unsigned convert_pos(unsigned x,unsigned y,unsigned z)const;
protected:
	class Compare{
	public:
	    bool operator() (Point a, Point b){
	    	if(a.dis_value>b.dis_value)return true;
	    	return false;
	    }
	};

	void find_route(Route* route,unsigned start,unsigned destination,unsigned max_time=10000,unsigned min_time=5000);

	void convert_pos(const unsigned &pos,unsigned &x,unsigned &y,unsigned &z);
	Route::point convert_pos(unsigned pos);
	unsigned compute_dis_value(unsigned pos,unsigned cur_dis,unsigned end);
	unsigned compute_dis(unsigned start,unsigned end);
	void initialize(int _msx,int _msy,int _msz,Map *map);
	void creat_route_map();
	void creat_search_map();

	int msx,msy,msz;
	unsigned char *path;
	unsigned *route_map,*route_dis;
	bool *search_map;
	Map *map;
	std::queue<F_R*>find_route_q;
	std::vector<Route*>route_v;
	clock_t time_used;
};

#endif /* PATH_H_ */
