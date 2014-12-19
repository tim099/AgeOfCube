#ifndef LIST_H_
#define LIST_H_
#include "ResourcesTexDefine.h"
#include "Resources/Resource.h"
#include "ListFonts.h"
#include <queue>
#include <string>
class List : public ListFonts{
	struct Lstr{
		Lstr(){
			pos_x=0;pos_y=0;str=0;
		}
		~Lstr(){
			delete str;
		}
		std::string *str;
		double pos_x;
		double pos_y;
	};
public:
	List(double size=0.0016,int list_type=0,double px=0.0,double py=0.0,double list_size=1.0);
	virtual ~List();
	void dp_list();
	void push_str(std::string str,double px,double py);
	void push_str(std::string *str,double px,double py);
	void push_temp_str(std::string str,double px,double py);
	void push_temp_str(std::string *str,double px,double py);
	void push_resources(Resource *resource,double res_x=-0.008,double res_y=0.007);
	void push_resources(Resource resource,double res_x=-0.008,double res_y=0.007);
	void clear_temp_str();
	void clear_dp_resources();
	void clear();
protected:
	void dp_resources();
	void creat_all_list();
	std::vector<GLuint> Lists;
	std::queue<Lstr*> Lstrs;
	std::queue<Lstr*> temp_strs;
	Resource *resource;
	bool tmp_res;
	int list_type;
	double lpx,lpy,list_size;
	double res_x,res_y;

};

#endif /* LIST_H_ */
