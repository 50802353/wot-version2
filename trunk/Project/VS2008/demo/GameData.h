#ifndef __GAMEDATA_H__
#define __GAMEDATA_H__

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

	float operator | (const Position pos)
	{
		return (sqrt(pow(x - pos.x,2) + pow(y - pos.y,2) + pow(z - pos.z,2)));
	}
};

//Temp data
//Temp data
static SMapData MapData1("MAP_NAME_1", 10, 10, LogicPosition(0,0), LogicPosition(10,10), 100, 20, 0, 0);
static STowerData TowerData1("TOWER_NAME_1",10,4, 1000, 100,ETowerType::E_TOWER_ATTACK, 1, 1);
static SEnemyData EnemyData1("ENEMY_NAME_1",30,10,2,2);
static SObstacleData ObstacleData1("OBSTACLE_NAME_1",3,3);
static SBulletData BulletData1("BULLET_NAME_1",20,10,4,4);

#define SELL_PERCENT 0.3


#endif