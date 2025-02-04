#include "ObstacleObject.h"

CObstacleObject::CObstacleObject(SObstacleData *data, LogicPosition position)
{
	this->ObjectType = EGameObject::E_OBJ_OBSTACLE;
	this->data = data;
	this->position = Position(position.x+0.5,position.y+0.5,0);
	this->logicposition = position;
}

CObstacleObject::~CObstacleObject(void)
{
}

void CObstacleObject::Init()
{
}

void CObstacleObject::Update(int delta_time)
{
}

void CObstacleObject::Render()
{
	CGraphics2D::GetInstance()->SetColor(SColor<float>(1,1,0,1));
	CGraphics2D::GetInstance()->FillRect(SRect<float>(position.x-0.5, position.y-0.5, 1, 1));
	CGraphics2D::GetInstance()->Flush();
}

void CObstacleObject::Destroy()
{
}