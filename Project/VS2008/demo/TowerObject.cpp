#include "TowerObject.h"
#include "ObjectManager.h"



CTowerObject::CTowerObject(STowerData *data)
{
	this->ObjectType = EGameObject::E_OBJ_TOWER;
	this->data = data;
	this->position = Position(1, 1, 0);
	this->logicposition = LogicPosition(0, 0);
	this->damage = data->Damage;
	this->range = data->Range;
	this->time_to_shoot = 0;
	this->target = NULL;
	this->isSelected = false;
	this->Map = CObjectManager::CurrentObjectManager->Map;

}

CTowerObject::~CTowerObject(void)
{
}

void CTowerObject::Init()
{
}

void CTowerObject::Update(int delta_time)
{
	if ((!target) || (!target->isInMap) || ((target->position | this->position) > this->range))
		FindTarget();

	if (target)
		if (time_to_shoot<=0)
		{
				time_to_shoot += this->data->AttackSpeed;
				Shoot(target);
		}
		else
		{
			time_to_shoot -= delta_time;	
		}
}

void CTowerObject::Render()
{
	if (isSelected)
		CGraphics2D::GetInstance()->SetColor(SColor<float>(0,1,0,1));
	else
		CGraphics2D::GetInstance()->SetColor(SColor<float>(0,0.8,0,1));

	CGraphics2D::GetInstance()->FillRect(SRect<float>(position.x-0.9, position.y-0.9, 1.8, 1.8));
	CGraphics2D::GetInstance()->Flush();
}

void CTowerObject::Destroy()
{
	CObjectManager::CurrentObjectManager->RemoveObject(this);
	delete this;
}

void CTowerObject::FindTarget()
{
	CObjectManager* ObjectManager = CObjectManager::CurrentObjectManager;
	CEnemyObject* ChosenTarget = NULL;
	ObjectManager->EnemyList.BeginTravel();
	float mindistance=-1;
	while (!ObjectManager->EnemyList.IsEndOfTravel())
	{
		CEnemyObject* cur = (CEnemyObject*)ObjectManager->EnemyList.Travel();
		float distance = (cur->position | this->position);
		if ((cur->isInMap) && (distance < range) && (!ChosenTarget || ((mindistance==-1)||(mindistance>distance))))
		{
			ChosenTarget = cur;
			mindistance = distance;
		}
	}
	this->target = ChosenTarget;
}

void CTowerObject::Shoot(CEnemyObject* Enemy)
{
		CBulletObject* Bullet = new CBulletObject(&BulletData1,this->position,Enemy,this->damage);
		CObjectManager::CurrentObjectManager->AddObject(Bullet);
}

void CTowerObject::Upgrade(STowerData *data)
{
	this->data = data;
	this->time_to_shoot = 0;
	CObjectManager::CurrentObjectManager->Map->Money -= this->data->Cost;
}

void CTowerObject::Sell()
{
	CObjectManager::CurrentObjectManager->Map->Money += int(this->data->Cost * SELL_PERCENT);
	Destroy();	
}


