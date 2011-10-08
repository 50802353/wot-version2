#pragma once
#include "gametutor.h"
#include "TowerData.h"
#include "EnemyData.h"
#include "MapData.h"
#include "ObstacleData.h"
#include "BulletData.h"


enum EGameObject
{
	E_OBJ_TOWER,
	E_OBJ_ENEMY,
	E_OBJ_BULLET,
	E_OBJ_OBSTACLE,
	E_OBJ_MAP,
};

struct Position
{
	float x;
	float y;
	float z;

	Position()
	{
		x=y=z=0;
	}

	Position(float x, float y, float z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}

	Position operator = (const Position pos)
	{
		x = pos.x;
		y = pos.y;
		z = pos.z;
		return pos;
	}

	Position operator + (const Position pos)
	{
		return Position(x + pos.x, y + pos.y, z + pos.z);
	}
};

