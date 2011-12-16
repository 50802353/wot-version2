#ifndef __TOWEROBJECT_H__
#define __TOWEROBJECT_H__

#include "GameObject.h"
#include "EnemyObject.h"
#include "BulletObject.h"
#include "MapObject.h"


class CTowerObject :
	public CGameObject
{
public:
	CTowerObject(STowerData *data);
	~CTowerObject(void);

	void Init();
	void Update(int delta_time);
	void Render();
	void Destroy();

	Position position;
	LogicPosition logicposition;
	STowerData *data;

	int damage;
	int range;
	int time_to_shoot;
	int fade_in_time;
	//int fade_out_time;
	bool isSelected;
	CEnemyObject* target;

	CMapObject* Map;
	int status;
	irr::scene::IAnimatedMeshSceneNode* sceneNode;

	scene::IParticleSystemSceneNode* particleSystem;
	//TODO++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

	void FindTarget();
	void Shoot(CEnemyObject* Enemy); // viet ham tao. ra doi tuong CBulletObject, khoi tao damage cho Bullet, bay tu vi tri cua tower hien tai den vi tri cua Enemy
	void Upgrade(STowerData *data); // viet ham nang cap tru, thay doi data, thay doi damage, range cua tru hien tai thanh tru moi
	void Sell(); //huy? tru., lay' lai tien`

	//TODO------------------------------------------------------------------------------

	

	


};


#endif