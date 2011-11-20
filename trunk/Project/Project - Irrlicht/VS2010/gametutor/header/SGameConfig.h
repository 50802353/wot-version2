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
		irr::IrrlichtDevice *pVideoDevice;
		CAudioDriver *pAudioDriver;
		CGame* pGame;
	};
}

#endif