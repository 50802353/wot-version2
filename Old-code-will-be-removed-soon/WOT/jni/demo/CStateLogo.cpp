#include "CStateLogo.h"
#include "CSoundManagement.h"
#include "CStateAskSound.h"

CStateLogo::CStateLogo(): CState()
{}

void CStateLogo::Init()
{
	Log("State Logo: Init");
	CImageManager::GetInstance()->AddImage<CFileWin32Driver>(PATH_GRAPHIC("WOT_Logo.tga"),true);
	Logo = CImageManager::GetInstance()->Get(PATH_GRAPHIC("WOT_Logo.tga"));
	Logo->FreeBuffer();

	CSoundManagement::GetInstance()->AddSound(PATH_AUDIO("ALogo.wav"), (char*)"logo_sound");
	A_Background = CSoundManagement::GetInstance()->GetSound((char*)"logo_sound");
	A_Background->Play();
}

void CStateLogo::Update()
{	
	if (A_Background->GetPlayStatus() != AL_PLAYING)
	{
		CStateManagement::GetInstance()->SwitchState(new CStateAskSound());
	}
}

void CStateLogo::Render()
{
	__UINT32 w = (CViewController<VIEWCLASS>::GetInstance()->GetView()->GetWidth());
	__UINT32 h = (CViewController<VIEWCLASS>::GetInstance()->GetView()->GetHeight());

	CGraphics2D::GetInstance()->Clear(SColor<float>(0.0f,0.0f,0.0f,1.0f));	
	CGraphics2D::GetInstance()->DrawImageRegion(SRect<__INT32>(0, 0, w, h),Logo,SRect<__INT32>(0,0,800,480));	
	CGraphics2D::GetInstance()->Flush();
}

void CStateLogo::OnControllerEvent(SControllerEvent Event){
	////Change state when touched
	//if ((Event.Type == ECE_POINTER) && (Event.PointerData.Event == EPE_DRAGGED))
	//{
	//	A_Background->Pause();
	//	CStateManagement::GetInstance()->SwitchState(new CStateAskSound());
	//}
}

void CStateLogo::Exit()
{
	CSoundManagement::GetInstance()->Free((char*)"logo_sound");
	CImageManager::GetInstance()->Free(PATH_GRAPHIC("WOT_Logo.tga"));
	Log("State Logo: Exit");	
}
