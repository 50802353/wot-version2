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
	E_OBJ_NONE,
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

static SModelData ModelData1("./resource/model/Avenger/Avenger.md2", "./resource/model/Avenger/Avenger.bmp", "./resource/model/Avenger/avatar.bmp", core::vector3df(0.1,0.1,0.1), core::vector3df(0,0,0),20.0f);
static SModelData ModelData2("./resource/model/boba-fett/model.md2", "./resource/model/boba-fett/material.jpg", "./resource/model/boba-fett/avatar.bmp", core::vector3df(0.1,0.1,0.1), core::vector3df(0,0,0),20.0f);
static SModelData ModelData3("./resource/model/DrFreak/DrFreak.md2", "./resource/model/DrFreak/DrFreak.bmp", "./resource/model/DrFreak/avatar.bmp", core::vector3df(0.1,0.1,0.1), core::vector3df(0,0,0),20.0f);

static STowerData* UpgradeTowerList3[5]={0,0,0,0,0};
static STowerData TowerData3("TOWER_NAME_1", 10, 4, 1000, 100, ETowerType::E_TOWER_ATTACK, UpgradeTowerList3, ModelData2, 1);
static STowerData* UpgradeTowerList2[5]={&TowerData3,0,0,0,0};
static STowerData TowerData2("TOWER_NAME_1", 10, 4, 900, 50, ETowerType::E_TOWER_ATTACK, UpgradeTowerList2, ModelData1, 1);
static STowerData* UpgradeTowerList1[5]={&TowerData2,0,0,0,0};
static STowerData TowerData1("TOWER_NAME_1", 10, 4, 800, 70, ETowerType::E_TOWER_ATTACK, UpgradeTowerList1, ModelData3, 1);
static SEnemyData EnemyData1("ENEMY_NAME_1", 50, 30, 20, ModelData3, 2);
static SObstacleData ObstacleData1("OBSTACLE_NAME_1", 3, 3);
static SBulletData BulletData1("BULLET_NAME_1", 100, 10, 4, 4);

static int			SpawnTime[5]	=	{1000,			500,			500,			500,			500};
static SEnemyData*	Enemy[5]		=	{&EnemyData1,	&EnemyData1,	&EnemyData1,	&EnemyData1,	&EnemyData1};
static SWaveData WaveData1(5, SpawnTime, Enemy);
static SWaveData*	 Wave[5]		=	{&WaveData1,	&WaveData1,		&WaveData1,		&WaveData1,		&WaveData1};
static STowerData* BasicTowerList[5]={&TowerData1,0,0,0,0};
static SMapData MapData1("MAP_NAME_1", 10, 10, LogicPosition(0,0), LogicPosition(9,9), 5, 100, 5, Wave, BasicTowerList, 0, 0);


#define SELL_PERCENT 0.3


#endif