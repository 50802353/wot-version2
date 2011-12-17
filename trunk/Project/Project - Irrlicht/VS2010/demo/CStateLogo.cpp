#include "CStateLogo.h"
#include "CStateIngame.h"

#define LOGO_WAV "./resource/ALogo.wav"

CStateLogo::CStateLogo(): CState()
{}

void CStateLogo::Init()
{
	Logo = driver->getTexture("./resource/Logo.jpg");
	core::rect<s32> vp = driver->getViewPort();
	screen = guienv->addImage(vp, 0, -1, L"");
	screen->setImage(Logo);
	screen->setScaleImage(true);

	Log("State Logo: Init");
	CAudioPlayer::GetInstance()->Load<CFileWin32Driver>(LOGO_WAV);
	CAudioPlayer::GetInstance()->Play(LOGO_WAV,false);
}

void CStateLogo::Update()
{	
	if (!CAudioPlayer::GetInstance()->IsPlaying(LOGO_WAV))
		CStateManagement::GetInstance()->SwitchState(new CStateIngame());
	if (CControllerKeyManager::GetInstance()->WasAnyKeyRelease())
		CStateManagement::GetInstance()->SwitchState(new CStateIngame());
	core::rect<s32> vp = driver->getViewPort();
	if (CControllerPointerManager::GetInstance()->WasReleaseInside(0,0,vp.getWidth(),vp.getHeight()))
		CStateManagement::GetInstance()->SwitchState(new CStateIngame());
}

void CStateLogo::Render()
{
}

void CStateLogo::Exit()
{
	Log("State Logo: Exit");	
	screen->remove();
	if (CAudioPlayer::GetInstance()->IsPlaying(LOGO_WAV))
		CAudioPlayer::GetInstance()->Stop(LOGO_WAV);
}
