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
	extern class CGame;
	class MyEventReceiver : public irr::IEventReceiver
	{
	public:
		// This is the one method that we have to implement
		virtual bool OnEvent(const irr::SEvent& event)
		{
				// Remember whether each key is down or up
				SControllerEvent Event;
				if (event.EventType == irr::EET_KEY_INPUT_EVENT)
				{
					if (event.KeyInput.PressedDown)
					{					
						Event.Type = ECE_KEY;
						Event.KeyData.Event = EKE_PRESSED;
						Event.KeyData.KeyCode = event.KeyInput.Key;
						CGame::GetInstance()->SetEvent(Event);
					}
					else
					{
						Event.Type = ECE_KEY;
						Event.KeyData.Event = EKE_RELEASED;
						Event.KeyData.KeyCode = event.KeyInput.Key;
						CGame::GetInstance()->SetEvent(Event);
					}
				}
				else if (event.EventType == irr::EET_MOUSE_INPUT_EVENT)
				{
					/*if (event.MouseInput.Event == EMOUSE_INPUT_EVENT::
					case WM_LBUTTONDOWN:
						if (!CIrrlichtView::GetInstance()) return 0;
						CIrrlichtView::GetInstance()->m_isLeftMouseDown = true;
						Event.Type = ECE_POINTER;
						Event.PointerData.Event = EPE_PRESSED;
						Event.PointerData.ID = 0;
						Event.PointerData.X = LOWORD(lparam);
						Event.PointerData.Y = HIWORD(lparam);
						CGame::GetInstance()->SetEvent(Event);
						return 0;

					case WM_LBUTTONUP:
						if (!CIrrlichtView::GetInstance()) return 0;
						if (CIrrlichtView::GetInstance()->m_isLeftMouseDown)
						{
							CIrrlichtView::GetInstance()->m_isLeftMouseDown = false;
							Event.Type = ECE_POINTER;
							Event.PointerData.Event = EPE_RELEASED;
							Event.PointerData.ID = 0;
							Event.PointerData.X = LOWORD(lparam);
							Event.PointerData.Y = HIWORD(lparam);
							CGame::GetInstance()->SetEvent(Event);
						}		
						return 0;

					case WM_MOUSEMOVE:
						if (!CIrrlichtView::GetInstance()) return 0;
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
							if (CIrrlichtView::GetInstance()->m_isLeftMouseDown)
							{
								Event.PointerData.Event = EPE_RELEASED;					
								Event.PointerData.X = LOWORD(lparam);
								Event.PointerData.Y = HIWORD(lparam);
								CIrrlichtView::GetInstance()->m_isLeftMouseDown = false;
								CGame::GetInstance()->SetEvent(Event);
							}
						}
						break;*/

				}

				return false;
		}

		MyEventReceiver(){}
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

	//Open GL porting
	private: 
		irr::IrrlichtDevice *device;

	private:
		bool m_isLeftMouseDown;
		bool m_isKeyDown;
	};
}

#endif