#ifndef __CSTATEINGAME_H__
#define __CSTATEINGAME_H__

#include "gametutor.h"
#include "ObjectManager.h"

using namespace GameTutor;

enum ESTATUS_INGAME{
	ES_PAUSE=1<<7,
	ES_NONE=0,
	ES_BUILD,
	ES_UNBUILD,
	ES_TOWER,
	ES_SELECT_BUILD,
	ES_SELECT_UPGRADE,
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
	CTowerObject* selectedTower;
	int select_index;
	int select_x;
	int select_y;

	scene::IBillboardSceneNode* cursor ;
};



#endif