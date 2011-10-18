#include "ObjectManager.h"

CObjectManager* CObjectManager::CurrentObjectManager; 

CObjectManager::CObjectManager(void)
{
	TowerKeyCounter = 0;
	EnemyKeyCounter = 0;
	ObstacleKeyCounter = 0;
	BulletKeyCounter = 0;

	Map = NULL;

	CurrentObjectManager = this;
}

CObjectManager::~CObjectManager(void)
{
}

void CObjectManager::AddObject(CTowerObject* Tower)
{
	Tower->ObjectID = ++TowerKeyCounter;
	TowerList.AddItem(TowerKeyCounter, Tower);	
}

void CObjectManager::AddObject(CEnemyObject* Enemy)
{
	Enemy->ObjectID = ++EnemyKeyCounter;
	EnemyList.AddItem(EnemyKeyCounter, Enemy);	
}

void CObjectManager::AddObject(CBulletObject* Bullet)
{
	Bullet->ObjectID = ++BulletKeyCounter;
	BulletList.AddItem(BulletKeyCounter, Bullet);	
}

void CObjectManager::AddObject(CObstacleObject* Obstacle)
{
	Obstacle->ObjectID = ++ObstacleKeyCounter;
	ObstacleList.AddItem(ObstacleKeyCounter, Obstacle);	
}

void CObjectManager::RemoveObject(CTowerObject* Tower)
{
	TowerList.RemoveItem(Tower->ObjectID);
}

void CObjectManager::RemoveObject(CEnemyObject* Enemy)
{
	EnemyList.RemoveItem(Enemy->ObjectID);
}

void CObjectManager::RemoveObject(CObstacleObject* Obstacle)
{
	ObstacleList.RemoveItem(Obstacle->ObjectID);
}

void CObjectManager::RemoveObject(CBulletObject* Bullet)
{
	BulletList.RemoveItem(Bullet->ObjectID);
}

void CObjectManager::SetMapObject(CMapObject* MapObject)
{
	Map = MapObject;
}

void CObjectManager::Init()
{
}

void CObjectManager::Update(int delta_time)
{
	if (Map) Map->Update(delta_time);

	TowerList.BeginTravel();
	while (!TowerList.IsEndOfTravel())
	{
		CTowerObject* cur = (CTowerObject*)TowerList.Travel();
		cur->Update(delta_time);
	}

	EnemyList.BeginTravel();
	while (!EnemyList.IsEndOfTravel())
	{
		CEnemyObject* cur = (CEnemyObject*)EnemyList.Travel();
		cur->Update(delta_time);
	}

	BulletList.BeginTravel();
	while (!BulletList.IsEndOfTravel())
	{
		CBulletObject* cur = (CBulletObject*)BulletList.Travel();
		cur->Update(delta_time);
	}

	ObstacleList.BeginTravel();
	while (!ObstacleList.IsEndOfTravel())
	{
		CObstacleObject* cur = (CObstacleObject*)ObstacleList.Travel();
		cur->Update(delta_time);
	}
}

void CObjectManager::Render()
{
	if (Map) Map->Render();

	TowerList.BeginTravel();
	while (!TowerList.IsEndOfTravel())
	{
		CTowerObject* cur = (CTowerObject*)TowerList.Travel();
		cur->Render();
	}

	EnemyList.BeginTravel();
	while (!EnemyList.IsEndOfTravel())
	{
		CEnemyObject* cur = (CEnemyObject*)EnemyList.Travel();
		cur->Render();
	}

	BulletList.BeginTravel();
	while (!BulletList.IsEndOfTravel())
	{
		CBulletObject* cur = (CBulletObject*)BulletList.Travel();
		cur->Render();
	}

	ObstacleList.BeginTravel();
	while (!ObstacleList.IsEndOfTravel())
	{
		CObstacleObject* cur = (CObstacleObject*)ObstacleList.Travel();
		cur->Render();
	}
}

void CObjectManager::Destroy()
{
	TowerList.DeallocateElementPointer();
	TowerList.Clear();
	EnemyList.DeallocateElementPointer();
	EnemyList.Clear();
	BulletList.DeallocateElementPointer();
	BulletList.Clear();
	ObstacleList.DeallocateElementPointer();
	ObstacleList.Clear();
	delete this;
}