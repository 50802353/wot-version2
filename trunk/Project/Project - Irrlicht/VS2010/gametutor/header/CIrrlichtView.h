#ifndef __CVSVIEW_H__
#define __CVSVIEW_H__



#include "Header.h"
#include "CSingleton.h"
#include "CControllerEventManager.h"
#include "CGame.h"
#include "SGameConfig.h"

namespace GameTutor
{
	extern SGameConfig Configuation;
	//extern class CGame;
	class MyEventReceiver : public irr::IEventReceiver
	{
	public:
		virtual bool OnEvent(const irr::SEvent& event);		
		MyEventReceiver();
	};
	


	class CIrrlichtView: public CAbsSingleton<CIrrlichtView>
	{
	public:
		CIrrlichtView(__INT32 w, __INT32 h, irr::IrrlichtDevice* &Irrlichtdevice, bool fullscreen = false, const char*name = 0);
		virtual ~CIrrlichtView();
		void Update();
		__INT32 GetWidth() {return m_iWidth;}
		__INT32 GetHeight() {return m_iHeight;}
		__INT32 IsFullScreen() {return m_isFullScreen;}
		
	private:
		__INT32 m_iWidth;
		__INT32 m_iHeight;
		bool m_isFullScreen;
		char *m_strTitle;
		void InitClientWindow(irr::IrrlichtDevice *&IrrlichtDevice);
		void Destroy();
		MyEventReceiver* receiver;

	public:
		HGLRC m_hGLRC;
		HWND m_hwndWindow;
		HDC m_hGameWndDC;
		static LRESULT CALLBACK WndProc( HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam );

	public: 
		irr::IrrlichtDevice *device;

	public:
		bool m_isLeftMouseDown;
		bool m_isKeyDown;
	};
}

#endif