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

static SModelData ModelData1("./resource/model/_Dragoon/dragoon.md2", "./resource/model/_Dragoon/dragoon.pcx", "./resource/model/_Dragoon/dragoon2.png", core::vector3df(0.08,0.08,0.08), core::vector3df(0,0,0),20.0f);
static SModelData ModelData2("./resource/model/_DragoonJr/dragoonjr.md2", "./resource/model/_DragoonJr/dragoonjr.pcx", "./resource/model/_DragoonJr/dragoonjr2.png", core::vector3df(0.08,0.08,0.08), core::vector3df(0,0,0),20.0f);
static SModelData ModelData3("./resource/model/_Hydralisk/hydralisk.MD2", "./resource/model/_Hydralisk/hydralisk.pcx", "./resource/model/_Hydralisk/hydralisk2.png", core::vector3df(0.08,0.08,0.08), core::vector3df(0,0,0),20.0f);
static SModelData ModelData4("./resource/model/_Boss/boss.md2", "./resource/model/_Boss/boss.pcx", "./resource/model/_Boss/boss_avatar2.png", core::vector3df(0.08,0.08,0.08), core::vector3df(0,0,0),20.0f);

static SModelData ModelData5("./resource/model/_Boss/boss.md2", "./resource/model/_Boss/boss.pcx", "./resource/model/_Boss/boss_avatar2.png", core::vector3df(0.04,0.04,0.04), core::vector3df(0,0,0),20.0f);
static SModelData ModelData6("./resource/model/_Dragoon/dragoon.md2", "./resource/model/_Dragoon/dragoon.pcx", "./resource/model/_Dragoon/dragoon2.png", core::vector3df(0.04,0.04,0.04), core::vector3df(0,0,0),20.0f);
static SModelData ModelData7("./resource/model/_DragoonJr/dragoonjr.md2", "./resource/model/_DragoonJr/dragoonjr.pcx", "./resource/model/_DragoonJr/dragoonjr2.png", core::vector3df(0.04,0.04,0.04), core::vector3df(0,0,0),20.0f);
static SModelData ModelData8("./resource/model/_Hydralisk/hydralisk.MD2", "./resource/model/_Hydralisk/hydralisk.pcx", "./resource/model/_Hydralisk/hydralisk2.png", core::vector3df(0.04,0.04,0.04), core::vector3df(0,0,0),20.0f);

static STowerData* UpgradeTowerList4[5]={0,0,0,0,0};
static STowerData TowerData4("TOWER_NAME_4", 10, 4, 1000, 30, ETowerType::E_TOWER_ATTACK, UpgradeTowerList4, ModelData4, 1);
static STowerData* UpgradeTowerList3[5]={0,0,0,0,0};
static STowerData TowerData3("TOWER_NAME_3", 10, 4, 1000, 50, ETowerType::E_TOWER_ATTACK, UpgradeTowerList3, ModelData2, 1);
static STowerData* UpgradeTowerList2[5]={&TowerData3,0,0,0,0};
static STowerData TowerData2("TOWER_NAME_2", 10, 4, 900, 20, ETowerType::E_TOWER_ATTACK, UpgradeTowerList2, ModelData1, 1);
static STowerData* UpgradeTowerList1[5]={&TowerData2,&TowerData4,0,0,0};
static STowerData TowerData1("TOWER_NAME_1", 10, 4, 800, 10, ETowerType::E_TOWER_ATTACK, UpgradeTowerList1, ModelData3, 1);
static SEnemyData EnemyData1("ENEMY_NAME_1", 50, 30, 20, ModelData5, 2);
static SEnemyData EnemyData2("ENEMY_NAME_2", 20, 60, 30, ModelData6, 2);
static SEnemyData EnemyData3("ENEMY_NAME_3", 100, 15, 25, ModelData7, 2);
static SEnemyData EnemyData4("ENEMY_NAME_4", 100, 30, 20, ModelData8, 2);

static SObstacleData ObstacleData1("OBSTACLE_NAME_1", 3, 3);
static SBulletData BulletData1("BULLET_NAME_1", 100, 10, 4, 4);

static int			SpawnTime1[5]	=	{1000,			500,			500,			1000,			600};
static SEnemyData*	Enemy1[5]		=	{&EnemyData1,	&EnemyData1,	&EnemyData1,	&EnemyData1,	&EnemyData4};
static SWaveData WaveData1(5, SpawnTime1, Enemy1);

static int			SpawnTime2[5]	=	{1000,			500,			500,			1000,			600};
static SEnemyData*	Enemy2[5]		=	{&EnemyData2,	&EnemyData2,	&EnemyData2,	&EnemyData2,	&EnemyData3};
static SWaveData WaveData2(5, SpawnTime2, Enemy2);

static SWaveData*	 Wave[2]		=	{&WaveData1,	&WaveData2};
static STowerData* BasicTowerList[5]={&TowerData1,0,0,0,0};
static SObstacleData* ObstacleList[MAX_OBSTACLE_PER_MAP] = {&ObstacleData1,&ObstacleData1,&ObstacleData1,0,0,0,0,0,0,0,
															0,0,0,0,0,0,0,0,0,0};
static LogicPosition ObstaclePositionList[MAX_OBSTACLE_PER_MAP] = { LogicPosition(5,5),LogicPosition(3,0),LogicPosition(6,8),LogicPosition(),LogicPosition(),
																	LogicPosition(),LogicPosition(),LogicPosition(),LogicPosition(),LogicPosition(),
																	LogicPosition(),LogicPosition(),LogicPosition(),LogicPosition(),LogicPosition(),
																	LogicPosition(),LogicPosition(),LogicPosition(),LogicPosition(),LogicPosition()};
static int ObstacleSizeList[MAX_OBSTACLE_PER_MAP] = {2,2,1};


static SMapData MapData1("MAP_NAME_1", 10, 10, LogicPosition(0,0), LogicPosition(9,9), 5, 100, 2, Wave, BasicTowerList, ObstacleList,ObstaclePositionList,ObstacleSizeList);
//static SMapData MapData2("MAP_NAME_1", 10, 10, LogicPosition(0,0), LogicPosition(9,9), 5, 100, 2, Wave, BasicTowerList, ObstacleList,ObstaclePositionList,ObstacleSizeList);
static SMapData*  MapData[4] = {&MapData1,&MapData1,&MapData1,&MapData1};


#define SELL_PERCENT 0.3


#endif