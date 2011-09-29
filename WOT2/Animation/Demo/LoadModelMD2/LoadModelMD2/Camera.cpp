#include "Camera.h"
#include "esUtil.h"

Camera::Camera()
{
	x=y=z=xAngle=yAngle=zAngle=0;
	esMatrixLoadIdentity(&mView);
	SetProjection(45,4.0f/3.0f,0.2f,10.0f);
	SetLocation(0.0f,0.0f,0.0f);
	RotateXAngle(0.0f);
	RotateYAngle(0.0f);
	RotateZAngle(0.0f);
}

void Camera::SetIdentityViewMat()
{
	x=y=z=xAngle=yAngle=zAngle=0;
	esMatrixLoadIdentity(&mView);
}
void Camera::SetProjection(float fovy, float aspect, float zNear, float zFar)
{
	esMatrixLoadIdentity(&mProjection);
	esPerspective(&mProjection,fovy,aspect,zNear,zFar);
}

void Camera::SetLocation(float _x, float _y, float _z)
{
	esTranslate(&mView,x,y,z);

	x	=_x;
	y	=_y;
	z	=_z;

	//esMatrixLoadIdentity(&mView);
	esTranslate(&mView,-x,-y,-z);
}

void Camera::RotateXAngle(float _xAngle)
{
	xAngle	+=_xAngle;
	esRotate(&mView,-_xAngle,1,0,0);
}

void Camera::RotateYAngle(float _yAngle)
{
	yAngle	+=_yAngle;
	esRotate(&mView,-_yAngle,0,1,0);
}

void Camera::RotateZAngle(float _zAngle)
{
	zAngle	+=_zAngle;
	esRotate(&mView,-_zAngle,0,0,1);
}

float Camera::GetX()
{
	return x;
}

float Camera::GetY()
{
	return y;
}

float Camera::GetZ()
{
	return z;
}

void Camera::TranslateX(float _x)
{
	x	+=_x;
	esTranslate(&mView,-_x,0,0);
}

void Camera::TranslateY(float _y)
{
	y	+=_y;
	esTranslate(&mView,0,-_y,0);
}

void Camera::TranslateZ(float _z)
{
	z	+=_z;
	esTranslate(&mView,0,0,-_z);
}

float Camera::GetXAngle()
{
	return xAngle;
}

float Camera::GetYAngle()
{
	return yAngle;
}

float Camera::GetZAngle()
{
	return zAngle;
}

ESMatrix* Camera::GetViewMat()
{
	return &mView;
}

ESMatrix* Camera::GetProjectionMat()
{
	return &mProjection;
}

void Camera::LookAt(float xPos, float yPos, float zPos, float xTarget, float yTarget, float zTarget)
{
	esMatrixLoadIdentity(&mView);
	
}