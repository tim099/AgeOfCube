#ifndef SEARCH_H_
#define SEARCH_H_
class StaticCube;
class Search {
public:
	Search();
	virtual ~Search();
	virtual bool check_search(StaticCube* cube)=0;
protected:
};

#endif /* SEARCH_H_ */
