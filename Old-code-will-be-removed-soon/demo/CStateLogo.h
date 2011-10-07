#ifndef __CSTATELOGO_H__
#define __CSTATELOGO_H__

#include "gametutor.h"
using namespace GameTutor;

class CStateLogo: public CState
{
public:
	CStateLogo();
	~CStateLogo() {}

	void Init();
	void Update();
	void Render();
	void Exit();
private:
	__INT32 m_iCount;
};
#endif