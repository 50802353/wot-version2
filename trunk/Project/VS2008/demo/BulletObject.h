#ifndef __BULLETOBJECT_H__
#define __BULLETOBJECT_H__

#include "gameobject.h"
#include "EnemyObject.h"

class CBulletObject :
	public CGameObject
{
public:
	CBulletObject(SBulletData* data, Position position, CEnemyObject* target, int damgage);
	~CBulletObject(void);

	void Init();
	void Update();
	void Render();
	void Destroy();

	CEnemyObject* target;

	Position position;
	SBulletData *data;
	int damage;
	//TODO++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

	void Move(); //xac dinh new position cua bullet, tuong tu voi' enemy, chi khac' la bullet co' the di thang? den' muc tieu ko can thong qua MapObject de tinh' o ke' tiep'

	void Hit(); //Khi cham muc tieu, goi ham nay, gay damage len enemy, goi method Damaged cua doi tuong enemy, dong thoi huy doi' tuong bullet

	//TODO------------------------------------------------------------------------------

};

#endif