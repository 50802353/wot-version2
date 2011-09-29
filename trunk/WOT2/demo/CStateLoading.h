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
	void Exit();
private:
	__INT32 m_iCount;
};
#endif