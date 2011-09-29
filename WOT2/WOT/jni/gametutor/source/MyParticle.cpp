#include "MyParticle.h"
#include <stdlib.h>


namespace GameTutor
{

	MyParticle::MyParticle(void)
	{
		bx=by=bz=0.0f;
		size = 0.01f;

		aPosition = -1;
		aColor = -1;
		aUV = -1;
		uModel = -1;
		uProjection = -1;
		uView = -1;
		isDraw = true;
	}

	MyParticle::~MyParticle(void)
	{
	}

	void MyParticle::Initial(int mode)
	{
		
		scale = 1.0f;
		xpos = bx;
		ypos = by;
		zpos = bz;

		xcol = (float)(rand() % 100)/90;
		ycol = (float)(rand() % 100)/90;
		zcol = (float)(rand() % 100)/90;

		maxAge = (float)(rand() % 100)/2;

		if(mode==0)
		{
			xvel = (float)(rand() % 10)/1000 - 0.005;
			yvel = (float)(rand() % 10)/1000 - 0.005;
			zvel = (float)(rand() % 10)/1000 - 0.005;
		}
		else if(mode==1)
		{
			xvel = (float)(rand() % 10)/10000 - 0.0005;
			yvel = (float)(rand() % 10)/2000;
			zvel = (float)(rand() % 10)/10000 - 0.0005;
		}
		else if(mode==2)
		{
			xvel = 0.0006f;
			yvel = -(float)(rand() % 10)/5000;
			zvel = (float)(rand() % 10)/10000 - 0.0005;

			xcol = 0.0f;
			ycol = 0.3f;
			zcol = 0.8f;
		}
		else if(mode==3)
		{
			float r = 0.1f;
			float angle = (float)(rand() % 360);
			xpos = r*cosf(angle);
			ypos = r*sinf(angle);
			//zpos = r*sinf(angle);

			yvel = (float)(rand() % 10)/5000;
		}
		else if(mode==4)
		{
			xcol = 1.0f;
			ycol = 0.0f;
			zcol = 0.0f;

			float r = 0.04f;
			float angle = (float)(rand() % 360);
			xpos = r*cosf(angle)+ bx - (float)(rand() % 10)/2000 - 0.048;
			ypos = r*sinf(angle)+ by - (float)(rand() % 10)/2000 - 0.048;

			yvel = (float)(rand() % 10)/1000;

			//maxAge = 20.0f - (float)sqrtf((xpos-bx)*(xpos-bx) + (ypos-by)*(ypos-by));
		}
		else if(mode==5)
		{
			xcol = 1.0f;
			ycol = 0.8f;
			zcol = 0.3f;

			float r = 0.5;
			float angle1 = (float)(rand() % 360);
			float angle2 = (float)(rand() % 360);

			xvel = (r/maxAge)*cos(angle1)*cos(angle2);
			yvel = (r/maxAge)*cos(angle1)*sin(angle2);
			zvel = (r/maxAge)*sin(angle1);
		}
		else if(mode==6)
		{
			xcol = 0.3f;
			ycol = float((rand() % 20)+80)/100;
			zcol = 0.3f;

			float r = 0.03;
			float angle1 = (float)(rand() % 360);
			float angle2 = (float)(rand() % 360);

			xpos = (r)*cos(angle1)*cos(angle2);
			ypos = (r)*cos(angle1)*sin(angle2);
			zpos = (r)*sin(angle1);


			xvel = float((rand() % 5)+92)/100;
			yvel = float((rand() % 5)+92)/100;
			zvel = float((rand() % 5)+92)/100;

			scale = float((rand()%300)+100)/100;
		}
		else if(mode==7)
		{
			xcol = float((rand() % 10)+90)/100;
			ycol = float((rand() % 10)+90)/100;
			zcol = 0.9f;

			float r = 0.1f;
			float angle = (float)(rand() % 360);
			xpos = r*cosf(angle)+ bx - (float)(rand() % 10)/2000 - 0.048;
			ypos = r*sinf(angle)+ by - (float)(rand() % 10)/2000 - 0.048;
			zpos = 0;


			xvel = 0.98;
			yvel = 0.98;
			zvel = 0.01;//float(rand() % 100)/1000+0.01;

			//scale = (float(rand() % 50)/100)+1.0;
		}
		else if(mode==8)
		{
			float r = 0.03;
			float angle1 = (float)(rand() % 360);
			float angle2 = (float)(rand() % 360);

			xpos = (r)*cos(angle1)*cos(angle2);
			ypos = (r)*cos(angle1)*sin(angle2);
			zpos = (r)*sin(angle1);


			xcol = float((rand() % 30)+70)/100;
			ycol = float((rand() % 10)+10)/100;
			zcol = float((rand() % 10)+0)/100;

			scale = float((rand()%500)+100)/100;

			zvel = -0.01;
		}


	

		currentAge = 0.0f;
	}
	//
	void MyParticle::Render(Matrix *model)
	{
		if (isDraw)
		{
			float positions[] = {
								xpos-size*scale,ypos+size*scale,zpos,	// top		left
								xpos-size*scale,ypos-size*scale,zpos,	// botton	left
								xpos+size*scale,ypos+size*scale,zpos,	// top		right
								xpos+size*scale,ypos-size*scale,zpos,	// botton	right
								};

			float uvs[] = {	0.0f, 1.0f, 0.0f,
							0.0f, 0.0f, 0.0f,
							1.0f, 1.0f, 0.0f,
							1.0f, 0.0f, 0.0f};

			unsigned int  indices[] = {0,1,2,3};
		
			

			CGraphics2D::GetInstance()->DrawParticle(4, model, positions, uvs, indices, CImageManager::GetInstance()->Get(PARTICLE_FILE_NAME)->GetTextureID(),
				SColor<float>(xcol,ycol,zcol,1.0f));
		}

	}

	void MyParticle::Update(int mode)
	{
		currentAge+=0.05f;
		if(currentAge<maxAge)
		{
			if(mode==0)
			{
				xpos += xvel;//+currentAge/10000; 
				ypos += yvel; 
				zpos += zvel; 
				//ypos -= currentAge/10000;
				//size += 0.00001f;
			}
			else if(mode==1)
			{
				xpos += xvel;//+currentAge/10000; 
				ypos += yvel; 
				zpos += zvel; 
				ypos -= currentAge/500;
				//size += 0.0002f;
			}
			else if(mode==2)
			{
				xpos += xvel;//+currentAge/10000; 
				ypos += yvel; 
				zpos += zvel; 
				ypos -= currentAge/10000;
				//size += 0.00001f;
			}
			else if(mode==3)
			{
				currentAge+=0.2f;			
				ypos += yvel; 
			}
			else if( mode==4)
			{
				ycol+=0.02f;//(float)currentAge/maxAge;
				currentAge+=0.9f;			
				ypos += yvel; 
			}
			else if( mode==5)
			{
				ycol+=0.02f;//(float)currentAge/maxAge;
				currentAge+=0.9f;			
				xpos += xvel; 
				ypos += yvel; 
				zpos += zvel; 
				scale *=0.7;
			}
			else if( mode==6)
			{
				xcol*=0.99f;
				ycol*=0.99f;
				zcol*=0.99f;
				currentAge+=0.9f;			
				xpos *= xvel; 
				ypos *= yvel; 
				zpos = (zpos-0.01) * zvel + 0.01; 
				//scale *=0.98;
			}
			else if( mode==7)
			{
				xcol *= 1.06;
				ycol *= 1.06;
				zcol -= 0.07;
				currentAge+=1;			
				xpos *= xvel; 
				ypos *= yvel; 
				zpos += zvel; 
				scale *=0.98;
			}
			else if( mode==8)
			{
				ycol += 0.07;
				zcol += 0.02;
				//zcol = 0.01;
				currentAge+=1;				
				scale *=0.90;
				zpos += zvel;
			}
		}
		else
		{
			Initial(mode);
			if (mode==5)	isDraw = false;
			if (mode==8)	isDraw = false;
		}
	}

	void MyParticle::SetBeginPosition(float x, float y, float z)
	{
		xpos = x;
		ypos = y;
		zpos = z;
	}



}