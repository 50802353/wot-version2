#ifndef __SGAMECONFIG_H__
#define __SGAMECONFIG_H__

#include "Header.h"

namespace GameTutor
{
	class CAudioDriver;
	class CGame;
	class IVideoDriver;
	struct SGameConfig
	{
		__UINT16 iWidth;
		__UINT16 iHeight;
		bool isUseFullScreen;
		const char *strTitle;
		IVideoDriver *pVideoDriver;
		CAudioDriver *pAudioDriver;
		CGame* pGame;
	};
}

#endif