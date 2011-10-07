#include "CDevice.h"
#include "CViewController.h"
#include "SGameConfig.h"
#include "CGraphics2D.h"
#include "CFpsController.h"
#include "CStateManagement.h"
#include "CImageManager.h"
#include "CSprite.h"
#include "CControllerEventManager.h"
#include "CAudioPlayer.h"
#include "CText.h"

namespace GameTutor
{
	SGameConfig Configuation;
}
#if CONFIG_PLATFORM==PLATFORM_WIN32_VS
namespace GameTutor
{
	void CDevice::SleepEx(__UINT64 milisec)
	{
		Sleep(DWORD(milisec));
	}

	__UINT64 CDevice::GetTimer()
	{
		return clock();
	}

	void StartApp(SGameConfig cnf)
	{
		//init view
		Configuation = cnf;
		CViewController<VIEWCLASS>::CreateView(cnf.iWidth, cnf.iHeight, cnf.isUseFullScreen, cnf.strTitle);	
		CViewController<VIEWCLASS>::GetInstance()->GetView()->Update();
	}

	void FinalizeApp()
	{
		SAFE_DEL(Configuation.pGame);
		SAFE_DEL(Configuation.pVideoDriver);
		CFpsController::FreeInstance();
		CViewController<VIEWCLASS>::FreeInstance();
		CFileWin32Driver::FreeInstance();
		CStreamDriverBuffer::FreeInstance();
		CDevice::FreeInstance();
		CStateManagement::FreeInstance();
		CGraphics2D::FreeInstance();
		CImageManager::FreeInstance();
		CSpriteDBManagement::FreeInstance();
		CControllerEventManager::FreeInstance();
		CAudioPlayer::FreeInstance();
		CText::FreeInstance();
	}
}

BOOL (WINAPI *doSetConsoleTextAttribute)(HANDLE hConsoleOutput, WORD attr);
inline void *getConsoleFunction(char *name) {
	static HMODULE kernel32=(HMODULE)0xffffffff;
	if(kernel32==0)
	{
		return NULL;
	}
	if(kernel32==(HMODULE)0xffffffff) 
	{
		kernel32=LoadLibrary("kernel32.dll");
		if(kernel32==0)
		{
			return 0; 
		}
	}
	return GetProcAddress(kernel32,name);
}
inline void SetCommandTextColor(WORD color)
{
	HANDLE hCon;
	hCon=GetStdHandle(STD_OUTPUT_HANDLE);
	doSetConsoleTextAttribute=(BOOL (__stdcall *)(HANDLE,WORD))getConsoleFunction("SetConsoleTextAttribute");
	if(doSetConsoleTextAttribute==NULL) 
	{
		return;
	} 
	(*doSetConsoleTextAttribute)(hCon,color);
}

#else // CONFIG_PLATFORM!=PLATFORM_WIN32_VS

namespace GameTutor
{
	CDevice* CDevice::s_pInstance = 0;

	void CDevice::SleepEx(__UINT64 milisec)
	{
		TODO("CDevice::SleepEx for CONFIG_PLATFORM!=PLATFORM_WIN32_VS is not implement yet !");
	}

	__UINT64 CDevice::GetTimer()
	{
		TODO(" CDevice::GetTimer for CONFIG_PLATFORM!=PLATFORM_WIN32_VS is not implement yet !");
		return 0;
	}
}
#endif


