
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
	//---------------------------------------------------------------------------
	// Constructor
	//---------------------------------------------------------------------------

	CIrrlichtView::CIrrlichtView(int w, int h, irr::IrrlichtDevice* &Irrlichtdevice, bool fullscreen, const char*name):m_iWidth(w), 
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

			CGame::GetInstance()->Update();
			if (!CGame::GetInstance()->IsAlive())
			{
				device->closeDevice();
				break;
			}
			smgr->drawAll();
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