#ifndef __SGAMECONFIG_H__
#define __SGAMECONFIG_H__

#include "Header.h"
#include "CGame.h"
#include "IVideoDriver.h"

namespace GameTutor
{
	class CGame;
	class IVideoDriver;
	struct SGameConfig
	{
		__UINT16 iWidth;
		__UINT16 iHeight;
		bool isUseFullScreen;
		const char *strTitle;
		IVideoDriver *pVideoDriver;
		CGame* pGame;
#if CONFIG_PLATFORM==PLATFORM_WIN32_VS
		ESContext *esContext;
#endif
	};
}

#endif