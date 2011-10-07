#ifndef _GAME_OBJECT_H
#define _GAME_OBJECT_H

#include "gametutor.h"
using namespace GameTutor;

struct MapPosition
{
	__INT32 mX;
	__INT32 mY;
	MapPosition()
	{
	}
	MapPosition(__INT32 x, __INT32 y)
	{
		mX = x;
		mY = y;
	}
};

enum ObjectType {OBJECT_NONE, OBJECT_ENEMY, OBJECT_TOWER , OBJECT_MENU, OBJECT_MAP, OBJECT_TREE, OBJECT_BULLET};

class GameObject
{
public:
	//type of object
	ObjectType mType;

	GameObject();
	~GameObject();
	virtual void Render();
	virtual void Update(float tpf);
};

#endif