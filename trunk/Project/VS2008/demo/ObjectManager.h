#ifndef __OBJECTMANAGER_H__
#define __OBJECTMANAGER_H__

#include "TowerObject.h"
#include "EnemyObject.h"
#include "ObstacleObject.h"
#include "BulletObject.h"
#include "MapObject.h"

class CObjectManager
{
public:
	friend void CTowerObject::FindTarget();
	CObjectManager(void);
	~CObjectManager(void);

	void Init();
	void Update(int delta_time);
	void Render();
	void Destroy();

	static CObjectManager* CurrentObjectManager;

	void AddObject(CTowerObject*);
	void AddObject(CEnemyObject*);
	void AddObject(CObstacleObject*);
	void AddObject(CBulletObject*);

	void RemoveObject(CTowerObject*);
	void RemoveObject(CEnemyObject*);
	void RemoveObject(CObstacleObject*);
	void RemoveObject(CBulletObject*);

	void ClearEnemy();
	void ClearTower();
	void ClearObstacle();
	void ClearBullet();

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

#endif