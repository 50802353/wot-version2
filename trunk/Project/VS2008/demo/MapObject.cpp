#include "MapObject.h"

CMapObject::CMapObject(SMapData *data)
{
	this->ObjectType = EGameObject::E_OBJ_MAP;
	this->data = data;
	ObjectMap = new int[this->data->Height * this->data->Width];
	memset(ObjectMap, 0, sizeof(int) * this->data->Height * this->data->Width);
	TowerKeyCounter = 0;
	EnemyKeyCounter = 0;
	ObstacleKeyCounter = 0;
	BulletKeyCounter = 0;

	CImageManager::GetInstance()->AddImage<CFileWin32Driver>("..\\resource\\grid_cell.tga",true);
	MapGridTexture = CImageManager::GetInstance()->Get("..\\resource\\grid_cell.tga");
}

CMapObject::~CMapObject(void)
{
	SAFE_DEL_ARRAY(ObjectMap);
}

void CMapObject::Init()
{
}

void CMapObject::Update()
{
	TowerList.BeginTravel();
	while (!TowerList.IsEndOfTravel())
	{
		CTowerObject* cur = (CTowerObject*)TowerList.Travel();
		cur->Update();
	}

	EnemyList.BeginTravel();
	while (!EnemyList.IsEndOfTravel())
	{
		CEnemyObject* cur = (CEnemyObject*)EnemyList.Travel();
		cur->Update();
	}

	BulletList.BeginTravel();
	while (!BulletList.IsEndOfTravel())
	{
		CBulletObject* cur = (CBulletObject*)BulletList.Travel();
		cur->Update();
	}

	ObstacleList.BeginTravel();
	while (!ObstacleList.IsEndOfTravel())
	{
		CObstacleObject* cur = (CObstacleObject*)ObstacleList.Travel();
		cur->Update();
	}
}

void CMapObject::Render()
{
	
	CGraphics2D::GetInstance()->DrawImageRegion(SRect<float>(0,0,10,10),MapGridTexture,SRect<float>(0,0,MapGridTexture->GetWidth()*10,MapGridTexture->GetHeight()*10));


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

void CMapObject::Destroy()
{
}

void CMapObject::AddObject(CTowerObject* Tower)
{
	TowerList.AddItem(TowerKeyCounter++, Tower);
}

void CMapObject::AddObject(CEnemyObject* Enemy)
{
	EnemyList.AddItem(EnemyKeyCounter++, Enemy);
}

void CMapObject::AddObject(CBulletObject* Bullet)
{
	BulletList.AddItem(BulletKeyCounter++, Bullet);
}

void CMapObject::AddObject(CObstacleObject* Obstacle)
{
	ObstacleList.AddItem(ObstacleKeyCounter++, Obstacle);
}