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
					if ((gui::IGUIButton*)event.GUIEvent.Caller==state->bContinue)
					{
						//do something

						
					}
					else if ((gui::IGUIButton*)event.GUIEvent.Caller==state->bRestart)
					{
						//do something

					}
					else if ((gui::IGUIButton*)event.GUIEvent.Caller==state->bQuit)
					{
						//do something

					}
					else if ((gui::IGUIButton*)event.GUIEvent.Caller==state->bMainMenu)
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