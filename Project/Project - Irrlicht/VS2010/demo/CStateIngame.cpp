
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
	selectedTower = 0;
	select_index = -1;
	select_x = -1;
	select_y = -1;

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
	
	irr::core::vector3df lightpos = center+irr::core::vector3df(0,5,0);

	irr::scene::ILightSceneNode* light = smgr->addLightSceneNode(0, lightpos, irr::video::SColorf(1.0f, 1.0f, 1.0f, 1.0f), 800.0f);
	irr::video::SLight light_data;
	light_data.AmbientColor=irr::video::SColor(200,255,255,255);
	light_data.DiffuseColor=irr::video::SColor(55,255,255,255);
	light_data.SpecularColor=irr::video::SColor(255,255,255,255);
	light_data.Radius=800.0f;
	light_data.Type = irr::video::ELT_POINT;

	light->setLightData(light_data);

	//
	
	Money_text = guienv->addStaticText(L"Money : -",irr::core::rect<irr::s32>(10,10,110,20),false,false,0,-1,true);
	Life_text = guienv->addStaticText(L"Lives : -",irr::core::rect<irr::s32>(10,30,110,40),false,false,0,-1,true);

	status=ES_NONE;
	printf("status -> ES_NONE\n");

	cursor = smgr->addBillboardSceneNode(0,core::dimension2df(0.3,0.3));
	cursor->setMaterialTexture(0, driver->getTexture("./resource/particle.bmp"));
	cursor->setMaterialFlag(video::EMF_LIGHTING, false);
	//cursor->setMaterialFlag(video::EMF_ZBUFFER, false);
	cursor->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR);
	//guienv->addImage(
	
}

void CStateIngame::Update()
{
	//input handle
	if (CControllerKeyManager::GetInstance()->WasAnyKeyPressed())
	{
		if (CControllerKeyManager::GetInstance()->WasKeyPressed(EKEY_CODE::KEY_KEY_A)) printf("A pressed");
	}


	//mode processing
	/*static irr::scene::ISceneNode* highlightedSceneNode = 0;
	if (highlightedSceneNode)
	{
		highlightedSceneNode->setMaterialFlag(irr::video::EMF_LIGHTING, true);
		highlightedSceneNode = 0;
	}*/
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
		cursor->setPosition(intersection);
		cursor->setVisible(true);
	}
	else
		cursor->setVisible(false);
	/*if (selectedSceneNode)
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
	}*/
	
		

	
	//driver->draw3DTriangle(hitTriangle, irr::video::SColor(255,0,125,0));

	CTowerObject* currentSelectTower = ObjectManager.GetTowerAtPosition((int)intersection.X,(int)intersection.Z);
	CMapObject* Map = ObjectManager.Map;
	if (selectedTower) selectedTower->sceneNode->getMaterial(0).AmbientColor = video::SColor(255,125,125,125);

	if (currentSelectTower) 
	{
		//core::aabbox3d<f32> TowerBox(currentSelectTower->logicposition.x+0.1,0.1,currentSelectTower->logicposition.y+0.1,currentSelectTower->logicposition.x+1.9,1.9,currentSelectTower->logicposition.y+1.9);
		//driver->setTransform(irr::video::ETS_WORLD, irr::core::matrix4());
		//driver->draw3DBox(TowerBox, irr::video::SColor(255,0,125,125));



		if (selectedTower!=currentSelectTower)
		{
			
			selectedTower = currentSelectTower;
			
			//render khung select moi'
			select_index = -1;
			status = ES_TOWER;
			printf("status -> ES_TOWER\n");

			select_x=selectedTower->logicposition.x;
			select_y=selectedTower->logicposition.y;
		}
		else
		{
			switch (status)
			{
			case ES_TOWER:
				//render khung select upgrade
				if (CControllerKeyManager::GetInstance()->WasKeyRelease(EKEY_CODE::KEY_KEY_1) && selectedTower->data->UpgradeTowerList[0])
				{
					select_index = 1;
					status= ES_SELECT_UPGRADE;
					printf("status -> ES_SELECT_UPGRADE\n");
				}
				else if (CControllerKeyManager::GetInstance()->WasKeyRelease(EKEY_CODE::KEY_KEY_2) && selectedTower->data->UpgradeTowerList[1])
				{
					select_index = 2;
					status= ES_SELECT_UPGRADE;
					printf("status -> ES_SELECT_UPGRADE\n");
				}
				else if (CControllerKeyManager::GetInstance()->WasKeyRelease(EKEY_CODE::KEY_KEY_3) && selectedTower->data->UpgradeTowerList[2])
				{
					select_index = 3;
					status= ES_SELECT_UPGRADE;
					printf("status -> ES_SELECT_UPGRADE\n");
				}
				else if (CControllerKeyManager::GetInstance()->WasKeyRelease(EKEY_CODE::KEY_KEY_4) && selectedTower->data->UpgradeTowerList[3])
				{
					select_index = 4;
					status= ES_SELECT_UPGRADE;
					printf("status -> ES_SELECT_UPGRADE\n");
				}
				else if (CControllerKeyManager::GetInstance()->WasKeyRelease(EKEY_CODE::KEY_KEY_5) && selectedTower->data->UpgradeTowerList[4])
				{
					select_index = 5;
					status= ES_SELECT_UPGRADE;
					printf("status -> ES_SELECT_UPGRADE\n");
				}
				break;
			case ES_SELECT_UPGRADE:
				if (CControllerPointerManager::GetInstance()->WasReleaseInside(0,0,CIrrlichtView::GetInstance()->GetWidth(),CIrrlichtView::GetInstance()->GetHeight()))
				{
					selectedTower->Upgrade(selectedTower->data->UpgradeTowerList[select_index-1]);
					status = ES_TOWER;
					printf("status -> ES_TOWER\n");
					select_index=-1;									
					return;
				}
				break;

			}
		}

		currentSelectTower->sceneNode->getMaterial(0).AmbientColor = video::SColor(255,255,255,255);
	}
	else
	{
		int startx=(int)intersection.X;
		int starty=(int)intersection.Z;
		if (intersection.X-(int)intersection.X<0.5) startx--;
		if (intersection.Y-(int)intersection.Y<0.5) starty--;
		Position pos[4] = {	Position(startx,starty,0),
							Position(startx+1,starty,0),
							Position(startx,starty+1,0),
							Position(startx+1,starty+1,0)};
		Position clickpos(intersection.X,intersection.Z,0);
		for (int i=0;i<3;i++)
		{
			for (int j=i+1;j<4;j++)
			{
				if (((pos[i]+Position(1,1,0))|clickpos)>((pos[j]+Position(1,1,0))|clickpos))
				{
					Position p = pos[i];
					pos[i] = pos[j];
					pos[j] = p;
				}
			}
		}
		for (int i=0;i<4;i++)
		{
			if (Map->iSBuildable((int)pos[i].x,(int)pos[i].y) && (int)pos[i].x>=0 && (int)pos[i].x<Map->data->Width-1 && (int)pos[i].y>=0 && (int)pos[i].y<Map->data->Height-1 && (selectedSceneNode!=0))
			{
				if (select_x!=(int)pos[i].x || select_y!=(int)pos[i].y)
				{
					status = ES_BUILD;
					selectedTower = 0;
					
					select_x = (int)pos[i].x;
					select_y = (int)pos[i].y;
					printf("status -> ES_BUILD %d %d %d %d\n", select_x, select_y, pos[0].x, pos[0].y);
				}
				else
				{
					switch (status)
					{
						case ES_BUILD:
							//render khung select build
							if (CControllerKeyManager::GetInstance()->WasKeyRelease(EKEY_CODE::KEY_KEY_1) && Map->data->BasicTowerList[0])
							{
								select_index = 1;
								status= ES_SELECT_BUILD;
								printf("status -> ES_SELECT_BUILD\n");
							}
							else if (CControllerKeyManager::GetInstance()->WasKeyRelease(EKEY_CODE::KEY_KEY_2) && Map->data->BasicTowerList[1])
							{
								select_index = 2;
								status= ES_SELECT_BUILD;
								printf("status -> ES_SELECT_BUILD\n");
							}
							else if (CControllerKeyManager::GetInstance()->WasKeyRelease(EKEY_CODE::KEY_KEY_3) && Map->data->BasicTowerList[2])
							{
								select_index = 3;
								status= ES_SELECT_BUILD;
								printf("status -> ES_SELECT_BUILD\n");
							}
							else if (CControllerKeyManager::GetInstance()->WasKeyRelease(EKEY_CODE::KEY_KEY_4) && Map->data->BasicTowerList[3])
							{
								select_index = 4;
								status= ES_SELECT_BUILD;
								printf("status -> ES_SELECT_BUILD\n");
							}
							else if (CControllerKeyManager::GetInstance()->WasKeyRelease(EKEY_CODE::KEY_KEY_5) && Map->data->BasicTowerList[4])
							{
								select_index = 5;
								status= ES_SELECT_BUILD;
								printf("status -> ES_SELECT_BUILD\n");
							}
							break;
						case ES_SELECT_BUILD:
							if (CControllerPointerManager::GetInstance()->WasReleaseInside(0,0,CIrrlichtView::GetInstance()->GetWidth(),CIrrlichtView::GetInstance()->GetHeight()))
							{
								if (Map->BuildTower(Map->data->BasicTowerList[select_index-1],LogicPosition(select_x,select_y)))
								{
									status = ES_TOWER;
									printf("status -> ES_TOWER\n");
									selectedTower = ObjectManager.GetTowerAtPosition(select_x, select_y);
									select_x = -1;
									select_y = -1;
									select_index=-1;									
								}
								return;
							}
							break;
					}
				}
				return;
			}
		}
		if (status!=ES_UNBUILD)
		{
			status = ES_UNBUILD;
			printf("status -> ES_UNBUILD\n");
			select_index = -1;
			select_x = -1;
			select_y = -1;
			selectedTower = 0;
		}
	}
}

void CStateIngame::Render()
{
	ObjectManager.Render();
	if (select_x!=-1 && select_y!=-1)
	{
		irr::video::SMaterial material;
		material.setTexture(0, 0);
		material.Lighting = false;
		material.NormalizeNormals = false;
		material.Wireframe = true;
		driver->setTransform(irr::video::ETS_WORLD, irr::core::matrix4());
		driver->setMaterial(material);
		driver->draw3DBox(core::aabbox3df(select_x,0.1,select_y,select_x+2,0.2,select_y+2),video::SColor(255,0,125,0));
	}
}

void CStateIngame::Exit()
{
	Log("State Ingame: Exit");
}
