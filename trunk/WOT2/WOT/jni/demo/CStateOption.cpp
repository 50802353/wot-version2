#include "CStateOption.h"
#include "CSoundManagement.h"
#include "CStateMenu.h"
#include "CExample.h"

void Back2MainMenuFunc(){
	CStateManagement::GetInstance()->SwitchState(new CStateMenu());
}

void Op_EnableSound(){
	CSoundManagement::GetInstance()->SetSound(true);
	CSoundManagement::GetInstance()->AddSound(PATH_AUDIO("AMenuBackground.ogg"), (char*)"menu_background");
	CSoundManagement::GetInstance()->AddSound(PATH_AUDIO("AButtonSelect.wav"), (char*)"Button_Select");
}

void Op_DisableSound(){
	CSoundManagement::GetInstance()->SetSound(false);
}

CStateOption::CStateOption(): CState()
{}

__UINT32 CStateOption::iVolLevel;

void CStateOption::Init()
{
	Log("State Option: Init");

	__UINT32 w = (CViewController<VIEWCLASS>::GetInstance()->GetView()->GetWidth());
	__UINT32 h = (CViewController<VIEWCLASS>::GetInstance()->GetView()->GetHeight());

	// background image
	CImageManager::GetInstance()->AddImage<CFileWin32Driver>(PATH_GRAPHIC("WOT_Option.tga"),true);
	Background = CImageManager::GetInstance()->Get(PATH_GRAPHIC("WOT_Option.tga"));
	Background->FreeBuffer();

	CSoundManagement::GetInstance()->AddSound(PATH_AUDIO("AMenuBackground.ogg"), (char*)"menu_background");
	CSoundManagement::GetInstance()->AddSound(PATH_AUDIO("AButtonSelect.wav"), (char*)"Button_Select");

	//Sound Level content
	CImageManager::GetInstance()->AddImage<CFileWin32Driver>(PATH_GRAPHIC("Button_Sprite.tga"),true);
	Loading = CImageManager::GetInstance()->Get(PATH_GRAPHIC("Button_Sprite.tga"));

	//button Back to main Menu
	but_Back2MainMenu = new CButton(PATH_GRAPHIC("Button_Sprite.tga"),PATH_GRAPHIC("Button_Sprite.tga"));
	but_Back2MainMenu->SetActiveFunction(Back2MainMenuFunc);
	but_Back2MainMenu->SetPosition(SRect<__INT32>		(w-220,		30,		200,	65));
	but_Back2MainMenu->SetRegion(SRect<__INT32>			(0,			0,		160,	50));
	but_Back2MainMenu->SetRegionHover(SRect<__INT32>	(160,		0,		160,	50));
	//but_Back2MainMenu->SetSelectedSound(CSoundManagement::GetInstance()->GetSound((char*)"Button_Select"));

	//button enable sound
	but_SoundIsEnable = new CButton(PATH_GRAPHIC("WOT_Option.tga"),PATH_GRAPHIC("WOT_Option.tga"),1.1);
	but_SoundIsEnable->SetActiveFunction(Op_DisableSound);
	but_SoundIsEnable->SetPosition(SRect<__INT32>		(155,		174,	87,		76));
	but_SoundIsEnable->SetRegion(SRect<__INT32>			(800,		0,		87,		76));
	//but_SoundIsEnable->SetSelectedSound(CSoundManagement::GetInstance()->GetSound((char*)"Button_Select"));
	
	//button Mute sound
	but_SoundIsMuted = new CButton(PATH_GRAPHIC("WOT_Option.tga"),PATH_GRAPHIC("WOT_Option.tga"),1.1);
	but_SoundIsMuted->SetActiveFunction(Op_EnableSound);
	but_SoundIsMuted->SetPosition(SRect<__INT32>		(155,		174,	87,		76));
	but_SoundIsMuted->SetRegion(SRect<__INT32>			(890,		0,		87,		76));
	//but_SoundIsEnable->SetSelectedSound(CSoundManagement::GetInstance()->GetSound((char*)"Button_Select"));
}

void CStateOption::Update()
{	
	if (CExample::GetInstance()->HasSound())
	{
		but_Back2MainMenu->SetSelectedSound(CSoundManagement::GetInstance()->GetSound((char*)"Button_Select"));
		A_Background = CSoundManagement::GetInstance()->GetSound((char*)"menu_background");
		A_Background->Play();
		but_SoundIsMuted->SetVisible(false);
		but_SoundIsEnable->SetVisible(true);

		CExample::m_fMasterVolume = CSoundManagement::GetInstance()->GetMasterVolume();
		iVolLevel = int(CExample::m_fMasterVolume  * 11) + 1;

		A_Background->VolumeControl(CExample::m_fMasterVolume);
	}
	else {
		iVolLevel = 0;
		but_SoundIsMuted->SetVisible(true);
		but_SoundIsEnable->SetVisible(false);
	}
}

void CStateOption::Render()
{
	__UINT32 w = (CViewController<VIEWCLASS>::GetInstance()->GetView()->GetWidth());
	__UINT32 h = (CViewController<VIEWCLASS>::GetInstance()->GetView()->GetHeight());
	__UINT32 loadWidth = 0;

	CGraphics2D::GetInstance()->Clear(SColor<float>(0.0f,0.0f,0.0f,1.0f));	
	CGraphics2D::GetInstance()->DrawImageRegion(SRect<__INT32>(0, 0, w, h),Background,SRect<__INT32>(0,0,800,480));	

	but_SoundIsEnable->Draw();
	but_SoundIsMuted->Draw();
	but_Back2MainMenu->Draw();

	for (__UINT32 i = 0; i<iVolLevel; i++)
	{
		CGraphics2D::GetInstance()->DrawImageRegion(SRect<__INT32>(250 + loadWidth, 190, 30, 40),Loading ,SRect<__INT32>(440 + loadWidth,0,30,40));	
		loadWidth += 34;
	}

	CGraphics2D::GetInstance()->Flush();
}

void CStateOption::OnControllerEvent(SControllerEvent Event){
	//Change state when touched
	if (CExample::GetInstance()->HasSound()){
		if ((Event.Type == ECE_POINTER) && 
			(Event.PointerData.Event == EPE_DRAGGED) &&
			(Event.PointerData.X >= 250 && Event.PointerData.X <= 650) && 
			(Event.PointerData.Y >= 190 && Event.PointerData.Y <= 230))
		{
			//Adjust Volume here
			CSoundManagement::GetInstance()->SetMasterVolume(float(float(Event.PointerData.X - 250)/400));
		}
	}
	but_Back2MainMenu->OnControllerEvent(Event);
	but_SoundIsEnable->OnControllerEvent(Event);
	but_SoundIsMuted->OnControllerEvent(Event);
}

void CStateOption::Exit()
{
	CSoundManagement::GetInstance()->Free((char*)"menu_background");
	CImageManager::GetInstance()->Free(PATH_GRAPHIC("WOT_Option.tga"));
	SAFE_DEL(but_Back2MainMenu);
	SAFE_DEL(but_SoundIsEnable);
	SAFE_DEL(but_SoundIsMuted);
	Log("State Option: Exit");	
}
