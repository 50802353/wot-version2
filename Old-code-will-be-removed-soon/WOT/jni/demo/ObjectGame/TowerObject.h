#pragma once
#include "GameObject.h"
#include "gametutor.h"
#include "CObject3D.h"
#include "BulletObject.h"

using namespace GameTutor;

class TowerObject :
	public GameObject
{
public:
	TowerObject();
	TowerObject(TowerProperties *properties);
	~TowerObject();
private:
	Object3D* mObject3D;
	float mPositionX;
	float mPositionY;
	bool OutRange(EnemyObject* _enemy);
	float timeForFire;
	bool isFiring;

public:
	__INT32 curSpeedAttack;
	__INT32 curDamage;
	__INT32 curCritical;
	TowerProperties *mProperties;
	MapPosition mPosition;
	Matrix* mWorldMatrix;
	EnemyObject* mTarget;

	//-----render-------
	float getPositionX();
	float getPositionY();
	void SetPosition(__INT32 x, __INT32 y);
	void SetPosition(__INT32 position);
	void SetObject3D(Object3D* _object3D);
	void SetModel(MD2Model* _model);
	void Update(float tpf);
	void SetAction(char* actionName, float time=0);
	void SetAction(char* actionName, GameSound* sound, float time=0);
	void Render();
};
