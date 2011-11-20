#ifndef __CDEMO_H__
#define __CDEMO_H__
#include "gametutor.h"

using namespace GameTutor;

class CDemo:public CGame
{
public:
	CDemo(): CGame() {}
	virtual ~CDemo() {}

protected:
	void Init();
	void Destroy();
};

#endif