#ifndef __CSTATEMAINMENU_H__
#define __CSTATEMAINMENU_H__

#include "gametutor.h"
using namespace GameTutor;

enum E_GUI_BUTTON_MAINMENU {
	E_GBMM_START,
	E_GBMM_QUIT,
};

class MainMenuEventReceiver;

class CStateMainMenu: public CState
{
public:
	CStateMainMenu();
	~CStateMainMenu() {}

	void Init();
	void Update();
	void Render();
	void Exit();

private:
	gui::IGUIImage* screen;
	gui::IGUIButton* bStartGame;
	gui::IGUIButton* bQuit;

	MainMenuEventReceiver* receiver;
};



#endif