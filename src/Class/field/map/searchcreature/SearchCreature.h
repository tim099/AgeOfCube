#ifndef SEARCHCREATURE_H_
#define SEARCHCREATURE_H_
class CubeCreature;
class SearchCreature {
public:
	SearchCreature();
	virtual ~SearchCreature();
	virtual bool check_creature(CubeCreature* creature)=0;
protected:
};

#endif /* SEARCHCREATURE_H_ */
