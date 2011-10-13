#pragma once
#include "TowerObject.h"
#include "EnemyObject.h"
#include "ObstacleObject.h"
#include "BulletObject.h"
#include "MapObject.h"

class CObjectManager
{
public:
	CObjectManager(void);
	~CObjectManager(void);

	void Init();
	void Update();
	void Render();
	void Destroy();

	void AddObject(CTowerObject*);
	void AddObject(CEnemyObject*);
	void AddObject(CObstacleObject*);
	void AddObject(CBulletObject*);

	void RemoveObject(CTowerObject*);
	void RemoveObject(CEnemyObject*);
	void RemoveObject(CObstacleObject*);
	void RemoveObject(CBulletObject*);

	void SetMapObject(CMapObject*);

	CMapObject* Map;
	CLutI<CTowerObject*> TowerList;
	int TowerKeyCounter;
	CLutI<CEnemyObject*> EnemyList;
	int EnemyKeyCounter;
	CLutI<CObstacleObject*> ObstacleList;
	int ObstacleKeyCounter;
	CLutI<CBulletObject*> BulletList;
	int BulletKeyCounter;
};
