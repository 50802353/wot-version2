#include "EnemyObject.h"
#include "ObjectManager.h"

CEnemyObject::CEnemyObject(SEnemyData* data, LogicPosition position)
{
	this->ObjectType = EGameObject::E_OBJ_ENEMY;
	this->data = data;
	this->position = Position(position.x+0.5,position.y+0.5,0);
	isInMap = false;

	NextPos = this->position;
	Map = CObjectManager::CurrentObjectManager->Map;
}

CEnemyObject::~CEnemyObject(void)
{
}

void CEnemyObject::Init()
{
}

void CEnemyObject::Update(int delta_time)
{
	if (!isInMap) return;
	Move(delta_time);
}

void CEnemyObject::Render()
{
	if (!isInMap) return;
	CGraphics2D::GetInstance()->SetColor(SColor<float>(1,0,0,1));
	CGraphics2D::GetInstance()->FillRect(SRect<float>(position.x-0.4, position.y-0.4, 0.8, 0.8));
	CGraphics2D::GetInstance()->Flush();
}

void CEnemyObject::Destroy()
{
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
			dmove = 0;
		}
	}
}

void CEnemyObject::ReachDestination()
{
	Map->RemainingLife--;
	isInMap = false;
	CObjectManager::CurrentObjectManager->Map->NumberOfEnemyInMap--;
}

void CEnemyObject::Spawn()
{
	isInMap = true;
	CObjectManager::CurrentObjectManager->Map->NumberOfEnemyInMap++;
}

void CEnemyObject::Die()
{
	Map->Money+=this->data->Bounty;
	isInMap = false;
	CObjectManager::CurrentObjectManager->Map->NumberOfEnemyInMap--;
}