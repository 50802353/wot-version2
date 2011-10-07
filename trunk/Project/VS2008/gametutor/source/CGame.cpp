#include "CGame.h"
#include "Header.h"
#include "CStateManagement.h"
#include "CDevice.h"
#include "CFpsController.h"
#include "CViewController.h"


namespace GameTutor
{
	CGame::CGame(): m_eStatus(EGSTATUS_NONE), m_eNextStatus(EGSTATUS_INIT)
	{
		SetInstance(this);
	}

	CGame::~CGame()
	{}

	void CGame::Pause()
	{
		m_eNextStatus = EGSTATUS_PAUSED;
	}

	void CGame::Resume()
	{
		m_eNextStatus = EGSTATUS_RUNNING;
	}

	void CGame::Exit()
	{
		if (m_eStatus != EGSTATUS_EXIT && m_eNextStatus != EGSTATUS_EXIT)
		{
			m_eNextStatus = EGSTATUS_CLEANUP;
		}
		
	}

	void CGame::Update()
	{
		if (m_eNextStatus != m_eStatus)
		{
			m_eStatus = m_eNextStatus;
		}
		switch (m_eStatus)
		{
		case EGSTATUS_INIT:
			this->Init();
			m_eNextStatus = EGSTATUS_RUNNING;
			break;
		case EGSTATUS_RUNNING:
		case EGSTATUS_PAUSED:
			CFpsController::GetInstance()->BeginCounter();
			CStateManagement::GetInstance()->Update(m_eStatus == EGSTATUS_PAUSED);
			if (m_eStatus == EGSTATUS_RUNNING)
			{
				CControllerEventManager::GetInstance()->Update();
			}
			CFpsController::GetInstance()->EndCounter();
			break;
		case EGSTATUS_CLEANUP:
			//force clean up current state
			CStateManagement::GetInstance()->SwitchState(0);
			CStateManagement::GetInstance()->Update(false);
			Destroy();
			m_eNextStatus = EGSTATUS_EXIT;
			break;
		default:
			break;
		}
	}

	void CGame::SetEvent(SControllerEvent Event)
	{
		CControllerEventManager::GetInstance()->OnEvent(Event);
		if (!this->OnControllerEvent(Event))
		{
			CState* state = CStateManagement::GetInstance()->GetCurrentState();
			if (state)
			{
				state->OnControllerEvent(Event);
			}
		}
	}
}