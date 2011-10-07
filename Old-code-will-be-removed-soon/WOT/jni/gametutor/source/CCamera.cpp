#include "CCamera.h"

namespace GameTutor
{
	void CCamera::CameraLookat(	float centerx, float centery, float centerz,
							float lookx, float looky, float lookz,
							float upx, float upy, float upz)
	{

		float dirx = (lookx-centerx);
		float diry = (looky-centery);
		float dirz = (lookz-centerz);
		float dirfrac = sqrtf(dirx*dirx + diry*diry +dirz*dirz);
		dirx/= dirfrac;
		diry/= dirfrac;
		dirz/= dirfrac;

		float upfrac = sqrtf(upx*upx + upy*upy + upz*upz);
		upx/= upfrac;
		upy/= upfrac;
		upz/= upfrac;

		float sidex = diry*upz - dirz*upy;
		float sidey = dirz*upx - dirx*upz;
		float sidez = dirx*upy - diry*upx;

		float vecUpx = sidey*dirz - sidez*diry;
		float vecUpy = sidez*dirx - sidex*dirz;
		float vecUpz = sidex*diry - sidey*dirx;

		float m[4][4];
		m[0][0]=sidex;
		m[1][0]=sidey;
		m[2][0]=sidez;
		m[3][0]=0.0f;
		m[0][1]=vecUpx;
		m[1][1]=vecUpy;
		m[2][1]=vecUpz;
		m[3][1]=0.0f;
		m[0][2]=-dirx;
		m[1][2]=-diry;
		m[2][2]=-dirz;
		m[3][2]=0.0f;
		m[0][3]=0.0f;
		m[1][3]=0.0f;
		m[2][3]=0.0f;
		m[3][3]=1.0f;

		Matrix mLook((float*)m);
		mLook.Translate(-centerx,-centery,-centerz);
		(*m_fMatrixV).Multiply(mLook);
	}

	void CCamera::CameraPerspective(float fovy, float aspect, float zNear, float zFar)
	{
		(*m_fMatrixP).Perspective(fovy, aspect, zNear, zFar);
	}

	void CCamera::CameraFrustume(float left, float right, float bottom, float top, float nearZ, float farZ)
	{
		(*m_fMatrixP).Frustume(left, right, top, bottom, nearZ, farZ);
	}
		
	void CCamera::CameraOrtho(float left, float right, float bottom, float top, float nearZ, float farZ)
	{
		(*m_fMatrixP).Ortho(left, right, top, bottom, nearZ, farZ);
	}

	void CCamera::CameraTranslate(float x, float y, float z)
	{
		(*m_fMatrixV).Translate(x,y,z);
	}

	void CCamera::CameraScale(float x, float y, float z)
	{
		(*m_fMatrixV).Scale(x,y,z);
	}

	void CCamera::CameraRotate(float angle, float x, float y, float z)
	{
		(*m_fMatrixV).Rotate(angle, x, y, z);
	}

	void CCamera::CameraLoadIdentity()
	{
		(*m_fMatrixV).LoadIdentity();
	}
	
	Matrix* CCamera::GetViewMatrix()
	{
		return m_fMatrixV;
	}

	Matrix* CCamera::GetProjectMatrix()
	{
		return m_fMatrixP;
	}
}