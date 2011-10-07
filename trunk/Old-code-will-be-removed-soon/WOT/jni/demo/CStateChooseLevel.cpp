#include "CStateChooseLevel.h"
#include "CStateLoading.h"
#include "CStateMenu.h"
#include "CExample.h"
#include "CSoundManagement.h"

CStateChooseLevel::CStateChooseLevel():CState() {}

void ChooseLevel_MainMenuFunc()
{
	Log("Back to Main Menu Func");
	CStateManagement::GetInstance()->SwitchState(new CStateMenu());
}

void ChooseLevel1Func()
{
	Log("Choose Level 1");
	CExample::m_LevelChose = 1;
	//CStateLoading::currentfile.loadfromFile(PATH_GRAPHIC("test.wotmap"));
	CStateManagement::GetInstance()->SwitchState(new CStateLoading());
}

void ChooseLevel2Func()
{
	Log("Choose Level 2");
	CExample::m_LevelChose = 2;
	//CStateLoading::currentfile.loadfromFile(PATH_GRAPHIC("Level2.wotmap"));
	CStateManagement::GetInstance()->SwitchState(new CStateLoading());
}

void ChooseLevel3Func()
{
	Log("Choose Level 3");
	CExample::m_LevelChose = 3;
	//CStateLoading::currentfile.loadfromFile(PATH_GRAPHIC("Level3.wotmap"));
	CStateManagement::GetInstance()->SwitchState(new CStateLoading());
}

void ChooseLevel4Func()
{
	Log("Choose Level 4");
	CExample::m_LevelChose = 4;
	//CStateLoading::currentfile.loadfromFile(PATH_GRAPHIC("Level4.wotmap"));
	CStateManagement::GetInstance()->SwitchState(new CStateLoading());
}

void ChooseLevel5Func()
{
	Log("Choose Level 5");
	CExample::m_LevelChose = 5;
	//CStateLoading::currentfile.loadfromFile(PATH_GRAPHIC("Level5.wotmap"));
	CStateManagement::GetInstance()->SwitchState(new CStateLoading());
}

void ChooseLevel6Func()
{
	Log("Choose Level 6");
	CExample::m_LevelChose = 6;
	//CStateLoading::currentfile.loadfromFile(PATH_GRAPHIC("Level6.wotmap"));
	CStateManagement::GetInstance()->SwitchState(new CStateLoading());
}

void ChooseLevel7Func()
{
	Log("Choose Level 7");
	CExample::m_LevelChose = 7;
	//CStateLoading::currentfile.loadfromFile(PATH_GRAPHIC("Level7.wotmap"));
	CStateManagement::GetInstance()->SwitchState(new CStateLoading());
}

void ChooseLevel8Func()
{
	Log("Choose Level 8");
	CExample::m_LevelChose = 8;
	//CStateLoading::currentfile.loadfromFile(PATH_GRAPHIC("Level8.wotmap"));
	CStateManagement::GetInstance()->SwitchState(new CStateLoading());
}

void ChooseLevel9Func()
{
	Log("Choose Level 9");
	CExample::m_LevelChose = 9;
	//CStateLoading::currentfile.loadfromFile(PATH_GRAPHIC("Level9.wotmap"));
	CStateManagement::GetInstance()->SwitchState(new CStateLoading());
}


void CStateChooseLevel::Init()
{
	Log("State ChooseLevel: Init");

	__INT32 w = VIEWCLASS::GetInstance()->GetWidth();
	__INT32 h = VIEWCLASS::GetInstance()->GetHeight();

	// background image
	CImageManager::GetInstance()->AddImage<CFileWin32Driver>(PATH_GRAPHIC("WOT_ChooseLevel.tga"),true);
	background = CImageManager::GetInstance()->Get(PATH_GRAPHIC("WOT_ChooseLevel.tga"));

	// background sound
	CSoundManagement::GetInstance()->AddSound(PATH_AUDIO("AMenuBackground.ogg"), (char*)"chooseLevel_background");
	A_Background = CSoundManagement::GetInstance()->GetSound((char*)"chooseLevel_background");
	A_Background->SetLoop(true);
	A_Background->Play();

	CSoundManagement::GetInstance()->AddSound(PATH_AUDIO("AButtonSelect.wav"),(char*)"Button_Select");

	// button New game
	but_MainMenu = new CButton(PATH_GRAPHIC("Button_Sprite.tga"),PATH_GRAPHIC("Button_Sprite.tga"));
	but_MainMenu->SetActiveFunction(ChooseLevel_MainMenuFunc);
	but_MainMenu->SetPosition(SRect<__INT32>		(w-220,		20,		200,	65));
	but_MainMenu->SetRegion(SRect<__INT32>			(0,			0,		160,	50));
	but_MainMenu->SetRegionHover(SRect<__INT32>		(160,		0,		160,	50));
	but_MainMenu->SetSelectedSound(CSoundManagement::GetInstance()->GetSound((char*)"Button_Select"));

	// Button level
	for (int i = 0; i<9; i++)
	{
		but_Level[i] = new CButton(PATH_GRAPHIC("Button_Sprite.tga"),PATH_GRAPHIC("Button_Sprite.tga"));
		if (CExample::m_LevelUnlocked > i) 
			but_Level[i]->SetRegion(SRect<__INT32>		(320,	60,		60,		60));	
		else
			but_Level[i]->SetRegion(SRect<__INT32>		(440,	60,		60,		60));
		but_Level[i]->SetRegionHover(SRect<__INT32>		(380,	60,		60,		60));
		but_Level[i]->SetSelectedSound(CSoundManagement::GetInstance()->GetSound((char*)"Button_Select"));
	}

	//Level 1 North America
	but_Level[0]->SetPosition(SRect<__INT32>		(75,		337,		60,		60));
	but_Level[0]->SetActiveFunction(ChooseLevel1Func);

	//Level 2 South America
	but_Level[1]->SetPosition(SRect<__INT32>		(160,		140,		60,		60));
	but_Level[1]->SetActiveFunction(ChooseLevel2Func);

	//Level 3
	but_Level[2]->SetPosition(SRect<__INT32>		(315,		245,		60,		60));
	but_Level[2]->SetActiveFunction(ChooseLevel3Func);

	//Level 4
	but_Level[3]->SetPosition(SRect<__INT32>		(360,		105,		60,		60));
	but_Level[3]->SetActiveFunction(ChooseLevel4Func);

	//Level 5
	but_Level[4]->SetPosition(SRect<__INT32>		(350,		350,		60,		60));
	but_Level[4]->SetActiveFunction(ChooseLevel5Func);

	//Level 6
	but_Level[5]->SetPosition(SRect<__INT32>		(420,		250,		60,		60));
	but_Level[5]->SetActiveFunction(ChooseLevel6Func);

	//Level 7
	but_Level[6]->SetPosition(SRect<__INT32>		(510,		380,		60,		60));
	but_Level[6]->SetActiveFunction(ChooseLevel7Func);

	//Level 8
	but_Level[7]->SetPosition(SRect<__INT32>		(555,		280,		60,		60));
	but_Level[7]->SetActiveFunction(ChooseLevel8Func);

	//Level 9
	but_Level[8]->SetPosition(SRect<__INT32>		(630,		100,		60,		60));
	but_Level[8]->SetActiveFunction(ChooseLevel9Func);
}

void CStateChooseLevel::Update()
{
}

void CStateChooseLevel::Render()
{	
	__UINT32 w = (CViewController<VIEWCLASS>::GetInstance()->GetView()->GetWidth());
	__UINT32 h = (CViewController<VIEWCLASS>::GetInstance()->GetView()->GetHeight());
	
	CGraphics2D::GetInstance()->Clear(SColor<float>(1.0f,0.0f,0.0f,1.0f));
	CGraphics2D::GetInstance()->DrawImageRegion(SRect<__INT32>(0,0,w,h),background,SRect<__INT32>(0,0,800,480));
	but_MainMenu->Draw();
	for (int i = 0; i< 9; i++)
	{
		but_Level[i]->Draw();
	}
	CGraphics2D::GetInstance()->Flush();
}

void CStateChooseLevel::OnControllerEvent(SControllerEvent Event)
{
	but_MainMenu->OnControllerEvent(Event);
	for (int i = 0; i< CExample::m_LevelUnlocked; i++)
	{
		but_Level[i]->OnControllerEvent(Event);
	}
}

void CStateChooseLevel::Exit()
{
	CSoundManagement::GetInstance()->Free((char*)"chooseLevel_background");
	CImageManager::GetInstance()->Get(PATH_GRAPHIC("WOT_ChooseLevel.tga"));
	for (int i = 0; i< 9; i++)
	{
		SAFE_DEL(but_Level[i]);
	}
	SAFE_DEL(but_MainMenu);
	Log("State ChooseLevel: Exit");
}
