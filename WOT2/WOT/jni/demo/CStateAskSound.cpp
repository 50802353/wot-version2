#include "CStateAskSound.h"
#include "CStatePoster.h"
#include "CSoundManagement.h"
#include "CExample.h"

void EnableSound(){
	CSoundManagement::GetInstance()->SetSound(true);
	CStateManagement::GetInstance()->SwitchState(new CStatePoster());
}

void DisableSound(){
	CSoundManagement::GetInstance()->SetSound(false);
	CStateManagement::GetInstance()->SwitchState(new CStatePoster());
}

CStateAskSound::CStateAskSound(): CState()
{}

void CStateAskSound::Init()
{
	Log("State AskSound: Init");
	CImageManager::GetInstance()->AddImage<CFileWin32Driver>(PATH_GRAPHIC("WOT_AskSound.tga"),true);
	Background = CImageManager::GetInstance()->Get(PATH_GRAPHIC("WOT_AskSound.tga"));

	CSoundManagement::GetInstance()->AddSound(PATH_AUDIO("AButtonSelect.wav"), (char*)"Button_Select");

	__UINT32 w = (CViewController<VIEWCLASS>::GetInstance()->GetView()->GetWidth());
	__UINT32 h = (CViewController<VIEWCLASS>::GetInstance()->GetView()->GetHeight());
	but_EnableSound = new CButton(PATH_GRAPHIC("Button_Sprite.tga"),PATH_GRAPHIC("Button_Sprite.tga"));
	but_EnableSound->SetActiveFunction(EnableSound);
	but_EnableSound->SetPosition(SRect<__INT32>(w-220,h-40-65,200,65));
	but_EnableSound->SetRegion(SRect<__INT32>(0,100,160,50));
	but_EnableSound->SetRegionHover(SRect<__INT32>(160,100,160,50));
	but_EnableSound->SetSelectedSound(CSoundManagement::GetInstance()->GetSound((char*)"Button_Select"));

	but_DisableSound = new CButton(PATH_GRAPHIC("Button_Sprite.tga"),PATH_GRAPHIC("Button_Sprite.tga"));
	but_DisableSound->SetActiveFunction(DisableSound);
	but_DisableSound->SetPosition(SRect<__INT32>(20,40,200,65));
	but_DisableSound->SetRegion(SRect<__INT32>(0,50,160,50));
	but_DisableSound->SetRegionHover(SRect<__INT32>(160,50,160,50));
}

void CStateAskSound::Update()
{
}

void CStateAskSound::Render()
{
	__UINT32 w = (CViewController<VIEWCLASS>::GetInstance()->GetView()->GetWidth());
	__UINT32 h = (CViewController<VIEWCLASS>::GetInstance()->GetView()->GetHeight());
	CGraphics2D::GetInstance()->Clear(SColor<float>(0.0f,0.0f,0.0f,1.0f));
	
	CGraphics2D::GetInstance()->DrawImageRegion(SRect<__INT32>(0, 0, w, h),Background,SRect<__INT32>(0,0,800,480));
	but_EnableSound->Draw();
	but_DisableSound->Draw();

	CGraphics2D::GetInstance()->Flush();
}

void CStateAskSound::OnControllerEvent(SControllerEvent Event){
	but_EnableSound->OnControllerEvent(Event);
	but_DisableSound->OnControllerEvent(Event);
}

void CStateAskSound::Exit()
{
	CImageManager::GetInstance()->Free(PATH_GRAPHIC("WOT_AskSound.tga"));
	SAFE_DEL(but_EnableSound);
	SAFE_DEL(but_DisableSound);
	Log("State Logo: Exit");
}
