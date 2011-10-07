#include "CVSView.h"
#include "CGame.h"
#include "CDevice.h"
#if (CONFIG_PLATFORM==PLATFORM_WIN32_VS)

namespace GameTutor
{
	//---------------------------------------------------------------------------
	// Constructor
	//---------------------------------------------------------------------------

	//CVSView::CVSView(int w, int h, bool fullscreen, const char*name):m_iWidth(w), 
	//	m_iHeight(h), m_isFullScreen(false),
	//	m_hGLRC(0), m_hwndWindow(0), m_hGameWndDC(0)
	//{
	//	SetInstance(this);
	//	if (name)
	//	{
	//		m_strTitle = new char[strlen(name) + 1];
	//		memcpy(m_strTitle, name, strlen(name) + 1);
	//	}
	//	else
	//	{
	//		char *xname = "Untitle";
	//		m_strTitle = new char[strlen(xname) + 1];
	//		memcpy(m_strTitle, xname, strlen(xname) + 1);
	//	}
	//	InitClientWindow();
	//}
	CVSView::CVSView(int w, int h, bool fullscreen, const char*name):m_iWidth(w), 
		m_iHeight(h), m_isFullScreen(false)
		{
		if (name)
		{
			m_strTitle = new char[strlen(name) + 1];
			memcpy(m_strTitle, name, strlen(name) + 1);
		}
		else
		{
			char *xname = "Untitle";
			m_strTitle = new char[strlen(xname) + 1];
			memcpy(m_strTitle, xname, strlen(xname) + 1);
		}
		this->s_pSingletonInstance = this;
	}

	//---------------------------------------------------------------------------
	// Destructor
	//---------------------------------------------------------------------------
	CVSView::~CVSView()
	{
		Destroy();
		delete m_strTitle;
	}

	void UpdateFunc(ESContext* esContext, float time)
	{
		CGame* a = CGame::GetInstance();
		CGame::GetInstance()->Update();
		if (!CGame::GetInstance()->IsAlive())
			{
				CGame::GetInstance()->Exit();
				SendMessageA(esContext->hWnd, WM_CLOSE, 0, 0);
				//eglDestroyContext(esContext->eglDisplay, esContext->eglSurface);

				return;
			}
		eglSwapBuffers(esContext->eglDisplay, esContext->eglSurface);
	}



	void CVSView::startLoop() {
		esRegisterUpdateFunc(esContext, UpdateFunc);
		esMainLoop ( esContext );
	}

	void CVSView::onPaint(ESContext *esContext) {
		/*CGame::GetInstance()->Update();
		if (!CGame::GetInstance()->IsAlive())
			{
				CGame::GetInstance()->Exit();

				
				SendMessage( esContext->hWnd, WM_DESTROY, 0, 0 );
				
				return;
			}*/
		//eglSwapBuffers ( esContext->eglDisplay, esContext->eglSurface );
	}

	void CVSView::onKey(ESContext *esContext, unsigned char key, int x, int y) {
		printf("Pressed: %c\n",key);
	}
	void CVSView::onTouchDown(ESContext *esContext, int x, int y) {
		if (!CVSView::GetInstance()) return;
		printf("Clicked at: %d, %d\n",x,y);
		SControllerEvent Event;
		CVSView::GetInstance()->m_isLeftMouseDown = true;
		Event.Type = ECE_POINTER;
		Event.PointerData.Event = EPE_PRESSED;
		Event.PointerData.ID = 0;
		Event.PointerData.X = x;
		Event.PointerData.Y = y;
		CGame::GetInstance()->SetEvent(Event);
	}
	void CVSView::onTouchUp(ESContext *esContext, int x, int y) {
		if (!CVSView::GetInstance()) return;
		printf("Up at: %d, %d\n",x,y);
		SControllerEvent Event;
		if (CVSView::GetInstance()->m_isLeftMouseDown)
		{
			CVSView::GetInstance()->m_isLeftMouseDown = false;
			Event.Type = ECE_POINTER;
			Event.PointerData.Event = EPE_RELEASED;
			Event.PointerData.ID = 0;
			Event.PointerData.X = x;
			Event.PointerData.Y = y;
			CGame::GetInstance()->SetEvent(Event);
		}
	}
	void CVSView::onTouchMove(ESContext *esContext, WPARAM wparam, int x, int y) {
		if (!CVSView::GetInstance()) return;
		SControllerEvent Event;
		Event.Type = ECE_POINTER;
			Event.PointerData.ID = 0;
			if(wparam == MK_LBUTTON)
			{				
				Event.PointerData.Event = EPE_DRAGGED;
				Event.PointerData.X = x;
				Event.PointerData.Y = y;
				CGame::GetInstance()->SetEvent(Event);
			}
			else
			{
				if (CVSView::GetInstance()->m_isLeftMouseDown)
				{
					Event.PointerData.Event = EPE_RELEASED;					
					Event.PointerData.X = x;
					Event.PointerData.Y = y;
					CVSView::GetInstance()->m_isLeftMouseDown = false;
					CGame::GetInstance()->SetEvent(Event);
				}
			}
	}
	//---------------------------------------------------------------------------
	// Init win32 client window
	//---------------------------------------------------------------------------
	void CVSView::SetContext(ESContext *e)
	{
		esContext = e;
	}

	//---------------------------------------------------------------------------
	// update win32 message
	//---------------------------------------------------------------------------
	void CVSView::Update1() {
		this->Update(esContext);
	}

	

	void CVSView::Update(ESContext *esContext)
	{
		CGame::GetInstance()->Update();
		if (!CGame::GetInstance()->IsAlive())
			{
				CGame::GetInstance()->Exit();
				eglDestroyContext(esContext->eglDisplay, esContext->eglSurface);
				return;
			}
		RefreshGL();

		//while (true)
		//{
		//	// handle win32 message
		//	MSG msg;
		//	if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		//	{
		//		TranslateMessage(&msg);
		//		if (msg.hwnd == m_hwndWindow)
		//		{
		//			WndProc(m_hwndWindow, msg.message, msg.wParam, msg.lParam);
		//		}
		//	}
		//	CGame::GetInstance()->Update();
		//	if (!CGame::GetInstance()->IsAlive())
		//	{
		//		DestroyWindow(m_hwndWindow);
		//		return;
		//	}
		//	RefreshGL();
		//	DispatchMessage(&msg);
		//}
	}

	//---------------------------------------------------------------------------
	// Destroy win32 window
	//---------------------------------------------------------------------------
	void CVSView::Destroy()
	{
		//if (m_isFullScreen)
		//{
		//	ChangeDisplaySettings(NULL, 0);
		//}
	}


	//---------------------------------------------------------------------------
	// Win32 Message Callback
	//---------------------------------------------------------------------------
	//LRESULT CALLBACK CVSView::WndProc( HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam )
	//{
	//	SControllerEvent Event;
	//	switch( message )
	//	{
	//	case WM_CREATE:
	//		return 0;
	//		break;

	//	case WM_PAINT: // paint event
	//		PAINTSTRUCT ps;
	//		BeginPaint(hwnd, &ps);
	//		EndPaint(hwnd, &ps);
	//		return 0;
	//	case WM_DESTROY: // killing the window
	//		CGame::GetInstance()->Exit();
	//		PostQuitMessage( 0 );
	//		return 0;
	//	case WM_LBUTTONDOWN:
	//		if (!CVSView::GetInstance()) return 0;
	//		CVSView::GetInstance()->m_isLeftMouseDown = true;
	//		Event.Type = ECE_POINTER;
	//		Event.PointerData.Event = EPE_PRESSED;
	//		Event.PointerData.ID = 0;
	//		Event.PointerData.X = LOWORD(lparam);
	//		Event.PointerData.Y = HIWORD(lparam);
	//		CGame::GetInstance()->SetEvent(Event);
	//		return 0;

	//	case WM_LBUTTONUP:
	//		if (!CVSView::GetInstance()) return 0;
	//		if (CVSView::GetInstance()->m_isLeftMouseDown)
	//		{
	//			CVSView::GetInstance()->m_isLeftMouseDown = false;
	//			Event.Type = ECE_POINTER;
	//			Event.PointerData.Event = EPE_RELEASED;
	//			Event.PointerData.ID = 0;
	//			Event.PointerData.X = LOWORD(lparam);
	//			Event.PointerData.Y = HIWORD(lparam);
	//			CGame::GetInstance()->SetEvent(Event);
	//		}		
	//		return 0;

	//	case WM_MOUSEMOVE:
	//		if (!CVSView::GetInstance()) return 0;
	//		Event.Type = ECE_POINTER;
	//		Event.PointerData.ID = 0;
	//		if(wparam == MK_LBUTTON)
	//		{				
	//			Event.PointerData.Event = EPE_DRAGGED;
	//			Event.PointerData.X = LOWORD(lparam);
	//			Event.PointerData.Y = HIWORD(lparam);
	//			CGame::GetInstance()->SetEvent(Event);
	//		}
	//		else
	//		{
	//			if (CVSView::GetInstance()->m_isLeftMouseDown)
	//			{
	//				Event.PointerData.Event = EPE_RELEASED;					
	//				Event.PointerData.X = LOWORD(lparam);
	//				Event.PointerData.Y = HIWORD(lparam);
	//				CVSView::GetInstance()->m_isLeftMouseDown = false;
	//				CGame::GetInstance()->SetEvent(Event);
	//			}
	//		}
	//		break;

	//	case WM_KEYDOWN:
 //			if (!CVSView::GetInstance()) return 0;
	//		Event.Type = ECE_KEY;
	//		Event.KeyData.Event = EKE_PRESSED;
	//		Event.KeyData.KeyCode = wparam;
	//		Event.KeyData.KeyCode <<= 4;
	//		CGame::GetInstance()->SetEvent(Event);
	//		break;

	//	case WM_KEYUP:
	//		if (!CVSView::GetInstance()) return 0;
	//		Event.Type = ECE_KEY;
	//		Event.KeyData.Event = EKE_RELEASED;
	//		Event.KeyData.KeyCode = wparam;
	//		Event.KeyData.KeyCode <<= 4;
	//		CGame::GetInstance()->SetEvent(Event);
	//		break;
	//	}
	//	return DefWindowProc(hwnd, message, wparam, lparam);
	//}

	//-------------------------------------------------------------------------------------------------------
	// OGL Porting
	//-------------------------------------------------------------------------------------------------------
	void CVSView::InitGL()
	{
	}

	void CVSView::RefreshGL()
	{
		eglSwapBuffers ( esContext->eglDisplay, esContext->eglSurface );
	}
}

#endif