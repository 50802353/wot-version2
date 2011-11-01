#include "MapObject.h"
#include "ObjectManager.h"

CMapObject::CMapObject(SMapData *data)
{
	this->ObjectType = EGameObject::E_OBJ_MAP;
	this->data = data;
	ObjectMap = new int[this->data->Height * this->data->Width];
	memset(ObjectMap, 0, sizeof(int) * this->data->Height * this->data->Width);
	DirectionMap = new int[this->data->Height * this->data->Width];
	memset(DirectionMap, 0, sizeof(int) * this->data->Height * this->data->Width);
	RemainingLife = data->GivenLife;
	Money = data->GivenMoney;
	memset(Enemy, 0, sizeof(Enemy));
	isSpawnTime = false;
	NumberOfEnemyInMap = 0;
	CalculateEnemyPath(ObjectMap, DirectionMap);

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

void CMapObject::Update(int delta_time)
{
	static int CurrentWave = 0;
	static int NextSpawnTime;
	static int EnemyIndexInWave;
	if ((!isSpawnTime) && (NumberOfEnemyInMap==0))
	{
		if (CObjectManager::CurrentObjectManager->BulletList.GetCount()==0)
		{
			if (CurrentWave < this->data->NumberOfWaves)
			{
				CObjectManager::CurrentObjectManager->ClearEnemy();
				isSpawnTime = true;
				EnemyIndexInWave = 0;
				NextSpawnTime = this->data->Wave[CurrentWave]->SpawnTime[EnemyIndexInWave];
			}
		}
	}

	if (isSpawnTime)
	{
		if (NextSpawnTime>delta_time)
		{
			NextSpawnTime -= delta_time;
		}
		else
		{
			CEnemyObject* Enemy = new CEnemyObject(this->data->Wave[CurrentWave]->Enemy[EnemyIndexInWave], this->data->SourcePosition);
			Enemy->Spawn();
			CObjectManager::CurrentObjectManager->AddObject(Enemy);
			EnemyIndexInWave++;
			if (EnemyIndexInWave >= this->data->Wave[CurrentWave]->Quantity)
			{
				NextSpawnTime = 0;
				isSpawnTime = false;				
				CurrentWave++;
			}
			else
			{
				NextSpawnTime = this->data->Wave[CurrentWave]->SpawnTime[EnemyIndexInWave] - (delta_time-NextSpawnTime);
			}
		}
	}

}

void CMapObject::Render()
{
	CGraphics2D::GetInstance()->DrawImageRegion(SRect<float>(0,0,10,10),MapGridTexture,SRect<float>(0,0,MapGridTexture->GetWidth()*10,MapGridTexture->GetHeight()*10));
	CGraphics2D::GetInstance()->Flush();
}

void CMapObject::Destroy()
{
	CObjectManager::CurrentObjectManager->SetMapObject(NULL);
	delete this;
}

bool CMapObject::CalculateEnemyPath(int* ObjectMap, int* DirectionMap)
{
	int* TraceMap = new int[data->Width*data->Height];
	memset(TraceMap, 0, (data->Width)*(data->Height)*sizeof(int));
	TraceMap[data->DestinationPosition.y*data->Width+data->DestinationPosition.x] = 1;

	
	

	LogicPosition* Queue = new LogicPosition[(data->Width)*(data->Height)];	//allocate queue
	int cur = 0;	//current index of queue
	int last = 0;	//last index of queue
	Queue[0] = data->DestinationPosition;	//add destination to queue
	while (cur<=last)
	{
		LogicPosition curpos = Queue[cur];
		for (int i=1; i<=4; i++)
		{
			LogicPosition nextpos = curpos + OppositeMove[i];
			if (	(nextpos.x>=0) && (nextpos.x<data->Width) && (nextpos.y>=0) && (nextpos.y<data->Height) 
					&&(ObjectMap[nextpos.y*data->Width+nextpos.x]!=E_OBJ_TOWER)
					&& (ObjectMap[nextpos.y*data->Width+nextpos.x]!=E_OBJ_OBSTACLE)
					&& (TraceMap[nextpos.y*data->Width+nextpos.x]== 0))
			{
				TraceMap[nextpos.y*data->Width+nextpos.x] = TraceMap[curpos.y*data->Width+curpos.x] + 1;
				DirectionMap[nextpos.y*data->Width+nextpos.x] = i;
				Queue[++last] = nextpos;
			}
		}
		cur++;
	}

	bool isValid = true;

	for (int i=0; i<data->Width; i++)
	{
		for (int j=0; j<data->Height; j++)
		{
			LogicPosition curpos(i,j);
			if (	(curpos.x>=0) && (curpos.x<data->Width) && (curpos.y>=0) && (curpos.y<data->Height) 
					&&(ObjectMap[curpos.y*data->Width+curpos.x]!=E_OBJ_TOWER)
					&& (ObjectMap[curpos.y*data->Width+curpos.x]!=E_OBJ_OBSTACLE)
					&& (TraceMap[curpos.y*data->Width+curpos.x]==0))
			{
				isValid = false;
				break;
			}
		}
		if (!isValid) break;
	}
	SAFE_DEL(TraceMap);
	return isValid;
}


void CMapObject::BuildTower(STowerData* data, LogicPosition position)
{
	CTowerObject* tower = new CTowerObject(data);
	int* NewObjectMap = new int[this->data->Width* this->data->Height];
	memcpy(NewObjectMap, this->ObjectMap, sizeof(int)*this->data->Width* this->data->Height);
	NewObjectMap[position.y *this->data->Width + position.x] = E_OBJ_TOWER;
	NewObjectMap[(position.y+1) *this->data->Width + position.x] = E_OBJ_TOWER;
	NewObjectMap[position.y *this->data->Width + (position.x+1)] = E_OBJ_TOWER;
	NewObjectMap[(position.y+1) *this->data->Width + (position.x+1)] = E_OBJ_TOWER;
	int* NewDirectionMap = new int[this->data->Width* this->data->Height];
	memset(NewDirectionMap, 0, sizeof(int)*this->data->Width* this->data->Height);
	if (CalculateEnemyPath(NewObjectMap, NewDirectionMap))
	{
		tower->logicposition = position;
		tower->position = Position(position.x+1, position.y+1, 0);
		CObjectManager::CurrentObjectManager->AddObject(tower);
		SAFE_DEL(ObjectMap);
		this->ObjectMap = NewObjectMap;
		SAFE_DEL(DirectionMap);
		this->DirectionMap = NewDirectionMap;
	}	
}