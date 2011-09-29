#include "CExample.h"
#include "CStateLogo.h"
#include "CStateIngame.h"
#include "CStateMenu.h"
#include "CStateChooseLevel.h"

float CExample::m_fMasterVolume = 0.5;
__UINT16 CExample::m_LevelUnlocked;
__UINT16 CExample::m_LevelChose;

void CExample::Init()
{
	CExample::m_LevelUnlocked = 1;
	CStateManagement::GetInstance()->SwitchState(new CStateLogo());
	Log("Init");
}

void CExample::Destroy()
{
	Log("Destroy my Game");
}

