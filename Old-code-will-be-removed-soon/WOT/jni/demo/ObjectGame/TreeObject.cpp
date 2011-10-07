#include "TreeObject.h"
#include "../CObjectManagement.h"

//using namespace gametutor;

TreeObject::TreeObject()
{
	this->mType = OBJECT_TREE;
	mWorldMatrix = new Matrix();
	mObject3D = new Object3D(0.5);
}

TreeObject::~TreeObject()
{
	if (mObject3D != 0)
		delete mObject3D;
	mObject3D = 0;
	if (mWorldMatrix != 0)
		delete mWorldMatrix;
	mWorldMatrix = 0;
}

void TreeObject::SetPosition(__INT32 x, __INT32 y)
{
	this->mPosition.mX = x;
	this->mPosition.mY = y;

	float translateX = x*0.5 + 0.25;
	float translateY = y*0.5 + 0.25;

	mWorldMatrix->LoadIdentity();
	mWorldMatrix->Translate(translateX,translateY,0.0f);
	
	//update map Logic
	__INT32* LogicMap = CObjectManagement::GetInstance()->GetMap()->mLogicMap;
	__INT32 position = x + y*CObjectManagement::GetInstance()->GetMap()->GetWidth();
	LogicMap[position] = OBJECT_TREE;
}

void TreeObject::Render()
{
	//Matrix matrix;
	//matrix.Multiply(*mWorldMatrix);
	//matrix.Rotate(0.0f,0.0f,0.0f,1.0f);
	mObject3D->RenderAnimation(mWorldMatrix);
}

void TreeObject::SetModel(MD2Model* _model)
{
	mObject3D->SetModel(_model);
	////this->mWorldMatrix = _model->mModelMatrix;
	//Matrix temp;
	//temp.Multiply(*this->mWorldMatrix);
	//temp.Multiply(*_model->mModelMatrix);
	//mWorldMatrix->LoadIdentity();
	//mWorldMatrix->Multiply(temp);
	//this->mWorldMatrix->Multiply(*_model->mModelMatrix);
	SetAction((char*)"stand");
}

void TreeObject::Update(float tpf)
{
	this->mObject3D->UpdateAnimation(tpf);
}

void TreeObject::SetAction(char* actionName)
{	
	this->mObject3D->SetAnimation(actionName);
}

void TreeObject::SetAction(char* actionName, GameSound* sound)
{
	this->mObject3D->SetAnimation(actionName, sound);
}