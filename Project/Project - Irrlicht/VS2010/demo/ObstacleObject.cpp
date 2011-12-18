#include "ObstacleObject.h"

CObstacleObject::CObstacleObject(SObstacleData *data, int size)
{
	this->ObjectType = EGameObject::E_OBJ_OBSTACLE;
	this->data = data;
	this->position = Position(0,0,0);
	this->logicposition = LogicPosition(0,0);
	this->size = size;
	Init();
}

CObstacleObject::~CObstacleObject(void)
{
	Destroy();
}

void CObstacleObject::Init()
{
	sceneNode = smgr->addCubeSceneNode(float(size));	
	sceneNode->setScale(irr::core::vector3df(1,1.0/size,1));
	sceneNode->setMaterialTexture(0, driver->getTexture("./resource/sample_obstacle.bmp"));
	sceneNode->setPosition(irr::core::vector3df(position.x, position.z, position.y));
}

void CObstacleObject::Update(int delta_time)
{
}

void CObstacleObject::Render()
{
	/*CGraphics2D::GetInstance()->SetColor(SColor<float>(1,1,0,1));
	CGraphics2D::GetInstance()->FillRect(SRect<float>(position.x-0.5, position.y-0.5, 1, 1));
	CGraphics2D::GetInstance()->Flush();*/

	float vertex[] = {	position.x-0.4, position.y-0.4, 0,
						position.x-0.4, position.y+0.4, 0,
						position.x+0.4, position.y-0.4, 0,
						position.x-0.4, position.y+0.4, 0,
						position.x+0.4, position.y-0.4, 0,
						position.x+0.4, position.y+0.4, 0};

	float color[] = {	1,1,0,1,
						1,1,0,1,
						1,1,0,1,
						1,1,0,1,
						1,1,0,1,
						1,1,0,1};

	//CGraphics3D::GetInstance()->DrawModel(6, vertex, NULL, color, NULL, NULL);
}

void CObstacleObject::Destroy()
{
	if (sceneNode)
	{
		sceneNode->remove();
		sceneNode = 0;
	}
}