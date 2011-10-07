#include "MyMatrix.h"

MyMatrix::MyMatrix(void)
{
	for(int i=0;i<4;i++)
	{
		for(int j=0;j<4;j++)
		{
			m[i][j] = 0.0f;
		}
	}
}
MyMatrix::MyMatrix(MyMatrix *mt)
{
	float *temp = mt->ToArray();
	for(int i=0;i<4;i++)
	{
		for(int j=0;j<4;j++)
		{
			m[i][j] = temp[i*4+j];
		}
	}
	delete []mt;
}
MyMatrix::~MyMatrix(void)
{

}
//void MyMatrix::CreateViewMatrix(float xPos, float yPos, float zPos)//,
////float xRot, float yRotY, float zRot,
////float angle)
//{
//	Translation(xPos,yPos,zPos);
//}
void MyMatrix::CreateFrutum(float xLeft, float xRight, float yBottom, float yTop, float zNear, float zFar)
{
	float       xDelta = xRight - xLeft;
	float       yDelta = yTop - yBottom;
	float       zDelta = zFar - zNear;

	if ( (zNear <= 0.0f) || (zFar <= 0.0f) ||
		(xDelta <= 0.0f) || (yDelta <= 0.0f) || (zDelta <= 0.0f) )
		return;

	m[0][0] = 2.0f * zNear / xDelta;
	m[0][1] = m[0][2] = m[0][3] = 0.0f;

	m[1][1] = 2.0f * zNear / yDelta;
	m[1][0] = m[1][2] = m[1][3] = 0.0f;

	m[2][0] = (xRight + xLeft) / xDelta;
	m[2][1] = (yTop + yBottom) / yDelta;
	m[2][2] = -(zNear + zFar) / zDelta;
	m[2][3] = -1.0f;

	m[3][2] = -2.0f * zNear * zFar / zDelta;
	m[3][0] = m[3][1] = m[3][3] = 0.0f;
}
void MyMatrix::CreatePerspective(float fovy, float aspect, float nearZ, float farZ)
{
	float frustumW, frustumH;

	frustumH = tanf( fovy / 360.0f * PI ) * nearZ;
	frustumW = frustumH * aspect;

	CreateFrutum(-frustumW, frustumW, -frustumH, frustumH, nearZ, farZ );
}
void MyMatrix::LoadIndentity()
{
	for(int i=0;i<4;i++)
	{
		for(int j=0;j<4;j++)
		{
			m[i][j] = 0.0;
		}
	}
	m[0][0] = m[1][1] = m[2][2] = m[3][3] = 1.0;
}
void MyMatrix::MatrixMultiply(MyMatrix *matrixA, MyMatrix *matrixB)
{
	MyMatrix *temp = new MyMatrix();

	for (int i=0; i<4; i++)
	{
		temp->m[i][0] =	(matrixA->m[i][0] * matrixB->m[0][0]) +
						(matrixA->m[i][1] * matrixB->m[1][0]) +
						(matrixA->m[i][2] * matrixB->m[2][0]) +
						(matrixA->m[i][3] * matrixB->m[3][0]) ;

		temp->m[i][1] =	(matrixA->m[i][0] * matrixB->m[0][1]) + 
						(matrixA->m[i][1] * matrixB->m[1][1]) +
						(matrixA->m[i][2] * matrixB->m[2][1]) +
						(matrixA->m[i][3] * matrixB->m[3][1]) ;

		temp->m[i][2] =	(matrixA->m[i][0] * matrixB->m[0][2]) + 
						(matrixA->m[i][1] * matrixB->m[1][2]) +
						(matrixA->m[i][2] * matrixB->m[2][2]) +
						(matrixA->m[i][3] * matrixB->m[3][2]) ;

		temp->m[i][3] =	(matrixA->m[i][0] * matrixB->m[0][3]) + 
						(matrixA->m[i][1] * matrixB->m[1][3]) +
						(matrixA->m[i][2] * matrixB->m[2][3]) +
						(matrixA->m[i][3] * matrixB->m[3][3]) ;
	}

	this->Copy(temp);
	delete temp;
}
void MyMatrix::MatrixSubtraction(MyMatrix *matrixA, MyMatrix *matrixB)
{
	for(int i=0;i<4;i++)
	{
		for(int j=0;j<4;j++)
		{
			m[i][j] = matrixA->m[i][j] - matrixB->m[i][j];
		}
	}
}
void MyMatrix::MatrixSum(MyMatrix *matrixA, MyMatrix *matrixB)
{
	for(int i=0;i<4;i++)
	{
		for(int j=0;j<4;j++)
		{
			m[i][j] = matrixA->m[i][j] + matrixB->m[i][j];
		}
	}
}
void MyMatrix::MatrixTransposition(MyMatrix *matrixSource)
{
	float *temp = this->ToArray();
	for(int i=0;i<4;i++)
	{
		for(int j=0;j<4;j++)
		{
			m[j][i] = temp[i*4+j];
		}
	}
	delete []temp;
}
void MyMatrix::RotateX(float angle)
{
	float sinAngle, cosAngle;
	sinAngle = sinf ( angle * PI / 180.0f );
	cosAngle = cosf ( angle * PI / 180.0f );
	MyMatrix temp;
	temp.LoadIndentity();
	temp.m[1][1] = temp.m[2][2] = cosAngle;
	temp.m[1][2] = sinAngle;
	temp.m[2][1] = -sinAngle;
	MatrixMultiply(&temp,this);
}
void MyMatrix::RotateY(float angle)
{
	float sinAngle, cosAngle;
	sinAngle = sinf ( angle * PI / 180.0f );
	cosAngle = cosf ( angle * PI / 180.0f );
	MyMatrix temp;
	temp.LoadIndentity();
	temp.m[0][0] = temp.m[2][2] = cosAngle;
	temp.m[2][0] = sinAngle;
	temp.m[0][2] = -sinAngle;
	MatrixMultiply(&temp,this);
}
void MyMatrix::RotateZ(float angle)
{
	float sinAngle, cosAngle;
	sinAngle = sinf ( angle * PI / 180.0f );
	cosAngle = cosf ( angle * PI / 180.0f );
	MyMatrix temp;
	temp.LoadIndentity();
	temp.m[0][0] = temp.m[1][1] = cosAngle;
	temp.m[0][1] = sinAngle;
	temp.m[1][0] = -sinAngle;
	MatrixMultiply(&temp,this);
}
void MyMatrix::Rotate(float angle, float x, float y, float z)
{
	float sinAngle, cosAngle;
	float mag = sqrtf(x * x + y * y + z * z);

	sinAngle = sinf ( angle * PI / 180.0f );
	cosAngle = cosf ( angle * PI / 180.0f );

	if ( mag > 0.0f )
	{
		float xx, yy, zz, xy, yz, zx, xs, ys, zs;
		float oneMinusCos;
		MyMatrix rotMat;
		x /= mag;
		y /= mag;
		z /= mag;

		xx = x * x;
		yy = y * y;
		zz = z * z;
		xy = x * y;
		yz = y * z;
		zx = z * x;
		xs = x * sinAngle;
		ys = y * sinAngle;
		zs = z * sinAngle;
		oneMinusCos = 1.0f - cosAngle;

		rotMat.m[0][0] = (oneMinusCos * xx) + cosAngle;
		rotMat.m[0][1] = (oneMinusCos * xy) - zs;
		rotMat.m[0][2] = (oneMinusCos * zx) + ys;
		rotMat.m[0][3] = 0.0F; 

		rotMat.m[1][0] = (oneMinusCos * xy) + zs;
		rotMat.m[1][1] = (oneMinusCos * yy) + cosAngle;
		rotMat.m[1][2] = (oneMinusCos * yz) - xs;
		rotMat.m[1][3] = 0.0F;

		rotMat.m[2][0] = (oneMinusCos * zx) - ys;
		rotMat.m[2][1] = (oneMinusCos * yz) + xs;
		rotMat.m[2][2] = (oneMinusCos * zz) + cosAngle;
		rotMat.m[2][3] = 0.0F; 

		rotMat.m[3][0] = 0.0F;
		rotMat.m[3][1] = 0.0F;
		rotMat.m[3][2] = 0.0F;
		rotMat.m[3][3] = 1.0F;

		MatrixMultiply( &rotMat, this);
	}
}

void MyMatrix::Translation(float x, float y, float z)
{
	/*m[3][0] += (m[0][0] * x + m[1][0] * y + m[2][0] * z);
    m[3][1] += (m[0][1] * x + m[1][1] * y + m[2][1] * z);
    m[3][2] += (m[0][2] * x + m[1][2] * y + m[2][2] * z);
    m[3][3] += (m[0][3] * x + m[1][3] * y + m[2][3] * z);*/

	for(int i=0;i<4;i++)
		m[3][i] += m[0][i] * x + m[1][i] * y + m[2][i] * z;
}
void MyMatrix::Scale(float x, float y, float z)
{
	for(int i=0;i<4;i++)
	{
		m[0][i] *= x;
		m[1][i] *= y;
		m[2][i] *= z;
	}
}
float* MyMatrix::ToArray()
{
	float *fArray = new float[16];
	for(int i=0;i<4;i++)
	{
		for(int j=0;j<4;j++)
		{
			fArray[i*4+j] = m[i][j];
		}
	}
	return fArray;
}
void MyMatrix::Copy(MyMatrix *mt)
{
	for(int i=0;i<4;i++)
	{
		for(int j=0;j<4;j++)
		{
			m[i][j] = mt->m[i][j];
		}
	}
}

void MyMatrix::Copy(float *fArray)
{
	for(int i=0;i<4;i++)
	{
		for(int j=0;j<4;j++)
		{
			m[i][j] = fArray[4*i+j];
		}
	}
}