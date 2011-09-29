#include "Animation.h"

namespace GameTutor
{
	Animation::Animation()
	{
		firstIndex = 0;
		lastIndex = 0;
		curIndex = 0;
		timePerFrame = 0.1f;
		nextFrameDelay = 0.0f;
	}

	void Animation::setModel(MD2Model* _model)
	{
		model = _model;
		this->firstIndex = _model->startFrame;
		this->lastIndex = _model->endFrame;
		this->curIndex = this->firstIndex;
		timePerFrame	= 0.1f;
		nextFrameDelay	= 0.0f;
	}

	void Animation::SetAnimation(char* aniName)
	{
		this->model->GetFirstLastFrameOfAnimation(aniName,&this->firstIndex,&this->lastIndex);
		this->curIndex = this->firstIndex;
	}

	void Animation::RenderAnimation(){
		this->model->draw(this->curIndex,this->GetNextIndex(),this->GetFraction());
	}
	//------------------------------------------

	void Animation::SetTimePerFrame(float _timePerFrame)
	{
		timePerFrame	= _timePerFrame;
	}
	void Animation::SetFps(__UINT32 fps){
		timePerFrame = (float) 1/fps;
	}

	void Animation::UpdateAnimation(float t)
	{
		nextFrameDelay+=t;
		if(nextFrameDelay>timePerFrame)
		{
			nextFrameDelay-=timePerFrame;
			if(curIndex<lastIndex)
			{
				curIndex++;
			}
			else 
			{
				curIndex=firstIndex;
			}
		}
	}

	float Animation::GetFraction()
	{
		int numFrame=lastIndex-firstIndex+1;
		float time=((curIndex-firstIndex)*timePerFrame+nextFrameDelay)/
						(numFrame*timePerFrame);
		float frac=time*numFrame-(curIndex-firstIndex);
		return frac;
	}

	int Animation::GetNextIndex()
	{
		int nextIndex;
		if(curIndex<lastIndex)
		{
			nextIndex=curIndex+1;
		}
		else 
		{
			nextIndex=firstIndex;
		}
		return nextIndex;
	}
}