#include "BulletObject.h"
#include "ObjectManager.h"

CBulletObject::CBulletObject(SBulletData* data, Position position, CEnemyObject* target, int damage)
{
	this->ObjectType = EGameObject::E_OBJ_BULLET;
	this->data = data;
	this->position = position;
	this->target = target;
	this->damage = damage;
	this->up_move = 0.05;
	Init();
}

CBulletObject::~CBulletObject(void)
{
	Destroy();
}

void CBulletObject::Init()
{
	sceneNode = smgr->addBillboardSceneNode(0,core::dimension2df(0.5,0.5));
	sceneNode->setMaterialTexture(0, driver->getTexture("./resource/particle.bmp"));
	sceneNode->setMaterialFlag(video::E_MATERIAL_FLAG::EMF_LIGHTING,false);
	sceneNode->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR);
	sceneNode->setPosition(irr::core::vector3df(position.x, position.z, position.y));

	CAudioPlayer::GetInstance()->Load<CFileWin32Driver>("./resource/ABomb.wav");
}

void CBulletObject::Update(int delta_time)
{
	Move(delta_time);
}

void CBulletObject::Render()
{
}

void CBulletObject::Destroy()
{
	//CObjectManager::CurrentObjectManager->RemoveObject(this);
	if (sceneNode)
	{
		sceneNode->remove();
		sceneNode=0;
	}
}

void CBulletObject::Move(int delta_time)
{
	if (up_move>0)
	{
		this->position = this->position + Position(0,0,up_move);
		up_move-=(float)delta_time*0.05/1000.0;
	}

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
		sceneNode->setPosition(irr::core::vector3df(position.x, position.z, position.y));
	}
	else 
	{
		// neu' time lon' hon 
		Hit();
	}
}

void CBulletObject::Hit()
{
	if (this->target->isInMap)
	{
		this->target->Damaged(this->damage);
		CAudioPlayer::GetInstance()->Play("./resource/ABomb.wav",false);
	}
	CObjectManager::CurrentObjectManager->RemoveObject(this);
	delete this;
}