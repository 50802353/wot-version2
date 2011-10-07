
#include "CStateMainMenu.h"
#include "CStateIngame.h"
#include "CStateAbout.h"
#include "CStateOption.h"

CStateMainMenu::CStateMainMenu():m_iCount(0), CState()
{}

void CStateMainMenu::Init()
{
	Log("---");
	Log("State MainMenu: Init");
	Log("[Click top left corner to switch into Ingame state]");
	Log("[      top right                      Option      ]");
	Log("[      bottom left                    About       ]");
	Log("[      bottom right                   Exit        ]");
	m_iCount = 0;
}

void CStateMainMenu::Update()
{
	int w = VIEWCLASS::GetInstance()->GetWidth();
	int h = VIEWCLASS::GetInstance()->GetHeight();
	if (CControllerPointerManager::GetInstance()->WasReleaseInside(0, 0, w/2, h/2))
	{
		Log("State MainMenu: Chose Menu_Play");
		CStateManagement::GetInstance()->SwitchState(new CStateIngame());
	}
	else if (CControllerPointerManager::GetInstance()->WasReleaseInside(w/2, 0, w, h/2))
	{
		Log("State MainMenu: Chose Menu_About");
		CStateManagement::GetInstance()->SwitchState(new CStateAbout());
	}
	else if (CControllerPointerManager::GetInstance()->WasReleaseInside(0, h/2, w/2, h))
	{
		Log("State MainMenu: Chose Menu_Option");
		CStateManagement::GetInstance()->SwitchState(new CStateOption());
	}
	else if (CControllerPointerManager::GetInstance()->WasReleaseInside(w/2, h/2, w, h))
	{
		Log("State MainMenu: Chose Menu_Quit");
		CGame::GetInstance()->Exit();
	}

}

void CStateMainMenu::Render()
{
	//Do nothing
}

void CStateMainMenu::Exit()
{
	Log("State MainMenu: Exit");
}
