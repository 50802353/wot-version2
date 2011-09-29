#ifndef _CSKYBOX_H_
#define _CSKYBOX_H_

#include "CGraphics2D.h"
#include "CImageManager.h"

namespace GameTutor
{
	class SkyBox
	{
	public:
		SkyBox(char* filenameLeft, char* filenameRight, char* filenameTop, char* filenameBottom, char* filenameNear, char* filenameFar);
		void Render();
		~SkyBox();
	private:
		float skyBoxLeft[18];
		float skyBoxRight[18];
		float skyBoxTop[18];
		float skyBoxBottom[18];
		float skyBoxNear[18];
		float skyBoxFar[18];

		float TexSkyBoxLeft[18];
		float TexSkyBoxRight[18];
		float TexSkyBoxTop[18];
		float TexSkyBoxBottom[18];
		float TexSkyBoxNear[18];
		float TexSkyBoxFar[18];

		//texture handle
		GLuint leftTexHandle;
		GLuint rightTexHandle;
		GLuint topTexHandle;
		GLuint bottomTexHandle;
		GLuint farTexHandle;
		GLuint nearTexHandle;

		char* fleft;
		char* fright;
		char* ftop;
		char* fbottom;
		char* fnear;
		char* ffar;

	public:
		Matrix* mWorldMatrix;

	};
}

#endif