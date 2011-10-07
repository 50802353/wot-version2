#include "CObjectManagement.h"

using namespace GameTutor;

Item::Item(ObjectType _type, CList<GameObject*>* _objects)
{
	type = _type;
	objects = _objects;
}

CObjectManagement::CObjectManagement() {
	m_ListLookup = new CList<Item*>;
	mTotalLives = 20;
	mTotalMoney = 1000;
};

void CObjectManagement::UpdateBoost()
{
	ResetBoost();

	CList<TowerObject*>* boostTowerList = GetAllBoostTower();
	if(boostTowerList)
	{
		boostTowerList->BeginTravel();
		while(!boostTowerList->IsEndOfTravel())
		{
			TowerObject* boostTower = boostTowerList->Travel();
			BoostInRange(boostTower);
		}
	}
}

void CObjectManagement::InitLiveAndMoney(__INT32 _lives, __INT32 _money)
{
	mTotalLives = _lives;
	mTotalMoney = _money;
}

void CObjectManagement::ResetBoost()
{
	CList<GameObject*>* towerList = GetListObject(OBJECT_TOWER);
	if(towerList)
	{
		towerList->BeginTravel();
		while(!towerList->IsEndOfTravel())
		{
			TowerObject* temp = (TowerObject*) towerList->Travel();
			if(temp)
			{
				temp->curCritical = temp->mProperties->mCritical;
				temp->curDamage = temp->mProperties->mBaseDamage;
				temp->curSpeedAttack = temp->mProperties->mSpeedAttack;
			}
		}
	}
}

CList<TowerObject*>* CObjectManagement::GetAllBoostTower()
{
	CList<GameObject*>* towerList = GetListObject(OBJECT_TOWER);
	CList<TowerObject*>* result = 0;
	bool haveBoostTower = false;
	if(towerList)
	{
		result = new CList<TowerObject*>;
		towerList->BeginTravel();
		while(!towerList->IsEndOfTravel())
		{
			TowerObject* temp = (TowerObject*) towerList->Travel();
			if(temp && temp->mProperties->mSkillID == 2)
			{
				result->AddItem(temp);
				haveBoostTower = true;
			}
			temp = 0;
		}
		if(!haveBoostTower)
		{
			delete result;
			result = 0;
		}
	}
	return result;
}

void CObjectManagement::BoostInRange(TowerObject* boostTower)
{
	CList<GameObject*>* towerList = GetListObject(OBJECT_TOWER);
	if(towerList)
	{
		towerList->BeginTravel();
		while(!towerList->IsEndOfTravel())
		{
			TowerObject* tower = (TowerObject*) towerList->Travel();
			float s = length(tower->getPositionX(),tower->getPositionY(),boostTower->getPositionX(),boostTower->getPositionY());
			if(s <= boostTower->mProperties->mRange && tower->mProperties->mSkillID != 2)
			{
				tower->curDamage += boostTower->mProperties->mBoostDamage;
				tower->curCritical += boostTower->mProperties->mBoostCritical;
				tower->curSpeedAttack += boostTower->mProperties->mBoostSpeed;
			}
		}
	}
}

void CObjectManagement::AddList(CList<GameObject*>* list)
{
	if(list && list->GetElement(0))
	{
		ObjectType type = list->GetElement(0)->mType;
		//check if object exists in ListLookup
		Item* item = 0;
		m_ListLookup->BeginTravel();
		while(!m_ListLookup->IsEndOfTravel())
		{
			item = m_ListLookup->Travel();
			if(item != 0)
			{
				if(item->type == type)
				{
					break;
				}
				else item = 0;
			}
		}

		//add input list to m_ListLookup
		if(!item)
		{
			Item* item = new Item(type, list);
			m_ListLookup->AddItem(item);
		}
		else
		{
			list->BeginTravel();
			while(!list->IsEndOfTravel())
			{
				GameObject* tempObj = list->Travel();
				if(tempObj)
					item->objects->AddItem(tempObj);
			}
		}
	}
}
void CObjectManagement::AddElement(GameObject* ele)
{
	if(ele)
	{
		ObjectType type = ele->mType;
		//check if object exists in ListLookup
		Item* item = 0;
		m_ListLookup->BeginTravel();
		while(!m_ListLookup->IsEndOfTravel())
		{
			item = m_ListLookup->Travel();
			if(item != 0)
			{
				if(item->type == type)
				{
					break;
				}
				else item = 0;
			}
		}

		//process to add this object to List
		if(item)
		{
			item->objects->AddItem(ele);
		}
		else
		{
			//create objects for Item
			CList<GameObject*>* objects = new CList<GameObject*>;
			objects->AddItem(ele);
			//create Item from objects and type
			Item* item = new Item(type, objects);
			m_ListLookup->AddItem(item);
		}
	}
}
CList<EnemyObject*>* CObjectManagement::GetEnemies(MapPosition _position)
{
	//check if the enemys exists in ListLookup
	Item* item = 0;
	m_ListLookup->BeginTravel();
	while(!m_ListLookup->IsEndOfTravel())
	{
		item = m_ListLookup->Travel();
		if(item != 0)
		{
			if(item->type == OBJECT_ENEMY)
			{
				break;
			}
			else item = 0;
		}
	}

	if(!item) return 0;
	else
	{
		//check if any object is at the position
		bool foundObject = false;
		CList<EnemyObject*>* result = new CList<EnemyObject*>; //for return
		CList<GameObject*>* listTemp = item->objects; //for travel

		if(listTemp)
		{
			listTemp->BeginTravel();
			while(!listTemp->IsEndOfTravel())
			{
				EnemyObject* obj = (EnemyObject*) listTemp->Travel();
				if(obj)
				{
					MapPosition* objPos = obj->GetCurPos();
					if(objPos)
					{
						if(_position.mX == objPos->mX && _position.mY == objPos->mY)
						{
							foundObject = true;
							result->AddItem(obj);
						}
					}
				}
			}
		}

		if(!foundObject)
		{
			delete result;
			return 0;
		}
		else return result;
	}
}
MapObject* CObjectManagement::GetMap()
{
	//check if the map is existed
	Item* item = 0;
	m_ListLookup->BeginTravel();
	while(!m_ListLookup->IsEndOfTravel())
	{
		item = m_ListLookup->Travel();
		if(item != 0)
		{
			if(item->type == OBJECT_MAP)
			{
				break;
			}
			else item = 0;
		}
	}
	//return the map
	if(!item) return 0;
	else
	{
		if(item->objects)
		{
			MapObject* map = (MapObject*) item->objects->GetElement(0);
			return map;
		} 
		else return 0;
	}
}
TowerObject* CObjectManagement::GetTower(MapPosition _position)
{
	//check if towers are existed
	Item* item = 0;
	m_ListLookup->BeginTravel();
	while(!m_ListLookup->IsEndOfTravel())
	{
		item = m_ListLookup->Travel();
		if(item != 0)
		{
			if(item->type == OBJECT_TOWER)
			{
				break;
			}
			else item = 0;
		}
	}

	if(!item) return 0;
	else
	{
		TowerObject* tTower = 0;
		CList<GameObject*>* listTemp = item->objects;
		if(listTemp)
		{
			listTemp->BeginTravel();
			while(!listTemp->IsEndOfTravel())
			{
				tTower = (TowerObject*) listTemp->Travel();
				if(tTower)
				{
					if(tTower->mPosition.mX == _position.mX && tTower->mPosition.mY == _position.mY)
					{
						break;
					}
					else tTower = 0;
				}
			}
		}
		return tTower;
	}
}
CList<GameObject*>* CObjectManagement::GetListObject(ObjectType type)
{
	//check if object exists in ListLookup
	Item* item = 0;
	m_ListLookup->BeginTravel();
	while(!m_ListLookup->IsEndOfTravel())
	{
		item = m_ListLookup->Travel();
		if(item != 0)
		{
			if(item->type == type)
			{
				break;
			}
			else item = 0;
		}
	}
	//return
	if(item)
	{
		return item->objects;
	}
	else return 0;
}
void CObjectManagement::Render()
{
	if(m_ListLookup)
	{
		m_ListLookup->BeginTravel();
		while(!m_ListLookup->IsEndOfTravel())
		{
			Item* item = m_ListLookup->Travel();
			Log("Render object TYPE=%d %lu",item->type,__UINT32(CDevice::GetInstance()->GetTimer()));
			if(item && item->objects)
			{
				item->objects->BeginTravel();
				while (!item->objects->IsEndOfTravel())
				{
					item->objects->Travel()->Render();
					Log("Render object TYPE=%d %lu ____RENDER OBJECT",item->type,__UINT32(CDevice::GetInstance()->GetTimer()));
				}
			}
		}
	}
}
void CObjectManagement::Update(float tpf)
{
	m_ListLookup->BeginTravel();
	while(!m_ListLookup->IsEndOfTravel())
	{
		Item* item = m_ListLookup->Travel();
		item->objects->BeginTravel();
		if (item->type == OBJECT_BULLET)
		{
			while (!item->objects->IsEndOfTravel())
			{
				BulletObject *bullet = (BulletObject*)item->objects->Travel();
				bullet->Update(tpf);
				if (bullet->IsFinished())
				{
					item->objects->RemoveItem(bullet);
					SAFE_DEL(bullet);
				}
			}
		}
		else
			while (!item->objects->IsEndOfTravel())
		{
			item->objects->Travel()->Update(tpf);
		}
	}
}
EnemyObject* CObjectManagement::getTarget(MapPosition* _position, __INT32 _range)
{
	EnemyObject* result = 0;
	float towerX = (_position->mX + 1)*0.5;
	float towerY = (_position->mY + 1)*0.5;

	CList<GameObject*>* list = this->GetListObject(OBJECT_ENEMY);
	if(list)
	{
		__INT32* temp = new __INT32[list->GetCount()];
		__INT32 idx = 0;
		list->BeginTravel();
		while(!list->IsEndOfTravel())
		{
			EnemyObject* enemy = (EnemyObject*) list->Travel();
			if(enemy && !enemy->isDying && enemy->isAlive)
			{
				float x,y;
				enemy->GetPos(x,y);
				float s = length(towerX, towerY, x, y);
				if(s <= _range) temp[idx++] = s;
				else temp[idx++] = -1;
			}
			else temp[idx++] = -1;
		}
		//find min
		idx = 0;
		for(int i = 0; i < list->GetCount(); i++)
		{
			if(temp[idx] == -1) idx = i;
			else
			{
				if(temp[i] != -1 && temp[i] < temp[idx]) idx = i;
			}
		}
		//return
		if(temp[idx] == -1) result = 0;
		else result = (EnemyObject*) list->GetElement(idx);
	}
	return result;
}
void CObjectManagement::ClearAll()
{
	if(m_ListLookup)
	{
		m_ListLookup->BeginTravel();
		while(!m_ListLookup->IsEndOfTravel())
		{
			Item* item = m_ListLookup->Travel();
			//delete all Object
			if(item && item->objects)
			{
				item->objects->BeginTravel();
				while(!item->objects->IsEndOfTravel())
				{
					GameObject *object = item->objects->Travel();
					item->objects->RemoveItem(object);
					SAFE_DEL(object);
				}
				item->objects->Clear();
			}
		}
		m_ListLookup->Clear();
	}
}
void CObjectManagement::ClearObjectType(ObjectType _type)
{
	if(m_ListLookup)
	{
		Item* item = 0;
		m_ListLookup->BeginTravel();
		while(!m_ListLookup->IsEndOfTravel())
		{
			item = m_ListLookup->Travel();
			if(item && item->type == _type)
				break;
			else item = 0;
		}
		if(item && item->objects)
		{
			item->objects->BeginTravel();
			while(!item->objects->IsEndOfTravel())
			{
				GameObject *obj = item->objects->Travel();
				item->objects->RemoveItem(obj);
				SAFE_DEL(obj);
			}
			item->objects->Clear();
			m_ListLookup->RemoveItem(item);
			SAFE_DEL(item);
		}
	}
}

CObjectManagement::~CObjectManagement() 
{
	if(m_ListLookup)
	{
		m_ListLookup->BeginTravel();
		while(!m_ListLookup->IsEndOfTravel())
		{
			Item* item = m_ListLookup->Travel();
			//delete all Object
			if(item && item->objects)
			{
				item->objects->BeginTravel();
				while(!item->objects->IsEndOfTravel())
				{
					GameObject *object = item->objects->Travel();
					item->objects->RemoveItem(object);
					SAFE_DEL(object);
				}
				item->objects->Clear();
			}
		}
		m_ListLookup->Clear();
	}
}

void CObjectManagement::RemoveTower(TowerObject* _tower)
{
	//get Item which included _tower
	Item* item = 0;
	m_ListLookup->BeginTravel();
	while(!m_ListLookup->IsEndOfTravel())
	{
		item = m_ListLookup->Travel();
		if(item->type == OBJECT_TOWER)
		{
			break;
		}
		item = 0;
	}
	//remove _tower
	if(item)
	{
		item->objects->RemoveItem(_tower);
		SAFE_DEL(_tower);
	}
}

bool CObjectManagement::isFinishWave()
{
	CList<GameObject*>* list = GetListObject(OBJECT_ENEMY);
	if(list)
	{
		list->BeginTravel();
		while(!list->IsEndOfTravel())
		{
			EnemyObject* temp = (EnemyObject*) list->Travel();
			if(temp->isAlive) return false;
		}
	}
	return true;
}

void CObjectManagement::UpdateLives(__INT32 _lives)
{
	mTotalLives += _lives;
}
void CObjectManagement::UpdateMoney(__INT32 _money)
{
	mTotalMoney += _money;
}
__INT32 CObjectManagement::GetLives()
{
	return mTotalLives;
}
__INT32 CObjectManagement::GetMoney()
{
	return mTotalMoney;
}
