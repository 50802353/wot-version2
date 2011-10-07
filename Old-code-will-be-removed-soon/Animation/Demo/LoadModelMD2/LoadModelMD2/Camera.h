#pragma once

#include "esUtil.h"
class Camera
{
private:
	float x;
	float y;
	float z;

	float xAngle;
	float yAngle;
	float zAngle;

	ESMatrix mView;
	ESMatrix mProjection;

public:
	Camera();
	
	void SetIdentityViewMat();
	void SetProjection(float fovy, float aspect, float zNear, float zFar);
	void SetLocation(float _x, float _y, float _z);
	
	void RotateXAngle(float _xAngle);
	void RotateYAngle(float _yAngle);
	void RotateZAngle(float _zAngle);

	void TranslateX(float _x);
	void TranslateY(float _y);
	void TranslateZ(float _z);

	void LookAt(float xPos, float yPos, float zPos, float xTarget, float yTarget, float zTarget);

	float GetX();
	float GetY();
	float GetZ();
	float GetXAngle();
	float GetYAngle();
	float GetZAngle();
	ESMatrix* GetViewMat();
	ESMatrix* GetProjectionMat();
	
};