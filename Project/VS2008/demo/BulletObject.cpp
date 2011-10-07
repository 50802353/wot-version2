#include "BulletObject.h"

CBulletObject::CBulletObject(SBulletData* data)
{
	this->ObjectType = EGameObject::E_OBJ_BULLET;
	this->data = data;
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
}

void CBulletObject::Destroy()
{
}