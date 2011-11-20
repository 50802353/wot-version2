#include "EnemyObject.h"
#include "ObjectManager.h"

CEnemyObject::CEnemyObject(SEnemyData* data, LogicPosition position)
{
	this->ObjectType = EGameObject::E_OBJ_ENEMY;
	this->data = data;
	this->position = Position(position.x+0.5,position.y+0.5,0.3);
	isInMap = false;
	NextPos = this->position;
	Map = CObjectManager::CurrentObjectManager->Map;
	this->currentHP = data->MaxHP;
	Init();
}

CEnemyObject::~CEnemyObject(void)
{
	Destroy();
}

void CEnemyObject::Init()
{
	sceneNode = smgr->addSphereSceneNode(0.3);	
	sceneNode->setMaterialTexture(0, driver->getTexture("./resource/sample_enemy.bmp"));
	sceneNode->setPosition(core::vector3df(position.x, position.z, position.y));
	sceneNode->setVisible(isInMap);
}

void CEnemyObject::Update(int delta_time)
{
	if (!isInMap) return;
	Move(delta_time);
}

void CEnemyObject::Render()
{
}

void CEnemyObject::Destroy()
{
	sceneNode->remove();
}

void CEnemyObject::Move(int delta_time)
{
	float dmove = this->data->MoveSpeed * (float)delta_time / 10000;
	while (dmove>0)
	{
		
		float distance = NextPos | this->position;
		if (dmove>distance)
		{
			LogicPosition CurLogicPos((int)this->position.x,(int)this->position.y);
			if (CurLogicPos == Map->data->DestinationPosition)
			{
				ReachDestination();
				return;
			}

			LogicPosition NextLogicPos = CurLogicPos + ::Move[(Map->DirectionMap[(int)this->position.y * Map->data->Width + (int)this->position.x])];		

			this->position = NextPos;
			NextPos.x = NextLogicPos.x + 0.5;
			NextPos.y = NextLogicPos.y + 0.5;
			dmove -= distance;
		}
		else
		{
			this->position = this->position + ((NextPos - this->position) * (dmove/distance));
			sceneNode->setPosition(irr::core::vector3df(position.x, position.z, position.y));
			dmove = 0;
		}
	}
}

void CEnemyObject::ReachDestination()
{
	if (!isInMap) return;
	Map->RemainingLife--;
	isInMap = false;
	sceneNode->setVisible(isInMap);
	printf("Reach destination");
	CObjectManager::CurrentObjectManager->Map->NumberOfEnemyInMap--;
	if (Map->RemainingLife<=0) Map->Lose();
}

void CEnemyObject::Spawn()
{
	isInMap = true;
	sceneNode->setVisible(isInMap);
	CObjectManager::CurrentObjectManager->Map->NumberOfEnemyInMap++;
}

void CEnemyObject::Die()
{
	if (isInMap)
	{
		isInMap = false;
		sceneNode->setVisible(isInMap);
		Map->Money+=this->data->Bounty;
		CObjectManager::CurrentObjectManager->Map->NumberOfEnemyInMap--;
	}
}

void CEnemyObject::Damaged(int HP)
{
	if (!isInMap) return;
	int damage = HP; //sau nay thay the' bang cong thuc' phuc' tap. hon voi' anh huong cua giap, thuoc tinh' ....
	if (currentHP>damage)
	{
		currentHP-=damage;
	}
	else 
	{
		currentHP=0;
		Die();
	}
}