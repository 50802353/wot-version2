#pragma once

#include "GameObject.h"
#include "gametutor.h"
#include "MapObject.h"
#include "CObject3D.h"
#include "EnemyObject.h"

using namespace GameTutor;

class BulletObject:
	public GameObject
{
public:
	BulletObject(__INT32 Poison);
	~BulletObject(void);
private:
	EnemyObject* mTarget;
	Object3D* mObject3D;
	__INT32 mDamage;
	__INT32 mCrit;
	float mCurX;
	float mCurY;
	float mAngle;
	float mAngleX;
	__INT32 mSpeed;
	bool isFinished;
	bool isFiring;
	__INT32 isPoison;
	__INT32 skipForUpdate;
public:
	bool killed;
	//The bullet will follow the target position
	void setTarget(EnemyObject* _target, float _startX, float _startY, float _speed, float _damage, float _crit);
	void Fire();
	bool IsFinished();

	//-----render-------
	void SetModel(MD2Model* _model);
	void Update(float tpf);
	
	void SetAction(char* actionName);
	void SetAction(char* actionName, GameSound* sound);


	/*void setWorldMatrix(Matrix* _worldMatrix);*/
	void Render();
private:
	void updatePositon(float tpf);
	void updateAnimation(float tpf);
	float getAngle(float _p1X, float _p1Y, float _p2X, float _p2Y);
};

