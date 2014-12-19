#include "resources/Resource.h"

Resource::Resource(int _resources[TOTAL_RESOURCES]) {
	memcpy(resources, _resources, sizeof(resources));
}
Resource::Resource(const Resource& _resource){
	//memcpy(this, &_resource, sizeof(Resource));
	(*this)=_resource;
}
Resource::Resource() {
	for(int i=0;i<TOTAL_RESOURCES;i++)resources[i]=0;
}
Resource::~Resource() {

}
void Resource::save(FILE *fop){
	for(int i=0;i<TOTAL_RESOURCES;i++){
		fprintf(fop,"%d ",resources[i]);
	}
}
void Resource::load(FILE *fop){
	for(int i=0;i<TOTAL_RESOURCES;i++){
		fscanf(fop,"%d ",&resources[i]);
	}
}
void Resource::clear_res(){
	for(int i=0;i<TOTAL_RESOURCES;i++){
		resources[i]=0;
	}
}
Resource& Resource::operator=(const Resource &_resource){
	if(this!=&_resource){
		memcpy(this->resources, _resource.resources, sizeof(this->resources));
	}
	return (*this);
}
Resource& Resource::operator+=(const Resource &res){
	for(int i=0;i<TOTAL_RESOURCES;i++){
		resources[i]+=res.resources[i];
	}
	return (*this);
}
Resource& Resource::operator-=(const Resource &res){
	for(int i=0;i<TOTAL_RESOURCES;i++){
		resources[i]-=res.resources[i];
	}
	return (*this);
}
bool Resource::operator==(const Resource &res)const{
	for(int i=0;i<TOTAL_RESOURCES;i++){
		if(resources[i]!=res.resources[i])return false;
	}
	return true;
}
bool Resource::operator>=(const Resource &res)const{
	for(int i=0;i<TOTAL_RESOURCES;i++){
		if(resources[i]<res.resources[i])return false;
	}
	return true;
}
bool Resource::operator>(const Resource &res)const{
	for(int i=0;i<TOTAL_RESOURCES;i++){
		if(resources[i]<=res.resources[i])return false;
	}
	return true;
}
bool Resource::operator<(const Resource &res)const{
	for(int i=0;i<TOTAL_RESOURCES;i++){
		if(resources[i]>=res.resources[i])return false;
	}
	return true;
}
bool Resource::operator<=(const Resource &res)const{
	for(int i=0;i<TOTAL_RESOURCES;i++){
		if(resources[i]>res.resources[i])return false;
	}
	return true;
}
int Resource::res_num(int res)const{
	if(res>=TOTAL_RESOURCES)return -1;
	return resources[res];
}
int Resource::get_res(int res,int num){
	if(res>=TOTAL_RESOURCES)return -1;
	if(resources[res]>=num){
		resources[res]-=num;
		return num;
	}else{
		int buff=resources[res];
		resources[res]=0;
		return buff;
	}
}
void Resource::push_res(int res,int num){
	if(res>=TOTAL_RESOURCES){
		printf("no resources %d\n",res);
		return ;
	}
	resources[res]+=num;
}
void Resource::set_res(int res,int num){
	if(res>=TOTAL_RESOURCES){
		printf("no resources %d\n",res);
		return ;
	}
	resources[res]=num;
}
