#ifndef __CSTATEINGAME_H__
#define __CSTATEINGAME_H__
#include "gametutor.h"
#include "ObjectManager.h"

using namespace GameTutor;

class CStateLogo :
	public CState
{
public:
	CStateLogo(void);
	~CStateLogo(void);

	void Init();
	void OnControllerEvent(SControllerEvent Event);
	void Update();
	void Render();
	void Exit();
	
};
#endif //end __CSTATEINGAME_H__
