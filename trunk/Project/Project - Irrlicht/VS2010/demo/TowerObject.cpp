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
	this->fade_in_time = 0;
	this->Map = CObjectManager::CurrentObjectManager->Map;
	this->particleSystem = 0;
	Init();
}

CTowerObject::~CTowerObject(void)
{
	Destroy();
}

void CTowerObject::Init()
{
	sceneNode = smgr->addAnimatedMeshSceneNode(smgr->getMesh(data->ModelData.modelname),0, 2);//smgr->addSphereSceneNode(0.8,16,0,2);
	sceneNode->setMaterialTexture(0, driver->getTexture(data->ModelData.skinname));
	sceneNode->setMD2Animation(scene::EMAT_STAND);
	sceneNode->setAnimationSpeed(20.f);
	sceneNode->setScale(data->ModelData.scale);
	sceneNode->setRotation(data->ModelData.rotate);
	sceneNode->getMaterial(0).Lighting = true;
	sceneNode->getMaterial(0).NormalizeNormals = true;
	sceneNode->getMaterial(0).AmbientColor = video::SColor(255,125,125,125);
	sceneNode->setPosition(irr::core::vector3df(position.x, position.z, position.y));
	/*irr::scene::ITriangleSelector* selector = smgr->createTriangleSelector(sceneNode);
	sceneNode->setTriangleSelector(selector);
	selector->drop();*/
	sceneNode->setMaterialType(video::EMT_SOLID); 
	fade_in_time = 1000;
	status=0;

	CAudioPlayer::GetInstance()->Load<CFileWin32Driver>("./resource/AMagic.wav");
	CAudioPlayer::GetInstance()->Load<CFileWin32Driver>("./resource/AUpgrade.wav");
	CAudioPlayer::GetInstance()->Play("./resource/AMagic.wav",false);
	CAudioPlayer::GetInstance()->Load<CFileWin32Driver>("./resource/ASplash.wav");
}

void CTowerObject::Update(int delta_time)
{
	if (fade_in_time>0)
	{
		fade_in_time -= delta_time;
		if (fade_in_time<0) fade_in_time=0;
		/*int alpha = (int)((float)(1000-fade_in_time)/1000.f*255);
		smgr->getMeshManipulator()->setVertexColorAlpha(sceneNode->getMesh(), alpha);*/
	}
	else //if (!sceneNode->isVisible())
	{
		//sceneNode->setVisible(true);
		//smgr->getMeshManipulator()->setVertexColorAlpha(sceneNode->getMesh(), 255);
		//sceneNode->setMaterialType(video::EMT_SOLID); 
		scene::IParticleEmitter* em = particleSystem->getEmitter();
		em->setMinParticlesPerSecond(0);
		em->setMaxParticlesPerSecond(0);
		//sceneNode->setMaterialFlag(video::EMF_WIREFRAME, false); 
	}

	if ((!target) || (!target->isInMap) || ((target->position | this->position) > this->range))
		FindTarget();

	if (target)
	{
		/*if (status==0)
		{
			status=1;
			sceneNode->setMD2Animation(scene::EMD2_ANIMATION_TYPE::EMAT_JUMP);
		}*/
		if (time_to_shoot<=0)
		{
				time_to_shoot += this->data->AttackSpeed;
				Shoot(target);
				sceneNode->setMD2Animation(scene::EMAT_JUMP);
				sceneNode->setLoopMode(false);
				status=1;
		}
		else
		{
			time_to_shoot -= delta_time;	
		}

		float degree = atan2(target->position.y-this->position.y,target->position.x-this->position.x)/3.1416*180;//-atan((float)(target->position.y-this->position.y)/(target->position.x-this->position.x))/3.1416*180;
		sceneNode->setRotation(core::vector3df(0,-degree,0));
	}
	else
	{
		//status=0;
		if (status!=0)
		{
			status=0;
			sceneNode->setMD2Animation(scene::EMAT_STAND);
			sceneNode->setLoopMode(true);
		}
	}
}

void CTowerObject::Render()
{
	/*if (fade_in_time>0 && !sceneNode->isVisible())
	{
		smgr->getMeshManipulator()->setVertexColors( sceneNode->getMesh(), video::SColor( (int)((float)(1000-fade_in_time)/1000.f*255), 255, 255, 255 ) ); 
		//sceneNode->setVisible(true);
		driver->setTransform(irr::video::ETS_WORLD,sceneNode->getAbsoluteTransformation());
		sceneNode->render();
		//sceneNode->setVisible(false);
		smgr->getMeshManipulator()->setVertexColors( sceneNode->getMesh(), video::SColor( 255, 255, 255, 255 ) ); 
	}*/
	
	//sceneNode->render();
	//sceneNode->setVisible(true);
}

void CTowerObject::Destroy()
{
	if (sceneNode) 
	{
		sceneNode->remove();
		sceneNode = 0;
	}
	if (particleSystem) 
	{
		particleSystem->remove();
		particleSystem = 0;
	}
	
	//CObjectManager::CurrentObjectManager->RemoveObject(this);
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
	CAudioPlayer::GetInstance()->Play("./resource/ASplash.wav",false);
}

void CTowerObject::Upgrade(STowerData *data)
{
	this->data = data;
	this->time_to_shoot = 0;
	CObjectManager::CurrentObjectManager->Map->Money -= this->data->Cost;
	sceneNode->remove();

	sceneNode = smgr->addAnimatedMeshSceneNode(smgr->getMesh(data->ModelData.modelname),0, 2);//smgr->addSphereSceneNode(0.8,16,0,2);
	sceneNode->setMaterialTexture(0, driver->getTexture(data->ModelData.skinname));
	sceneNode->setMD2Animation(scene::EMAT_STAND);
	sceneNode->setAnimationSpeed(20.f);
	sceneNode->setScale(irr::core::vector3df(0.05,0.05,0.05));
	sceneNode->getMaterial(0).Lighting = true;
	sceneNode->getMaterial(0).NormalizeNormals = true;
	sceneNode->setPosition(irr::core::vector3df(position.x, position.z, position.y));
	irr::scene::ITriangleSelector* selector = smgr->createTriangleSelector(sceneNode);
	sceneNode->setTriangleSelector(selector);
	selector->drop();
	sceneNode->setMaterialType(video::EMT_SOLID); 
	fade_in_time = 1000;
	//status=0;

	scene::IParticleEmitter* em = particleSystem->getEmitter();
	em->setMinParticlesPerSecond(8);
	em->setMaxParticlesPerSecond(10);

	CAudioPlayer::GetInstance()->Play("./resource/AUpgrade.wav",false);
}

void CTowerObject::Sell()
{
	CObjectManager::CurrentObjectManager->Map->Money += int(this->data->Cost * SELL_PERCENT);
	CObjectManager::CurrentObjectManager->RemoveObject(this);
	delete this;
}


