#include "Effect.h"

Effect::Effect() {


}
Effect::~Effect() {

}
int Effect::Effect_type(){
	return E_EFFECT;
}
void Effect::collision(Collidable* obj){
	printf("cant do collision with E_EFFECT\n");
}
