
#ifndef __COBJECT_3D_H__
#define __COBJECT_3D_H__

#include "CMD2Model.h"

namespace GameTutor
{
	class Object3D
	{
	public:
		Object3D(float _size);
		~Object3D();
		
	private:
		MD2Model *model;
		float objectSize;

		int curIndex;
		int firstIndex;
		int lastIndex;
		float timePerFrame;
		float nextFrameDelay;
		GameSound* mSound;

	public:
		void SetModel(MD2Model* _model);
		void SetAnimation(char* aniName, float time=0);
		void SetAnimation(char* aniName, GameSound* sound);
		void UpdateAnimation(float t);
		void RenderAnimation(Matrix* worldMatrix);
		bool IsFinishAction();

		void SetFps(__UINT32 fps);
		void SetTimePerFrame(float _timePerFrame);

		int GetNextIndex();
		float GetFraction();

		MD2Model* GetModel();
	};
}
#endif