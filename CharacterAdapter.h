#ifndef CHARACTER_ADAPTER_H
#define CHARACTER_ADAPTER_H

#include "Character.h"
class CharacterAdapter
{
private:
	Character* adaptee;

public:
	CharacterAdapter(Character* adaptee_);
	Vec3 getPlayerPos();
	Vec3 getPos();
	int getHealth();
};

#endif;