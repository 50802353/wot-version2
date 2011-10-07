#ifndef __MATRIX_H__
#define __MATRIX_H__

#include "header.h"

namespace GameTutor
{
	#define PI 3.1415926535897932384626433832795f
	enum AXIS {X_AXIS, Y_AXIS, Z_AXIS};

	class Vector
	{
	protected:
		float data[4];
	public:
		Vector();
		Vector(float x, float y, float z, float w);
		Vector(float*);
		Vector operator = (const Vector);
		float* GetData();
		void Normalize();

	};

	class Matrix
	{
	protected:
		float data[4][4];
	public:
		Matrix();
		Matrix(float*);
		Matrix operator = (const Matrix);
		bool operator == (const Matrix);
		void Multiply (const Matrix);
		void Multiply (float* data);
		void LoadIdentity();
		void Translate(float x, float y, float z);
		void Rotate(float angle, AXIS axis);
		void Rotate(float angle, float x, float y, float z);
		void Scale(float x, float y, float z);
		void Frustume(float left, float right, float bottom, float top, float near, float far);
		void Perspective(float fovy, float aspect, float nearZ, float farZ);
		float* GetData();
		void Inverse();
		void Ortho(float left, float right, float bottom, float top, float nearZ, float farZ);
		bool Decompose_Pos_AngleZ(float &x, float &y, float &z, float &angle);
		Vector MultVector(Vector v);
	};

	
}
#endif