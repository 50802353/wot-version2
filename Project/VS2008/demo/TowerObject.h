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
	CTowerObject(STowerData *data, LogicPosition position);
	~CTowerObject(void);

	void Init();
	void Update();
	void Render();
	void Destroy();

	Position position;
	STowerData *data;

	int damage;
	int range;


	//TODO++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


	void Shoot(CEnemyObject* Enemy); // viet ham tao. ra doi tuong CBulletObject, khoi tao damage cho Bullet, bay tu vi tri cua tower hien tai den vi tri cua Enemy
	void Upgrade(STowerData *data); // viet ham nang cap tru, thay doi data, thay doi damage, range cua tru hien tai thanh tru moi
	void Sell(int* Money); //huy? tru., lay' lai tien`

	//TODO------------------------------------------------------------------------------

	

	


};


#endif