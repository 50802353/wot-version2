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
	/*sceneNode = smgr->addCubeSceneNode(float(size));	
	sceneNode->setScale(irr::core::vector3df(1,1.0/size,1));
	sceneNode->setMaterialTexture(0, driver->getTexture("./resource/sample_obstacle.bmp"));
	sceneNode->setPosition(irr::core::vector3df(position.x, position.z, position.y));*/

	sceneNode = smgr->addMeshSceneNode(smgr->getMesh(data->ModelData.modelname));
	sceneNode->setMaterialTexture(0, driver->getTexture(data->ModelData.skinname));
	sceneNode->setScale(data->ModelData.scale*size);
	sceneNode->setRotation(data->ModelData.rotate);
	sceneNode->getMaterial(0).Lighting = true;
	sceneNode->getMaterial(0).NormalizeNormals = true;
	sceneNode->getMaterial(0).AmbientColor = video::SColor(255,125,125,125);
	sceneNode->setPosition(irr::core::vector3df(position.x, position.z, position.y));
	/*irr::scene::ITriangleSelector* selector = smgr->createTriangleSelector(sceneNode);
	sceneNode->setTriangleSelector(selector);
	selector->drop();*/
	sceneNode->setMaterialType(video::EMT_SOLID); 
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