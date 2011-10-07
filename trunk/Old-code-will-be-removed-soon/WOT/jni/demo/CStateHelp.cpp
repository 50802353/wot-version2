
#include "CStateHelp.h"
#include "CSoundManagement.h"
#include "CStateMenu.h"
#include "CStateAbout.h"

void h_AboutFunc(){
	CStateManagement::GetInstance()->SwitchState(new CStateAbout());
}

void h_TutFunc(){
	//CStateManagement::GetInstance()->SwitchState(new CStateTut());
}

void h_MainMenuFunc(){
	CStateManagement::GetInstance()->SwitchState(new CStateMenu());
}

CStateHelp::CStateHelp(): CState()
{}

void CStateHelp::Init()
{
	Log("State Help: Init");

	__INT32 w = VIEWCLASS::GetInstance()->GetWidth();
	__INT32 h = VIEWCLASS::GetInstance()->GetHeight();

	CImageManager::GetInstance()->AddImage<CFileWin32Driver>(PATH_GRAPHIC("WOT_Menu.tga"),true);
	Background = CImageManager::GetInstance()->Get(PATH_GRAPHIC("WOT_Menu.tga"));
	Background->FreeBuffer();

	CSoundManagement::GetInstance()->AddSound(PATH_AUDIO("AButtonSelect.wav"), (char*)"Button_Select");
	CSoundManagement::GetInstance()->AddSound(PATH_AUDIO("AMenuBackground.ogg"), (char*)"menu_background");
	A_Background = CSoundManagement::GetInstance()->GetSound((char*)"menu_background");
	A_Background->Play();

	// button About
	but_About = new CButton(PATH_GRAPHIC("Button_Sprite.tga"),PATH_GRAPHIC("Button_Sprite.tga"));
	but_About->SetActiveFunction(h_AboutFunc);
	but_About->SetPosition		(SRect<__INT32>		(w-220,		105,		200,	65));
	but_About->SetRegion		(SRect<__INT32>		(0,			200,		160,	50));
	but_About->SetRegionHover	(SRect<__INT32>		(160,		200,		160,	50));
	but_About->SetSelectedSound(CSoundManagement::GetInstance()->GetSound((char*)"Button_Select"));

	// button Tutorial
	but_Tutorial = new CButton(PATH_GRAPHIC("Button_Sprite.tga"),PATH_GRAPHIC("Button_Sprite.tga"));
	but_Tutorial->SetActiveFunction(h_TutFunc);
	but_Tutorial->SetPosition	(SRect<__INT32>		(w-220,		170,		200,	65));
	but_Tutorial->SetRegion		(SRect<__INT32>		(320,		450,		160,	50));
	but_Tutorial->SetRegionHover(SRect<__INT32>		(480,		450,		160,	50));
	but_Tutorial->SetSelectedSound(CSoundManagement::GetInstance()->GetSound((char*)"Button_Select"));

	// button main Menu
	but_MainMenu = new CButton(PATH_GRAPHIC("Button_Sprite.tga"),PATH_GRAPHIC("Button_Sprite.tga"));
	but_MainMenu->SetActiveFunction(h_MainMenuFunc);
	but_MainMenu->SetPosition	(SRect<__INT32>		(w-220,		40,		200,	65));
	but_MainMenu->SetRegion		(SRect<__INT32>		(0,			0,		160,	50));
	but_MainMenu->SetRegionHover(SRect<__INT32>		(160,		0,		160,	50));
	but_MainMenu->SetSelectedSound(CSoundManagement::GetInstance()->GetSound((char*)"Button_Select"));
}

void CStateHelp::Update()
{	
	
}

void CStateHelp::Render()
{
	__UINT32 w = (CViewController<VIEWCLASS>::GetInstance()->GetView()->GetWidth());
	__UINT32 h = (CViewController<VIEWCLASS>::GetInstance()->GetView()->GetHeight());

	CGraphics2D::GetInstance()->Clear(SColor<float>(0.0f,0.0f,0.0f,1.0f));	
	CGraphics2D::GetInstance()->DrawImageRegion(SRect<__INT32>(0, 0, w, h),Background,SRect<__INT32>(0,0,800,480));	
	but_About->Draw();
	but_MainMenu->Draw();
	but_Tutorial->Draw();
	CGraphics2D::GetInstance()->Flush();
}

void CStateHelp::OnControllerEvent(SControllerEvent Event){
	but_Tutorial->OnControllerEvent(Event);
	but_About->OnControllerEvent(Event);
	but_MainMenu->OnControllerEvent(Event);
}

void CStateHelp::Exit()
{
	CSoundManagement::GetInstance()->Free((char*)"menu_background");
	CImageManager::GetInstance()->Free(PATH_GRAPHIC("WOT_Menu.tga"));
	SAFE_DEL(but_About);
	SAFE_DEL(but_MainMenu);
	SAFE_DEL(but_Tutorial);
	Log("State Help: Exit");	
}
