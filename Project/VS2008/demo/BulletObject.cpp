#include "BulletObject.h"

CBulletObject::CBulletObject(SBulletData* data, Position position, int damage)
{
	this->ObjectType = EGameObject::E_OBJ_BULLET;
	this->data = data;
	this->position = position;
	this->damage = damage;
}

CBulletObject::~CBulletObject(void)
{
}

void CBulletObject::Init()
{
}

void CBulletObject::Update()
{
}

void CBulletObject::Render()
{
	CGraphics2D::GetInstance()->SetColor(SColor<float>(1,0,0,1));
	CGraphics2D::GetInstance()->FillRect(SRect<float>(position.x-0.1, position.y-0.1, 0.2, 0.2));
}

void CBulletObject::Destroy()
{
}