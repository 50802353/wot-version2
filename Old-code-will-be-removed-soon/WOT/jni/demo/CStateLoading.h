#ifndef __CSTATELOADING_H__
#define __CSTATELOADING_H__

#include "gametutor.h"
using namespace GameTutor;

class CStateLoading: public CState
{
public:
	CStateLoading();
	~CStateLoading() {}

	void Init();
	void Update();
	void Render();
	//void OnControllerEvent(SControllerEvent Event);
	void Exit();
private:
	bool FinishedLoadAllResources;
	__UINT32 m_iPercent;
	__UINT32 m_iLoadState;

	CImage *Background;
	CImage *loading_icon;
	CImage *loading_icon2;

	GameSound* A_Background;
	GameSound* A_Background2;
};
#endif