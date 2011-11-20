
#include "CStateIngame.h"



	
//--------------------------

CStateIngame::CStateIngame():CState()
{}

void CStateIngame::Init()
{
	Log("State Ingame: Init");

	//intial irr devices
	CFpsController::GetInstance()->SetLimitFps(100);
	CGameObject::smgr = smgr;
	CGameObject::driver = driver;
	CGameObject::guienv = guienv;	
	
    //device->getCursorControl()->setVisible(false);

	//TempObject:	2 tower at (5,0) and (8,5), 
	//				1 enemy at (2,2)
	//				1 obstacle at (3,3)


	CMapObject* map = new CMapObject(&MapData1);
	ObjectManager.SetMapObject(map);
	map->BuildTower(&TowerData1, LogicPosition(5,0));
	map->BuildTower(&TowerData1, LogicPosition(8,5));
	map->AddObstacle(&ObstacleData1, LogicPosition(5,5),2);
	map->AddObstacle(&ObstacleData1, LogicPosition(3,0),2);
	map->AddObstacle(&ObstacleData1, LogicPosition(6,8),1);


	//camera
	irr::core::vector3df center = ObjectManager.Map->sceneNode->getTerrainCenter();
	irr::scene::ICameraSceneNode *camera = NULL;
	camera = smgr->addCameraSceneNodeFPS(0, 100, 0.05);
	camera->setPosition(center+irr::core::vector3df(0,10,-10));
	camera->setTarget(center);
	camera->setFarValue(42000.0f);

	
	irr::scene::ISceneNodeAnimator* anim = smgr->createCollisionResponseAnimator(map->sceneNode->getTriangleSelector(), camera, irr::core::vector3df(1,10,1),irr::core::vector3df(0,-10000.0f,0));
	camera->addAnimator(anim);
	anim->drop();

	//
	
	irr::core::vector3df lightpos = center+irr::core::vector3df(0,50,0);

	irr::scene::ILightSceneNode* light = smgr->addLightSceneNode(0, lightpos, irr::video::SColorf(1.0f, 1.0f, 1.0f, 1.0f), 800.0f);
	irr::video::SLight light_data;
	light_data.AmbientColor=irr::video::SColor(255,55,55,55);
	light_data.DiffuseColor=irr::video::SColor(255,200,200,200);
	light_data.SpecularColor=irr::video::SColor(255,255,255,255);
	light_data.Radius=800.0f;
	light_data.Type = irr::video::ELT_POINT;

	light->setLightData(light_data);

	//
	
	Money_text = guienv->addStaticText(L"Money : -",irr::core::rect<irr::s32>(10,10,110,20),false,false,0,-1,true);
	Life_text = guienv->addStaticText(L"Lives : -",irr::core::rect<irr::s32>(10,30,110,40),false,false,0,-1,true);

	
}

void CStateIngame::Update()
{
	static irr::scene::ISceneNode* highlightedSceneNode = 0;
	if (highlightedSceneNode)
	{
		highlightedSceneNode->setMaterialFlag(irr::video::EMF_LIGHTING, true);
		highlightedSceneNode = 0;
	}
	ObjectManager.Update(CFpsController::GetInstance()->GetFrameDt());
	
	Money_text->setText((irr::core::stringw(L"Money : ")+irr::core::stringw(ObjectManager.Map->Money)).c_str());
	Life_text->setText((irr::core::stringw(L"Lives : ")+irr::core::stringw(ObjectManager.Map->RemainingLife)).c_str());

	irr::core::line3d<irr::f32> ray;
	irr::scene::ICameraSceneNode* camera = smgr->getActiveCamera();
		ray.start = camera->getPosition();
		ray.end = ray.start + (camera->getTarget() - ray.start).normalize() * 100000.0f;
		irr::core::vector3df intersection;
		irr::core::triangle3df hitTriangle;
		irr::scene::ISceneNode * selectedSceneNode = smgr->getSceneCollisionManager()->getSceneNodeAndCollisionPointFromRay(
			ray,
			intersection, // This will be the position of the collision
			hitTriangle, // This will be the triangle hit in the collision
			2, // This ensures that only nodes that we have
					// set up to be pickable are considered
			0); // Check the entire scene (this is actually the implicit default)
		if (selectedSceneNode)
		{
			driver->setTransform(irr::video::ETS_WORLD, irr::core::matrix4());
			irr::video::SMaterial material;
			material.setTexture(0, 0);
			material.Lighting = false;
			material.NormalizeNormals = false;
			material.Wireframe = true;
			driver->setMaterial(material);
			driver->draw3DTriangle(hitTriangle, irr::video::SColor(0,255,0,0));

			highlightedSceneNode = selectedSceneNode;
			highlightedSceneNode->setMaterialFlag(irr::video::EMF_LIGHTING, false);
		}



}

void CStateIngame::Render()
{
	ObjectManager.Render();
}

void CStateIngame::Exit()
{
	Log("State Ingame: Exit");
}
