#ifndef ROUTE_H_
#define ROUTE_H_
#include <vector>
const signed char R_STOP_FIND = -2;
const signed char R_CANT_FIND = -1;
const signed char R_NOT_YET_FIND = 0;
const signed char R_FIND = 1;

class Route {
public:
	struct point{
		point(unsigned _x,unsigned _y,unsigned _z){
			x=_x;y=_y,z=_z;
		}
		unsigned x,y,z;
	};

	Route();
	virtual ~Route();
	signed char find()const;
	void set_find();
	void set_not_find();
	void end_route();
	void delete_route();
	bool exits()const;
	std::vector<point>route;
protected:
	signed char _find;
	bool _exist;
};

#endif /* ROUTE_H_ */
