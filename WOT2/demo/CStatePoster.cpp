#include "CStatePoster.h"
#include "CStateMainMenu.h"

CStatePoster::CStatePoster(): CState()
{
}

void CStatePoster::Init()
{
	Log("---");
	Log("State Poster: Init");	
	Log("[Press any key to continue]");	
	//Display a picture or a animation of the game


	CGraphics2D::GetInstance()->Reset();

	CSpriteDBManagement::GetInstance()->AddSpriteDBFromTextFile<CFileWin32Driver>("test.txt");

	
	spr = new CSprite(CSpriteDBManagement::GetInstance()->Get("test.txt"));
	spr->SetAnimation("XYZ", -1);
	spr->SetPosition(SPosition2D<__INT32>(0, 0));


	//pic->LoadTGA(
}

void CStatePoster::Update()
{
	spr->UpdateAnimation(CFpsController::GetInstance()->GetFrameDt());
	int w = VIEWCLASS::GetInstance()->GetWidth();
	int h = VIEWCLASS::GetInstance()->GetHeight();
	if (CControllerPointerManager::GetInstance()->WasReleaseInside(0, 0, w, h))
	{
		spr->SetAnimation("XYZ", 100);
	}
}

void CStatePoster::OnControllerEvent(SControllerEvent Event)
{
	if (Event.Type == ECE_KEY && Event.KeyData.Event == EKE_PRESSED)
	{
		CStateManagement::GetInstance()->SwitchState(new CStateMainMenu());
	}
}

void CStatePoster::Render()
{
	CGraphics2D::GetInstance()->Clear(SColor<float>(0, 0, 0, 1));
	spr->RenderAnimation(CGraphics2D::GetInstance());
	CGraphics2D::GetInstance()->Flush();
}

void CStatePoster::Exit()
{
	Log("State Poster: Exit");
	SAFE_DEL(spr);
	CSpriteDBManagement::GetInstance()->Free("test.txt");
}
