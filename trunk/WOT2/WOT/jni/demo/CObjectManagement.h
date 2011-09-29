#ifndef __COBJECTMANAGEMENT_H__
#define __COBJECTMANAGEMENT_H__

#include "Header.h"
#include "CSingleton.h"
#include "CList.h"
#include "GameObject.h"
#include "EnemyObject.h"
#include "TowerObject.h"
#include "TreeObject.h"
#include "MapObject.h"
#include "BulletObject.h"

using namespace GameTutor;

struct Item
{
	ObjectType type;
	CList<GameObject*>* objects;
	Item(ObjectType _type, CList<GameObject*>* _objects);
};

class CObjectManagement: public CSingleton<CObjectManagement>
{
	friend class  CSingleton<CObjectManagement>;
protected:
	CList<Item*>* m_ListLookup;
	__INT32 mTotalLives;
	__INT32 mTotalMoney;

	CObjectManagement();
public:
	void AddList(CList<GameObject*>* list);
	void AddElement(GameObject* ele);
	CList<EnemyObject*>* GetEnemies(MapPosition _position);
	MapObject* GetMap();
	TowerObject* GetTower(MapPosition _position);
	CList<GameObject*>* GetListObject(ObjectType type);
	void RemoveTower(TowerObject* _tower);
	bool isFinishWave();
	void Render();
	void Update(float tpf);
	EnemyObject* getTarget(MapPosition* _position, __INT32 _range);
	void ClearAll();
	void ClearObjectType(ObjectType _type);
	virtual ~CObjectManagement();

	void UpdateLives(__INT32 _lives);
	void UpdateMoney(__INT32 _money);
	void InitLiveAndMoney(__INT32 _lives, __INT32 _money);
	__INT32 GetLives();
	__INT32 GetMoney();
	//for boost tower
	void BoostInRange(TowerObject* boostTower);
	CList<TowerObject*>* GetAllBoostTower();
	void UpdateBoost();
	void ResetBoost();

};

#endif