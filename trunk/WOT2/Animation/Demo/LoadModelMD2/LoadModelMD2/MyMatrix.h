#pragma once
#include <math.h>
#define PI 3.1415926535897932384626433832795f
class MyMatrix
{
public:
	float m[4][4];
public:
	/*void CreateViewMatrix(
		float xPos = 0.0, float yPos = 0.0, float zPos = 0.0);*/
	void CreateFrutum(float xLeft, float xRight, float yBottom, float yTop, float zNear, float zFar);
	void CreatePerspective(float fovy, float aspect, float nearZ, float farZ);
	void LoadIndentity();
	void MatrixMultiply(MyMatrix *matrixA, MyMatrix *matrixB);
	void MatrixSubtraction(MyMatrix *matrixA, MyMatrix *matrixB);
	void MatrixSum(MyMatrix *matrixA, MyMatrix *matrixB);
	void MatrixTransposition(MyMatrix *matrixSource);

//	void Transpose(MyMatrix* result, MyMatrix* src)
//{
//	if(result!=src)
//	{
//		for(int i=0;i<4;i++)
//			for(int j=0;j<4;j++)
//				(*result).m[i][j]=(*src).m[i][j];
//	}
//
//	for(int i=0;i<4;i++)
//	{
//		for(int j=0;j<i;j++)
//		{
//			Swap((*result).m[i][j],(*result).m[j][i]);
//		}
//	}
//}

	void RotateX(float angle);
	void RotateY(float angle);
	void RotateZ(float angle);

	// rotate by cos(anpha)
	void Rotate(float angle, float x, float y, float z);
	void Translation(float x, float y, float z);
	void Scale(float x, float y, float z);

	float* ToArray();
	float* GetM(){return &m[0][0];}

	void Copy(MyMatrix *mt);
	void Copy(float* fArray);
	MyMatrix(void);
	MyMatrix(MyMatrix*);
	~MyMatrix(void);
};
