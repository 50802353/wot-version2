#ifndef __CSTATEMANAGEMENT_H__
#define __CSTATEMANAGEMENT_H__
#include "CState.h"
#include "CSingleton.h"
namespace GameTutor
{
	class CStateManagement: public CSingleton<CStateManagement>
	{
		friend class CSingleton<CStateManagement>;
	protected:
		CStateManagement():m_pCurrentState(0), m_pNextState(0) {}
	protected:
		CState* m_pCurrentState;
		CState* m_pNextState;
	public:
		void Update(bool isPause);
		void SwitchState(CState* nextState);
		CState* GetCurrentState() {return m_pCurrentState;}
	};
}
#endif