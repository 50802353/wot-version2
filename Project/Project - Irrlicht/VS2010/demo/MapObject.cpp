#include "MapObject.h"
#include "ObjectManager.h"

#define WIN_WAV "./resource/AWin.wav"
#define LOSE_WAV "./resource/ALose.wav"


/*class CSampleSceneNode : public scene::ITerrainSceneNode
{	
	virtual void render()
	{
		scene::ITerrainSceneNode::render();

		video::IVideoDriver* driver = SceneManager->getVideoDriver();
		video::SMaterial Material = getMaterial(0);
		Material.Wireframe = true;
		driver->setMaterial(Material);
		if (!IsVisible || !SceneManager->getActiveCamera())
			return;

		if (!Mesh->getMeshBufferCount())
			return;

		video::IVideoDriver* driver = SceneManager->getVideoDriver();

		driver->setTransform (video::ETS_WORLD, core::IdentityMatrix);
		driver->setMaterial(Mesh->getMeshBuffer(0)->getMaterial());

		RenderBuffer->getIndexBuffer().set_used(IndicesToRender);

		// For use with geomorphing
		driver->drawMeshBuffer(RenderBuffer);

		RenderBuffer->getIndexBuffer().set_used(RenderBuffer->getIndexBuffer().allocated_size());

	}
};*/






CMapObject::CMapObject(SMapData *data)
{
	this->ObjectType = EGameObject::E_OBJ_MAP;
	this->data = data;
	ObjectMap = new int[this->data->Height * this->data->Width];	
	DirectionMap = new int[this->data->Height * this->data->Width];
	Reset();

	//CImageManager::GetInstance()->AddImage<CFileWin32Driver>("..\\..\\resource\\grid_cell.tga",true);
	//MapGridTexture = CImageManager::GetInstance()->Get("..\\..\\resource\\grid_cell.tga");
	Init();
}

CMapObject::~CMapObject(void)
{
	SAFE_DEL_ARRAY(ObjectMap);
	SAFE_DEL_ARRAY(DirectionMap);
	Destroy();
}

void CMapObject::Init()
{

	sceneNode = smgr->addTerrainSceneNode(
                "./resource/terrain-heightmap.bmp",
                0,											// parent node
                2,											// node id
				irr::core::vector3df(-120.f+(float)data->Width/2, 0.f, -120.f+(float)data->Height/2),         // position
                irr::core::vector3df(0.f, 0.f, 0.f),         // rotation
                irr::core::vector3df(1.f, 1.f, 1.f),		  // scale
                irr::video::SColor ( 255, 255, 255, 255 ),   // vertexColor
                5,											 // maxLOD
                irr::scene::ETPS_17,                         // patchSize
                4											 // smoothFactor
                );

    //sceneNode->setMaterialFlag(irr::video::EMF_LIGHTING, true);

    sceneNode->setMaterialTexture(0,
                    driver->getTexture("./resource/terrain-texture.jpg"));
    sceneNode->setMaterialTexture(1,
                    driver->getTexture("./resource/detailmap3.jpg"));
        
    sceneNode->setMaterialType(irr::video::EMT_DETAIL_MAP);

    sceneNode->scaleTexture(1.0f, 20.0f);

	irr::scene::ITriangleSelector* selector = smgr->createTerrainTriangleSelector(sceneNode, 0);
	sceneNode->setTriangleSelector(selector);
	selector->drop();

	skydome =smgr->addSkyDomeSceneNode(driver->getTexture("./resource/skydome.jpg"),16,8,0.95f,2.0f);
	//irr::scene::IMesh* m = sceneNode->getMesh();
	//int a=1;


	drawGrid=false;
	
	PSsrc = smgr->addParticleSystemSceneNode(false);
	scene::IParticleEmitter* em = PSsrc->createRingEmitter(
		core::vector3df(0,0,0),0.4,0.3,core::vector3df(0,0.001,0),10U,20U,video::SColor(255,255,255,255),video::SColor(255,255,255,255),2000U,4000U,0,core::dimension2df(0.2,0.2),core::dimension2df(0.5,0.5));
	PSsrc->setEmitter(em);
	PSsrc->setScale(core::vector3df(1,1,1));
	PSsrc->setMaterialFlag(video::EMF_LIGHTING, false);
	PSsrc->setMaterialFlag(video::EMF_ZWRITE_ENABLE, false);
	PSsrc->setMaterialTexture(0, driver->getTexture("./resource/particle2.bmp"));
	PSsrc->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR);
	em->drop();

	scene::IParticleAffector* paf = PSsrc->createRotationAffector(core::vector3df(0,135,0),core::vector3df(data->SourcePosition.x+0.5,0,data->SourcePosition.y+0.5));
	PSsrc->addAffector(paf);
	paf->drop();

	paf = PSsrc->createFadeOutParticleAffector(video::SColor(0,0,0,0),2000);
	PSsrc->addAffector(paf);
	paf->drop();

	//scene::
	PSsrc->setPosition(core::vector3df(data->SourcePosition.x+0.5,0,data->SourcePosition.y+0.5));




	PSdst = smgr->addParticleSystemSceneNode(false);
	em = PSdst->createRingEmitter(
		core::vector3df(0,0,0),0.4,0.3,core::vector3df(0,0.001,0),10U,20U,video::SColor(255,255,255,255),video::SColor(255,255,255,255),2000U,4000U,0,core::dimension2df(0.2,0.2),core::dimension2df(0.5,0.5));
	PSdst->setEmitter(em);
	PSdst->setScale(core::vector3df(1,1,1));
	PSdst->setMaterialFlag(video::EMF_LIGHTING, false);
	PSdst->setMaterialFlag(video::EMF_ZWRITE_ENABLE, false);
	PSdst->setMaterialTexture(0, driver->getTexture("./resource/particle2.bmp"));
	PSdst->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR);
	em->drop();

	paf = PSdst->createRotationAffector(core::vector3df(0,260,0),core::vector3df(data->DestinationPosition.x+0.5,0,data->DestinationPosition.y+0.5));
	PSdst->addAffector(paf);
	paf->drop();

	paf = PSdst->createAttractionAffector(core::vector3df(data->DestinationPosition.x+0.5,0,data->DestinationPosition.y+0.5),1);
	PSdst->addAffector(paf);
	paf->drop();

	paf = PSdst->createFadeOutParticleAffector(video::SColor(0,0,0,0),2000);
	PSdst->addAffector(paf);
	paf->drop();

	//scene::
	PSdst->setPosition(core::vector3df(data->DestinationPosition.x+0.5,0,data->DestinationPosition.y+0.5));




	CAudioPlayer::GetInstance()->Load<CFileWin32Driver>(WIN_WAV);
	CAudioPlayer::GetInstance()->Load<CFileWin32Driver>(LOSE_WAV);
}

void CMapObject::Update(int delta_time)
{
	if (status == ESTATUS_PLAY)
	{


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
				else Win();
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
	} ///if status == ESTATUS_PLAY



}

void CMapObject::Render()
{
	if (!drawGrid) return;
	video::SMaterial material;
	material.setTexture(0,0);
	material.Wireframe = true;
	material.Lighting = false;
	material.ZBuffer = false;
	material.ZWriteEnable = false;
	material.NormalizeNormals = false;
	material.MaterialType = video::EMT_TRANSPARENT_ADD_COLOR;


	driver->setMaterial(material);
	driver->setTransform (video::ETS_WORLD, core::IdentityMatrix);
	for (int i=0;i<=data->Width;i++)
		driver->draw3DLine(core::vector3df(i,sceneNode->getHeight(i,0),0),core::vector3df(i,sceneNode->getHeight(i,data->Height),data->Height),video::SColor(0,125,55,0));
	for (int i=0;i<=data->Height;i++)
		driver->draw3DLine(core::vector3df(0,sceneNode->getHeight(0,i),i),core::vector3df(data->Width,sceneNode->getHeight(data->Width,i),i),video::SColor(0,125,55,0));
	
}

void CMapObject::Destroy()
{
	sceneNode->remove();
	skydome->remove();
	PSsrc->remove();
	PSdst->remove();

	CObjectManager::CurrentObjectManager->SetMapObject(NULL);
	//delete this;
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

bool CMapObject::BuildTower(STowerData* data, LogicPosition position)
{
	if (Money<data->Cost) return false;
	
	CTowerObject* tower = new CTowerObject(data);
	int* NewObjectMap = new int[this->data->Width* this->data->Height];
	memcpy(NewObjectMap, this->ObjectMap, sizeof(int)*this->data->Width* this->data->Height);

	for (int i=0;i<2;i++)
		for (int j=0;j<2;j++)
			if (NewObjectMap[(position.y+i) *this->data->Width + (position.x+j)] == E_OBJ_NONE)
			{
				NewObjectMap[(position.y+i) *this->data->Width + (position.x+j)] = E_OBJ_TOWER;
			}
			else
			{
				delete NewObjectMap;
				tower->Destroy();
				return false;
			}

	/*NewObjectMap[position.y *this->data->Width + position.x] = E_OBJ_TOWER;
	NewObjectMap[(position.y+1) *this->data->Width + position.x] = E_OBJ_TOWER;
	NewObjectMap[position.y *this->data->Width + (position.x+1)] = E_OBJ_TOWER;
	NewObjectMap[(position.y+1) *this->data->Width + (position.x+1)] = E_OBJ_TOWER;*/
	int* NewDirectionMap = new int[this->data->Width* this->data->Height];
	memset(NewDirectionMap, 0, sizeof(int)*this->data->Width* this->data->Height);
	if (CalculateEnemyPath(NewObjectMap, NewDirectionMap))
	{
		Money-= data->Cost;
		tower->logicposition = position;
		tower->position = Position(position.x+1, position.y+1, 0.8);
		tower->sceneNode->setPosition(irr::core::vector3df(tower->position.x, tower->position.z, tower->position.y));


		tower->particleSystem =
		smgr->addParticleSystemSceneNode(false);

		core::vector3df normal(0,0.5,0);
		scene::IParticleEmitter* em  = tower->particleSystem->createRingEmitter(
			core::vector3df(0,0,0),
			0.5,
			0.1,
			core::vector3df(0,0.001,0),
			8U,
			10U,
			video::SColor(0,255,255,255),
			video::SColor(0,255,255,255),
			1000U,
			2000U,
			0,
			core::dimension2df(0.5,0.5),
			core::dimension2df(0.1,0.1));

		tower->particleSystem->setEmitter(em);
		em->drop();
		tower->particleSystem->setScale(core::vector3df(1,1,1));
		tower->particleSystem->setMaterialFlag(video::EMF_LIGHTING, false);
		tower->particleSystem->setMaterialFlag(video::EMF_ZWRITE_ENABLE, false);
		tower->particleSystem->setMaterialTexture(0, driver->getTexture("./resource/particle.bmp"));
		tower->particleSystem->setMaterialType(video::EMT_TRANSPARENT_VERTEX_ALPHA);

		tower->particleSystem->setPosition(irr::core::vector3df(tower->position.x, tower->position.z-0.7, tower->position.y));
		scene::IParticleAffector* paf =   tower->particleSystem->createRotationAffector(core::vector3df(0,500,0),irr::core::vector3df(tower->position.x, tower->position.z-0.7, tower->position.y));
		tower->particleSystem->addAffector(paf);
		paf->drop();
		paf = tower->particleSystem->createAttractionAffector(irr::core::vector3df(tower->position.x, tower->position.z+5, tower->position.y),0.5);
		tower->particleSystem->addAffector(paf);
		paf->drop();
		paf = tower->particleSystem->createFadeOutParticleAffector();
		tower->particleSystem->addAffector(paf);
		paf->drop();

		CObjectManager::CurrentObjectManager->AddObject(tower);
		SAFE_DEL(ObjectMap);
		this->ObjectMap = NewObjectMap;
		SAFE_DEL(DirectionMap);
		this->DirectionMap = NewDirectionMap;

		
		return true;
	}	
	else
	{
		delete NewObjectMap;
		tower->Destroy();
		return false;
	}
}

boolean CMapObject::iSBuildable(int x, int y)
{
	if (x<0) return false;
	if (x>=data->Width-1) return false;
	if (y<0) return false;
	if (y>=data->Height-1) return false;
	int* OMap = CObjectManager::CurrentObjectManager->GetMapObjectIncludingEnemy();
	if (OMap[y*data->Width+x]==E_OBJ_NONE && OMap[(y+1)*data->Width+x]==E_OBJ_NONE &&
		OMap[y*data->Width+x+1]==E_OBJ_NONE && OMap[(y+1)*data->Width+x+1]==E_OBJ_NONE) return true;
	else return false;
}

void CMapObject::AddObstacle(SObstacleData* data, LogicPosition position, int size)
{
	CObstacleObject* obstacle = new CObstacleObject(data,size);
	int* NewObjectMap = new int[this->data->Width* this->data->Height];
	memcpy(NewObjectMap, this->ObjectMap, sizeof(int)*this->data->Width* this->data->Height);

	for (int i=0;i<obstacle->size;i++)
		for (int j=0;j<obstacle->size;j++)
			if (NewObjectMap[(position.y+i) *this->data->Width + (position.x+j)] == E_OBJ_NONE)
			{
				NewObjectMap[(position.y+i) *this->data->Width + (position.x+j)] = E_OBJ_OBSTACLE;
			}
			else
			{
				delete NewObjectMap;
				return;
			}

	int* NewDirectionMap = new int[this->data->Width* this->data->Height];
	memset(NewDirectionMap, 0, sizeof(int)*this->data->Width* this->data->Height);
	if (CalculateEnemyPath(NewObjectMap, NewDirectionMap))
	{
		obstacle->logicposition = position;
		obstacle->position = Position(position.x+(float)size/2.0, position.y+(float)size/2.0, 0);
		obstacle->sceneNode->setPosition(irr::core::vector3df(obstacle->position.x, obstacle->position.z, obstacle->position.y));
		CObjectManager::CurrentObjectManager->AddObject(obstacle);
		SAFE_DEL(ObjectMap);
		this->ObjectMap = NewObjectMap;
		SAFE_DEL(DirectionMap);
		this->DirectionMap = NewDirectionMap;
	}	
}

void CMapObject::Win()
{
	if (status!=ESTATUS_WIN)
	{
		status = ESTATUS_WIN;
		printf("WIN\n");
		CAudioPlayer::GetInstance()->Play(WIN_WAV,false);
	}
}

void CMapObject::Lose()
{
	if (status!=ESTATUS_LOSE)
	{
		status = ESTATUS_LOSE;
		printf("LOSE\n");
		CAudioPlayer::GetInstance()->Play(LOSE_WAV,false);
	}
}

void CMapObject::Reset()
{
	memset(ObjectMap, 0, sizeof(int) * this->data->Height * this->data->Width);
	memset(DirectionMap, 0, sizeof(int) * this->data->Height * this->data->Width);
	RemainingLife = data->GivenLife;
	Money = data->GivenMoney;
	isSpawnTime = false;
	NumberOfEnemyInMap = 0;

	CalculateEnemyPath(ObjectMap, DirectionMap);
	status = ESTATUS_PLAY;

	CurrentWave = 0;
	NextSpawnTime = 0;
	EnemyIndexInWave = 0;
	for (int i=0;i<MAX_OBSTACLE_PER_MAP;i++)
	{
		if (data->ObstacleList[i])
		{
			AddObstacle(data->ObstacleList[i],ObstaclePositionList[i],ObstacleSizeList[i]);
		}
		else break;
	
	}
}