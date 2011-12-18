#ifndef __CSTATEINGAME_H__
#define __CSTATEINGAME_H__

#include "gametutor.h"
#include "ObjectManager.h"

using namespace GameTutor;

enum ESTATUS_INGAME{
	ES_NONE,
	ES_BUILD,
	ES_UNBUILD,
	ES_TOWER,
	ES_SELECT_BUILD,
	ES_SELECT_UPGRADE,
};

enum ESTATUS_TIME{
	ES_PAUSE,
	ES_PLAY,
};


extern class IngameEventReceiver;

enum E_GUI_BUTTON_INGAME{
	E_GBIG_CONTINUE=5000,
	E_GBIG_RESTART,
	E_GBIG_QUIT,
	E_GBIG_MAINMENU,
	//E_GBIG_YES,
	//E_GBIG_NO,

};


class CStateIngame: public CState
{
public:
	CStateIngame();
	~CStateIngame() {}

	void Init();
	void Update();
	void Render();
	void Exit();

	CObjectManager ObjectManager;

	irr::gui::IGUIStaticText* Money_text;
	irr::gui::IGUIStaticText* Life_text;
	ESTATUS_INGAME status;
	ESTATUS_TIME time_status;
	CTowerObject* selectedTower;
	int select_index;
	int select_x;
	int select_y;

	gui::IGUIImage* cursor ;
	void updateSelectPane(STowerData** list);
	gui::IGUIImage* selectPane[11];

	gui::IGUIImage* menuIngame;

	gui::IGUIButton* bContinue;
	gui::IGUIButton* bRestart;
	gui::IGUIButton* bMainMenu;
	gui::IGUIButton* bQuit;

	IngameEventReceiver* receiver;

};

class IngameEventReceiver: public MyEventReceiver
{
public:
	IngameEventReceiver(CStateIngame* state):MyEventReceiver()
	{
		this->state = state;
	}

	virtual bool OnEvent(const SEvent& event)
	{
		bool inAction = false;
		if (MyEventReceiver::OnEvent(event)) inAction=true;
		if (event.EventType==EEVENT_TYPE::EET_GUI_EVENT)
		{
			switch (event.GUIEvent.EventType)
			{
			case gui::EGUI_EVENT_TYPE::EGET_BUTTON_CLICKED:
				{
					if (event.GUIEvent.Caller->getID()==E_GBIG_CONTINUE)
					{
						printf("CONTINUE\n");
						state->time_status = ES_PLAY;
						state->menuIngame->setVisible(false);
						//tat' menu ingame
						CIrrlichtView::GetInstance()->device->getTimer()->start();
						state->smgr->getActiveCamera()->setInputReceiverEnabled(true);
						CIrrlichtView::GetInstance()->device->getCursorControl()->setVisible(false);
						core::rect<s32> vp = state->driver->getViewPort();
						CIrrlichtView::GetInstance()->device->getCursorControl()->setPosition(vp.getWidth()/2, vp.getHeight()/2);
					}
					else if (event.GUIEvent.Caller->getID()==E_GBIG_RESTART)
					{
						//do something
						state->ObjectManager.Reset();
						state->selectedTower = 0;
						state->select_index = -1;
						state->select_x = -1;
						state->select_y = -1;
						state->status = ES_NONE;
						state->time_status = ES_PLAY;

						state->menuIngame->setVisible(false);
						//tat' menu ingame
						CIrrlichtView::GetInstance()->device->getTimer()->start();
						state->smgr->getActiveCamera()->setInputReceiverEnabled(true);
						CIrrlichtView::GetInstance()->device->getCursorControl()->setVisible(false);
						core::rect<s32> vp = state->driver->getViewPort();
						CIrrlichtView::GetInstance()->device->getCursorControl()->setPosition(vp.getWidth()/2, vp.getHeight()/2);
					}
					else if (event.GUIEvent.Caller->getID()==E_GBIG_QUIT)
					{
						//do something
						CGame::GetInstance()->Exit();

					}
					else if (event.GUIEvent.Caller==state->bMainMenu)
					{
						//do something
					}
					inAction = true;
				}
				break;
			default:
				{
					
				}
				break;
			}
		}
		return inAction;
	}

private:
	CStateIngame* state;

};


#endif