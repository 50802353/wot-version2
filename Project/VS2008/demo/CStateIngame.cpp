
#include "CStateIngame.h"

CStateIngame::CStateIngame():CState()
{}

void CStateIngame::Init()
{
	Log("State Ingame: Init");
}

void CStateIngame::Update()
{
}

void CStateIngame::Render()
{
	//Log("State Ingame: Fps = %d FrameDT = %d", CFpsController::GetInstance()->GetRuntimeFps(), CFpsController::GetInstance()->GetFrameDt());
}

void CStateIngame::Exit()
{
	Log("State Ingame: Exit");
}
