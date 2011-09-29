
#include "CStateAbout.h"
#include "CStateMainMenu.h"

CStateAbout::CStateAbout():m_iCount(0), CState()
{}

void CStateAbout::Init()
{
	Log("---");
	Log("State About: Init");
	Log("[Press any key to go back Main Menu, or wait a short time]");
	//Display About screen

	m_iCount = 0;
}

void CStateAbout::Update()
{
	m_iCount++;
	if (m_iCount >= 100)
	{
		CStateManagement::GetInstance()->SwitchState(new CStateMainMenu());
	}
}


void CStateAbout::OnControllerEvent(SControllerEvent Event)
{
	if (Event.Type == ECE_KEY && Event.KeyData.Event == EKE_PRESSED)
	{
		CStateManagement::GetInstance()->SwitchState(new CStateMainMenu());
	}
}


void CStateAbout::Render()
{
	//Do nothing
}

void CStateAbout::Exit()
{
	Log("State About: Exit");
}
