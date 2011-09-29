
#ifndef __Animation_H__
#define __Animation_H__

#include "md2model.h"

namespace GameTutor
{
	class Animation
	{
	public:
		Animation();
	private:
		MD2Model *model;
		int curIndex;
		int firstIndex;
		int lastIndex;
		float timePerFrame;
		float nextFrameDelay;
	public:

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