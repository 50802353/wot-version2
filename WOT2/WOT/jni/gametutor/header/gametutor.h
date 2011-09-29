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
//#include "CGLPipelineDriver.h"
#include "CGLES2Driver.h"
#include "CGraphics2D.h"
#include "CSkyBox.h"

#include "Stream.h"
#include "CImage.h"
#include "IVideoDriver.h"
#include "CSprite.h"
#include "SoundDriver.h"

#include "CControllerEventManager.h"
#include "Utils.h"

#include "CStringBufferStream.h"
#include "CToken.h"
#include "Matrix.h"
#include "vec3f.h"

#include "CLookupTableStr.h"
#include "CLookupTableI.h"
#include "CList.h"
#include "MyParticleSystem.h"
#include "CParticleManager.h"
#include "CDropdownButton.h"


#include "CButton.h"

#if CONFIG_PLATFORM==PLATFORM_WIN32_VS
#	pragma comment(lib, "gametutor.lib")
#endif

using namespace GameTutor;
extern SGameConfig Configuation;
#endif