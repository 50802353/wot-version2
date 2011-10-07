#include "CStateManagement.h"
#include "CControllerEventManager.h"
#include "CParticleManager.h"
#include "CGame.h"

namespace GameTutor
{
	void CStateManagement::Update(bool isPause)
	{
		// check if need switch state
		if (m_pCurrentState != m_pNextState)
		{
			if (m_pCurrentState) 
			{
				m_pCurrentState->Exit();
				delete m_pCurrentState;
			}
			CControllerPointerManager::GetInstance()->Reset();
			CControllerKeyManager::GetInstance()->Reset();
			if (m_pNextState) 
			{
				m_pNextState->Init();
			}
			m_pCurrentState = m_pNextState;
			CControllerPointerManager::GetInstance()->Reset();
			CControllerKeyManager::GetInstance()->Reset();
			CGame::GetInstance()->isListenEvent = true;
		}

		//update state
		if (m_pCurrentState)
		{
			if (!isPause)
			{
				m_pCurrentState->Update();
				CParticleManager::GetInstance()->Update();
			}
			
			m_pCurrentState->Render();			
		}
	}

	void CStateManagement::SwitchState(CState* nextState)
	{
		m_pNextState = nextState;
		CGame::GetInstance()->isListenEvent = false;
	}
}