#ifndef PLAYEROWNOBJECT_H_
#define PLAYEROWNOBJECT_H_
#include <cstdio>
#include "playerdefine.h"
class PlayerOwnObject {
public:
	PlayerOwnObject(int player);
	virtual ~PlayerOwnObject();
	int player_num()const;
	int belong_to()const;

protected:
	virtual void save_player(FILE *file);
	virtual void load_player(FILE *file);
	int player;
};

#endif /* PLAYEROWNOBJECT_H_ */
