#include "CSkyBox.h"

namespace GameTutor
{
	SkyBox::SkyBox(char* filenameLeft, char* filenameRight, char* filenameTop, char* filenameBottom, char* filenameNear, char* filenameFar)
	{
		//right
		//-1
		Log("1");
		skyBoxRight[0] = 1.0f;
		skyBoxRight[1] = 1.0f;
		skyBoxRight[2] = 1.0f;
		//-2
		skyBoxRight[3] = 1.0f;
		skyBoxRight[4] = 1.0f;
		skyBoxRight[5] = -1.0f;
		//-4
		skyBoxRight[6] = 1.0f;
		skyBoxRight[7] = -1.0f;
		skyBoxRight[8] = 1.0f;
		//-2
		skyBoxRight[9] = 1.0f;
		skyBoxRight[10] = 1.0f;
		skyBoxRight[11] = -1.0f;
		//-3
		skyBoxRight[12] = 1.0f;
		skyBoxRight[13] = -1.0f;
		skyBoxRight[14] = -1.0f;
		//-4
		skyBoxRight[15] = 1.0f;
		skyBoxRight[16] = -1.0f;
		skyBoxRight[17] = 1.0f;

		//top
		//-6
		skyBoxTop[0] = -1.0f;
		skyBoxTop[1] = 1.0f;
		skyBoxTop[2] = -1.0f;
		//-2
		skyBoxTop[3] = 1.0f;
		skyBoxTop[4] = 1.0f;
		skyBoxTop[5] = -1.0f;
		//-1
		skyBoxTop[6] = 1.0f;
		skyBoxTop[7] = 1.0f;
		skyBoxTop[8] = 1.0f;
		//-6
		skyBoxTop[9] = -1.0f;
		skyBoxTop[10] = 1.0f;
		skyBoxTop[11] = -1.0f;
		//-1
		skyBoxTop[12] = 1.0f;
		skyBoxTop[13] = 1.0f;
		skyBoxTop[14] = 1.0f;
		//-5
		skyBoxTop[15] = -1.0f;
		skyBoxTop[16] = 1.0f;
		skyBoxTop[17] = 1.0f;

		//near
		//-5
		skyBoxNear[0] = -1.0f;
		skyBoxNear[1] = 1.0f;
		skyBoxNear[2] = 1.0f;
		//-1
		skyBoxNear[3] = 1.0f;
		skyBoxNear[4] = 1.0f;
		skyBoxNear[5] = 1.0f;
		//-4
		skyBoxNear[6] = 1.0f;
		skyBoxNear[7] = -1.0f;
		skyBoxNear[8] = 1.0f;
		//-5
		skyBoxNear[9] = -1.0f;
		skyBoxNear[10] = 1.0f;
		skyBoxNear[11] = 1.0f;
		//-4
		skyBoxNear[12] = 1.0f;
		skyBoxNear[13] = -1.0f;
		skyBoxNear[14] = 1.0f;
		//-8
		skyBoxNear[15] = -1.0f;
		skyBoxNear[16] = -1.0f;
		skyBoxNear[17] = 1.0f;

		//bottom
		//-7
		skyBoxBottom[0] = -1.0f;
		skyBoxBottom[1] = -1.0f;
		skyBoxBottom[2] = -1.0f;
		//-3
		skyBoxBottom[3] = 1.0f;
		skyBoxBottom[4] = -1.0f;
		skyBoxBottom[5] = -1.0f;
		//-4
		skyBoxBottom[6] = 1.0f;
		skyBoxBottom[7] = -1.0f;
		skyBoxBottom[8] = 1.0f;
		//-7
		skyBoxBottom[9] = -1.0f;
		skyBoxBottom[10] = -1.0f;
		skyBoxBottom[11] = -1.0f;
		//-4
		skyBoxBottom[12] = 1.0f;
		skyBoxBottom[13] = -1.0f;
		skyBoxBottom[14] = 1.0f;
		//-8
		skyBoxBottom[15] = -1.0f;
		skyBoxBottom[16] = -1.0f;
		skyBoxBottom[17] = 1.0f;

		//left
		//-5
		skyBoxLeft[0] = -1.0f;
		skyBoxLeft[1] = 1.0f;
		skyBoxLeft[2] = 1.0f;
		//-6
		skyBoxLeft[3] = -1.0f;
		skyBoxLeft[4] = 1.0f;
		skyBoxLeft[5] = -1.0f;
		//-7
		skyBoxLeft[6] = -1.0f;
		skyBoxLeft[7] = -1.0f;
		skyBoxLeft[8] = -1.0f;
		//-5
		skyBoxLeft[9] = -1.0f;
		skyBoxLeft[10] = 1.0f;
		skyBoxLeft[11] = 1.0f;
		//-7
		skyBoxLeft[12] = -1.0f;
		skyBoxLeft[13] = -1.0f;
		skyBoxLeft[14] = -1.0f;
		//-8
		skyBoxLeft[15] = -1.0f;
		skyBoxLeft[16] = -1.0f;
		skyBoxLeft[17] = 1.0f;

		//Far
		//-6
		skyBoxFar[0] = -1.0f;
		skyBoxFar[1] = 1.0f;
		skyBoxFar[2] = -1.0f;
		//-2
		skyBoxFar[3] = 1.0f;
		skyBoxFar[4] = 1.0f;
		skyBoxFar[5] = -1.0f;
		//-3
		skyBoxFar[6] = 1.0f;
		skyBoxFar[7] = -1.0f;
		skyBoxFar[8] = -1.0f;
		//-6
		skyBoxFar[9] = -1.0f;
		skyBoxFar[10] = 1.0f;
		skyBoxFar[11] = -1.0f;
		//-3
		skyBoxFar[12] = 1.0f;
		skyBoxFar[13] = -1.0f;
		skyBoxFar[14] = -1.0f;
		//-7
		skyBoxFar[15] = -1.0f;
		skyBoxFar[16] = -1.0f;
		skyBoxFar[17] = -1.0f;

		//TexCoord
		//right
		//-1
		TexSkyBoxRight[0] = 0.0f;
		TexSkyBoxRight[1] = 1.0f;
		TexSkyBoxRight[2] = 0.0f;
		//-2
		TexSkyBoxRight[3] = 1.0f;
		TexSkyBoxRight[4] = 1.0f;
		TexSkyBoxRight[5] = 0.0f;
		//-4
		TexSkyBoxRight[6] = 0.0f;
		TexSkyBoxRight[7] = 0.0f;
		TexSkyBoxRight[8] = 0.0f;
		//-2
		TexSkyBoxRight[9] = 1.0f;
		TexSkyBoxRight[10] = 1.0f;
		TexSkyBoxRight[11] = 0.0f;
		//-3
		TexSkyBoxRight[12] = 1.0f;
		TexSkyBoxRight[13] = 0.0f;
		TexSkyBoxRight[14] = 0.0f;
		//-4
		TexSkyBoxRight[15] = 0.0f;
		TexSkyBoxRight[16] = 0.0f;
		TexSkyBoxRight[17] = 0.0f;

		//-top
		//-6
		TexSkyBoxTop[0] = 0.0f;
		TexSkyBoxTop[1] = 1.0f;
		TexSkyBoxTop[2] = 0.0f;
		//-2
		TexSkyBoxTop[3] = 1.0f;
		TexSkyBoxTop[4] = 1.0f;
		TexSkyBoxTop[5] = 0.0f;
		//-1
		TexSkyBoxTop[6] = 1.0f;
		TexSkyBoxTop[7] = 0.0f;
		TexSkyBoxTop[8] = 0.0f;
		//-6
		TexSkyBoxTop[9] = 0.0f;
		TexSkyBoxTop[10] = 1.0f;
		TexSkyBoxTop[11] = 0.0f;
		//-1
		TexSkyBoxTop[12] = 1.0f;
		TexSkyBoxTop[13] = 0.0f;
		TexSkyBoxTop[14] = 0.0f;
		//-5
		TexSkyBoxTop[15] = 0.0f;
		TexSkyBoxTop[16] = 0.0f;
		TexSkyBoxTop[17] = 0.0f;
		
		//-near
		//-5
		TexSkyBoxNear[0] = 0.0f;
		TexSkyBoxNear[1] = 1.0f;
		TexSkyBoxNear[2] = 0.0f;
		//-1
		TexSkyBoxNear[3] = 1.0f;
		TexSkyBoxNear[4] = 1.0f;
		TexSkyBoxNear[5] = 0.0f;
		//-4
		TexSkyBoxNear[6] = 1.0f;
		TexSkyBoxNear[7] = 0.0f;
		TexSkyBoxNear[8] = 0.0f;
		//-5
		TexSkyBoxNear[9] = 0.0f;
		TexSkyBoxNear[10] = 1.0f;
		TexSkyBoxNear[11] = 0.0f;
		//-4
		TexSkyBoxNear[12] = 1.0f;
		TexSkyBoxNear[13] = 0.0f;
		TexSkyBoxNear[14] = 0.0f;
		//-8
		TexSkyBoxNear[15] = 0.0f;
		TexSkyBoxNear[16] = 0.0f;
		TexSkyBoxNear[17] = 0.0f;

		//-bottom
		//-7
		TexSkyBoxBottom[0] = 0.0f;
		TexSkyBoxBottom[1] = 0.0f;
		TexSkyBoxBottom[2] = 0.0f;
		//-3
		TexSkyBoxBottom[3] = 1.0f;
		TexSkyBoxBottom[4] = 0.0f;
		TexSkyBoxBottom[5] = 0.0f;
		//-4
		TexSkyBoxBottom[6] = 1.0f;
		TexSkyBoxBottom[7] = 1.0f;
		TexSkyBoxBottom[8] = 0.0f;
		//-7
		TexSkyBoxBottom[9] = 0.0f;
		TexSkyBoxBottom[10] = 0.0f;
		TexSkyBoxBottom[11] = 0.0f;
		//-4
		TexSkyBoxBottom[12] = 1.0f;
		TexSkyBoxBottom[13] = 1.0f;
		TexSkyBoxBottom[14] = 0.0f;
		//-8
		TexSkyBoxBottom[15] = 0.0f;
		TexSkyBoxBottom[16] = 1.0f;
		TexSkyBoxBottom[17] = 0.0f;

		//-left
		//-5
		TexSkyBoxLeft[0] = 1.0f;
		TexSkyBoxLeft[1] = 1.0f;
		TexSkyBoxLeft[2] = 0.0f;
		//-6
		TexSkyBoxLeft[3] = 0.0f;
		TexSkyBoxLeft[4] = 1.0f;
		TexSkyBoxLeft[5] = 0.0f;
		//-7
		TexSkyBoxLeft[6] = 0.0f;
		TexSkyBoxLeft[7] = 0.0f;
		TexSkyBoxLeft[8] = 0.0f;
		//-5
		TexSkyBoxLeft[9] = 1.0f;
		TexSkyBoxLeft[10] = 1.0f;
		TexSkyBoxLeft[11] = 0.0f;
		//-7
		TexSkyBoxLeft[12] = 0.0f;
		TexSkyBoxLeft[13] = 0.0f;
		TexSkyBoxLeft[14] = 0.0f;
		//-8
		TexSkyBoxLeft[15] = 1.0f;
		TexSkyBoxLeft[16] = 0.0f;
		TexSkyBoxLeft[17] = 0.0f;

		//-far
		//-6
		TexSkyBoxFar[0] = 1.0f;
		TexSkyBoxFar[1] = 1.0f;
		TexSkyBoxFar[2] = 0.0f;
		//-2
		TexSkyBoxFar[3] = 0.0f;
		TexSkyBoxFar[4] = 1.0f;
		TexSkyBoxFar[5] = 0.0f;
		//-3
		TexSkyBoxFar[6] = 0.0f;
		TexSkyBoxFar[7] = 0.0f;
		TexSkyBoxFar[8] = 0.0f;
		//-6
		TexSkyBoxFar[9] = 1.0f;
		TexSkyBoxFar[10] = 1.0f;
		TexSkyBoxFar[11] = 0.0f;
		//-3
		TexSkyBoxFar[12] = 0.0f;
		TexSkyBoxFar[13] = 0.0f;
		TexSkyBoxFar[14] = 0.0f;
		//-7
		TexSkyBoxFar[15] = 1.0f;
		TexSkyBoxFar[16] = 0.0f;
		TexSkyBoxFar[17] = 0.0f;

		//get texture ID
		Log("2");

		CImageManager::GetInstance()->AddImage<CFileWin32Driver>(filenameLeft,true);
		CImageManager::GetInstance()->Get(filenameLeft)->FreeBuffer();
		leftTexHandle = (CImageManager::GetInstance()->Get(filenameLeft))->GetTextureID();

		CImageManager::GetInstance()->AddImage<CFileWin32Driver>(filenameRight,true);
		CImageManager::GetInstance()->Get(filenameRight)->FreeBuffer();
		rightTexHandle = (CImageManager::GetInstance()->Get(filenameRight))->GetTextureID();

		CImageManager::GetInstance()->AddImage<CFileWin32Driver>(filenameTop,true);
		CImageManager::GetInstance()->Get(filenameTop)->FreeBuffer();
		topTexHandle = (CImageManager::GetInstance()->Get(filenameTop))->GetTextureID();

		CImageManager::GetInstance()->AddImage<CFileWin32Driver>(filenameBottom,true);
		CImageManager::GetInstance()->Get(filenameBottom)->FreeBuffer();
		bottomTexHandle = (CImageManager::GetInstance()->Get(filenameBottom))->GetTextureID();

		CImageManager::GetInstance()->AddImage<CFileWin32Driver>(filenameNear,true);
		CImageManager::GetInstance()->Get(filenameNear)->FreeBuffer();
		nearTexHandle = (CImageManager::GetInstance()->Get(filenameNear))->GetTextureID();

		CImageManager::GetInstance()->AddImage<CFileWin32Driver>(filenameFar,true);
		CImageManager::GetInstance()->Get(filenameFar)->FreeBuffer();
		farTexHandle = (CImageManager::GetInstance()->Get(filenameFar))->GetTextureID();

		Log("3");

		fleft = new char[100];fleft = strcpy(fleft,filenameLeft);
		fright = new char[100];fright = strcpy(fright,filenameRight);
		ftop = new char[100];ftop = strcpy(ftop,filenameTop);
		fbottom = new char[100];fbottom = strcpy(fbottom,filenameBottom);
		fnear = new char[100];fnear = strcpy(fnear,filenameNear);
		ffar = new char[100];ffar = strcpy(ffar,filenameFar);
		Log("4");
		mWorldMatrix = new Matrix;
		Log("5");
	}
	void SkyBox::Render()
	{
		/*GameTutor::CGraphics2D::GetInstance()->DrawModel(2,skyBoxLeft,TexSkyBoxLeft,leftTexHandle);
		GameTutor::CGraphics2D::GetInstance()->DrawModel(2,skyBoxRight,TexSkyBoxRight,rightTexHandle);
		GameTutor::CGraphics2D::GetInstance()->DrawModel(2,skyBoxTop,TexSkyBoxTop,topTexHandle);
		GameTutor::CGraphics2D::GetInstance()->DrawModel(2,skyBoxBottom,TexSkyBoxBottom,bottomTexHandle);
		GameTutor::CGraphics2D::GetInstance()->DrawModel(2,skyBoxNear,TexSkyBoxNear,nearTexHandle);
		GameTutor::CGraphics2D::GetInstance()->DrawModel(2,skyBoxFar,TexSkyBoxFar,farTexHandle);*/
		GameTutor::CGraphics2D::GetInstance()->DrawMesh(2, mWorldMatrix, skyBoxLeft, TexSkyBoxLeft, leftTexHandle);
		GameTutor::CGraphics2D::GetInstance()->DrawMesh(2, mWorldMatrix, skyBoxRight, TexSkyBoxRight, rightTexHandle);
		GameTutor::CGraphics2D::GetInstance()->DrawMesh(2, mWorldMatrix, skyBoxTop, TexSkyBoxTop, topTexHandle);
		GameTutor::CGraphics2D::GetInstance()->DrawMesh(2, mWorldMatrix, skyBoxBottom, TexSkyBoxBottom, bottomTexHandle);
		GameTutor::CGraphics2D::GetInstance()->DrawMesh(2, mWorldMatrix, skyBoxNear, TexSkyBoxNear, nearTexHandle);
		GameTutor::CGraphics2D::GetInstance()->DrawMesh(2, mWorldMatrix, skyBoxFar, TexSkyBoxFar, farTexHandle);
	}

	SkyBox::~SkyBox()
	{
		CImageManager::GetInstance()->Free(fleft);
		CImageManager::GetInstance()->Free(fright);
		CImageManager::GetInstance()->Free(ftop);
		CImageManager::GetInstance()->Free(fbottom);
		CImageManager::GetInstance()->Free(fnear);
		CImageManager::GetInstance()->Free(ffar);

		SAFE_DEL_ARRAY(fleft);
		SAFE_DEL_ARRAY(fright);
		SAFE_DEL_ARRAY(ftop);
		SAFE_DEL_ARRAY(fbottom);
		SAFE_DEL_ARRAY(fnear);
		SAFE_DEL_ARRAY(ffar);
	}
}