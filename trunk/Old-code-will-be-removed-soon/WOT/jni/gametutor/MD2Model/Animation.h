#ifndef _ANIMATION_H_
#define _ANIMATION_H_

#include "md2model.h"
namespace GameTutor
{
	class Animation
	{
	public:
		Animation();
		int curIndex;
		int firstIndex;
		int lastIndex;
		float timePerFrame;
		float nextFrameDelay;
		MD2Model* model;

		void setModel(MD2Model* _model);
		void SetAnimation(char* aniName);

		void UpdateAnimation(float t);
		void RenderAnimation();

		void SetFps(__UINT32 fps);
		void SetTimePerFrame(float _timePerFrame);

		int GetNextIndex();

	
		float GetFraction();
	};
}
#endif