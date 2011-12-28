
#include "CStateIngame.h"
#include "CStateMainMenu.h"

STowerData* EmptyTowerList[] = {0,0,0,0,0};



class IngameEventReceiver: public MyEventReceiver
{
public:
	IngameEventReceiver(CStateIngame* state):MyEventReceiver()
	{
		this->state = state;
	}

	virtual bool OnEvent(const SEvent& event)
	{
		bool inAction = false;
		if (MyEventReceiver::OnEvent(event)) inAction=true;
		/*if (event.EventType==EEVENT_TYPE::EET_KEY_INPUT_EVENT)
		{
			core::vector3df campos = state->camera->getPosition();
			core::vector3df camtar = state->camera->getTarget();
				
			core::vector3df dir = (camtar - campos);dir.Y = 0;dir.normalize();
			if (dir.getLength()<0.001)
			{
				dir = state->camera->getUpVector();
				dir.Y = 0;
				dir.normalize();
			}

			core::vector3df camfw = campos+dir;
			printf("W dir %f %f %f",camfw.X, camfw.Y, camfw.Z);

			switch (event.KeyInput.Key)
			{
			case EKEY_CODE::KEY_KEY_W:	
				printf("W dir %f %f %f",dir.X, dir.Y, dir.Z);
				state->camera->setPosition(camfw);
				state->camera->setTarget(camtar+dir);
				break;
			case EKEY_CODE::KEY_KEY_A:
				break;
			case EKEY_CODE::KEY_KEY_S:
				state->camera->setPosition(campos-dir);
				state->camera->setTarget(camtar-dir);
				break;
			case EKEY_CODE::KEY_KEY_D:
				break;

			}
		}
		else */if (event.EventType==EEVENT_TYPE::EET_GUI_EVENT)
		{
			switch (event.GUIEvent.EventType)
			{
			case gui::EGUI_EVENT_TYPE::EGET_BUTTON_CLICKED:
				{
					if (event.GUIEvent.Caller->getID()==E_GBIG_CONTINUE)
					{
						printf("CONTINUE\n");
						state->time_status = ES_PLAY;
						state->menuIngame->setVisible(false);
						//tat' menu ingame
						CIrrlichtView::GetInstance()->device->getTimer()->start();
						state->smgr->getActiveCamera()->setInputReceiverEnabled(true);
						CIrrlichtView::GetInstance()->device->getCursorControl()->setVisible(false);
						core::rect<s32> vp = state->driver->getViewPort();
						CIrrlichtView::GetInstance()->device->getCursorControl()->setPosition(vp.getWidth()/2, vp.getHeight()/2);
					}
					else if (event.GUIEvent.Caller->getID()==E_GBIG_RESTART)
					{
						//do something
						state->ObjectManager.Reset();
						state->selectedTower = 0;
						state->select_index = -1;
						state->select_x = -1;
						state->select_y = -1;
						state->status = ES_NONE;
						state->time_status = ES_PLAY;

						state->menuIngame->setVisible(false);
						state->menuIngame_WIN->setVisible(false);
						state->menuIngame_LOSE->setVisible(false);
						//tat' menu ingame
						CIrrlichtView::GetInstance()->device->getTimer()->start();
						state->smgr->getActiveCamera()->setInputReceiverEnabled(true);
						CIrrlichtView::GetInstance()->device->getCursorControl()->setVisible(false);
						core::rect<s32> vp = state->driver->getViewPort();
						CIrrlichtView::GetInstance()->device->getCursorControl()->setPosition(vp.getWidth()/2, vp.getHeight()/2);
					}
					else if (event.GUIEvent.Caller->getID()==E_GBIG_QUIT)
					{
						//do something
						CGame::GetInstance()->Exit();

					}
					else if (event.GUIEvent.Caller->getID()==E_GBIG_MAINMENU)
					{
						CIrrlichtView::GetInstance()->device->getTimer()->start();
						CStateManagement::GetInstance()->SwitchState(new CStateMainMenu());
					}
					else if (event.GUIEvent.Caller->getID()==E_GBIG_NEXT)
					{
						CIrrlichtView::GetInstance()->device->getTimer()->start();
						CStateManagement::GetInstance()->SwitchState(new CStateIngame(state->MapDataList,state->currentMapIndex+1));
					}
					inAction = true;
				}
				break;
			default:
				{
					
				}
				break;
			}
		}
		return inAction;
	}

private:
	CStateIngame* state;

};

	
//--------------------------

CStateIngame::CStateIngame(SMapData** MapDataList, int index):CState()
{
	this->MapDataList = MapDataList;
	currentMapIndex = index;
}

void CStateIngame::Init()
{
	core::rect<s32> vp = driver->getViewPort();

	Log("State Ingame: Init");

	//intial irr devices
	CFpsController::GetInstance()->SetLimitFps(100);
	CGameObject::smgr = smgr;
	CGameObject::driver = driver;
	CGameObject::guienv = guienv;	
	

	gui::ICursorControl* gcursor = CIrrlichtView::GetInstance()->device->getCursorControl();
	//gcursor->set
	gcursor->setVisible(false);

	//TempObject:	2 tower at (5,0) and (8,5), 
	//				1 enemy at (2,2)
	//				1 obstacle at (3,3)
	selectedTower = 0;
	select_index = -1;
	select_x = -1;
	select_y = -1;

	CMapObject* map = new CMapObject(MapDataList[currentMapIndex]);
	ObjectManager.SetMapObject(map);

	//camera
	irr::core::vector3df center = ObjectManager.Map->sceneNode->getTerrainCenter();

	irr:SKeyMap keymap[4];
	keymap[0].Action = EKEY_ACTION::EKA_MOVE_FORWARD;
	keymap[0].KeyCode = EKEY_CODE::KEY_KEY_W;

	keymap[1].Action = EKEY_ACTION::EKA_MOVE_BACKWARD;
	keymap[1].KeyCode = EKEY_CODE::KEY_KEY_S;

	keymap[2].Action = EKEY_ACTION::EKA_STRAFE_LEFT;
	keymap[2].KeyCode = EKEY_CODE::KEY_KEY_A;

	keymap[3].Action = EKEY_ACTION::EKA_STRAFE_RIGHT;
	keymap[3].KeyCode = EKEY_CODE::KEY_KEY_D;

	camera = smgr->addCameraSceneNodeFPS(0, 100, 0.05, -1, keymap, 4, true);
	camera->setPosition(center+irr::core::vector3df(ObjectManager.Map->data->Width/2,6,-ObjectManager.Map->data->Height/2));
	camera->setTarget(center);
	camera->setFarValue(42000.0f);

	
	irr::scene::ISceneNodeAnimator* anim = smgr->createCollisionResponseAnimator(map->sceneNode->getTriangleSelector(), camera, irr::core::vector3df(1,6,1),irr::core::vector3df(0,-10000.0f,0));
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
	gui::IGUIFont* font = guienv->getFont("./resource/myfont.xml");

	Money_text = guienv->addStaticText(L"Money : -",irr::core::rect<irr::s32>(10,10,410,110),false,false,0,-1,false);
	Money_text->setOverrideFont(font);
	Money_text->setOverrideColor(video::SColor(180,255,255,0));
	Money_text->enableOverrideColor(true);


	Life_text = guienv->addStaticText(L"Lives : -",irr::core::rect<irr::s32>(vp.LowerRightCorner.X-10-400,10,vp.LowerRightCorner.X,110),false,false,0,-1,false);
	Life_text->setOverrideFont(font);
	Life_text->setOverrideColor(video::SColor(180,255,0,0));
	Life_text->enableOverrideColor(true);
	Life_text->setTextAlignment(gui::EGUIA_CENTER,gui::EGUIA_CENTER);

	status=ES_NONE;
	printf("status -> ES_NONE\n");

	/*cursor = smgr->addBillboardSceneNode(0,core::dimension2df(0.3,0.3));
	cursor->setMaterialTexture(0, driver->getTexture("./resource/particle.bmp"));
	cursor->setMaterialFlag(video::EMF_LIGHTING, false);
	//cursor->setMaterialFlag(video::EMF_ZBUFFER, false);
	cursor->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR);
	//guienv->addImage(*/

	cursor = guienv->addImage(core::rect<s32>(gcursor->getPosition(),core::dimension2di(16,16)));
	cursor->setImage(driver->getTexture("./resource/cursor.png"));
	cursor->setUseAlphaChannel(true);
	
	
	s32 width = vp.getWidth();
	s32 height = vp.getHeight();

	selectPane[0] = guienv->addImage(core::rect<s32>(width-74*5-20,height-94,width-10,height-10),0,-1,L"");

	selectPane[1] = guienv->addImage(core::rect<s32>(10,10,74,74),selectPane[0],-1,L"");
	selectPane[2] = guienv->addImage(core::rect<s32>(84,10,146,74),selectPane[0],-1,L"");
	selectPane[3] = guienv->addImage(core::rect<s32>(156,10,220,74),selectPane[0],-1,L"");
	selectPane[4] = guienv->addImage(core::rect<s32>(230,10,294,74),selectPane[0],-1,L"");
	selectPane[5] = guienv->addImage(core::rect<s32>(304,10,370,74),selectPane[0],-1,L"");


	gui::IGUIFont * numberfont = guienv->getFont("./resource/number.xml");
	gui::IGUIStaticText* text;
	text = guienv->addStaticText(L"1",core::rect<s32>(10,49,25,79),false,false,selectPane[1],-1,false);
	text->setNotClipped(true);
	text->setOverrideFont(numberfont);
	text->setOverrideColor(video::SColor(255,0,255,0));

	text = guienv->addStaticText(L"2",core::rect<s32>(10,49,25,79),false,false,selectPane[2],-1,false);
	text->setNotClipped(true);
	text->setOverrideFont(numberfont);
	text->setOverrideColor(video::SColor(255,0,255,0));

	text = guienv->addStaticText(L"3",core::rect<s32>(10,49,25,79),false,false,selectPane[3],-1,false);
	text->setNotClipped(true);
	text->setOverrideFont(numberfont);
	text->setOverrideColor(video::SColor(255,0,255,0));

	text = guienv->addStaticText(L"4",core::rect<s32>(10,49,25,79),false,false,selectPane[4],-1,false);
	text->setNotClipped(true);
	text->setOverrideFont(numberfont);
	text->setOverrideColor(video::SColor(255,0,255,0));

	text = guienv->addStaticText(L"5",core::rect<s32>(10,49,25,79),false,false,selectPane[5],-1,false);
	text->setNotClipped(true);
	text->setOverrideFont(numberfont);
	text->setOverrideColor(video::SColor(255,0,255,0));


	for (int i=0;i<6;i++)
		selectPane[i]->setUseAlphaChannel(true);

	time_status=ES_PLAY;


	menuIngame = guienv->addImage(vp);
	gui::IGUIImage* menu = guienv->addImage(core::rect<s32>(core::vector2di((vp.getWidth()-153)/2-10,(vp.getHeight()-206)/2-10),core::dimension2di(153+20,206+20)),menuIngame);
	video::SColor color (255,255,255,255);
	guienv->getSkin()->setColor(gui::EGUI_DEFAULT_COLOR::EGDC_WINDOW,color);
	gui::IGUIButton* bContinue =  guienv->addButton(core::rect<s32>(10,10,162,54),menu,E_GBIG_CONTINUE);
	bContinue->setImage(driver->getTexture("./resource/button/continue.png"));
	bContinue->setUseAlphaChannel(true);
	bContinue->setDrawBorder(false);
	gui::IGUIButton* bRestart = guienv->addButton(core::rect<s32>(10,64,162,108),menu,E_GBIG_RESTART);
	bRestart->setImage(driver->getTexture("./resource/button/restart.png"));
	bRestart->setUseAlphaChannel(true);
	bRestart->setDrawBorder(false);
	gui::IGUIButton* bMainMenu = guienv->addButton(core::rect<s32>(10,118,162,162),menu,E_GBIG_MAINMENU);
	bMainMenu->setImage(driver->getTexture("./resource/button/mainmenu.png"));
	bMainMenu->setUseAlphaChannel(true);
	bMainMenu->setDrawBorder(false);
	gui::IGUIButton* bQuit = guienv->addButton(core::rect<s32>(10,172,162,216),menu,E_GBIG_QUIT);
	bQuit->setImage(driver->getTexture("./resource/button/quit.png"));
	bQuit->setUseAlphaChannel(true);
	bQuit->setDrawBorder(false);
	menuIngame->setVisible(false);

	menuIngame_WIN = guienv->addImage(vp);
	//menuIngame_WIN->setImage(driver->getTexture("./resource/win.jpg"));
	//menuIngame_WIN->setScaleImage(true);
	text = guienv->addStaticText(L"YOU WIN", core::rect<s32>(core::vector2di(0,(vp.getHeight()-206)/2-10-110),core::dimension2di(vp.getWidth(),100)),false,true,menuIngame_WIN,-1,false);
	text->setNotClipped(true);
	text->setOverrideColor(video::SColor(255,0,255,0));
	text->setOverrideFont(font);
	text->setTextAlignment(gui::EGUIA_CENTER,gui::EGUIA_CENTER);

	menu = guienv->addImage(core::rect<s32>(core::vector2di((vp.getWidth()-153)/2-10,(vp.getHeight()-206)/2-10),core::dimension2di(153+20,206+20)),menuIngame_WIN);
	gui::IGUIButton* bwNext =  guienv->addButton(core::rect<s32>(10,10,162,54),menu,E_GBIG_NEXT);
	bwNext->setImage(driver->getTexture("./resource/button/continue.png"));
	bwNext->setUseAlphaChannel(true);
	bwNext->setDrawBorder(false);
	if (currentMapIndex>=3) bwNext->setEnabled(false);

	gui::IGUIButton* bwRestart = guienv->addButton(core::rect<s32>(10,64,162,108),menu,E_GBIG_RESTART);
	bwRestart->setImage(driver->getTexture("./resource/button/restart.png"));
	bwRestart->setUseAlphaChannel(true);
	bwRestart->setDrawBorder(false);
	gui::IGUIButton* bwMainMenu = guienv->addButton(core::rect<s32>(10,118,162,162),menu,E_GBIG_MAINMENU);
	bwMainMenu->setImage(driver->getTexture("./resource/button/mainmenu.png"));
	bwMainMenu->setUseAlphaChannel(true);
	bwMainMenu->setDrawBorder(false);
	gui::IGUIButton* bwQuit = guienv->addButton(core::rect<s32>(10,172,162,216),menu,E_GBIG_QUIT);
	bwQuit->setImage(driver->getTexture("./resource/button/quit.png"));
	bwQuit->setUseAlphaChannel(true);
	bwQuit->setDrawBorder(false);
	menuIngame_WIN->setVisible(false);

	menuIngame_LOSE = guienv->addImage(vp);
	//menuIngame_LOSE->setImage(driver->getTexture("./resource/lose.jpg"));
	//menuIngame_LOSE->setScaleImage(true);
	text = guienv->addStaticText(L"YOU LOSE", core::rect<s32>(core::vector2di(0,(vp.getHeight()-152)/2-10-110),core::dimension2di(vp.getWidth(),100)),false,true,menuIngame_LOSE,-1,false);
	text->setNotClipped(true);
	text->setOverrideColor(video::SColor(255,0,255,0));
	text->setOverrideFont(font);
	text->setTextAlignment(gui::EGUIA_CENTER,gui::EGUIA_CENTER);

	menu = guienv->addImage(core::rect<s32>(core::vector2di((vp.getWidth()-153)/2-10,(vp.getHeight()-152)/2-10),core::dimension2di(153+20,152+20)),menuIngame_LOSE);
	gui::IGUIButton* blRestart =  guienv->addButton(core::rect<s32>(10,10,162,54),menu,E_GBIG_RESTART);
	blRestart->setImage(driver->getTexture("./resource/button/restart.png"));
	blRestart->setUseAlphaChannel(true);
	blRestart->setDrawBorder(false);
	gui::IGUIButton* blMainMenu = guienv->addButton(core::rect<s32>(10,64,162,108),menu,E_GBIG_MAINMENU);
	blMainMenu->setImage(driver->getTexture("./resource/button/mainmenu.png"));
	blMainMenu->setUseAlphaChannel(true);
	blMainMenu->setDrawBorder(false);
	gui::IGUIButton* blQuit = guienv->addButton(core::rect<s32>(10,118,162,162),menu,E_GBIG_QUIT);
	blQuit->setImage(driver->getTexture("./resource/button/quit.png"));
	blQuit->setUseAlphaChannel(true);
	blQuit->setDrawBorder(false);
	//blQuit->
	menuIngame_LOSE->setVisible(false);

	receiver = new IngameEventReceiver(this);
	CIrrlichtView::GetInstance()->device->setEventReceiver(receiver);
}

void CStateIngame::updateSelectPane(STowerData** list)
{
	for (int i=0;i<5;i++)
	{
		/*core::stringc s = "./resource/selectPane_layer";
		s+=(i+1);
		if (i==select_index-1)
			s+="_hl.png";
		else
			s+=".png";
		selectPane[i+6]->setImage(driver->getTexture(s));*/

		if (list[i])
		{
			selectPane[i+1]->setImage(driver->getTexture(list[i]->ModelData.avatarname));			
			if (ObjectManager.Map->Money>=list[i]->Cost)
				selectPane[i+1]->setColor(video::SColor(125,255,255,255));
			else
				selectPane[i+1]->setColor(video::SColor(125,255,150,150));
			if (select_index==i+1) 
			{
				selectPane[i+1]->setColor(video::SColor(255,255,255,255));
			}
		}
		else
			selectPane[i+1]->setImage(driver->getTexture("./resource/selectPane.bmp"));
	}
}

void CStateIngame::Update()
{
	core::vector2df origin((float)(ObjectManager.Map->data->Width)/2,(float)(ObjectManager.Map->data->Height)/2);
	core::vector3df new3dpos(camera->getPosition());
	core::vector2df cam2dpos(new3dpos.X,new3dpos.Z);
	if (cam2dpos.getDistanceFrom(origin)>origin.getLength()*2)
	{
		core::vector2df new2dpos = (cam2dpos-origin).normalize()*(origin.getLength()*2)+origin;
		new3dpos.X = new2dpos.X;
		new3dpos.Z = new2dpos.Y;
		camera->setPosition(new3dpos);
	}
	//printf("Camera position %f %f %f\n", camera->getPosition().X, camera->getPosition().Y, camera->getPosition().Z);

	if (time_status==ES_WAIT_END) return;

	if (ObjectManager.Map->status==2 ||ObjectManager.Map->status==3) 
	{
		if (ObjectManager.Map->status==2)
			menuIngame_WIN->setVisible(true);
		else 
			menuIngame_LOSE->setVisible(true);

		time_status = ES_WAIT_END;

		CIrrlichtView::GetInstance()->device->getTimer()->stop();
		smgr->getActiveCamera()->setInputReceiverEnabled(false);
		CIrrlichtView::GetInstance()->device->getCursorControl()->setVisible(true);

		return; //WIN/LOSE
	}


	if (CControllerKeyManager::GetInstance()->WasKeyRelease((int)EKEY_CODE::KEY_ESCAPE))
	{
		switch (time_status)
		{
		case ES_PLAY:
			time_status = ES_PAUSE;
			menuIngame->setVisible(true);
			//render menu ingame
			CIrrlichtView::GetInstance()->device->getTimer()->stop();
			smgr->getActiveCamera()->setInputReceiverEnabled(false);
			CIrrlichtView::GetInstance()->device->getCursorControl()->setVisible(true);
			break;
		case ES_PAUSE:
			time_status = ES_PLAY;
			menuIngame->setVisible(false);
			//tat' menu ingame
			CIrrlichtView::GetInstance()->device->getTimer()->start();
			smgr->getActiveCamera()->setInputReceiverEnabled(true);
			CIrrlichtView::GetInstance()->device->getCursorControl()->setVisible(false);
			core::rect<s32> vp = driver->getViewPort();
			CIrrlichtView::GetInstance()->device->getCursorControl()->setPosition(vp.getWidth()/2, vp.getHeight()/2);
			break;

		}
	}

	if (CControllerKeyManager::GetInstance()->WasKeyRelease(EKEY_CODE::KEY_SPACE))
	{
		ObjectManager.Map->drawGrid = !ObjectManager.Map->drawGrid;
	}

	if (time_status==ES_PAUSE) return;

	cursor->setRelativePosition(core::recti(CIrrlichtView::GetInstance()->device->getCursorControl()->getPosition()-core::dimension2di(8,8),core::dimension2di(16,16)));

	

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

	//driver->draw3DTriangle(hitTriangle, irr::video::SColor(255,0,125,0));

	CTowerObject* currentSelectTower = ObjectManager.GetTowerAtPosition((int)intersection.X,(int)intersection.Z);
	CMapObject* Map = ObjectManager.Map;
	if (selectedTower) 
	{
		selectedTower->sceneNode->getMaterial(0).AmbientColor = video::SColor(255,125,125,125);
		updateSelectPane(selectedTower->data->UpgradeTowerList);
	}
	else
		if (status==ES_UNBUILD)
			updateSelectPane(EmptyTowerList);
		else
			updateSelectPane(Map->data->BasicTowerList);




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
			if (CControllerKeyManager::GetInstance()->WasKeyRelease(EKEY_CODE::KEY_KEY_E))
			{
				select_index = -1;
				status = ES_NONE;
				printf("status -> ES_NONE\n");
				selectedTower->Sell();
				selectedTower=0;
				select_x = -1;
				select_y = -1;
				return;
			}
			else
			{

				switch (status)
				{
				case ES_TOWER:case ES_SELECT_UPGRADE:
					//render khung select upgrade
				
					if (CControllerKeyManager::GetInstance()->WasKeyRelease(EKEY_CODE::KEY_KEY_1) && selectedTower->data->UpgradeTowerList[0])
					{
						if (Map->Money>=selectedTower->data->UpgradeTowerList[0]->Cost)
						{
							select_index = 1;
							status= ES_SELECT_UPGRADE;
							printf("status -> ES_SELECT_UPGRADE\n");
						}
					}
					else if (CControllerKeyManager::GetInstance()->WasKeyRelease(EKEY_CODE::KEY_KEY_2) && selectedTower->data->UpgradeTowerList[1])
					{
						if (Map->Money>=selectedTower->data->UpgradeTowerList[1]->Cost)
						{
							select_index = 2;
							status= ES_SELECT_UPGRADE;
							printf("status -> ES_SELECT_UPGRADE\n");
						}
					}
					else if (CControllerKeyManager::GetInstance()->WasKeyRelease(EKEY_CODE::KEY_KEY_3) && selectedTower->data->UpgradeTowerList[2])
					{
						if (Map->Money>=selectedTower->data->UpgradeTowerList[2]->Cost)
						{
							select_index = 3;
							status= ES_SELECT_UPGRADE;
							printf("status -> ES_SELECT_UPGRADE\n");
						}
					}
					else if (CControllerKeyManager::GetInstance()->WasKeyRelease(EKEY_CODE::KEY_KEY_4) && selectedTower->data->UpgradeTowerList[3])
					{
						if (Map->Money>=selectedTower->data->UpgradeTowerList[3]->Cost)
						{
							select_index = 4;
							status= ES_SELECT_UPGRADE;
							printf("status -> ES_SELECT_UPGRADE\n");
						}
					}
					else if (CControllerKeyManager::GetInstance()->WasKeyRelease(EKEY_CODE::KEY_KEY_5) && selectedTower->data->UpgradeTowerList[4])
					{
						if (Map->Money>=selectedTower->data->UpgradeTowerList[4]->Cost)
						{
							select_index = 5;
							status= ES_SELECT_UPGRADE;
							printf("status -> ES_SELECT_UPGRADE\n");
						}
					}

					if (status==ES_SELECT_UPGRADE)
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
						case ES_BUILD:case ES_SELECT_BUILD:
							//render khung select build
							
							if (CControllerKeyManager::GetInstance()->WasKeyRelease(EKEY_CODE::KEY_KEY_1) && Map->data->BasicTowerList[0])
							{
								if (Map->Money>=Map->data->BasicTowerList[0]->Cost)
								{
									select_index = 1;
									status= ES_SELECT_BUILD;
									printf("status -> ES_SELECT_BUILD\n");
								}
							}
							else if (CControllerKeyManager::GetInstance()->WasKeyRelease(EKEY_CODE::KEY_KEY_2) && Map->data->BasicTowerList[1])
							{
								if (Map->Money>=Map->data->BasicTowerList[1]->Cost)
								{
									select_index = 2;
									status= ES_SELECT_BUILD;
									printf("status -> ES_SELECT_BUILD\n");
								}
							}
							else if (CControllerKeyManager::GetInstance()->WasKeyRelease(EKEY_CODE::KEY_KEY_3) && Map->data->BasicTowerList[2])
							{
								if (Map->Money>=Map->data->BasicTowerList[2]->Cost)
								{
									select_index = 3;
									status= ES_SELECT_BUILD;
									printf("status -> ES_SELECT_BUILD\n");
								}
							}
							else if (CControllerKeyManager::GetInstance()->WasKeyRelease(EKEY_CODE::KEY_KEY_4) && Map->data->BasicTowerList[3])
							{
								if (Map->Money>=Map->data->BasicTowerList[3]->Cost)
								{
									select_index = 4;
									status= ES_SELECT_BUILD;
									printf("status -> ES_SELECT_BUILD\n");
								}
							}
							else if (CControllerKeyManager::GetInstance()->WasKeyRelease(EKEY_CODE::KEY_KEY_5) && Map->data->BasicTowerList[4])
							{
								if (Map->Money>=Map->data->BasicTowerList[4]->Cost)
								{
									select_index = 5;
									status= ES_SELECT_BUILD;
									printf("status -> ES_SELECT_BUILD\n");
								}
							}


							if (status==ES_SELECT_BUILD && (CControllerPointerManager::GetInstance()->WasReleaseInside(0,0,CIrrlichtView::GetInstance()->GetWidth(),CIrrlichtView::GetInstance()->GetHeight())))
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
		video::SMaterial gridmaterial1;
		gridmaterial1.setTexture(0,driver->getTexture("./resource/grid_cell_white.png"));
		gridmaterial1.Lighting = false;
		gridmaterial1.ZWriteEnable = false;
		gridmaterial1.NormalizeNormals = false;
		gridmaterial1.MaterialType = video::EMT_TRANSPARENT_ALPHA_CHANNEL;

		video::S3DVertex Vertices[4] = {
			video::S3DVertex(select_x,0.1,select_y, 0,1,0,video::SColor(255,255,255,255), 0, 0),
			video::S3DVertex(select_x,0.1,select_y+2, 0,1,0,video::SColor(255,255,255,255), 0, 1),
			video::S3DVertex(select_x+2,0.1,select_y+2, 0,1,0,video::SColor(255,255,255,255), 1, 1),
			video::S3DVertex(select_x+2,0.1,select_y, 0,1,0,video::SColor(255,255,255,255), 1, 0)
		};
		u16 indices[] = {	0,1,2, 0,2,3, };

		driver->setTransform(irr::video::ETS_WORLD, irr::core::matrix4());
		driver->setMaterial(gridmaterial1);
		//driver->draw3DBox(core::aabbox3df(,0.1,select_y,select_x+2,0.2,select_y+2),video::SColor(255,0,125,0));	
		driver->drawVertexPrimitiveList(Vertices, 4, indices, 2);
	}
}

void CStateIngame::Exit()
{
	Log("State Ingame: Exit");


	menuIngame->remove();
	menuIngame_LOSE->remove();
	menuIngame_WIN->remove();
	selectPane[0]->remove();

	Money_text->remove();
	Life_text->remove();
	cursor->remove();
	ObjectManager.ClearTower();
	ObjectManager.ClearEnemy();
	ObjectManager.ClearBullet();
	ObjectManager.ClearObstacle();
	delete ObjectManager.Map;
	//ObjectManager.SetMapObject(0);
	camera->remove();
	
}
