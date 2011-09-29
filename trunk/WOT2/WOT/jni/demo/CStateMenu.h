#ifndef __CSTATEMENU_H__
#define __CSTATEMENU_H__

#include "gametutor.h"
using namespace GameTutor;

class CStateMenu: public CState
{
public:
	CStateMenu();
	~CStateMenu() {}

	void Init();
	void Update();
	void Render();
	void Exit();
	void OnControllerEvent(SControllerEvent Event);
private:
	//bool m_bEnableResume;			//Enable resume button 
	//bool m_bEnableLoadGame;			//Enable Load Saved Game button

	CImage *background;
	GameSound *A_Background;

	CButton *but_Newgame;
	//CButton *but_Resume;
	//CButton *but_LoadSaveGame;
	CButton *but_Option;
	CButton *but_Help;
	//CButton *but_About;
	CButton *but_Quit;
};
#endif