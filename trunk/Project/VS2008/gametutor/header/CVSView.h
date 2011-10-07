#ifndef __CVSVIEW_H__
#define __CVSVIEW_H__

#include "Header.h"
#include "CSingleton.h"
#if (CONFIG_PLATFORM==PLATFORM_WIN32_VS)

namespace GameTutor
{
	class CVSView: public CAbsSingleton<CVSView>
	{
	public:
		CVSView(__INT32 w, __INT32 h, bool fullscreen = false, const char*name = 0);
		virtual ~CVSView();
		void Update();
		__INT32 GetWidth() {return m_iWidth;}
		__INT32 GetHeight() {return m_iHeight;}
		__INT32 IsFullScreen() {return m_isFullScreen;}
		
	private:
		__INT32 m_iWidth;
		__INT32 m_iHeight;
		bool m_isFullScreen;
		char *m_strTitle;
		void InitClientWindow();
		void Destroy();

	public:
		HGLRC m_hGLRC;
		HWND m_hwndWindow;
		HDC m_hGameWndDC;
		static LRESULT CALLBACK WndProc( HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam );

	//Open GL porting
	private: 
		void InitGL();
		void RefreshGL();

	private:
		bool m_isLeftMouseDown;
		bool m_isKeyDown;
	};
}

#endif //(CONFIG_PLATFORM==PLATFORM_WIN32_VS)
#endif