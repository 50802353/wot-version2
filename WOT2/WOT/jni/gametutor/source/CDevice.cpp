#include "CDevice.h"
#include "CViewController.h"
#include "SGameConfig.h"
#include "CGraphics2D.h"
#include "CFpsController.h"
#include "CStateManagement.h"
#include "CImageManager.h"
#include "CSprite.h"
#include "CControllerEventManager.h"

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
		CViewController<VIEWCLASS>::CreateView(cnf.iWidth, cnf.iHeight, cnf.isUseFullScreen, cnf.strTitle);
		CVSView::GetInstance()->SetContext(cnf.esContext);
		CGraphics2D::GetInstance()->SetVideoDriver(cnf.pVideoDriver);
		Configuation = cnf;
		CViewController<VIEWCLASS>::GetInstance()->GetView()->Update1();
		CVSView::GetInstance()->startLoop();
	}

	void FinalizeApp()
	{
		SAFE_DEL(Configuation.pGame);
		SAFE_DEL(Configuation.pVideoDriver);
		delete CFpsController::GetInstance();
		delete CViewController<VIEWCLASS>::GetInstance();
		delete CFileWin32Driver::GetInstance();
		delete CDevice::GetInstance();
		delete CStateManagement::GetInstance();
		delete CGraphics2D::GetInstance();
		delete CImageManager::GetInstance();
		delete CSpriteDBManagement::GetInstance();
		delete CControllerEventManager::GetInstance();
	}
}

BOOL (WINAPI *doSetConsoleTextAttribute)(HANDLE hConsoleOutput, WORD attr);
inline void *getConsoleFunction(char *name) {
	/*static HMODULE kernel32=(HMODULE)0xffffffff;
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
	return GetProcAddress(kernel32,name);*/
}
inline void SetCommandTextColor(WORD color)
{
	/*HANDLE hCon;
	hCon=GetStdHandle(STD_OUTPUT_HANDLE);
	doSetConsoleTextAttribute=(BOOL (__stdcall *)(HANDLE,WORD))getConsoleFunction("SetConsoleTextAttribute");
	if(doSetConsoleTextAttribute==NULL) 
	{
		return;
	} 
	(*doSetConsoleTextAttribute)(hCon,color);*/
}

#elif CONFIG_PLATFORM==PLATFORM_ANDROID
	#ifdef WIN32DEBUG
	#include "c:\DevTools\android-ndk-r6\platforms\android-8\arch-x86\usr\include\sys\time.h"
	#else
	#include <unistd.h>
	#include <time.h>
	#endif




namespace GameTutor
{
	void CDevice::SleepEx(__UINT64 milisec)
	{
		usleep(__UINT64(milisec)*1000);
	}

	__UINT64 CDevice::GetTimer()
	{
		__UINT32 time = __UINT32(clock())/1000;
		Log("Time %lu",time);
		return time;
	}

	void StartApp(SGameConfig cnf)
	{
		//init view
		CViewController<VIEWCLASS>::CreateView(cnf.iWidth, cnf.iHeight, cnf.isUseFullScreen, cnf.strTitle);
		CGraphics2D::GetInstance()->SetVideoDriver(cnf.pVideoDriver);
		Configuation = cnf;
		CViewController<VIEWCLASS>::GetInstance()->GetView()->Update();
	}

	void FinalizeApp()
	{
		SAFE_DEL(Configuation.pGame);
		SAFE_DEL(Configuation.pVideoDriver);
		delete CFpsController::GetInstance();
		delete CViewController<VIEWCLASS>::GetInstance();
		delete CFileWin32Driver::GetInstance();
		delete CDevice::GetInstance();
		delete CStateManagement::GetInstance();
		delete CGraphics2D::GetInstance();
		delete CImageManager::GetInstance();
		delete CSpriteDBManagement::GetInstance();
		delete CControllerEventManager::GetInstance();
	}

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


