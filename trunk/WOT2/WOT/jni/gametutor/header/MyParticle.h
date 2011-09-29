#ifndef __MYPARTICLE_H__
#define __MYPARTICLE_H__

#include "Matrix.h"
#include "CGraphics2D.h"
#include "CImageManager.h"

#define PARTICLE_FILE_NAME PATH_GRAPHIC("particle2.tga")

namespace GameTutor
{


	class MyParticle
	{
	
	public:
		float bx,by,bz;
		float xpos,ypos,zpos;
		float xvel,yvel,zvel;
		float xcol,ycol,zcol;
		float maxAge;
		float currentAge;
		float size;
		float scale;
		bool isDraw;
		

	private:
		 int aPosition;
		 int aColor;
		 int aUV;
		 int uModel;
		 int uProjection;
		 int uView;
	public:

		void SetParameter(	int aposition,
							int acolor,
							int auv,
							int umodel,
							int uprojection,
							int uview);

		void SetBeginPosition(float x, float y, float z);
		void Initial(int mode);
		void Render(Matrix *model);
		void Update(int mode);
		void SetSize(float s){size = s;}

		float GetPosX(){return xpos;}
		float GetPosY(){return ypos;}
		float GetPosZ(){return zpos;}

		MyParticle(void);
		~MyParticle(void);
	};
}

#endif