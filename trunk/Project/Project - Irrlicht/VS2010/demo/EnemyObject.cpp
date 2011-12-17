#include "EnemyObject.h"
#include "ObjectManager.h"
#include <math.h>

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
	sceneNode = smgr->addAnimatedMeshSceneNode(smgr->getMesh(data->ModelData.modelname),0, 2);//smgr->addSphereSceneNode(0.8,16,0,2);
	sceneNode->setMaterialTexture(0, driver->getTexture(data->ModelData.skinname));
	sceneNode->setMD2Animation(scene::EMAT_RUN);
	sceneNode->setAnimationSpeed(20.f);
	sceneNode->setScale(data->ModelData.scale);
	sceneNode->setRotation(data->ModelData.rotate);
	sceneNode->getMaterial(0).Lighting = true;
	sceneNode->getMaterial(0).NormalizeNormals = true;
	sceneNode->setPosition(irr::core::vector3df(position.x, position.z, position.y));

	healthBar = smgr->addBillboardSceneNode(sceneNode,core::dimension2df(1,0.1),core::vector3df(0.0,30.0,0.0));
	healthBar->setMaterialTexture(0,driver->getTexture("./resource/HP.bmp"));
	healthBar->setMaterialFlag(video::EMF_LIGHTING,false);
	healthBar->setMaterialFlag(video::EMF_ZBUFFER,false);
	healthBar->setMaterialType(video::EMT_TRANSPARENT_VERTEX_ALPHA);
	healthBar->setColor(video::SColor(10,255,255,255),video::SColor(10,255,255,255));
	CAudioPlayer::GetInstance()->Load<CFileWin32Driver>("./resource/ACreepDeath.wav");
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
	//if (sceneNode->is) sceneNode->remove();
}

void CEnemyObject::Move(int delta_time)
{
	float dmove = this->data->MoveSpeed * (float)delta_time / 10000;
	while (dmove>0)
	{
		LogicPosition CurLogicPos((int)this->position.x,(int)this->position.y);
		LogicPosition NextLogicPos = CurLogicPos + ::Move[(Map->DirectionMap[(int)this->position.y * Map->data->Width + (int)this->position.x])];	
		if (Map->ObjectMap[(int)(NextPos.y-0.5)*Map->data->Width+(int)(NextPos.x-0.5)]!=E_OBJ_NONE)
		{
			NextPos.x = NextLogicPos.x + 0.5;
			NextPos.y = NextLogicPos.y + 0.5;
		}

		float distance = NextPos | this->position;
		if (dmove>distance)
		{			
			if (CurLogicPos == Map->data->DestinationPosition)
			{
				ReachDestination();
				return;
			}				

			this->position = NextPos;
			NextPos.x = NextLogicPos.x + 0.5;
			NextPos.y = NextLogicPos.y + 0.5;
			dmove -= distance;
		}
		else
		{
			this->position = this->position + ((NextPos - this->position) * (dmove/distance));
			sceneNode->setPosition(irr::core::vector3df(position.x, position.z, position.y));


			float degree = atan2(NextPos.y-this->position.y,NextPos.x-this->position.x)/3.1416*180;//-atan((float)(target->position.y-this->position.y)/(target->position.x-this->position.x))/3.1416*180;
			sceneNode->setRotation(core::vector3df(0,-degree,0));
			dmove = 0;
		}
	}
}

void CEnemyObject::ReachDestination()
{
	if (!isInMap) return;
	Map->RemainingLife--;
	isInMap = false;
	//sceneNode->setVisible(isInMap);
	sceneNode->remove();
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
		//sceneNode->setVisible(isInMap);
		sceneNode->setMD2Animation(scene::EMD2_ANIMATION_TYPE::EMAT_DEATH_FALLBACK);
		sceneNode->setLoopMode(false);
		sceneNode->addAnimator(smgr->createDeleteAnimator(1000));
		Map->Money+=this->data->Bounty;
		CObjectManager::CurrentObjectManager->Map->NumberOfEnemyInMap--;

		CAudioPlayer::GetInstance()->Play("./resource/ACreepDeath.wav",false);
	}
}

void CEnemyObject::Damaged(int HP)
{
	if (!isInMap) return;
	int damage = HP; //sau nay thay the' bang cong thuc' phuc' tap. hon voi' anh huong cua giap, thuoc tinh' ....
	if (currentHP>damage)
	{
		currentHP-=damage;
		healthBar->setSize(core::dimension2df((float)this->currentHP/data->MaxHP,0.1));
	}
	else 
	{
		currentHP=0;
		healthBar->setSize(core::dimension2df(0.0001,0.1));
		Die();
	}
}