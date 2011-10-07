#ifndef __CIVIDEODRIVER_H__
#define __CIVIDEODRIVER_H__

#include "Header.h"
#include "CSingleton.h"

namespace GameTutor
{
	enum EVideoDriver
	{
		EVIDEO_DRIVER_OGLPIPELINE,
		EVIDEO_DRIVER_OGLES2
	};
	class IVideoDriver
	{
	public:
		IVideoDriver(EVideoDriver driver)
		{
			m_CIVideoDriver = driver;
		}
		bool IsVideoDriver(EVideoDriver driver) {return m_CIVideoDriver == driver;}
		virtual void PrintInfomation() = 0;
		virtual __UINT32 GetError() = 0;
	protected:
		EVideoDriver m_CIVideoDriver;
	};
}
#endif