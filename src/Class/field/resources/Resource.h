#ifndef RESOURCE_H_
#define RESOURCE_H_
#include "resources_define.h"
#include "cstring"
#include "cstdio"
class Resource {
public:
	Resource(int resources[TOTAL_RESOURCES]);
	Resource(const Resource& resource);
	Resource();
	int res_num(int res)const;
	int get_res(int res,int num);
	void push_res(int res,int num);
	void set_res(int res,int num);
	void clear_res();
	void save(FILE *fop);
	void load(FILE *fop);

	Resource& operator=(const Resource &res);
	Resource& operator+=(const Resource &res);
	Resource& operator-=(const Resource &res);
	bool operator==(const Resource &res)const;
	bool operator>=(const Resource &res)const;
	bool operator>(const Resource &res)const;
	bool operator<=(const Resource &res)const;
	bool operator<(const Resource &res)const;

	virtual ~Resource();
protected:
	int resources[TOTAL_RESOURCES];
};

#endif /* RESOURCE_H_ */
