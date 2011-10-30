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
	E_OBJ_TOWER=1,
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

	Position operator - (const Position pos)
	{
		return Position(x - pos.x, y - pos.y, z - pos.z);
	}

	Position operator * (const float scale)
	{
		return Position(x * scale, y * scale, z * scale);
	}

	float operator | (const Position pos)
	{
		return (sqrt(pow(x - pos.x,2) + pow(y - pos.y,2) + pow(z - pos.z,2)));
	}

	bool operator == (const Position pos)
	{
		return (x==pos.x) && (y==pos.y) && (z==pos.z);
	}
};




//Temp data
//Temp data

static STowerData TowerData1("TOWER_NAME_1", 10, 4, 500, 100, ETowerType::E_TOWER_ATTACK, 1, 1);
static SEnemyData EnemyData1("ENEMY_NAME_1", 30, 10, 20, 2, 2);
static SObstacleData ObstacleData1("OBSTACLE_NAME_1", 3, 3);
static SBulletData BulletData1("BULLET_NAME_1", 20, 10, 4, 4);

static int			SpawnTime[5]	=	{5000,			1000,			1000,			1000,			1000};
static SEnemyData*	Enemy[5]		=	{&EnemyData1,	&EnemyData1,	&EnemyData1,	&EnemyData1,	&EnemyData1};
static SWaveData WaveData1(5, SpawnTime, Enemy);
static SWaveData*	 Wave[5]		=	{&WaveData1,	&WaveData1,		&WaveData1,		&WaveData1,		&WaveData1};
static SMapData MapData1("MAP_NAME_1", 10, 10, LogicPosition(0,0), LogicPosition(9,9), 100, 20, 5, Wave, 0, 0);

#define SELL_PERCENT 0.3


#endif