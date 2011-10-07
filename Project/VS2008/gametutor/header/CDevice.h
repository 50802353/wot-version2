#ifndef __CDEVICE_H__
#define __CDEVICE_H__

#include "Header.h"
#include "SGameConfig.h"
#include "CSingleton.h"

namespace GameTutor
{
	struct SGameConfig;
	class CDevice: public CSingleton<CDevice>
	{
		friend class CSingleton<CDevice>;
	public:
		virtual ~CDevice(void) {}
	
	public:
		void SleepEx(__UINT64 milisec);
		__UINT64 GetTimer();
	protected:
		CDevice() {}
	};

#if CONFIG_PLATFORM==PLATFORM_WIN32_VS
	void StartApp(SGameConfig cnf);
	void FinalizeApp();
#endif
}
#endif