#include <cstdio>
#include <math.h>
#include <stdlib.h>
#include "glm.h"
#include "glm.cpp"
#include "cstring"
#include "Class/Game.h"

Game *game;
#include "callbackfunc.cpp"
int main() {
	//printf("game ver1\n");
	//printf("%X\n",(unsigned int)test);
	game=new Game();
	callbackrigister();
	delete game;
	return 0;
}
