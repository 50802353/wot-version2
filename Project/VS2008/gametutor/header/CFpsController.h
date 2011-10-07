#ifndef __CFPSCONTROLLER_H__
#define __CFPSCONTROLLER_H__

#include "Header.h"
#include "CSingleton.h"

#define DEFAULT_LIMIT_FPS 25
namespace GameTutor
{
	class CFpsController: public CSingleton<CFpsController>
	{
		friend class CSingleton<CFpsController>;
	public:
		virtual ~CFpsController(){}
		
		void SetLimitFps(__UINT32 limitFps);
		void BeginCounter();
		void EndCounter();

		__INT32 GetFrameDt() {return m_iFrameDt;}
		__INT32 GetRuntimeFps() {return (m_iFrameDt)?__INT32(1000/m_iFrameDt):0;}

	protected:
		CFpsController(): m_iLimitFps(0), m_iLimitFrameDt(0), 
			m_iStartTime(0), m_iFrameDt(0)
		{
			SetLimitFps(DEFAULT_LIMIT_FPS);
		}
	protected:
		__INT32 m_iLimitFps;
		__INT32 m_iLimitFrameDt;	
		__INT32 m_iFrameDt;
	private:
		__UINT64 m_iStartTime;
	};
}

#endif