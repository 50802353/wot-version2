#include "BulletObject.h"
#include "ObjectManager.h"

CBulletObject::CBulletObject(SBulletData* data, Position position, CEnemyObject* target, int damage)
{
	this->ObjectType = EGameObject::E_OBJ_BULLET;
	this->data = data;
	this->position = position;
	this->target = target;
	this->damage = damage;
}

CBulletObject::~CBulletObject(void)
{
}

void CBulletObject::Init()
{
}

void CBulletObject::Update(int delta_time)
{
	Move(delta_time);
}

void CBulletObject::Render()
{
	CGraphics2D::GetInstance()->SetColor(SColor<float>(1,1,1,1));
	CGraphics2D::GetInstance()->FillRect(SRect<float>(position.x-0.1, position.y-0.1, 0.2, 0.2));
	CGraphics2D::GetInstance()->Flush();
}

void CBulletObject::Destroy()
{
	CObjectManager::CurrentObjectManager->RemoveObject(this);
	delete this;
}

void CBulletObject::Move(int delta_time)
{
	double dmove; // khoang cach di chuyen cua bullet
	double distance; // khoang cach hien tai giua bullet va enemy

	float dx, dy, dz; // do lech toa do cua bullet va enemy
	double rate; // ti le giua bulletEnemy va distance
	float x, y, z; // tao do moi cua bullet

	dmove = this->data->MoveSpeed * (float)delta_time / 10000;

	dx = this->target->position.x - this->position.x;
	dy = this->target->position.y - this->position.y;
	dz = this->target->position.z - this->position.z;
	distance = sqrt(dx * dx + dy * dy + dz * dz);
	rate = dmove/distance;

	if (rate<1)
	{
		// tinh tao do moi cua bullet
		x = this->position.x + dx*rate;
		y = this->position.y + dy*rate;
		z = this->position.z + dz*rate;
		this->position = Position(x, y, z);
	}
	else 
	{
		// neu' time lon' hon 
		Hit();
	}
}

void CBulletObject::Hit()
{
	//this->target->Damaged(this->damage);
	Destroy();
}