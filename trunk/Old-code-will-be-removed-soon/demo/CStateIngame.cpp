
#include "CStateIngame.h"
#include "CStateMainMenu.h"

CStateIngame::CStateIngame():isIngamePause(false), CState()
{}

void CStateIngame::Init()
{
	Log("---");
	Log("State Ingame: Init");
	Log("[Press space to open Ingame_Menu]");
	Log("[Press Q while IngameMenu is opening to back to Main Menu]");
	//Ingame state


	isIngamePause = false;
}

void CStateIngame::Update()
{

}

void CStateIngame::OnControllerEvent(SControllerEvent Event)
{
	if (Event.Type == ECE_KEY && Event.KeyData.Event == EKE_PRESSED && Event.KeyData.KeyCode == EKEY_SPACE)
	{
		if (!isIngamePause)
		{
			Log("State Ingame: Open Ingame Menu");
			isIngamePause=!isIngamePause;
		}
		else
		{
			Log("State Ingame: Close Ingame Menu");
			isIngamePause=!isIngamePause;
		}
		//CStateManagement::GetInstance()->SwitchState(new CStateIngameMenu());
	}
	else if (Event.Type == ECE_KEY && Event.KeyData.Event == EKE_PRESSED && Event.KeyData.KeyCode == EKEY_WIN_Q)
	{
		if (isIngamePause)
		{
			Log("State Ingame: Back to Main Menu");
			CStateManagement::GetInstance()->SwitchState(new CStateMainMenu());
		}
	}
}

void CStateIngame::Render()
{
}

void CStateIngame::Exit()
{
	Log("State Ingame: Exit");
}
