#include "CDevice.h"
#include "CViewController.h"
#include "SGameConfig.h"
#include "CFpsController.h"
#include "CStateManagement.h"
#include "CControllerEventManager.h"
#include "CAudioPlayer.h"
#include "Stream.h"

namespace GameTutor
{
	SGameConfig Configuation;
}

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
		CViewController::CreateView(cnf.iWidth, cnf.iHeight, Configuation.pVideoDevice, cnf.isUseFullScreen, cnf.strTitle);	
		CViewController::GetInstance()->GetView()->Update();
	}

	void FinalizeApp()
	{
		SAFE_DEL(Configuation.pGame);
		//SAFE_DEL(Configuation.pVideoDriver);
		CFpsController::FreeInstance();
		CViewController::FreeInstance();
		CFileWin32Driver::FreeInstance();
		CStreamDriverBuffer::FreeInstance();
		CDevice::FreeInstance();
		CStateManagement::FreeInstance();
		CControllerEventManager::FreeInstance();
		CAudioPlayer::FreeInstance();
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



