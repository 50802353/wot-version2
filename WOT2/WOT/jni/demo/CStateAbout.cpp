
#include "CStateAbout.h"
#include "CSoundManagement.h"
#include "CStateMenu.h"


CStateAbout::CStateAbout(): CState()
{}

void CStateAbout::Init()
{
	Log("State Logo: Init");
	CImageManager::GetInstance()->AddImage<CFileWin32Driver>(PATH_GRAPHIC("WOT_About.tga"),true);
	Logo = CImageManager::GetInstance()->Get(PATH_GRAPHIC("WOT_About.tga"));
	Logo->FreeBuffer();

	CSoundManagement::GetInstance()->AddSound(PATH_AUDIO("AIngameBackground.ogg"), (char*)"about_sound");
	A_Background = CSoundManagement::GetInstance()->GetSound((char*)"about_sound");
	A_Background->Play();
}

void CStateAbout::Update()
{	
}

void CStateAbout::Render()
{
	__UINT32 w = (CViewController<VIEWCLASS>::GetInstance()->GetView()->GetWidth());
	__UINT32 h = (CViewController<VIEWCLASS>::GetInstance()->GetView()->GetHeight());

	CGraphics2D::GetInstance()->Clear(SColor<float>(0.0f,0.0f,0.0f,1.0f));	
	CGraphics2D::GetInstance()->DrawImageRegion(SRect<__INT32>(0, 0, w, h),Logo,SRect<__INT32>(0,0,800,480));	
	CGraphics2D::GetInstance()->Flush();
}

void CStateAbout::OnControllerEvent(SControllerEvent Event){
	CStateManagement::GetInstance()->SwitchState(new CStateMenu());
}

void CStateAbout::Exit()
{
	CSoundManagement::GetInstance()->Free((char*)"about_sound");
	CImageManager::GetInstance()->Free(PATH_GRAPHIC("WOT_About.tga"));
	Log("State Logo: Exit");	
}
