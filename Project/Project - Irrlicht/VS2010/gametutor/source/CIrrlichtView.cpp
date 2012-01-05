
#include "CIrrlichtView.h"
#include "CGame.h"
#include "CDevice.h"

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

namespace GameTutor
{
		bool MyEventReceiver::OnEvent(const irr::SEvent& event)
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
				if (event.MouseInput.Event == irr::EMOUSE_INPUT_EVENT::EMIE_LMOUSE_PRESSED_DOWN)
				{
					/*if (!CIrrlichtView::GetInstance()) return 0;
					CIrrlichtView::GetInstance()->m_isLeftMouseDown = true;*/
					Event.Type = ECE_POINTER;
					Event.PointerData.Event = EPE_PRESSED;
					Event.PointerData.ID = 0;
					Event.PointerData.X = event.MouseInput.X;
					Event.PointerData.Y = event.MouseInput.Y;
					CGame::GetInstance()->SetEvent(Event);
					return 0;
				}
				else if (event.MouseInput.Event == irr::EMOUSE_INPUT_EVENT::EMIE_LMOUSE_LEFT_UP)
				{
					/*if (!CIrrlichtView::GetInstance()) return 0;
					if (CIrrlichtView::GetInstance()->m_isLeftMouseDown)*/
					{
						/*CIrrlichtView::GetInstance()->m_isLeftMouseDown = false;*/
						Event.Type = ECE_POINTER;
						Event.PointerData.Event = EPE_RELEASED;
						Event.PointerData.ID = 0;
						Event.PointerData.X = event.MouseInput.X;
						Event.PointerData.Y = event.MouseInput.Y;
						CGame::GetInstance()->SetEvent(Event);
					}		
					return 0;
				}
				else if (event.MouseInput.Event == irr::EMOUSE_INPUT_EVENT::EMIE_MOUSE_MOVED)
				{
					/*if (!CIrrlichtView::GetInstance()) return 0;*/
					Event.Type = ECE_POINTER;
					Event.PointerData.ID = 0;
					if(event.MouseInput.isLeftPressed())
					{				
						Event.PointerData.Event = EPE_DRAGGED;
						Event.PointerData.X = event.MouseInput.X;
						Event.PointerData.Y = event.MouseInput.Y;
						CGame::GetInstance()->SetEvent(Event);
					}
					/*else
					{
						if (CIrrlichtView::GetInstance()->m_isLeftMouseDown)
						{
							Event.PointerData.Event = EPE_RELEASED;					
							Event.PointerData.X = event.MouseInput.X;
							Event.PointerData.Y = event.MouseInput.Y;
							/*CIrrlichtView::GetInstance()->m_isLeftMouseDown = false;
							CGame::GetInstance()->SetEvent(Event);
						}
					}*/
				}
			}
				
			return false;
		}

		MyEventReceiver::MyEventReceiver()
		{
		}



	//---------------------------------------------------------------------------
	// Constructor
	//---------------------------------------------------------------------------

	CIrrlichtView::CIrrlichtView(int w, int h, irr::IrrlichtDevice* &Irrlichtdevice, bool fullscreen, const char*name):m_iWidth(w), 
		m_iHeight(h), m_isFullScreen(fullscreen),
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
		InitClientWindow(Irrlichtdevice);
		this->device = Irrlichtdevice;
	}

	//---------------------------------------------------------------------------
	// Destructor
	//---------------------------------------------------------------------------
	CIrrlichtView::~CIrrlichtView()
	{
		Destroy();
		delete m_strTitle;
	}

	//---------------------------------------------------------------------------
	// Init win32 client window
	//---------------------------------------------------------------------------
	void CIrrlichtView::InitClientWindow(irr::IrrlichtDevice *&Irrlichtdevice)
	{
		receiver = new MyEventReceiver();
		device = irr::createDevice( EDT_DIRECT3D9, dimension2d<u32>(m_iWidth, m_iHeight), 16,	m_isFullScreen, false, false, receiver);
		core::stringw title = m_strTitle;
		device->setWindowCaption(title.c_str());
		//device->getCursorControl()->setVisible(false);
		Irrlichtdevice = device;
	}

	//---------------------------------------------------------------------------
	// update win32 message
	//---------------------------------------------------------------------------
	void CIrrlichtView::Update()
	{
		irr::video::IVideoDriver* driver = device->getVideoDriver();
        irr::scene::ISceneManager* smgr = device->getSceneManager();
        irr::gui::IGUIEnvironment* guienv = device->getGUIEnvironment();

		while (device->run())
		{
			driver->beginScene(true, true, SColor(255,0,0,0));     
			smgr->drawAll();
			CGame::GetInstance()->Update();
			if (!CGame::GetInstance()->IsAlive())
			{
				device->closeDevice();
				break;
			}
			
			guienv->drawAll();

			driver->endScene();
		}
	}

	//---------------------------------------------------------------------------
	// Destroy win32 window
	//---------------------------------------------------------------------------
	void CIrrlichtView::Destroy()
	{
		delete receiver;
		device->drop();		
	}


}