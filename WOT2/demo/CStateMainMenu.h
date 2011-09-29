#ifndef __CSTATEMAINMENU_H__
#define __CSTATEMAINMENU_H__

#include "gametutor.h"
using namespace GameTutor;

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
	__INT32 m_iCount;
};
#endif