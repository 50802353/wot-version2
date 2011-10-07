#include "MyParticleSystem.h"



namespace GameTutor
{

	MyParticleSystem::MyParticleSystem(void)
	{
		xPos = 0;
		yPos = 0;
		zPos = 0;


		modelMatrix = new Matrix();
		modelMatrix->LoadIdentity();

		mode = 0;
		size = 0.02f;
		timeout = 100;
	}

	MyParticleSystem::MyParticleSystem(Matrix matrix)
	{
		xPos = 0;
		yPos = 0;
		zPos = 0;
		modelMatrix = new Matrix(matrix.GetData());
		mode = 0;
		size = 0.02f;
		timeout = 100;
	}

	MyParticleSystem::~MyParticleSystem(void)
	{
	}

	void MyParticleSystem::Initial(int number)
	{
		numberParticle = number;
		arrayParticle = new MyParticle[numberParticle];
	
		 int width;
		 int height;

		CImageManager::GetInstance()->AddImage<CFileWin32Driver>(PARTICLE_FILE_NAME,true);
		CImageManager::GetInstance()->Get(PARTICLE_FILE_NAME)->FreeBuffer();
		textureID = CImageManager::GetInstance()->Get(PARTICLE_FILE_NAME)->GetTextureID();

		for(int i=0;i<numberParticle;i++)
		{
			arrayParticle[i].SetBeginPosition(xPos,yPos,zPos);
			arrayParticle[i].SetSize(size);
			arrayParticle[i].Initial(mode);
		}
	}


	void MyParticleSystem::Render(Matrix* modelMatrix)
	{
		if (timeout>0)
		{
			if (modelMatrix==NULL) modelMatrix = this->modelMatrix;
			else modelMatrix->Translate(xPos,yPos,zPos);
			for(int i=0;i<numberParticle;i++)
			{
				if (size>0.0001)
					arrayParticle[i].Render(modelMatrix);
			}
		}
	}

	void MyParticleSystem::Update()
	{
		if (timeout>0)
		{
			for(int i=0;i<numberParticle;i++)
			{
				arrayParticle[i].Update(mode);
			}
			timeout--;
		}
		else if (timeout==0)
		{
			delete[] arrayParticle;
			arrayParticle = NULL;
			timeout = -1;
		}
	}
	void MyParticleSystem::SetPosition(float x,float y,float z)
	{
		xPos = x;
		yPos = y;
		zPos = z;
		//modelMatrix->Translate(xPos,yPos,zPos);
	}
}