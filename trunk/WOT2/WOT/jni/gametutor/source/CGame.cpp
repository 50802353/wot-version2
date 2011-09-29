#include "CGame.h"
#include "Header.h"
#include "CStateManagement.h"
#include "CDevice.h"
#include "CFpsController.h"
#include "CViewController.h"



namespace GameTutor
{

	bool CGame::isListenEvent = true;

	CGame::CGame(): m_eStatus(EGSTATUS_NONE), m_eNextStatus(EGSTATUS_INIT), m_eSoundStatus(EGSTATUS_PLAY_SOUND)
	{
		SetInstance(this);
	}

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
		//Log("CGame befor process %d %d",Event.PointerData.Y,VIEWCLASS::GetInstance()->GetHeight());
		Event.PointerData.Y =VIEWCLASS::GetInstance()->GetHeight() - abs(Event.PointerData.Y);
		Log("CGame event %d %d",Event.PointerData.X,Event.PointerData.Y);
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

	void CGame::SetSound(bool EnableSound){
		if (EnableSound) {
			Log ("Global: Turn on Sound");
			m_eSoundStatus = EGSTATUS_PLAY_SOUND;
		}
		else {
			Log("Global: Turn off Sound");
			m_eSoundStatus = EGSTATUS_NO_SOUND;
		}
	}

}