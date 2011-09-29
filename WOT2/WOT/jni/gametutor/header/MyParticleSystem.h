#ifndef __MYPARTICLESYSTEM_H__
#define __MYPARTICLESYSTEM_H__

#include "MyParticle.h"
#include "CImageManager.h"



namespace GameTutor
{

	class MyParticleSystem
	{
	private:
		int mode;
		float xPos;
		float yPos;
		float zPos;
		unsigned int textureID;
		int numberParticle;
		float size;
		int timeout;

	private:
		Matrix *modelMatrix;
		MyParticle *arrayParticle;
	public:
		void SetSize(float s){size = s;}
		void SetMode(int m){mode = m;}
		void SetPosition(float x, float y, float z);
		void SetTimeOut(int t){timeout = t;}
		void Initial(int number);
		void Render(Matrix*);
		void Update();
		bool isDied(){return timeout==-1;}
		MyParticleSystem(void);
		MyParticleSystem(Matrix matrix);
		~MyParticleSystem(void);
	};

}

	#endif