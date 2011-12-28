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
	ES_WAIT_END,
};


extern class IngameEventReceiver;

enum E_GUI_BUTTON_INGAME{
	E_GBIG_CONTINUE=5000,
	E_GBIG_RESTART,
	E_GBIG_QUIT,
	E_GBIG_MAINMENU,
	E_GBIG_NEXT,
	//E_GBIG_YES,
	//E_GBIG_NO,

};


class CStateIngame: public CState
{
public:
	CStateIngame(SMapData** MapDataList, int index);
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
	gui::IGUIImage* selectPane[6];

	gui::IGUIImage* menuIngame;
	gui::IGUIButton* bContinue;
	gui::IGUIButton* bRestart;
	gui::IGUIButton* bMainMenu;
	gui::IGUIButton* bQuit;

	gui::IGUIImage* menuIngame_WIN;
	gui::IGUIButton* bwRestart;
	gui::IGUIButton* bwNext;
	gui::IGUIButton* bwMainMenu;
	gui::IGUIButton* bwQuit;

	gui::IGUIImage* menuIngame_LOSE;
	gui::IGUIButton* blRestart;
	gui::IGUIButton* blMainMenu;
	gui::IGUIButton* blQuit;

	IngameEventReceiver* receiver;
	irr::scene::ICameraSceneNode* camera;

	SMapData** MapDataList;
	int currentMapIndex;
};




#endif