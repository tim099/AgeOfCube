#ifndef UNSIGNEDPOS_H_
#define UNSIGNEDPOS_H_
#include <cstdio>
class UnsignedPos {
public:
	UnsignedPos();
	UnsignedPos(unsigned x,unsigned y,unsigned z);
	virtual ~UnsignedPos();
	void save(FILE *file);
	void load(FILE *file);
	UnsignedPos& operator=(const UnsignedPos &pos);
	bool operator==(const UnsignedPos &pos)const;
	bool operator!=(const UnsignedPos &pos)const;

	unsigned x,y,z;

};

#endif /* UNSIGNEDPOS_H_ */
