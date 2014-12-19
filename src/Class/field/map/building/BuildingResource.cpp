#include "BuildingResource.h"

BuildingResource::BuildingResource() {
	resources=&res;
}
BuildingResource::~BuildingResource() {

}
void BuildingResource::save_res(FILE *file){
	res.save(file);
}
void BuildingResource::load_res(FILE *file){
	res.load(file);
}
bool BuildingResource::res_link()const{
	if(resources==(&res))return false;
	return true;
}
void BuildingResource::merge_res(Resource *_res){
	(*_res)+=(*resources);
	resources->clear_res();
	resources=_res;
}
bool BuildingResource::consume_resources(const Resource& res){
	if((*resources)>=res){
		(*resources)-=res;
		return true;
	}
	//printf("no enough resources\n");
	return false;
}
Resource* BuildingResource::resource()const{
	return resources;
}
