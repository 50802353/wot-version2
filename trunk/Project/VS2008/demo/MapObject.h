#pragma once
#include "GameObject.h"
#include "TowerObject.h"
#include "EnemyObject.h"
#include "ObstacleObject.h"
#include "BulletObject.h"

class CMapObject :
	public CGameObject
{
public:
	CMapObject(SMapData *data);
	~CMapObject(void);

	void Init();
	void Update();
	void Render();
	void Destroy();
	void AddObject(CTowerObject*);
	void AddObject(CEnemyObject*);
	void AddObject(CObstacleObject*);
	void AddObject(CBulletObject*);

	SMapData *data;
	CImage* MapGridTexture;

	int* ObjectMap;
	CLutI<CTowerObject*> TowerList;
	int TowerKeyCounter;
	CLutI<CEnemyObject*> EnemyList;
	int EnemyKeyCounter;
	CLutI<CObstacleObject*> ObstacleList;
	int ObstacleKeyCounter;
	CLutI<CBulletObject*> BulletList;
	int BulletKeyCounter;

	//TODO++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++




	//TODO------------------------------------------------------------------------------

};
