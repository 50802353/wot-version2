#include "Animation.h"

//----------Daniel--------------------------
Animation::Animation(MD2Model* _model)
{
	model = _model;
	timePerFrame	= 0.1f;
	nextFrameDelay	= 0.0f;
}
void Animation::setAction(char* aniName)
{
	this->model->GetFirstLastFrameOfAnimation(aniName,&this->firstIndex,&this->lastIndex);
	this->curIndex = this->firstIndex;
}
void Animation::draw(){
	this->model->draw(this->curIndex,this->GetNextIndex(),this->GetFraction());
}
//------------------------------------------

void Animation::SetTimePerFrame(float _timePerFrame)
{
	timePerFrame	= _timePerFrame;
}

void Animation::CreateAnimation(float t)
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