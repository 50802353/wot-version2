#include "EnemyObject.h"

CEnemyObject::CEnemyObject(SEnemyData* data, LogicPosition position)
{
	this->ObjectType = EGameObject::E_OBJ_ENEMY;
	this->data = data;
	this->position = Position(position.x+0.5,position.y+0.5,0);
}

CEnemyObject::~CEnemyObject(void)
{
}

void CEnemyObject::Init()
{
}

void CEnemyObject::Update()
{
}

void CEnemyObject::Render()
{
	CGraphics2D::GetInstance()->SetColor(SColor<float>(1,0,0,1));
	CGraphics2D::GetInstance()->FillRect(SRect<float>(position.x-0.5, position.y-0.5, 1, 1));
}

void CEnemyObject::Destroy()
{
}