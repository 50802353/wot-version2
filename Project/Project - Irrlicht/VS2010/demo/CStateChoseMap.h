#ifndef __CSTATECHOSEMAP_H__
#define __CSTATECHOSEMAP_H__

#include "gametutor.h"
using namespace GameTutor;

enum E_GUI_BUTTON_CHOSEMAP {
	E_GBCM_BACK,
	E_GBCM_MAP1,
	E_GBCM_MAP2,
	E_GBCM_MAP3,
	E_GBCM_MAP4,
};

extern class ChoseMapEventReceiver;
extern class CStateIngame;
extern class CStateMainMenu;

class CStateChoseMap: public CState
{
public:
	CStateChoseMap();
	~CStateChoseMap() {}

	void Init();
	void Update();
	void Render();
	void Exit();

private:
	gui::IGUIImage* screen;
	gui::IGUIButton* bBack;
	gui::IGUIButton* bMap1;
	gui::IGUIButton* bMap2;
	gui::IGUIButton* bMap3;
	gui::IGUIButton* bMap4;



	ChoseMapEventReceiver* receiver;
};



#endif