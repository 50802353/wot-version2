#ifndef __CSTATEPOSTER_H__
#define __CSTATEPOSTER_H__

#include "gametutor.h"
#include "md2model.h"
#include "CButton.h"
#include "CObject3D.h"

class CStatePoster :public CState
{
public:
	CStatePoster();
	~CStatePoster() {}
	
	void Init();
	void Update();
	void Render();
	void Exit();
	void OnControllerEvent(SControllerEvent Event);

private:
	float gray;
	GameSound *A_Background;
	CImage *font;
	CButton *button;
	CImage* Background;
};

#endif