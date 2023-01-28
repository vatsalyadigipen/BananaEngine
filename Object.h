#pragma once

/*
	- Emptiness!
*/

enum ObjectIDs
{
	Null,
	Character,
	NonCharacter,
	Projectile
};

class Object
{
public:
	virtual void BeginPlay() = 0;
	virtual void Update() = 0;
};