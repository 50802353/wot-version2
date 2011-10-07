


#include "CAndroidView.h"
#include "CGame.h"
#include "CDevice.h"


#if (CONFIG_PLATFORM==PLATFORM_ANDROID)

namespace GameTutor
{
	//---------------------------------------------------------------------------
	// Constructor only receive java's GLsurfaceView's config
	//---------------------------------------------------------------------------

	CAndroidView::CAndroidView(int w, int h, bool fullscreen, const char*name):m_iWidth(w), 
		m_iHeight(h), m_isFullScreen(false)
	{
		Log("Width %d Height %d", w, h);
		SetInstance(this);
	}

	//---------------------------------------------------------------------------
	// Destructor
	//---------------------------------------------------------------------------
	CAndroidView::~CAndroidView()
	{
	}

	//---------------------------------------------------------------------------
	// update message
	//---------------------------------------------------------------------------
	void CAndroidView::Update()
	{
		CGame::GetInstance()->Update();
		if (!CGame::GetInstance()->IsAlive())
		{
			TODO("Java check if game still alive");
			return;
		}
	}

	//---------------------------------------------------------------------------
	// Destroy win32 window
	//---------------------------------------------------------------------------


	//---------------------------------------------------------------------------
	// Win32 Message Callback
	//---------------------------------------------------------------------------
	__INT32 CAndroidView::ConvertKeyCode(int keycode)
	{
		switch (keycode)
			{
			case 0x13:			//KEYCODE_DPAD_UP 
				return 0x26;	//VK_UP
				break;
			case 0x14:			//KEYCODE_DPAD_DOWN 
				return 0x28;	//VK_DOWN
				break;
			case 0x15:			//KEYCODE_DPAD_LEFT 
				return 0x25;	//VK_LEFT
				break;
			case 0x16:			//KEYCODE_DPAD_RIGHT 
				return 0x27;	//VK_RIGHT
				break;
			default:
				break;
			}
	}

	void CAndroidView::onKeyDown(int keycode)
	{
		SControllerEvent Event;
		if (keycode == 0x04)
		{
			CGame::GetInstance()->Exit();
			return;
		}
		if (!CAndroidView::GetInstance()) return;
		Event.Type = ECE_KEY;
		Event.KeyData.Event = EKE_PRESSED;
		Event.KeyData.KeyCode = ConvertKeyCode(keycode);
		Event.KeyData.KeyCode <<= 4;
		CGame::GetInstance()->SetEvent(Event);
	}
	void CAndroidView::onKeyUp(int keycode)
	{
		if (keycode == 0x04)
		{
			CGame::GetInstance()->Exit();
			return;
		}
		SControllerEvent Event;
		if (!CAndroidView::GetInstance()) return;
		Event.Type = ECE_KEY;
		Event.KeyData.Event = EKE_RELEASED;
		Event.KeyData.KeyCode = ConvertKeyCode(keycode);
		Event.KeyData.KeyCode <<= 4;
		CGame::GetInstance()->SetEvent(Event);
	}
	void CAndroidView::onTouchDown(int x, int y)
	{
		if (!CAndroidView::GetInstance()) return;
		CAndroidView::GetInstance()->m_isTouch = true;
		SControllerEvent Event;
		Event.Type = ECE_POINTER;
		Event.PointerData.Event = EPE_PRESSED;
		Event.PointerData.ID = 0;
		Event.PointerData.X = x;
		Event.PointerData.Y = y;
		CGame::GetInstance()->SetEvent(Event);
	}
	void CAndroidView::onTouchUp(int x, int y)
	{
		if (!CAndroidView::GetInstance()) return;
		CAndroidView::GetInstance()->m_isTouch = false;
		SControllerEvent Event;
		Event.Type = ECE_POINTER;
		Event.PointerData.Event = EPE_RELEASED;
		Event.PointerData.ID = 0;
		Event.PointerData.X = x;
		Event.PointerData.Y = y;
		CGame::GetInstance()->SetEvent(Event);
	}
	void CAndroidView::onTouchMove(int x, int y)
	{
		if (!CAndroidView::GetInstance()) return;
		SControllerEvent Event;
		Event.Type = ECE_POINTER;
		Event.PointerData.ID = 0;
		Event.PointerData.Event = EPE_DRAGGED;
		Event.PointerData.X = x;
		Event.PointerData.Y = y;
		CGame::GetInstance()->SetEvent(Event);
	}

	
}





#endif

