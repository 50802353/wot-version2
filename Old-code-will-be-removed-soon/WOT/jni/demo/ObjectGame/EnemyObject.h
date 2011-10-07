#pragma once
#include "GameObject.h"
#include "gametutor.h"
#include "MapObject.h"
#include "CObject3D.h"
#include "CPathManagement.h"
#include "../GameProperties.h"


using namespace GameTutor;

class EnemyObject :
	public GameObject
{
public:
	EnemyObject(void);
	EnemyObject(EnemyProperties*);
	~EnemyObject(void);
private:
	//graphic
	Object3D* mObject3D;
public:
	//logic
	EnemyProperties *mProperties;
	__INT32 mCurHP;
	__INT32 mPoison;
	float mPoisonCD;
	//position
	float mX;
	float mY;
	float angleRotate;
	float newAngle;
	bool isRotating;
	bool rotated;
	bool isAlive;
	bool isDying;
	bool isReturned;

	MyParticleSystem *particle;

	//spawn Time
	float spawnTime;


	__INT32 mPathHandle; //use to get Path

	//for model
	void SetModel(MD2Model* _model);
	void Update(float tpf);
	void SetAction(char* actionName);
	void SetAction(char* actionName, GameSound* sound);
	void Render();
	void DrawHP();
	MapPosition* GetCurPos();
	void GetPos(float &x,float &y);
private:
	void updateAnimation(float tpf);
	void updatePosition(float tpf);
	bool isStraight(MapPosition* p1, MapPosition* p2, MapPosition* p3);
	float getAngle(MapPosition* p1, MapPosition* p2);
};
