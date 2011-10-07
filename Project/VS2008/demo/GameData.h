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
};