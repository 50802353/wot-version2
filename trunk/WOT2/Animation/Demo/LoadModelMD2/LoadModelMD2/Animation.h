#ifndef _ANIMATION_H_
#define _ANIMATION_H_

#include "md2model.h"
class Animation
{
public:
	int curIndex;
	int firstIndex;
	int lastIndex;
	float timePerFrame;
	float nextFrameDelay;
	MD2Model* model;

	Animation(MD2Model* _model);
	void setAction(char* aniName);
	void draw();
	void SetTimePerFrame(float _timePerFrame);

	int GetNextIndex();

	void CreateAnimation(float t);
	float GetFraction();
};

#endif