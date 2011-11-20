#ifndef __CGAME_H__
#define __CGAME_H__
#include "Header.h"
#include "CSingleton.h"
#include "CControllerEventManager.h"
namespace GameTutor
{
	enum EGameStatus {
		EGSTATUS_NONE = -1,
		EGSTATUS_INIT = 0,
		EGSTATUS_RUNNING,
		EGSTATUS_PAUSED,
		EGSTATUS_CLEANUP,
		EGSTATUS_EXIT,
	};

	class CGame: public CAbsSingleton<CGame>
	{
		friend class CVSView;
	public:
		virtual ~CGame();
		virtual void Update();
		virtual void Exit();
		virtual void Pause();
		virtual void Resume();
		virtual bool OnControllerEvent(SControllerEvent Event) {return false;}
		bool IsAlive() {return (m_eStatus != EGSTATUS_EXIT);}
		bool IsPause() {return (m_eStatus == EGSTATUS_PAUSED);}
		void SetEvent(SControllerEvent Event);
	protected:
		CGame();
		virtual void Init() = 0;
		virtual void Destroy() = 0;
		
	protected:
		enum EGameStatus m_eStatus;
		enum EGameStatus m_eNextStatus;
	};
}

#endif