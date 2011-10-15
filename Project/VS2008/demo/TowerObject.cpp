#include "TowerObject.h"
#include "ObjectManager.h"


CTowerObject::CTowerObject(STowerData *data, LogicPosition position)
{
	this->ObjectType = EGameObject::E_OBJ_TOWER;
	this->data = data;
	this->position = Position(position.x+1, position.y+1, 0);
	this->damage = data->Damage;
	this->range = data->Range;
}

CTowerObject::~CTowerObject(void)
{
}

void CTowerObject::Init()
{
}

void CTowerObject::Update()
{
}

void CTowerObject::Render()
{
	CGraphics2D::GetInstance()->SetColor(SColor<float>(0,1,0,1));
	CGraphics2D::GetInstance()->FillRect(SRect<float>(position.x-1, position.y-1, 2, 2));
}

void CTowerObject::Destroy()
{
}

void CTowerObject::Shoot(CEnemyObject* Enemy)
{
	CBulletObject* Bullet = new CBulletObject(&BulletData1,this->position,Enemy,this->damage);
	CObjectManager::CurrentObjectManager->AddObject(Bullet);
}