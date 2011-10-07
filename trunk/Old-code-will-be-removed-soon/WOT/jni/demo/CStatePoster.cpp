#include "CStatePoster.h"
#include "CStateMenu.h"
#include "CSoundManagement.h"
#include "CExample.h"

CStatePoster::CStatePoster(): CState()
{
}

void CStatePoster::Init()
{
	Log("State Poster: Init");
	
	CImageManager::GetInstance()->AddImage<CFileWin32Driver>(PATH_GRAPHIC("WOT_Poster.tga"),true);
	Background = CImageManager::GetInstance()->Get(PATH_GRAPHIC("WOT_Poster.tga"));

	CSoundManagement::GetInstance()->AddSound(PATH_AUDIO("APosterBackground.ogg"),(char*)"Poster_background");
	A_Background = CSoundManagement::GetInstance()->GetSound((char*)"Poster_background");
	A_Background->SetLoop(true);
	A_Background->Play();
}

void CStatePoster::Update()
{
}

void CStatePoster::OnControllerEvent(SControllerEvent Event)
{	
	A_Background->Pause();
	if ((Event.Type == ECE_POINTER) && (Event.PointerData.Event == EPE_RELEASED))
	{
		CStateManagement::GetInstance()->SwitchState(new CStateMenu());
	}	
}

void CStatePoster::Render()
{
	int w = VIEWCLASS::GetInstance()->GetWidth();
	int h = VIEWCLASS::GetInstance()->GetHeight();
	CGraphics2D::GetInstance()->Clear(SColor<float>(0.0f, 0.0f, 0.0f, 1.0f));
	CGraphics2D::GetInstance()->DrawImageRegion(SRect<__INT32>(0, 0, w, h),Background,SRect<__INT32>(0,0,800,480));	
	CGraphics2D::GetInstance()->Flush();
}

void CStatePoster::Exit()
{
	CSoundManagement::GetInstance()->Free((char*)"Poster_background");
	CImageManager::GetInstance()->Free(PATH_GRAPHIC("WOT_Poster.tga"));
	Log("State Poster: Exit");
}
