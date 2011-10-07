#include "CVSView.h"
#include "CGame.h"
#include "CDevice.h"
#if (CONFIG_PLATFORM==PLATFORM_WIN32_VS)

namespace GameTutor
{
	//---------------------------------------------------------------------------
	// Constructor
	//---------------------------------------------------------------------------

	CVSView::CVSView(int w, int h, bool fullscreen, const char*name):m_iWidth(w), 
		m_iHeight(h), m_isFullScreen(false),
		m_hGLRC(0), m_hwndWindow(0), m_hGameWndDC(0)
	{
		SetInstance(this);
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
		InitClientWindow();
	}

	//---------------------------------------------------------------------------
	// Destructor
	//---------------------------------------------------------------------------
	CVSView::~CVSView()
	{
		Destroy();
		delete m_strTitle;
	}

	//---------------------------------------------------------------------------
	// Init win32 client window
	//---------------------------------------------------------------------------
	void CVSView::InitClientWindow()
	{
		//get current instant
		HINSTANCE hInstance = GetModuleHandle(0);
		//----------------------------------
		// init WNDCLASSEX
		WNDCLASSEX wcex;
		wcex.cbSize = sizeof(WNDCLASSEX);
		wcex.style			= CS_HREDRAW | CS_VREDRAW;
		wcex.lpfnWndProc	= WndProc;
		wcex.cbClsExtra		= 0;
		wcex.cbWndExtra		= 0;
		wcex.hInstance		= hInstance;
		wcex.hIcon			= 0;//LoadIcon(hInstance, IDI_APPLICATION);
		wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
		wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
		wcex.lpszMenuName	= 0;
		wcex.lpszClassName	= "main";
		wcex.hIconSm		= 0;//LoadIcon(wcex.hInstance, IDI_APPLICATION);

		if (! RegisterClassEx( &wcex ) )
		{
			return; // ERR, SO QUIT
		}


		//----------------------------------
		// init HWND
		DWORD style = WS_POPUP;
		if(!m_isFullScreen)
		{
			style = WS_SYSMENU | WS_BORDER | WS_CAPTION | WS_CLIPCHILDREN | WS_CLIPSIBLINGS;
		}

		RECT clientSize;
		clientSize.top = 0;
		clientSize.left = 0;
		clientSize.right = m_iWidth;
		clientSize.bottom = m_iHeight;
		AdjustWindowRect(&clientSize, style, FALSE);

		const int realWidth = clientSize.right - clientSize.left;
		const int realHeight = clientSize.bottom - clientSize.top;

		int windowLeft = (GetSystemMetrics(SM_CXSCREEN) - realWidth) / 2;
		int windowTop = (GetSystemMetrics(SM_CYSCREEN) - realHeight) / 2;

		if(!m_isFullScreen)
		{
			m_hwndWindow = CreateWindow( "main", m_strTitle, style, windowLeft, windowTop,
				realWidth, realHeight, NULL, NULL, hInstance, NULL);
		}
		else
		{
			m_hwndWindow = CreateWindow( "main", m_strTitle, style, 0, 0,
				m_iWidth, m_iHeight, NULL, NULL, hInstance, NULL);
		}

		m_hGameWndDC = GetDC(m_hwndWindow);

		InitGL();

		ShowWindow( m_hwndWindow, SW_SHOW );
		UpdateWindow( m_hwndWindow );

		if(!m_isFullScreen)
		{
			MoveWindow(m_hwndWindow, windowLeft, windowTop, realWidth, realHeight, TRUE);
		}
		SetActiveWindow(m_hwndWindow);
		SetForegroundWindow(m_hwndWindow);

		if(m_isFullScreen)
		{
			DEVMODE dm;
			memset(&dm, 0, sizeof(dm));
			dm.dmSize	= sizeof(DEVMODE);
			dm.dmFields = DM_PELSWIDTH | DM_PELSHEIGHT | DM_BITSPERPEL;
			dm.dmPelsWidth	= m_iWidth;
			dm.dmPelsHeight = m_iHeight;
			dm.dmBitsPerPel = 32;
			ChangeDisplaySettings(&dm, CDS_FULLSCREEN);
		}
	}

	//---------------------------------------------------------------------------
	// update win32 message
	//---------------------------------------------------------------------------
	void CVSView::Update()
	{
		while (true)
		{
			// handle win32 message
			MSG msg;
			if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				if (msg.hwnd == m_hwndWindow)
				{
					WndProc(m_hwndWindow, msg.message, msg.wParam, msg.lParam);
				}
			}
			CGame::GetInstance()->Update();
			if (!CGame::GetInstance()->IsAlive())
			{
				DestroyWindow(m_hwndWindow);
				return;
			}
			RefreshGL();
			DispatchMessage(&msg);
		}
	}

	//---------------------------------------------------------------------------
	// Destroy win32 window
	//---------------------------------------------------------------------------
	void CVSView::Destroy()
	{
		if (m_isFullScreen)
		{
			ChangeDisplaySettings(NULL, 0);
		}
	}


	//---------------------------------------------------------------------------
	// Win32 Message Callback
	//---------------------------------------------------------------------------
	LRESULT CALLBACK CVSView::WndProc( HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam )
	{
		SControllerEvent Event;
		switch( message )
		{
		case WM_CREATE:
			return 0;
			break;

		case WM_PAINT: // paint event
			PAINTSTRUCT ps;
			BeginPaint(hwnd, &ps);
			EndPaint(hwnd, &ps);
			return 0;
		case WM_DESTROY: // killing the window
			CGame::GetInstance()->Exit();
			PostQuitMessage( 0 );
			return 0;
		case WM_LBUTTONDOWN:
			if (!CVSView::GetInstance()) return 0;
			CVSView::GetInstance()->m_isLeftMouseDown = true;
			Event.Type = ECE_POINTER;
			Event.PointerData.Event = EPE_PRESSED;
			Event.PointerData.ID = 0;
			Event.PointerData.X = LOWORD(lparam);
			Event.PointerData.Y = HIWORD(lparam);
			CGame::GetInstance()->SetEvent(Event);
			return 0;

		case WM_LBUTTONUP:
			if (!CVSView::GetInstance()) return 0;
			if (CVSView::GetInstance()->m_isLeftMouseDown)
			{
				CVSView::GetInstance()->m_isLeftMouseDown = false;
				Event.Type = ECE_POINTER;
				Event.PointerData.Event = EPE_RELEASED;
				Event.PointerData.ID = 0;
				Event.PointerData.X = LOWORD(lparam);
				Event.PointerData.Y = HIWORD(lparam);
				CGame::GetInstance()->SetEvent(Event);
			}		
			return 0;

		case WM_MOUSEMOVE:
			if (!CVSView::GetInstance()) return 0;
			Event.Type = ECE_POINTER;
			Event.PointerData.ID = 0;
			if(wparam == MK_LBUTTON)
			{				
				Event.PointerData.Event = EPE_DRAGGED;
				Event.PointerData.X = LOWORD(lparam);
				Event.PointerData.Y = HIWORD(lparam);
				CGame::GetInstance()->SetEvent(Event);
			}
			else
			{
				if (CVSView::GetInstance()->m_isLeftMouseDown)
				{
					Event.PointerData.Event = EPE_RELEASED;					
					Event.PointerData.X = LOWORD(lparam);
					Event.PointerData.Y = HIWORD(lparam);
					CVSView::GetInstance()->m_isLeftMouseDown = false;
					CGame::GetInstance()->SetEvent(Event);
				}
			}
			break;

		case WM_KEYDOWN:
 			if (!CVSView::GetInstance()) return 0;
			Event.Type = ECE_KEY;
			Event.KeyData.Event = EKE_PRESSED;
			Event.KeyData.KeyCode = wparam;
			Event.KeyData.KeyCode <<= 4;
			CGame::GetInstance()->SetEvent(Event);
			break;

		case WM_KEYUP:
			if (!CVSView::GetInstance()) return 0;
			Event.Type = ECE_KEY;
			Event.KeyData.Event = EKE_RELEASED;
			Event.KeyData.KeyCode = wparam;
			Event.KeyData.KeyCode <<= 4;
			CGame::GetInstance()->SetEvent(Event);
			break;
		}
		return DefWindowProc(hwnd, message, wparam, lparam);
	}

	//-------------------------------------------------------------------------------------------------------
	// OGL Porting
	//-------------------------------------------------------------------------------------------------------
	void CVSView::InitGL()
	{
		HDC hdc = m_hGameWndDC;
		GLuint	PixelFormat;
		static	PIXELFORMATDESCRIPTOR pfd =				// pfd Tells Windows How We Want Things To Be
		{
			sizeof(PIXELFORMATDESCRIPTOR),				// Size Of This Pixel Format Descriptor
			1,											// Version Number
			PFD_DRAW_TO_WINDOW |						// Format Must Support Window
			PFD_SUPPORT_OPENGL |						// Format Must Support OpenGL
			PFD_DOUBLEBUFFER,							// Must Support Double Buffering
			PFD_TYPE_RGBA,								// Request An RGBA Format
			16,											// Select Our Color Depth
			0, 0, 0, 0, 0, 0,							// Color Bits Ignored
			16,											// Alpha Buffer
			0,											// Shift Bit Ignored
			0,											// Accumulation Buffer
			0, 0, 0, 0,									// Accumulation Bits Ignored
			16,											// 16Bit Z-Buffer (Depth Buffer)  
			8,											// Stencil Buffer
			0,											// Auxiliary Buffer
			PFD_MAIN_PLANE,								// Main Drawing Layer
			0,											// Reserved
			0, 0, 0										// Layer Masks Ignored
		};	
		PixelFormat = ChoosePixelFormat(hdc, &pfd);

		SetPixelFormat(hdc, PixelFormat, &pfd);
		m_hGLRC = wglCreateContext(hdc);
		wglMakeCurrent(hdc, m_hGLRC);
	}

	void CVSView::RefreshGL()
	{
		SwapBuffers(m_hGameWndDC);
	}
}

#endif