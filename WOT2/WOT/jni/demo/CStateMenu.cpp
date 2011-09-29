#include "CStateMenu.h"
#include "CExample.h"
#include "CStateChooseLevel.h"
#include "CStateOption.h"
#include "CStateHelp.h"
#include "CSoundManagement.h"

CStateMenu::CStateMenu():CState()
{}

void NewGameFunc()
{
	Log("Call NewGame Func");
	CStateManagement::GetInstance()->SwitchState(new CStateChooseLevel());
}

void OptionFunc()
{
	Log("Call Option Func");
	CStateManagement::GetInstance()->SwitchState(new CStateOption());
}
void HelpFunc()
{
	Log("Call Help Func");
	CStateManagement::GetInstance()->SwitchState(new CStateHelp());
}

void QuitFunc()
{
	Log("Call Quit Func");
	CGame::GetInstance()->Exit();
}

void CStateMenu::Init()
{
	Log("State Menu: Init");

	__INT32 w = VIEWCLASS::GetInstance()->GetWidth();
	__INT32 h = VIEWCLASS::GetInstance()->GetHeight();
	
	// background image
	CImageManager::GetInstance()->AddImage<CFileWin32Driver>(PATH_GRAPHIC("WOT_Menu.tga"),true);
	background = CImageManager::GetInstance()->Get(PATH_GRAPHIC("WOT_Menu.tga"));

	// background sound
	CSoundManagement::GetInstance()->AddSound(PATH_AUDIO("AMenuBackground.ogg"), (char*)"menu_background");
	CSoundManagement::GetInstance()->AddSound(PATH_AUDIO("AButtonSelect.wav"), (char*)"Button_Select");
	A_Background = CSoundManagement::GetInstance()->GetSound((char*)"menu_background");
	A_Background->SetLoop(true);
	A_Background->Play();

	//button Quit
	but_Quit = new CButton(PATH_GRAPHIC("Button_Sprite.tga"),PATH_GRAPHIC("Button_Sprite.tga"));
	but_Quit->SetActiveFunction(QuitFunc);
	but_Quit->SetPosition(SRect<__INT32>		(20,		h-20-60,	60,		60));
	but_Quit->SetRegion(SRect<__INT32>			(320,		0,			60,		60));
	but_Quit->SetRegionHover(SRect<__INT32>		(380,		0,			60,		59));
	but_Quit->SetSelectedSound(CSoundManagement::GetInstance()->GetSound((char*)"Button_Select"));

	// button Help
	but_Help = new CButton(PATH_GRAPHIC("Button_Sprite.tga"),PATH_GRAPHIC("Button_Sprite.tga"));
	but_Help->SetActiveFunction(HelpFunc);
	but_Help->SetPosition(SRect<__INT32>		(w-220,		40,			200,	65));
	but_Help->SetRegion(SRect<__INT32>			(0,			250,		160,	50));
	but_Help->SetRegionHover(SRect<__INT32>		(160,		250,		160,	50));
	but_Help->SetSelectedSound(CSoundManagement::GetInstance()->GetSound((char*)"Button_Select"));

	// button Option
	but_Option = new CButton(PATH_GRAPHIC("Button_Sprite.tga"),PATH_GRAPHIC("Button_Sprite.tga"));
	but_Option->SetActiveFunction(OptionFunc);
	but_Option->SetPosition(SRect<__INT32>		(w-220,		105,		200,	65));
	but_Option->SetRegion(SRect<__INT32>		(0,			300,		160,	50));
	but_Option->SetRegionHover(SRect<__INT32>	(160,		300,		160,	50));
	but_Option->SetSelectedSound(CSoundManagement::GetInstance()->GetSound((char*)"Button_Select"));

	// button New game
	but_Newgame = new CButton(PATH_GRAPHIC("Button_Sprite.tga"),PATH_GRAPHIC("Button_Sprite.tga"));
	but_Newgame->SetActiveFunction(NewGameFunc);
	but_Newgame->SetPosition(SRect<__INT32>		(w-220,		170,		200,	65));
	but_Newgame->SetRegion(SRect<__INT32>		(0,			350,		160,	50));
	but_Newgame->SetRegionHover(SRect<__INT32>	(160,		350,		160,	50));
	but_Newgame->SetSelectedSound(CSoundManagement::GetInstance()->GetSound((char*)"Button_Select"));
}

void CStateMenu::Update()
{
}

void CStateMenu::Render()
{	
	__UINT32 w = (CViewController<VIEWCLASS>::GetInstance()->GetView()->GetWidth());
	__UINT32 h = (CViewController<VIEWCLASS>::GetInstance()->GetView()->GetHeight());
	
	CGraphics2D::GetInstance()->Clear(SColor<float>(1.0f,0.0f,0.0f,1.0f));
	CGraphics2D::GetInstance()->DrawImageRegion(SRect<__INT32>(0,0,w,h),background,SRect<__INT32>(0,0,800,480));
	but_Newgame->Draw();
	but_Option->Draw();
	but_Help->Draw();
	but_Quit->Draw();
	CGraphics2D::GetInstance()->Flush();
}

void CStateMenu::OnControllerEvent(SControllerEvent Event)
{	
	but_Newgame->OnControllerEvent(Event);
	but_Option->OnControllerEvent(Event);
	but_Help->OnControllerEvent(Event);
	but_Quit->OnControllerEvent(Event);
}

void CStateMenu::Exit()
{
	CSoundManagement::GetInstance()->Free((char*)"menu_background");
	CImageManager::GetInstance()->Free(PATH_GRAPHIC("WOT_Menu.tga"));
	SAFE_DEL(but_Help);
	SAFE_DEL(but_Newgame);
	SAFE_DEL(but_Option);
	SAFE_DEL(but_Quit);
	Log("State Menu: Exit");
}
