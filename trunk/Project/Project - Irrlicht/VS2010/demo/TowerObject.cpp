#include "TowerObject.h"
#include "ObjectManager.h"



CTowerObject::CTowerObject(STowerData *data)
{
	this->ObjectType = EGameObject::E_OBJ_TOWER;
	this->data = data;
	this->position = Position(1, 1, 0.8);
	this->logicposition = LogicPosition(0, 0);
	this->damage = data->Damage;
	this->range = data->Range;
	this->time_to_shoot = 0;
	this->target = NULL;
	this->isSelected = false;
	this->Map = CObjectManager::CurrentObjectManager->Map;
	Init();
}

CTowerObject::~CTowerObject(void)
{
	Destroy();
}

void CTowerObject::Init()
{
	
	sceneNode = smgr->addSphereSceneNode(0.8,16,0,2);
	sceneNode->setMaterialTexture(0, driver->getTexture("./resource/sample_tower.bmp"));
	sceneNode->getMaterial(0).NormalizeNormals = true;
	sceneNode->setPosition(irr::core::vector3df(position.x, position.z, position.y));
	irr::scene::ITriangleSelector* selector = smgr->createTriangleSelector(((irr::scene::IMeshSceneNode*)sceneNode)->getMesh(),sceneNode);
	sceneNode->setTriangleSelector(selector);
	selector->drop();
	
	//sceneNode->setMaterialFlag(irr::video::E_MATERIAL_FLAG::EMF_LIGHTING, false);
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
	//sceneNode->render();
	//sceneNode->setVisible(true);
}

void CTowerObject::Destroy()
{
	sceneNode->remove();
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


