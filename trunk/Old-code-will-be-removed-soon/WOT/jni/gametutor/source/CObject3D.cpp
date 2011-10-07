#include "CObject3D.h"

namespace GameTutor
{
	Object3D::Object3D(float _size)
	{
		firstIndex = 0;
		lastIndex = 0;
		curIndex = 0;
		timePerFrame = 0.1f;
		nextFrameDelay = 0.0f;
		mSound = 0;
		objectSize = _size;
	}
	
	Object3D::~Object3D()
	{
	}

	void Object3D::SetModel(MD2Model* _model)
	{
		model = _model;
		this->firstIndex = _model->startFrame;
		this->lastIndex = _model->endFrame;
		this->curIndex = this->firstIndex;
		timePerFrame	= 0.1f;
		nextFrameDelay	= 0.0f;
	}

	void Object3D::SetAnimation(char* aniName, GameSound* sound)
	{
		this->model->GetFirstLastFrameOfAnimation(aniName,&this->firstIndex,&this->lastIndex);
		this->curIndex = this->firstIndex;
		this->mSound = sound;
	}

	void Object3D::SetAnimation(char* aniName, float time)
	{
		this->model->GetFirstLastFrameOfAnimation(aniName,&this->firstIndex,&this->lastIndex);
		if (time!=0)
			this->SetTimePerFrame(time/float(lastIndex-firstIndex));
		else
			this->SetTimePerFrame(0.1f);
		this->curIndex = this->firstIndex;
	}

	void Object3D::RenderAnimation(Matrix* worldMatrix){
		Matrix matrix;
		matrix.Multiply(*worldMatrix);
		//scale to fix position and size of model
		float scale = objectSize/(model->mRange.zMax - model->mRange.zMin);

		float translateX = (model->mRange.xMax + model->mRange.xMin)/2;
		//if(model->mRange.xMax + model->mRange.xMin != 0.0f) translateX = (
		float translateY = (model->mRange.yMax + model->mRange.yMin)/2;
		float translateZ = 0.0f;
		if(model->mRange.zMin != 0) translateZ = -model->mRange.zMin;
		
		matrix.Scale(scale,scale,scale);
		matrix.Translate(-translateX,-translateY,translateZ);
		//set Position in Map
		//matrix.Multiply(*worldMatrix);
		this->model->Draw(this->curIndex,this->GetNextIndex(),this->GetFraction(), &matrix);
		//for sound
		if(this->curIndex == this->lastIndex)
			if(mSound != 0) mSound->Play();
	}
	//------------------------------------------

	void Object3D::SetTimePerFrame(float _timePerFrame)
	{
		timePerFrame	= _timePerFrame;
	}
	void Object3D::SetFps(__UINT32 fps){
		timePerFrame = (float) 1/fps;
	}

	void Object3D::UpdateAnimation(float t)
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

	float Object3D::GetFraction()
	{
		int numFrame=lastIndex-firstIndex+1;
		float time=((curIndex-firstIndex)*timePerFrame+nextFrameDelay)/
						(numFrame*timePerFrame);
		float frac=time*numFrame-(curIndex-firstIndex);
		return frac;
	}

	int Object3D::GetNextIndex()
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

	MD2Model* Object3D::GetModel()
	{
		return this->model;
	}
	bool Object3D::IsFinishAction()
	{
		return (curIndex == lastIndex);
	}
}