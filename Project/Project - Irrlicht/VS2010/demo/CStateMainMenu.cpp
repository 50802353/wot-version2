#include "CStateMainMenu.h"
#include "CStateChoseMap.h"

#define MAINMENU_BACKGROUND_IMAGE "./resource/backgroundMainMenu.jpg"
#define MAINMENU_BACKGROUND_MUSIC "./resource/backgroundMainMenu.wav"


class MainMenuEventReceiver:public MyEventReceiver
{
public:
	MainMenuEventReceiver(CStateMainMenu* state):MyEventReceiver()
	{
		this->state = state;
	}

	virtual bool MainMenuEventReceiver::OnEvent(const SEvent& event)
	{
		bool inAction = false;
		if (MyEventReceiver::OnEvent(event)) inAction=true;
		if (event.EventType==EEVENT_TYPE::EET_GUI_EVENT)
		{
			switch (event.GUIEvent.EventType)
			{
			case gui::EGUI_EVENT_TYPE::EGET_BUTTON_CLICKED:
				if (event.GUIEvent.Caller->getID()==E_GBMM_START)
				{
					CStateManagement::GetInstance()->SwitchState(new CStateChoseMap());

				}
				else if (event.GUIEvent.Caller->getID()==E_GBMM_QUIT)
				{
					CGame::GetInstance()->Exit();
				}
				inAction=true;
				break;
			}
		}
		return inAction;
	}

private:
	CStateMainMenu* state;
};

CStateMainMenu::CStateMainMenu(): CState()
{}

void CStateMainMenu::Init()
{
	core::rect<s32> vp = driver->getViewPort();
	screen = guienv->addImage(vp, 0, -1, L"");
	screen->setImage(driver->getTexture(MAINMENU_BACKGROUND_IMAGE));
	screen->setScaleImage(true);


	bStartGame = guienv->addButton(core::recti(vp.LowerRightCorner-core::dimension2di(153+20,(44+10)*2+10),core::dimension2di(153,44)),screen, E_GBMM_START);
	bStartGame->setImage(driver->getTexture("./resource/button/newgame.png"));

	bQuit = guienv->addButton(core::recti(vp.LowerRightCorner-core::dimension2di(153+20,(44+10)*1+10),core::dimension2di(153,44)),screen, E_GBMM_QUIT);
	bQuit->setImage(driver->getTexture("./resource/button/quit.png"));

	Log("State Logo: Init");
	CAudioPlayer::GetInstance()->Load<CFileWin32Driver>(MAINMENU_BACKGROUND_MUSIC);
	CAudioPlayer::GetInstance()->Play(MAINMENU_BACKGROUND_MUSIC,true);

	receiver = new MainMenuEventReceiver(this);
	CIrrlichtView::GetInstance()->device->setEventReceiver(receiver);
}

void CStateMainMenu::Update()
{	
}

void CStateMainMenu::Render()
{
}

void CStateMainMenu::Exit()
{
	Log("State Logo: Exit");	
	screen->remove();
	if (CAudioPlayer::GetInstance()->IsPlaying(MAINMENU_BACKGROUND_MUSIC))
		CAudioPlayer::GetInstance()->Stop(MAINMENU_BACKGROUND_MUSIC);
}
