#ifndef __GAMETUTOR_H__
#define __GAMETUTOR_H__

#include "Header.h"
#include "CDevice.h"
#include "CFpsController.h"
#include "CGame.h"
#include "Config.h"
#include "CState.h"
#include "CStateManagement.h"
#include "CViewController.h"
#include "CVSView.h"
#include "SGameConfig.h"
#include "SGraphics.h"
#include "CGLPipelineDriver.h"
#include "CGraphics2D.h"
#include "Utils.h"
#include "Stream.h"
#include "CImage.h"
#include "IVideoDriver.h"
#include "CSprite.h"
#include "CStringBufferStream.h"
#include "CToken.h"
#include "CControllerEventManager.h"
#include "CLookupTableStr.h"
#include "CLookupTableI.h"
#include "CList.h"
#include "CAudioPlayer.h"
#include "CFont.h"
#include "CCompressor.h"
#include "CText.h"

#if CONFIG_PLATFORM==PLATFORM_WIN32_VS
#	pragma comment(lib, "gametutor.lib")
#endif

using namespace GameTutor;
extern SGameConfig Configuation;
#endif