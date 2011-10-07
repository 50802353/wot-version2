#ifndef __CCAMERA_H__
#define __CCAMERA_H__

#include "Matrix.h"
#include "CSingleton.h"

namespace GameTutor
{
	class CCamera
	{
	public:
		CCamera()
		{
			m_fMatrixV = new Matrix();
			m_fMatrixP = new Matrix();
		}
		void CameraLookat(	float centerx, float centery, float centerz,
							float lookx = 0.0f, float looky = 0.0f, float lookz = 0.0f,
							float upx = 0.0f, float upy = 1.0f, float upz = 0.0f);
		void CameraTranslate(float x, float y, float z);
		void CameraRotate(float angle, float x, float y, float z);
		void CameraScale(float x, float y, float z);
		void CameraPerspective(float fovy, float aspect, float zNear, float zFar);
		void CameraFrustume(float left, float right, float bottom, float top, float nearZ, float farZ);
		void CameraOrtho(float left, float right, float bottom, float top, float nearZ, float farZ);
		void CameraLoadIdentity();

		Matrix* GetViewMatrix();
		Matrix* GetProjectMatrix();

	private:
		Matrix *m_fMatrixV;
		Matrix *m_fMatrixP;
	};

	class CCamera2D:public CCamera,public CSingleton<CCamera2D>
	{
		friend class  CSingleton<CCamera2D>;
	};

	class CCamera3D:public CCamera,public CSingleton<CCamera3D>
	{
		friend class  CSingleton<CCamera3D>;
	};
}

#endif