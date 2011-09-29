#pragma once
#include "GameObject.h"
#include "gametutor.h"
#include "MapObject.h"
#include "CObject3D.h"


using namespace GameTutor;

class TreeObject :
	public GameObject
{
public:
	TreeObject(void);
	~TreeObject(void);
private:
	/*Matrix* mWorldMatrix;*/
	Object3D* mObject3D;
public:
	//---Position-----------
	MapPosition mPosition;
	Matrix* mWorldMatrix;
	//-----render-------
	void SetPosition(__INT32 x, __INT32 y);
	void SetModel(MD2Model* _model);
	void Update(float tpf);
	void SetAction(char* actionName);
	void SetAction(char* actionName, GameSound* sound);

	/*void setWorldMatrix(Matrix* _worldMatrix);*/
	void Render();
};
