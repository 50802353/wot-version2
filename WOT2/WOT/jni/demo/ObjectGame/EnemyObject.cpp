#include "EnemyObject.h"
#include "../CStateIngame.h"

//using namespace gametutor;

EnemyObject::EnemyObject(void):particle(NULL)
{
	//initial properties for enemy
	this->mProperties->mSpeed = 15;
	mProperties->mHP = 300;
	mCurHP = mProperties->mHP;
	mProperties->mCost = 100;
	mPoison = 0;
	mPoisonCD = 0;
	//--------------------------
	this->mType = OBJECT_ENEMY;
	mObject3D = new Object3D(0.5);
	//init Path
	//--for test
	
	//----------
	mPathHandle = CPathManagement::GetInstance()->addPath();
	MapPosition* curPos = CPathManagement::GetInstance()->getCurPos(mPathHandle);
	MapPosition* nextPos = CPathManagement::GetInstance()->getNextPos(mPathHandle);
	mX = curPos->mX*0.5 + 0.25;
	mY = curPos->mY*0.5 + 0.25;
	angleRotate = getAngle(curPos,nextPos);
	newAngle = angleRotate;
	isRotating = false;
	rotated = false;
	isAlive = true;
	isDying = false;
	isReturned = false;
	//spawn time
	Wave* thisWave = CStateIngame::currentfile->m_lstWave->Travel();
	spawnTime = 2.0*(mPathHandle%thisWave->amount);
	//set Position in Logic Map
	__INT32* logicMap = CObjectManagement::GetInstance()->GetMap()->mLogicMap;
	logicMap[curPos->mX + curPos->mY*CObjectManagement::GetInstance()->GetMap()->GetWidth()] = OBJECT_ENEMY;
}


EnemyObject::EnemyObject(EnemyProperties* properties):particle(NULL)
{
	//initial properties for enemy
	this->mProperties = properties;
	mCurHP = mProperties->mHP;
	mPoison = 0;
	mPoisonCD = 0;

	//--------------------------
	this->mType = OBJECT_ENEMY;
	mObject3D = new Object3D(0.5);
	//init Path
	//--for test
	
	//----------
	mPathHandle = CPathManagement::GetInstance()->addPath();
	MapPosition* curPos = CPathManagement::GetInstance()->getCurPos(mPathHandle);
	MapPosition* nextPos = CPathManagement::GetInstance()->getNextPos(mPathHandle);
	mX = curPos->mX*0.5 + 0.25;
	mY = curPos->mY*0.5 + 0.25;
	angleRotate = getAngle(curPos,nextPos);
	newAngle = angleRotate;
	isRotating = false;
	rotated = false;
	isAlive = true;
	isDying = false;
	isReturned = false;
	//spawn time

	spawnTime = 2.0*(mPathHandle%10) + 1;
	//set Position in Logic Map
	__INT32* logicMap = CObjectManagement::GetInstance()->GetMap()->mLogicMap;
	logicMap[curPos->mX + curPos->mY*CObjectManagement::GetInstance()->GetMap()->GetWidth()] = OBJECT_ENEMY;
}

EnemyObject::~EnemyObject(void)
{
	if(mObject3D !=0)
		delete mObject3D;
	mObject3D = 0;
}

void EnemyObject::SetModel(MD2Model* _model)
{
	mObject3D->SetModel(_model);
}

void EnemyObject::Update(float tpf)
{
	

	if(mCurHP > 0)
	{
		if(isAlive)
		{
			if (mPoison>0) mPoisonCD -= tpf;
			if ((mPoison>0)  && (mPoisonCD<0)) mPoison=0;
			if (mPoison>0)
			{
				float percent = float(100-mPoison)/100;
				if (percent<0.3) percent = 0.3;
				tpf = tpf*percent;
			}

			if(CPathManagement::GetInstance()->wasFinish(mPathHandle))
			{
				/*this->SetAction((char*)"stand");*/
				isAlive = false;
				CObjectManagement::GetInstance()->UpdateLives(-1);
				return;
			}
			if(spawnTime > 0.0f) spawnTime -= tpf;
			else{
				updateAnimation(tpf);
				updatePosition(tpf);
			}
		}
	}
	else 
	{
		if(isAlive)
		{
			updateAnimation(tpf);
			if(mObject3D->IsFinishAction())
			{
				CObjectManagement::GetInstance()->UpdateMoney(this->mProperties->mCost);
				isAlive = false;
			}
		}
	}
	if (particle) 
	{
		particle->Update();
		if (particle->isDied()) SAFE_DEL(particle);
	}
}

void EnemyObject::SetAction(char* actionName)
{
	this->mObject3D->SetAnimation(actionName);
}

void EnemyObject::SetAction(char* actionName, GameSound* sound)
{
	this->mObject3D->SetAnimation(actionName, sound);
}

void EnemyObject::DrawHP()
{
	if (mCurHP>0)
	{
		Matrix worldMatrix;
		worldMatrix.Translate(mX,mY,0.0f);
		Matrix HPMatrix;
		HPMatrix.Multiply(worldMatrix);
		Matrix MVP;
		MVP.Multiply(*(CCamera3D::GetInstance()->GetProjectMatrix()));
		MVP.Multiply(*(CCamera3D::GetInstance()->GetViewMatrix()));
		MVP.Multiply(worldMatrix);
		__INT32 W = VIEWCLASS::GetInstance()->GetWidth();
		__INT32 H = VIEWCLASS::GetInstance()->GetHeight();
		float x = (MVP.GetData())[12]/(MVP.GetData())[15];
		x = x/H*W;
		/*float y_tall = ((MVP.GetData())[9]*(mObject3D->GetModel()->mRange.yMax))
				/ ((MVP.GetData())[11]*(mObject3D->GetModel()->mRange.yMax));*/
		float y_tall = 0.15;
		float y = (MVP.GetData())[13]/(MVP.GetData())[15]+y_tall;
		CImage *img = CImageManager::GetInstance()->Get(PATH_GRAPHIC("HPBar.tga"));
		CGraphics2D::GetInstance()->DrawImageRegion(SRect<float>(x-0.1-0.015,y-0.005,0.203,0.03),img,SRect<float>(0.625,0,0.375,1));
		CGraphics2D::GetInstance()->DrawImageRegion(SRect<float>(x-0.1-0.01,y,0.202*float(mCurHP)/float(mProperties->mHP),0.02),img,SRect<float>(0,0,0.375,1));
		CGraphics2D::GetInstance()->Flush();
	}
}

void EnemyObject::Render()
{
	if(isAlive)
	{
		Matrix worldMatrix;
		worldMatrix.Translate(mX,mY,0.0f);
		//worldMatrix.Multiply(*this->mObject3D->GetModel()->mModelMatrix);
		worldMatrix.Rotate(angleRotate,0.0f,0.0f,1.0f);
		//worldMatrix.Rotate(0.0f,0.0f,0.0f,1.0f);
		
		mObject3D->RenderAnimation(&worldMatrix);

		Matrix m;
		m.Translate(mX,mY,0.5);
		if (particle) particle->Render(&m);

		DrawHP();
	}
}

void EnemyObject::updateAnimation(float tpf)
{
	this->mObject3D->UpdateAnimation(tpf);
}

void EnemyObject::updatePosition(float tpf)
{

	MapPosition* _cur = CPathManagement::GetInstance()->getCurPos(mPathHandle);
	MapPosition* _pre = CPathManagement::GetInstance()->getPrePos(mPathHandle);
	MapPosition* _next = CPathManagement::GetInstance()->getNextPos(mPathHandle);
	//---

	if(CPathManagement::GetInstance()->isChangeOriented(mPathHandle))
	{
		float ts = length(_cur->mX*0.5 + 0.25, _cur->mY*0.5 + 0.25, this->mX, this->mY);
		if(ts > 0.1)
		{
			if(!isReturned)
			{
				angleRotate += 180.0f;
				if(angleRotate > 360.0f) angleRotate = angleRotate - 360.0f;
				isReturned = true;
			}
			float s = tpf*2*(this->mProperties->mSpeed )/50;
			mX +=s*cos(angleRotate*3.14/180);
			mY +=s*sin(-angleRotate*3.14/180);
			return;
		}
		else
		{
			mX = _cur->mX*0.5 + 0.25;
			mY = _cur->mY*0.5 + 0.25;
			angleRotate = getAngle(_cur,_next);
			CPathManagement::GetInstance()->setNoChangeOriented(mPathHandle);
			newAngle = angleRotate;
			isReturned = false;
			isRotating = false;
			rotated = false;
			return;
		}
	}
	float ts = length(_cur->mX*0.5 + 0.25, _cur->mY*0.5 + 0.25, this->mX, this->mY);
	if(!isStraight(_pre,_cur,_next) && !rotated && (abs(_cur->mX*0.5 + 0.25 - this->mX) < 0.05f) && (abs(_cur->mY*0.5 + 0.25 - this->mY) < 0.05f))
	{
		if(!isRotating)
		{
			//count newAngle
			newAngle = getAngle(_cur,_next);
			isRotating = true;
		}
		if(angleRotate != newAngle)
		{
			float stepAngle = 5.0f;
			if(angleRotate == 0.0f && newAngle > 180.0f) angleRotate = 360.0f;
			if(newAngle == 0.0f && angleRotate > 180.0f) newAngle = 360.0f;
			if(newAngle > angleRotate) angleRotate += stepAngle;
			else angleRotate -= stepAngle;
		}
		else
		{
			rotated = true;
			isRotating = false;
		}
	}
	else if(!isStraight(_pre,_cur,_next) && rotated)
	{
		//float s = tpf*this->mProperties->mSpeed/50;
		float s = tpf*2*(this->mProperties->mSpeed )/50;
		mX +=s*cos(angleRotate*3.14/180);
		mY +=s*sin(-angleRotate*3.14/180);
		//check cur position
		float ts = length(mX,mY,_cur->mX*0.5+0.25,_cur->mY*0.5+0.25);
		float as = length(_cur->mX,_cur->mY,_next->mX,_next->mY)/2;
		if(ts > as)
		{
			CPathManagement::GetInstance()->next(mPathHandle);
			rotated = false;
		}
	}
	else
	{
		//float s = tpf*this->mProperties->mSpeed/50;
		float s = tpf*2*(this->mProperties->mSpeed )/50;
		mX +=s*cos(angleRotate*3.14/180);
		mY +=s*sin(-angleRotate*3.14/180);
		//check cur position
		float ts = length(mX,mY,_cur->mX*0.5+0.25,_cur->mY*0.5+0.25);
		float as = length(_cur->mX,_cur->mY,_next->mX,_next->mY)/2;
		if(ts > as)
			CPathManagement::GetInstance()->next(mPathHandle);
	}
} 

bool EnemyObject::isStraight(MapPosition* _pre, MapPosition* _cur, MapPosition* _next)
{
	if(!_pre || !_cur || !_next) return true;
	else
	{
		int aX = _cur->mX - _pre->mX;
		int aY = _cur->mY - _pre->mY;

		int bX = _next->mX - _cur->mX;
		int bY = _next->mY - _cur->mY;

		if(aX*bY - aY*bX == 0 && aX*bX > 0) return true;
		else return false;
	}

	/*if(!p1 || !p2 || !p3) return true;
	if(p1->mX == p2->mX && p2->mX == p3->mX) return true;
	else if(p1->mY == p2->mY && p2->mY == p3->mY) return true;
	else if(p1->mX != p2->mX && p2->mX != p3->mX && p3->mX != p1->mX
		&& p1->mY != p2->mY && p2->mY != p3->mY && p3->mY != p1->mY) return true;
	return false;*/
}


float EnemyObject::getAngle(MapPosition* p1, MapPosition* p2)
{
	if(p1->mX == p2->mX && p1->mY == p2->mY) return 0.0f;

	//else if(p1->mX == p2->mX && p1->mY > p2->mY) return 90.0f;
	//else if(p1->mX == p2->mX && p1->mY < p2->mY) return 270.0f;

	//else if(p1->mX > p2->mX && p1->mY == p2->mY) return 0.0f;
	//else if(p1->mX < p2->mX && p1->mY == p2->mY) return 180.0f;

	//else if(p1->mX > p2->mX && p1->mY > p2->mY) return 45.0f;
	//else if(p1->mX > p2->mX && p1->mY < p2->mY) return 315.0f;

	//else if(p1->mX < p2->mX && p1->mY > p2->mY) return 135.0f;
	//else if(p1->mX < p2->mX && p1->mY < p2->mY) return 225.0f;
	else if(p1->mX == p2->mX && p1->mY > p2->mY) return 90.0f;
	else if(p1->mX == p2->mX && p1->mY < p2->mY) return 270.0f;

	else if(p1->mX > p2->mX && p1->mY == p2->mY) return 180.0f;
	else if(p1->mX < p2->mX && p1->mY == p2->mY) return 0.0f;

	else if(p1->mX > p2->mX && p1->mY > p2->mY) return 135.0f;
	else if(p1->mX > p2->mX && p1->mY < p2->mY) return 255.0f;

	else if(p1->mX < p2->mX && p1->mY > p2->mY) return 45.0f;
	else if(p1->mX < p2->mX && p1->mY < p2->mY) return 315.0f;
}

MapPosition* EnemyObject::GetCurPos()
{
	 return CPathManagement::GetInstance()->getCurPos(mPathHandle);
}

void EnemyObject::GetPos(float &x,float &y)
{
	x = mX;
	y = mY;
}
