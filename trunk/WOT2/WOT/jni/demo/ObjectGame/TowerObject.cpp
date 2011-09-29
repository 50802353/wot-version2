#include "TowerObject.h"
#include "CModelManager.h"
#include "../CObjectManagement.h"


//using namespace gametutor;

TowerObject::TowerObject(void){
	this->mType = OBJECT_TOWER;
	mWorldMatrix = new Matrix();
	mObject3D = new Object3D(1.0f);
	//default tower
	mProperties->mBaseDamage = 10;
	mProperties->mCritical = 1;
	mProperties->mRange = 2;
	mProperties->mSpeedAttack = 2;
	mProperties->mValue = 10;
	mTarget = 0;
	isFiring = false;
	timeForFire = 0;
	//
	curSpeedAttack = mProperties->mSpeedAttack;
	curDamage = mProperties->mBaseDamage;
	curCritical = mProperties->mCritical;
}

TowerObject::TowerObject(TowerProperties *properties){
	this->mType = OBJECT_TOWER;
	mWorldMatrix = new Matrix();
	mObject3D = new Object3D(1.0f);
	//default tower
	mProperties = properties;
	mTarget = 0;
	isFiring = false;
	timeForFire = 0;

	//
	curSpeedAttack = mProperties->mSpeedAttack;
	curDamage = mProperties->mBaseDamage;
	curCritical = mProperties->mCritical;
}

float TowerObject::getPositionX()
{
	return mPositionX;
}

float TowerObject::getPositionY()
{
	return mPositionY;
}

TowerObject::~TowerObject()
{
	if(mObject3D != 0) delete mObject3D;
	mObject3D = 0;
	if(mWorldMatrix) delete mWorldMatrix;
	mWorldMatrix = 0;
}

void TowerObject::SetPosition(__INT32 x, __INT32 y)
{
	this->mPosition.mX = x;
	this->mPosition.mY = y;

	//float translateX = (x)*0.5 + 0.25;
	//float translateY = (y)*0.5 + 0.25;
	mPositionX = (x+1)*0.5;
	mPositionY = (y+1)*0.5;

	//temp.Translate(translateX,translateY,0.0f);
	//temp.Multiply(*mWorldMatrix);
	//mWorldMatrix->Translate(translateX,translateY,0.0f);
	mWorldMatrix->LoadIdentity();
	mWorldMatrix->Translate(mPositionX,mPositionY,0.0f);

	//set Logic Map
	__INT32* LogicMap = CObjectManagement::GetInstance()->GetMap()->mLogicMap;
	__INT32 position = x + y*CObjectManagement::GetInstance()->GetMap()->GetWidth();

	LogicMap[(position)] = OBJECT_TOWER;
	LogicMap[position+1] = OBJECT_TOWER;
	LogicMap[position+CObjectManagement::GetInstance()->GetMap()->GetWidth()] = OBJECT_TOWER;
	LogicMap[position+CObjectManagement::GetInstance()->GetMap()->GetWidth()+1] = OBJECT_TOWER;
}

void TowerObject::SetPosition(__INT32 position)
{
	__INT32 selectY = position / CObjectManagement::GetInstance()->GetMap()->GetWidth();
	__INT32 selectX = position - CObjectManagement::GetInstance()->GetMap()->GetWidth() * selectY;

	this->mPosition.mX = selectX;
	this->mPosition.mY = selectY;

	mPositionX = (selectX+1)*0.5;
	mPositionY = (selectY+1)*0.5;
	mWorldMatrix->LoadIdentity();
	mWorldMatrix->Translate(mPositionX,mPositionY,0.0f);

	__INT32* LogicMap = CObjectManagement::GetInstance()->GetMap()->mLogicMap;
	LogicMap[(position)] = OBJECT_TOWER;
	LogicMap[position+1] = OBJECT_TOWER;
	LogicMap[position+CObjectManagement::GetInstance()->GetMap()->GetWidth()] = OBJECT_TOWER;
	LogicMap[position+CObjectManagement::GetInstance()->GetMap()->GetWidth()+1] = OBJECT_TOWER;
}

void TowerObject::SetModel(MD2Model* _model)
{
	mObject3D->SetModel(_model);
	SetAction((char*)"stand");
}

bool TowerObject::OutRange(EnemyObject* _enemy)
{
	float x,y;
	_enemy->GetPos(x,y);

	float s = length(x,y,this->mPositionX,this->mPositionY);
	return (s>this->mProperties->mRange);
}

void TowerObject::Update(float tpf)
{
	if(timeForFire <= 0.0f)
	{
		//select target from enemy alive
		if(!mTarget || mTarget->isDying || !mTarget->isAlive || OutRange(mTarget))
			mTarget = CObjectManagement::GetInstance()->getTarget(&mPosition,mProperties->mRange);
		if(mTarget)
		{
			SetAction((char*)"jump", 1.0/float(this->mProperties->mSpeedAttack));
			isFiring = true;
			BulletObject* mBullet;
			switch (this->mProperties->mSkillID)
			{
			case 0:
				mBullet = new BulletObject(0);
				mBullet->SetModel(CModelManager::GetInstance()->Get(0));
				CObjectManagement::GetInstance()->AddElement(mBullet);			
				mBullet->setTarget(mTarget,mPositionX,mPositionY,3,this->curDamage,this->curCritical);
				mBullet->Fire();
				break;
			case 1:
				mBullet = new BulletObject(mProperties->mPoison);
				mBullet->SetModel(CModelManager::GetInstance()->Get(0));
				CObjectManagement::GetInstance()->AddElement(mBullet);			
				mBullet->setTarget(mTarget,mPositionX,mPositionY,3,curDamage,this->curCritical);
				mBullet->Fire();
				break;
			default:
				break;
			}				
			
		}
		else if (isFiring)
		{
			SetAction((char*)"stand");
			isFiring = false;
		}
		timeForFire = (float) 1/mProperties->mSpeedAttack;
	}
	else 
	{
		timeForFire -= tpf;
		
	}
	this->mObject3D->UpdateAnimation(tpf);
}

void TowerObject::SetAction(char* actionName,float time)
{
	this->mObject3D->SetAnimation(actionName,time);
}

void TowerObject::SetAction(char* actionName, GameSound* sound,float time)
{
	this->mObject3D->SetAnimation(actionName, sound);
}

void TowerObject::Render()
{
	//mAnimation.RenderAnimation();
	mObject3D->RenderAnimation(mWorldMatrix);
}

