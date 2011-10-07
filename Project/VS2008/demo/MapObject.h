#pragma once
#include "gameobject.h"
#include "TowerObject.h"
#include "EnemyObject.h"
#include "ObstacleObject.h"
#include "BulletObject.h"

class CMapObject :
	public CGameObject
{
public:
	CMapObject(void);
	~CMapObject(void);

	void Init();
	void Update();
	void Render();
	void Destroy();

	SMapData *data;

	int* ObjectMap;
	CLutI<CTowerObject> TowerList;
	CLutI<CEnemyObject> EnemyList;
	CLutI<CObstacleObject> ObstacleList;
	CLutI<CBulletObject> BulletList;
};
