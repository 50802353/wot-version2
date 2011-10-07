#include "CFpsController.h"
#include "CDevice.h"

namespace GameTutor
{
	void CFpsController::SetLimitFps(__UINT32 limitFps) 
	{
		m_iLimitFps = limitFps;
		m_iLimitFrameDt = 1000/limitFps;
	}

	void CFpsController::BeginCounter()
	{
		m_iStartTime = CDevice::GetInstance()->GetTimer();
	}

	void CFpsController::EndCounter()
	{
		__UINT64 Endtime = CDevice::GetInstance()->GetTimer();
		__INT32 Dt = __INT32(Endtime - m_iStartTime);
		if (Dt < m_iLimitFrameDt)
		{
			m_iFrameDt = m_iLimitFrameDt;
			CDevice::GetInstance()->SleepEx(m_iLimitFrameDt - Dt);
		}
		else
		{
			m_iFrameDt = Dt;
			CDevice::GetInstance()->SleepEx(1);
		}

	}
}
