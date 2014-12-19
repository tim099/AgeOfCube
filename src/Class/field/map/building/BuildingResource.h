#ifndef BUILDINGRESOURCE_H_
#define BUILDINGRESOURCE_H_
#include "resources/Resource.h"
#include <cstdio>
class BuildingResource {
public:
	BuildingResource();
	virtual ~BuildingResource();

	virtual void save_res(FILE *file);
	virtual void load_res(FILE *file);

	bool res_link()const;
	void merge_res(Resource *res);
	Resource* resource()const;
	bool consume_resources(const Resource& res);
protected:
	Resource *resources;
	Resource res;
};

#endif /* BUILDINGRESOURCE_H_ */
