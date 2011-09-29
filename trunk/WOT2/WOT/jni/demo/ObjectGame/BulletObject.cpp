#include "BulletObject.h"
#include "EnemyObject.h"
#include "../CObjectManagement.h"
#include "../CStateIngame.h"


//using namespace gametutor;

BulletObject::BulletObject(__INT32 Poison)
{
	this->mType = OBJECT_BULLET;
	mObject3D = new Object3D(1.0f);
	isFinished = true;
	isFiring = false;
	killed = false;
	mAngle = 180.0f;
	mAngleX = 0.0f;
	isPoison = Poison;
}

BulletObject::~BulletObject()
{
	if(mObject3D != 0) delete mObject3D;
	mObject3D = 0;
}

void BulletObject::setTarget(EnemyObject* _target, float _startX, float _startY, float _speed, float _damage, float _crit)
{
	if(isFinished)
	{
		killed = false;
		mDamage = _damage;
		mCrit = _crit;
		mTarget = 0;
		mSpeed = _speed;
		mCurX = _startX;
		mCurY = _startY;
		mTarget = _target;
		isFinished = false;
		skipForUpdate = 3;
	}
}

bool BulletObject::IsFinished()
{
	return isFinished;
}

void BulletObject::Fire()
{
	isFiring = true;
}

void BulletObject::Render()
{
	if(!isFinished && mTarget)
	{
		Matrix worldMatrix;

		//worldMatrix.Rotate(mAngleX,1.0f,0.0f,0.0f);
		worldMatrix.Translate(mCurX,mCurY,0.0f);
		
		worldMatrix.Rotate(mAngle,0.0f,0.0f,1.0f);
		//mObject3D->RenderAnimation(&worldMatrix);
	}
	else
	{
		//add particle
	}
}

void BulletObject::SetModel(MD2Model* _model)
{
	mObject3D->SetModel(_model);
	//SetAction("");
}

void BulletObject::Update(float tpf)
{
	if(isFiring && mTarget)
	{
		this->updateAnimation(tpf);
		this->updatePositon(tpf);
	}

	if (!IsFinished())
	{

		Matrix worldMatrix;
		worldMatrix.Translate(mCurX,mCurY,1.0f);
		worldMatrix.Rotate(mAngle,0.0f,0.0f,1.0f);

		MyParticleSystem* particle = new MyParticleSystem(worldMatrix);
		if (isPoison>0)
			particle->SetMode(6);
		else
			particle->SetMode(8);
		particle->SetSize(0.05);
		particle->Initial(20);
		particle->SetTimeOut(6);
		particle->SetPosition(0,0,0);

		GameTutor::CParticleManager::GetInstance()->AddParticle(0,particle);
	}

}

void BulletObject::SetAction(char* actionName)
{	
	this->mObject3D->SetAnimation(actionName);
}

void BulletObject::SetAction(char* actionName, GameSound* sound)
{
	this->mObject3D->SetAnimation(actionName, sound);
}

void BulletObject::updateAnimation(float tpf)
{
	this->mObject3D->UpdateAnimation(tpf);
}

void BulletObject::updatePositon(float tpf) {
	//angle for rotate about 0X
	mAngleX += 10.0f;
	if(mAngleX >= 360.0f) mAngleX = mAngleX - 360.0f;

	float targetX, targetY;
	mTarget->GetPos(targetX, targetY);

	//posX, posY: vi tri dang dung, targetX, targetY: vi tri can reach
	float s = length(mCurX, mCurY, targetX, targetY);
	float T = s/this->mSpeed;
	float alpha = tpf/T;
	//float alpha = 0.25/T;
	if (skipForUpdate > 0)
	{
		mCurX = (1-alpha)*mCurX + alpha*targetX;
		mCurY = (1-alpha)*mCurY + alpha*targetY;
	} else skipForUpdate--;

	mAngle = getAngle(mCurX, mCurY, targetX, targetY);
	if(s<=0.25) 
	{
		isFinished = true;
		isFiring = false;
		//tru damage
		__INT32 damage = CStateIngame::Damage(mDamage, mTarget->mProperties->mArmor, mCrit);
		mTarget->mCurHP -= damage;

		if (mTarget->particle==NULL)
		{
			Matrix mworld;
			float targetx,targety;
			mTarget->GetPos(targetx, targety);
			mworld.Translate(targetx, targety, 0);

			if (!mTarget->particle)
			{
				mTarget->particle = new MyParticleSystem(mworld);
				if (isPoison)
				{
					mTarget->particle->SetMode(6);
					mTarget->particle->Initial(100);
				}
				else
				{
					mTarget->particle->SetMode(5);
					mTarget->particle->Initial(20);
				}
				mTarget->particle->SetSize(0.1);
				mTarget->particle->SetTimeOut(10);
				mTarget->particle->SetPosition(0,0,0);
			}
			if (isPoison)
			{
				if (mTarget->mPoison==0) mTarget->mPoison=isPoison;
				else mTarget->mPoison+=1;
				mTarget->mPoisonCD = 3.0;
			}

		}

		if(mTarget->mCurHP <= 0)
		{
			killed = true;
			mTarget->SetAction((char*)"death1");
			mTarget->isDying = true;
			//remove position in Map Logic
			MapPosition* oldPosition = mTarget->GetCurPos();
			__INT32* logicMap = CObjectManagement::GetInstance()->GetMap()->mLogicMap;
			logicMap[oldPosition->mX + oldPosition->mY*CObjectManagement::GetInstance()->GetMap()->GetWidth()] = OBJECT_NONE;
			
			mTarget = 0;
		}
	}
}

float BulletObject::getAngle(float _p1X, float _p1Y, float _p2X, float _p2Y)
{
	float deltaX = _p2X - _p1X;
	float deltaY = _p2Y - _p1Y;

	float result = atan(deltaY/deltaX)*180.0f/3.14;
	if(result > 0)
	{
		if(deltaX > 0) result = 180.0f - result;
		else result = 360.0f - result;
	}
	else if(result < 0)
	{
		if(deltaX > 0) result = 180.0f - result;
		else result = -result;
	}
	else result = 180.0f;
	return result;
}