#include "CStateIngame.h"
#include "CExample.h"
#include "MyParticleSystem.h"
#include "CInfoPanel.h"

Ingame_status CStateIngame::status = INGAME_PLAY;
__INT32 CStateIngame::creepCount = 0;
__INT32 CStateIngame::MaxCreep = 100;
CRandom CStateIngame::isCrit;
CWOTMapfile* CStateIngame::currentfile;
CInfoPanel* info = NULL;
bool drawinfo = false;
TowerBuildBar* CStateIngame::currentBuildBar=NULL;

/*
 *	Begin Func for CState Ingame
 */

CStateIngame::CStateIngame():CState(),BuildBar(NULL),menu(NULL),WaveTime(0.0f),A_Background(NULL),A_Lose(NULL),A_Win(NULL),introTime(0)
{
}

void CStateIngame::Init()
{
	Log("State Ingame: Init");

	CImageManager::GetInstance()->Get(PATH_GRAPHIC("HPBar.tga"))->FreeBuffer();

	//install Sound to InGame State

	A_Background = CSoundManagement::GetInstance()->GetSound((char*) "InGame_Background");
	A_Background->SetLoop(true);
	A_Background->Play();

	A_Lose = CSoundManagement::GetInstance()->GetSound((char*)"LoseBG");
	A_Win = CSoundManagement::GetInstance()->GetSound((char*)"WinBG");

	//init Money and Lives
	//CObjectManagement::GetInstance()->InitLiveAndMoney(live,money); //wait Quan, get from currentFile

	//for map
	MapObject* mapWOT;
	mapWOT = new MapObject(PATH_GRAPHIC("grid_cell.tga"),PATH_GRAPHIC("grid_circle.tga"),currentfile->width,currentfile->height,0.5f,0,1);
	
	CObjectManagement::GetInstance()->AddElement(mapWOT);
			
	CStateIngame::currentfile->m_lstNature->BeginTravel();
	while (!CStateIngame::currentfile->m_lstNature->IsEndOfTravel())
	{
		GameObjectType* type = CStateIngame::currentfile->m_lstNature->Travel();
		switch(type->ID)
		{
		case TILE_BANANA:
			{
				TreeObject* tree = new TreeObject();
				tree->SetModel(CModelManager::GetInstance()->Get(0));
				tree->SetPosition(type->j,type->i);
				CObjectManagement::GetInstance()->AddElement(tree);
				break;
			}
		case TILE_COCONUT:
			{
				TreeObject* tree = new TreeObject();
				tree->SetModel(CModelManager::GetInstance()->Get(1));
				tree->SetPosition(type->j,type->i);
				CObjectManagement::GetInstance()->AddElement(tree);
				break;
			}
		}
	}

	


	currentfile->m_lstWave->BeginTravel();

	
	CCamera3D::GetInstance()->CameraLoadIdentity();
	CCamera3D::GetInstance()->CameraLookat(4.5,0,5,
											4.5,2,1,
											0,1,0);	
	//
	/*CCamera3D::GetInstance()->CameraRotate(45,1,0,0);
	CCamera3D::GetInstance()->CameraTranslate(-6,10,-10);
	CCamera3D::GetInstance()->CameraScale(4.5f,4.5f,4.5f);*/

	CStateIngame::status = INGAME_PLAY;

	SAFE_DEL(menu);
	menu = new IngameMenu();
	SAFE_DEL(BuildBar);
	BuildBar = new TowerBuildBar();
	CStateIngame::currentBuildBar = BuildBar;
	introTime = 3.0f;
	Log("Xong Init");
}

void CStateIngame::Update()
{
	//Log("FPS %d",CFpsController::GetInstance()->GetRuntimeFps());
	Log("Update time %lu",__UINT32(CDevice::GetInstance()->GetTimer()));
	/*if (introTime>0)
	{
		introTime-=float(CFpsController::GetInstance()->GetFrameDt())/1000.0;
		if (introTime<0) introTime = 0;
		
		float r = 5.0;
		float s = sin(introTime*2*PI);
		float c = -cos(introTime*2*PI);

		CCamera3D::GetInstance()->CameraLoadIdentity();
		CCamera3D::GetInstance()->CameraLookat(2.0*s+4.5,2.0*c+3.0,(introTime*2+3),
												4.5,3,(introTime*0.5+1),
												0,0,1);
		return;
	}*/
	if (status ==  INGAME_PLAY)
	{
		float tpf = (float) CFpsController::GetInstance()->GetFrameDt()/1000;
		if(CObjectManagement::GetInstance()->isFinishWave())
		{
			//clear all old enemy
			CObjectManagement::GetInstance()->ClearObjectType(OBJECT_ENEMY);
			CObjectManagement::GetInstance()->ClearObjectType(OBJECT_BULLET);
			//clear Path
			CPathManagement::GetInstance()->ClearAll();

			//init new wave
			if(!currentfile->m_lstWave->IsEndOfTravel())
			{
				Wave* thisWave = currentfile->m_lstWave->Travel();
				Way* way;
				if(currentfile->m_lstWay->GetElement(thisWave->wayID,way))
				{
					CPathManagement::GetInstance()->setPath(MapPosition(way->sj,way->si), MapPosition(way->dj,way->di),CObjectManagement::GetInstance()->GetMap());
					//CPathManagement::GetInstance()->setPath(MapPosition(0,0), MapPosition(17,10),CObjectManagement::GetInstance()->GetMap());
					EnemyProperties* eproperties;
					CStateIngame::currentfile->m_lstEnemyProperties->GetElement(thisWave->enemyType,eproperties);
					for(int i = 0; i < thisWave->amount; i++)
					{						
						EnemyObject* enemy1 = new EnemyObject(eproperties);
						enemy1->SetModel(CModelManager::GetInstance()->Get(eproperties->mModelID));
						enemy1->SetAction((char*)"run");
						//enemy1->mX = way->sj*0.5;
						//enemy1->mY = way->si*0.5;
						CObjectManagement::GetInstance()->AddElement(enemy1);
					}
				}
			}
			else 
			{
				//Update Win
				if (CObjectManagement::GetInstance()->isFinishWave())
				{
					status = INGAME_WIN;
					if(CExample::m_LevelChose == CExample::m_LevelUnlocked)
						CExample::m_LevelUnlocked++;
					A_Win->Play();
				}
			}
			//	Update Lose
			if (CObjectManagement::GetInstance()->GetLives() <= 0)
			{
				status = INGAME_LOSE;
				A_Lose->Play();
			}
		}
		
		//Background sound always plays when game is playing
		A_Background->Play();

		CObjectManagement::GetInstance()->Update(tpf);

		if (creepCount<MaxCreep) creepCount++;

		//mapWOT->Update();
		
		/*
		static float rotateangle=0;
		if (rotateangle<20)
		rotateangle+=(20-rotateangle)*(20-rotateangle)*(20-rotateangle)/1000;
		CCamera3D::GetInstance()->CameraLoadIdentity();
		CCamera3D::GetInstance()->CameraLookat(15*sin(rotateangle)+4.5,15*cos(rotateangle)+2,24-rotateangle,
												4.5,2,4,
												0,0,1);	*/
	}
	else 
		//Pause background music if Game not playing
		A_Background->Pause();
}

void CStateIngame::Render()
{	
	Log("Render time %lu",__UINT32(CDevice::GetInstance()->GetTimer()));
	CGraphics2D::GetInstance()->Clear(SColor<float>(0,0,0,1.0f));
	CObjectManagement::GetInstance()->Render();
	Log("Render Object %lu",__UINT32(CDevice::GetInstance()->GetTimer()));
	CParticleManager::GetInstance()->Render();
	Log("Render Particle %lu",__UINT32(CDevice::GetInstance()->GetTimer()));
	if (drawinfo) info->Draw();
	//BuildBar->Render();
	CStateIngame::currentBuildBar->Render();
	Log("Render build bar %lu",__UINT32(CDevice::GetInstance()->GetTimer()));
	if (status == INGAME_PAUSE_MENU || 
		status == INGAME_CONFIRM || 
		status == INGAME_WIN || 
		status == INGAME_LOSE) 
		menu->Render();
	Log("Render menu %lu",__UINT32(CDevice::GetInstance()->GetTimer()));
}

void CStateIngame::Exit()
{
	Log("State Ingame: Exit");
	CImageManager::GetInstance()->Clean();
	CSoundManagement::GetInstance()->Clean();
	CObjectManagement::GetInstance()->ClearAll();
	CModelManager::GetInstance()->Clean();

	//SAFE_DEL(A_Background);
	//SAFE_DEL(A_Win);
	//SAFE_DEL(A_Lose);
	//SAFE_DEL(skyBox);


	SAFE_DEL(BuildBar);
	SAFE_DEL(menu);
	
	delete CStateIngame::currentfile;
}

void CStateIngame::OnControllerEvent(SControllerEvent Event)
{
	if (Event.PointerData.Event == EPE_PRESSED) drawinfo = false;
	if (status == INGAME_PLAY)
	{
		if (!(CStateIngame::currentBuildBar->OnControllerEvent(Event)))
			CObjectManagement::GetInstance()->GetMap()->OnControllerEvent(Event);
	}
	else //if (status == INGAME_ gi` do'  (neu' co' phan` confirm thi them vo o day cho~ cho confirm nhan. event)
	{
		menu->OnControllerEvent(Event);
	}
}

void CStateIngame::ResetState()
{
	//delete CObjectManagement::GetInstance();
	CObjectManagement::GetInstance()->ClearAll();

	//SAFE_DEL(A_Background);
	//SAFE_DEL(A_Win);
	//SAFE_DEL(A_Lose);
	//SAFE_DEL(skyBox);


	SAFE_DEL(BuildBar);
	SAFE_DEL(menu);

	CStateIngame::status = INGAME_PLAY;//reset status
	Init();
}

int CStateIngame::Damage(int baseDamage, int amour, int probability) {
	__INT32 damage = baseDamage*(1 - 0.005*amour - 0.5*CStateIngame::isCrit.NextTrue(probability));
	if(damage <= 0) damage = 1;
	return damage;
}


/*
 *	End Func for CState Ingame
 */

//====================================================================================

/*
 *	Begin Func for Button Action
 */

void BuildTower(__INT32 key)
{
	if (key==0) return;
	TowerProperties* TowerProperties;
	CStateIngame::currentfile->m_lstTowerProperties->GetElement(key,TowerProperties);

	__INT32 tower_price = TowerProperties->mValue;
	__INT32 &selected = (CObjectManagement::GetInstance()->GetMap()->selected);
	__INT32 selectY = selected / CObjectManagement::GetInstance()->GetMap()->GetWidth();
	__INT32 selectX = selected - CObjectManagement::GetInstance()->GetMap()->GetWidth() * selectY;

	if (CObjectManagement::GetInstance()->GetMoney() >= tower_price && selected != -1)
	{
		TowerObject *oldtower = CObjectManagement::GetInstance()->GetTower(MapPosition(selectX,selectY));
		if (oldtower)
		{
			oldtower->mProperties = TowerProperties;
			oldtower->SetModel(CModelManager::GetInstance()->Get(oldtower->mProperties->mModelID));
			CObjectManagement::GetInstance()->GetMap()->CalculateBoundary( oldtower->mPosition.mX, oldtower->mPosition.mY, SELECTED_TOWER_CELL_COLOR, oldtower->mProperties->mRange);						
			CObjectManagement::GetInstance()->GetMap()->UpdateTowerBuildBar(oldtower->mProperties->mLstChildren);
		}
		else
		{			
			TowerObject *tower = new TowerObject(TowerProperties);
			tower->SetPosition(selected);
			tower->SetModel(CModelManager::GetInstance()->Get(tower->mProperties->mModelID));
			//tower->SetModel(CModelManager::GetInstance()->Get(2));
			CObjectManagement::GetInstance()->AddElement(tower);
			CStateIngame::currentBuildBar->sellButton->SetVisible(true);
			CObjectManagement::GetInstance()->GetMap()->CalculateBoundary( tower->mPosition.mX, tower->mPosition.mY, SELECTED_TOWER_CELL_COLOR, tower->mProperties->mRange);						
			CObjectManagement::GetInstance()->GetMap()->UpdateTowerBuildBar(tower->mProperties->mLstChildren);

		}
		//update Boost
		CObjectManagement::GetInstance()->UpdateBoost();
		//update Path
		CPathManagement::GetInstance()->Update();
		//CList<__INT32> empty;
		//CObjectManagement::GetInstance()->GetMap()->UpdateTowerBuildBar(&empty);
		//update money
		CObjectManagement::GetInstance()->UpdateMoney(-tower_price);
	}
}

void Build1()
{
	BuildTower(CStateIngame::currentBuildBar->towerID1);
}

void Build2()
{
	BuildTower(CStateIngame::currentBuildBar->towerID2);
}

void Build3()
{
	BuildTower(CStateIngame::currentBuildBar->towerID3);
}

void Build4()
{
	BuildTower(CStateIngame::currentBuildBar->towerID4);
}

void TowerInfo(__INT32 towerkey)
{
	TowerProperties *tmp;
	CStateIngame::GetInstance()->currentfile->m_lstTowerProperties->GetElement(towerkey, tmp);
	char buffer[200];
	sprintf(buffer, "Name|%s|Damage|%d|Speed|%d|Critical|%d", 
		tmp->mAlias, tmp->mBaseDamage, tmp->mSpeedAttack, tmp->mCritical);
	SAFE_DEL(info);
	info = new CInfoPanel(450,10,buffer,4,2);
	drawinfo = true;
}

void Info1()
{
	TowerInfo(CStateIngame::currentBuildBar->towerID1);
}

void Info2()
{
	TowerInfo(CStateIngame::currentBuildBar->towerID2);
}

void Info3()
{
	TowerInfo(CStateIngame::currentBuildBar->towerID3);
}

void Info4()
{
	TowerInfo(CStateIngame::currentBuildBar->towerID4);
}

void ContinueGame()
{
	if (CStateIngame::status==INGAME_PLAY) CStateIngame::status = INGAME_PAUSE_MENU;
	else if (CStateIngame::status==INGAME_PAUSE_MENU) CStateIngame::status = INGAME_PLAY;
}

void SellTower()
{
	__INT32 &selected = (CObjectManagement::GetInstance()->GetMap()->selected);
	if (selected != -1)
	{
		__INT32 selectY = selected / CObjectManagement::GetInstance()->GetMap()->GetWidth();
		__INT32 selectX = selected - CObjectManagement::GetInstance()->GetMap()->GetWidth() * selectY;

		TowerObject *tower = CObjectManagement::GetInstance()->GetTower(MapPosition(selectX,selectY));
		if(tower)
		{
			//get value of tower and update money
			CObjectManagement::GetInstance()->UpdateMoney( (__INT32) tower->mProperties->mValue*0.75);
			//remove tower
			//--update Map Logic
			__INT32* logicMap = CObjectManagement::GetInstance()->GetMap()->mLogicMap;
			logicMap[selected] = OBJECT_NONE;
			logicMap[selected + 1] = OBJECT_NONE;
			logicMap[selected + CObjectManagement::GetInstance()->GetMap()->GetWidth()] = OBJECT_NONE;
			logicMap[selected + CObjectManagement::GetInstance()->GetMap()->GetWidth() + 1] = OBJECT_NONE;
			//--remove tower in CObjectManager
			CObjectManagement::GetInstance()->RemoveTower(tower);
			//update Boost
			CObjectManagement::GetInstance()->UpdateBoost();
			//update Path
			CPathManagement::GetInstance()->Update();
			CObjectManagement::GetInstance()->GetMap()->CalculateBoundary( tower->mPosition.mX, tower->mPosition.mY, SELECTED_BUILDABLE_CELL_COLOR, 0);						
			CList<__INT32> towerList;
			towerList.AddItem(TOWER_GUN);
			CObjectManagement::GetInstance()->GetMap()->UpdateTowerBuildBar(&towerList);
		}
	}
}

void ExitGame()
{
	CGame::GetInstance()->Exit();
}

void RestartGame()
{
	Log("Call Restart Func");
	CStateIngame::GetInstance()->ResetState();
}

void MainMenu()
{
	CStateIngame::status = INGAME_PLAY;//reset status
	//CStateIngame::GetInstance()->Exit();
	//CStateIngame::GetInstance()->TotalMoney = 1000;
	//CStateIngame::GetInstance()->TotalMoney = 20;
	CStateManagement::GetInstance()->SwitchState(new CStateMenu());
	Log("Call MainMenu Func");
}


/*
 *	End Func for Button Action
 */

//====================================================================================

/*
 *	Begin Func for Tower BuildBar
 */


TowerBuildBar::TowerBuildBar():Tower1(NULL),Tower2(NULL),Tower3(NULL),Tower4(NULL),but_HOME(NULL),font(NULL), 
	InGameBar(NULL), CreepBar(NULL), sellButton(NULL)
{
	__INT32 W = VIEWCLASS::GetInstance()->GetWidth();
	__INT32 H = VIEWCLASS::GetInstance()->GetHeight();

	font = CImageManager::GetInstance()->Get(PATH_GRAPHIC("font_GillSanUltraBold2.tga"));


	//Tower1 = new CButton(PATH_GRAPHIC("tower_demo.tga"),PATH_GRAPHIC("tower_demo.tga"),1.2);
	Tower1 = new CDropdownButton(PATH_GRAPHIC("tower_demo.tga"),PATH_GRAPHIC("tower_demo.tga"),1.2);
	Tower1->SetActiveFunction(Build1);
	Tower1->SetDropdownFunction(Info1);
	Tower1->SetPosition(SRect<__INT32>(10,H-60-105+10,85,85));
	Tower1->SetRegion(SRect<float>(0,0,1,1));
	Tower1->SetVisible(false);

	Tower2 = new CDropdownButton(PATH_GRAPHIC("tower_demo.tga"),PATH_GRAPHIC("tower_demo.tga"),1.2);
	Tower2->SetActiveFunction(Build2);
	Tower2->SetDropdownFunction(Info2);
	Tower2->SetPosition(SRect<__INT32>(10,H-60-210+10,85,85));
	Tower2->SetRegion(SRect<float>(0,0,1,1));
	Tower2->SetVisible(false);

	Tower3 = new CDropdownButton(PATH_GRAPHIC("tower_demo.tga"),PATH_GRAPHIC("tower_demo.tga"),1.2);
	Tower3->SetActiveFunction(Build3);
	Tower3->SetDropdownFunction(Info3);
	Tower3->SetPosition(SRect<__INT32>(10,H-60-315+10,85,85));
	Tower3->SetRegion(SRect<float>(0,0,1,1));
	Tower3->SetVisible(false);

	Tower4 = new CDropdownButton(PATH_GRAPHIC("tower_demo.tga"),PATH_GRAPHIC("tower_demo.tga"),1.2);
	Tower4->SetActiveFunction(Build4);
	Tower4->SetDropdownFunction(Info4);
	Tower4->SetPosition(SRect<__INT32>(10,H-60-420+10,85,85));
	Tower4->SetRegion(SRect<float>(0,0,1,1));
	Tower4->SetVisible(false);

	but_HOME = new CButton(PATH_GRAPHIC("InGameBar.tga"),PATH_GRAPHIC("InGameBar.tga"),1.2);
	but_HOME->SetActiveFunction(ContinueGame);
	but_HOME->SetPosition(SRect<__INT32>(W/2-40,H-80,80,80));
	but_HOME->SetRegion(SRect<__INT32>(120,80,80,80));
	but_HOME->SetSelectedSound(CSoundManagement::GetInstance()->GetSound((char*)"Button_Select"));

	InGameBar = CImageManager::GetInstance()->Get(PATH_GRAPHIC("InGameBar.tga"));

	CreepBar = CImageManager::GetInstance()->Get(PATH_GRAPHIC("InGameBar.tga"));

	sellButton = new CButton(PATH_GRAPHIC("Button_Sprite.tga"),PATH_GRAPHIC("Button_Sprite.tga"),1.2);
	sellButton->SetActiveFunction(SellTower);
	sellButton->SetPosition	(SRect<__INT32>(W-84,	20,		64,		60));
	sellButton->SetRegion	(SRect<__INT32>(500,	60,		64,		60));
	sellButton->SetSelectedSound(CSoundManagement::GetInstance()->GetSound((char*)"Button_Select"));
	sellButton->SetVisible(false);
}

TowerBuildBar::~TowerBuildBar()
{
	if(Tower1) delete Tower1;
	Tower1 = 0;
	if(Tower2) delete Tower2;
	Tower2 = 0;
	if(Tower3) delete Tower3;
	Tower3 = 0;
	if(Tower4) delete Tower4;
	Tower4 = 0;

	if(but_HOME) delete but_HOME;
	but_HOME = 0;
}

void TowerBuildBar::Render()
{
	Tower1->Draw();
	Tower2->Draw();
	Tower3->Draw();
	Tower4->Draw();
	sellButton->Draw();


	 //////////////////////////////////////////////////////////////////////////
	//InGameBar Begin
	__INT32 W = VIEWCLASS::GetInstance()->GetWidth();
	__INT32 H = VIEWCLASS::GetInstance()->GetHeight();
	
	CGraphics2D::GetInstance()->DrawImageRegion(SRect<__INT32>(0,H-60,W,60),InGameBar,SRect<__INT32>(120,20,W,60));
	CGraphics2D::GetInstance()->DrawImageRegion(SRect<__INT32>(496,H-22,__INT32(float(CStateIngame::creepCount)/CStateIngame::MaxCreep*153),11),InGameBar,SRect<__INT32>(200,80,153,11));
	but_HOME->Draw();
	
	
	
	//Draw money
	PrintMoney(font, CObjectManagement::GetInstance()->GetMoney());

	//Draw Lives
	PrintLives(font, CObjectManagement::GetInstance()->GetLives());

	//InGameBar End

	CGraphics2D::GetInstance()->Flush();


	/*char string[20];	
	itoa(CStateIngame::money,string,10);
	CGraphics2D::GetInstance()->DrawString(font,string,-1,1,h_left|v_top,0.1,0.85);

	itoa(CStateIngame::lives,string,10);
	CGraphics2D::GetInstance()->DrawString(font,string,-0.5,1,h_left|v_top,0.1,0.85);
	*/

//	CGraphics2D::GetInstance()->Flush();
}

bool TowerBuildBar::OnControllerEvent(SControllerEvent Event)
{
	bool check = false;
	if(Tower1->Isvisible())
	{
		check = check | Tower1->OnControllerEvent(Event);
	}
	if(Tower2->Isvisible())
	{
		check = check | Tower2->OnControllerEvent(Event);
	}
	if(Tower3->Isvisible())
	{
		check = check | Tower3->OnControllerEvent(Event);
	}
	if(Tower4->Isvisible())
	{
		check = check | Tower4->OnControllerEvent(Event);
	}

	check = check | but_HOME->OnControllerEvent(Event);

	if(sellButton->Isvisible())
	{
		check = check | sellButton->OnControllerEvent(Event);
	}

	return check;
}

void TowerBuildBar::PrintMoney(CImage *font, __INT32 number)
{
	if (number >= 1000000) number = number % 1000000;
	char* String_tmp = new char[6];
	sprintf(String_tmp, "%d" , number);
	CGraphics2D::GetInstance()->DrawString(font,String_tmp,170,480,h_left|v_top,0.07,0.85);
	//CGraphics2D::GetInstance()->DrawString(font,(char*)"999999",float((2*257-W)/H),float((2*453-H)/H),h_right|v_bottom,0.08,0.85);
}

void TowerBuildBar::PrintLives(CImage *font, __INT32 number)
{
	if (number >= 100) number = number % 100;
	char* String_tmp = new char[2];
	sprintf(String_tmp, "%d" , number);
	CGraphics2D::GetInstance()->DrawString(font,String_tmp,317,470,h_left|v_top,0.09,0.6);
}


/*
 *	End Func for Tower BuildBar
 */

//====================================================================================

/*
 *	Begin Func for InGame Menu
 */


IngameMenu::IngameMenu():but_Continue(NULL),but_Restart(NULL),but_mainMenu(NULL),but_Quit(NULL),fade_background(NULL),
					but_Ask(NULL),but_Lose(NULL),but_No(NULL),but_Win(NULL),but_Yes(NULL)
{
	__INT32 W = VIEWCLASS::GetInstance()->GetWidth();
	__INT32 H = VIEWCLASS::GetInstance()->GetHeight();

	//Continue
	but_Continue = new CButton(PATH_GRAPHIC("Button_Sprite.tga"),PATH_GRAPHIC("Button_Sprite.tga"));
	but_Continue->SetActiveFunction(ContinueGame);
	but_Continue->SetPosition(SRect<__INT32>	(300,		280,		200,	65));
	but_Continue->SetRegion(SRect<__INT32>		(0,			400,		160,	50));
	but_Continue->SetRegionHover(SRect<__INT32>	(160,		400,		160,	50));
	but_Continue->SetSelectedSound(CSoundManagement::GetInstance()->GetSound((char*)"Button_Select"));
	//but_Continue->SetVisible(false);

	but_Restart = new CButton(PATH_GRAPHIC("Button_Sprite.tga"),PATH_GRAPHIC("Button_Sprite.tga"));
	but_Restart->SetActiveFunction(RestartGame);
	but_Restart->SetPosition(SRect<__INT32>		(300,		215,		200,	65));
	but_Restart->SetRegion(SRect<__INT32>		(0,			450,		160,	50));
	but_Restart->SetRegionHover(SRect<__INT32>	(160,		450,		160,	50));
	but_Restart->SetSelectedSound(CSoundManagement::GetInstance()->GetSound((char*)"Button_Select"));
	//but_Restart->SetVisible(false);

	but_mainMenu = new CButton(PATH_GRAPHIC("Button_Sprite.tga"),PATH_GRAPHIC("Button_Sprite.tga"));
	but_mainMenu->SetActiveFunction(MainMenu);
	but_mainMenu->SetPosition(SRect<__INT32>		(300,		150,		200,	65));
	but_mainMenu->SetRegion(SRect<__INT32>			(0,			0,		160,	50));
	but_mainMenu->SetRegionHover(SRect<__INT32>		(160,		0,		160,	50));
	but_mainMenu->SetSelectedSound(CSoundManagement::GetInstance()->GetSound((char*)"Button_Select"));
	//but_mainMenu->SetVisible(false);

	but_Quit = new CButton(PATH_GRAPHIC("Button_Sprite.tga"),PATH_GRAPHIC("Button_Sprite.tga"));
	but_Quit->SetActiveFunction(ExitGame);
	but_Quit->SetPosition(SRect<__INT32>		(300,		85,		200,	65));
	but_Quit->SetRegion(SRect<__INT32>			(0,			150,		160,	50));
	but_Quit->SetRegionHover(SRect<__INT32>		(160,		150,		160,	50));
	but_Quit->SetSelectedSound(CSoundManagement::GetInstance()->GetSound((char*)"Button_Select"));
	//but_Quit->SetVisible(false);

	but_Ask = new CButton(PATH_GRAPHIC("InGameBar.tga"),PATH_GRAPHIC("InGameBar.tga"));
	but_Ask->SetActiveFunction(ExitGame);
	but_Ask->SetPosition(SRect<__INT32>			(305,		260,	190,	32));
	but_Ask->SetRegion(SRect<__INT32>			(635,		80,		190,	32));
	//but_Ask->SetVisible(false);

	but_Yes = new CButton(PATH_GRAPHIC("Button_Sprite.tga"),PATH_GRAPHIC("Button_Sprite.tga"));
	but_Yes->SetActiveFunction(ExitGame);
	but_Yes->SetPosition(SRect<__INT32>			(200,		180,	200,	65));
	but_Yes->SetRegion(SRect<__INT32>			(0,			100,	160,	50));
	but_Yes->SetRegionHover(SRect<__INT32>		(160,		100,	160,	50));
	but_Yes->SetSelectedSound(CSoundManagement::GetInstance()->GetSound((char*)"Button_Select"));
	but_Yes->SetVisible(false);

	but_No = new CButton(PATH_GRAPHIC("Button_Sprite.tga"),PATH_GRAPHIC("Button_Sprite.tga"));
	but_No->SetActiveFunction(ExitGame);
	but_No->SetPosition(SRect<__INT32>			(400,		180,	200,	65));
	but_No->SetRegion(SRect<__INT32>			(0,			50,		160,	50));
	but_No->SetRegionHover(SRect<__INT32>		(160,		50,		160,	50));
	but_No->SetSelectedSound(CSoundManagement::GetInstance()->GetSound((char*)"Button_Select"));
	but_No->SetVisible(false);

	but_Win = new CButton(PATH_GRAPHIC("InGameBar.tga"),PATH_GRAPHIC("InGameBar.tga"));
	but_Win->SetActiveFunction(ExitGame);
	but_Win->SetPosition(SRect<__INT32>			(276,		240,	248,	60));
	but_Win->SetRegion(SRect<__INT32>			(635,		144,	248,	60));
	//but_Win->SetVisible(false);

	but_Lose = new CButton(PATH_GRAPHIC("InGameBar.tga"),PATH_GRAPHIC("InGameBar.tga"));
	but_Lose->SetActiveFunction(ExitGame);
	but_Lose->SetPosition(SRect<__INT32>		(235,		260,		323,	32));
	but_Lose->SetRegion(SRect<__INT32>			(635,		112,		323,	32));
	//but_Lose->SetVisible(false);

	fade_background = CImageManager::GetInstance()->Get(PATH_GRAPHIC("InGameBar.tga"));
}

void IngameMenu::Render()
{
	__INT32 W = VIEWCLASS::GetInstance()->GetWidth();
	__INT32 H = VIEWCLASS::GetInstance()->GetHeight();

	//Draw Fade background
	CGraphics2D::GetInstance()->DrawImageRegion(SRect<__INT32>(0,0,W,H),fade_background,SRect<__INT32>(120,160,10,10));

	//Draw InGameMenu Background
	CGraphics2D::GetInstance()->DrawImageRegion(SRect<__INT32>(182,60,436,310),fade_background,SRect<__INT32>(201,80,435,310));

	if (CStateIngame::status == INGAME_PAUSE_MENU)
	{
		//In game pause menu
		but_Continue->Draw();
		but_Restart->Draw();
		but_mainMenu->Draw();
		but_Quit->Draw();

		////In game Confirm menu		
		//but_Ask->Draw();
		//but_No->Draw();
		//but_Yes->Draw();

		////In game Lose menu
		//but_Lose->Draw();
		//but_Restart->SetPosition(SRect<__INT32>			(200,		180,	200,	65));
		//but_Restart->Draw();
		//but_mainMenu->SetPosition(SRect<__INT32>		(400,		180,	200,	65));
		//but_mainMenu->Draw();

		////In game Win menu
		//but_Win->Draw();
		//but_Restart->SetPosition(SRect<__INT32>			(200,		160,	200,	65));
		//but_Restart->Draw();
		//but_mainMenu->SetPosition(SRect<__INT32>		(400,		160,	200,	65));
		//but_mainMenu->Draw();
	}
	else if (CStateIngame::status == INGAME_CONFIRM)
	{
		but_Ask->Draw();
		but_No->Draw();
		but_Yes->Draw();
	}
	else if (CStateIngame::status == INGAME_LOSE)
	{
		but_Lose->Draw();
		but_Restart->SetPosition(SRect<__INT32>			(200,		180,	200,	65));
		but_Restart->Draw();
		but_mainMenu->SetPosition(SRect<__INT32>		(400,		180,	200,	65));
		but_mainMenu->Draw();
	}
	else if (CStateIngame::status == INGAME_WIN)
	{
		but_Win->Draw();
		but_Restart->SetPosition(SRect<__INT32>			(200,		160,	200,	65));
		but_Restart->Draw();
		but_mainMenu->SetPosition(SRect<__INT32>		(400,		160,	200,	65));
		but_mainMenu->Draw();
	}
	
	CGraphics2D::GetInstance()->Flush();
}

bool IngameMenu::OnControllerEvent(SControllerEvent Event)
{
	bool check = false;
	check = check | but_Continue->OnControllerEvent(Event);
	check = check | but_Restart->OnControllerEvent(Event);
	check = check | but_mainMenu->OnControllerEvent(Event);
	check = check | but_Quit->OnControllerEvent(Event);

	check = check | but_Yes->OnControllerEvent(Event);
	check = check | but_No->OnControllerEvent(Event);
	return check;
}

/*
 *	End Func for Tower BuildBar
 */