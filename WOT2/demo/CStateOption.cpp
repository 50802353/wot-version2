
#include "CStateOption.h"
#include "CStateMainMenu.h"

CStateOption::CStateOption():CState()
{}

void CStateOption::Init()
{
	Log("---");
	Log("State Option: Init");
	Log("[Press any key to go back Main Menu]");
	//Display Option screen
}

void CStateOption::Update()
{
}


void CStateOption::OnControllerEvent(SControllerEvent Event)
{
	if (Event.Type == ECE_KEY && Event.KeyData.Event == EKE_PRESSED)
	{
		CStateManagement::GetInstance()->SwitchState(new CStateMainMenu());
	}
}


void CStateOption::Render()
{
	//Do nothing
}

void CStateOption::Exit()
{
	Log("State Option: Exit");
}
