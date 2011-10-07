#include "Matrix.h"

namespace GameTutor
{	
	Matrix::Matrix()
	{
		LoadIdentity();
	}

	Matrix::Matrix(float* InitData)
	{
		memcpy(data, InitData, sizeof(float)*16);
	}

	void Matrix::LoadIdentity()
	{
		memset(data, 0, sizeof(float)*16);
		data[0][0] = data[1][1] = data[2][2] = data[3][3] = 1;
	}

	Matrix Matrix::operator = (const Matrix M)
	{
		memcpy(data, M.data, sizeof(float)*16);
		return (*this);
	}

	bool Matrix::operator == (const Matrix M)
	{
		return (memcmp(data, M.data, sizeof(float)*16)==0);
	}

	void Matrix::Multiply (const Matrix M)
	{
		Matrix result;
		for (int row=0; row<4; row++)
			for (int col=0; col<4; col++)
			{
				float sum=0;
				for (int i=0; i<4; i++)
					sum += data[i][row]*M.data[col][i];
				result.data[col][row] = sum;
			}
		(*this) = result;
	}

	void Matrix::Multiply(float* data)
	{
		Matrix M(data);
		this->Multiply(M);
	}

	void Matrix::Translate(float x, float y, float z)
	{
		Matrix M;
		M.data[3][0]=x;
		M.data[3][1]=y;
		M.data[3][2]=z;
		this->Multiply(M);
	}

	void Matrix::Rotate(float angle, AXIS axis)
	{
		Matrix M;
		float c = cos(angle/180*3.14159265);
		float s = sin(angle/180*3.14159265);
		int a1,a2;
		switch(axis)
		{
		case X_AXIS:
			a1=1;a2=2;
			break;
		case Y_AXIS:
			a1=2;a2=0;
			break;
		case Z_AXIS:
			a1=0;a2=1;
			break;
		default:
			return;
			break;
		}
		M.data[a1][a1]=M.data[a2][a2]=c;
		M.data[a2][a1]=s;
		M.data[a1][a2]=-s;
		this->Multiply(M);
	}


	void Matrix::Rotate(float angle, float x, float y, float z)
	{
		float sinAngle, cosAngle;
		float mag = sqrtf(x * x + y * y + z * z);

		sinAngle = sinf ( angle * PI / 180.0f );
		cosAngle = cosf ( angle * PI / 180.0f );

		if ( mag > 0.0f )
		{
			float oneMinusCos;
			Matrix M;
			x /= mag;
			y /= mag;
			z /= mag;

			float xx = x * x;
			float yy = y * y;
			float zz = z * z;
			float xy = x * y;
			float yz = y * z;
			float zx = z * x;
			float xs = x * sinAngle;
			float ys = y * sinAngle;
			float zs = z * sinAngle;
			oneMinusCos = 1.0f - cosAngle;

			M.data[0][0] = (oneMinusCos * xx) + cosAngle;
			M.data[0][1] = (oneMinusCos * xy) - zs;
			M.data[0][2] = (oneMinusCos * zx) + ys;
			M.data[0][3] = 0.0F; 

			M.data[1][0] = (oneMinusCos * xy) + zs;
			M.data[1][1] = (oneMinusCos * yy) + cosAngle;
			M.data[1][2] = (oneMinusCos * yz) - xs;
			M.data[1][3] = 0.0F;

			M.data[2][0] = (oneMinusCos * zx) - ys;
			M.data[2][1] = (oneMinusCos * yz) + xs;
			M.data[2][2] = (oneMinusCos * zz) + cosAngle;
			M.data[2][3] = 0.0F; 

			M.data[3][0] = 0.0F;
			M.data[3][1] = 0.0F;
			M.data[3][2] = 0.0F;
			M.data[3][3] = 1.0F;

			this->Multiply(M);
		}
	}




	void Matrix::Scale(float x, float y, float z)
	{
		Matrix M;
		M.data[0][0] = x;
		M.data[1][1] = y;
		M.data[2][2] = z;
		this->Multiply(M);
	}

	void Matrix::Frustume(float f_left, float f_right, float f_bottom, float f_top, float f_near, float f_far)
	{
		float dx = f_right-f_left;
		float dy = f_top-f_bottom;
		float dz = f_far-f_near;
		Matrix M;
		M.data[0][0]=2*f_near/dx;
		M.data[1][1]=2*f_near/dy;
		M.data[2][2]=-(f_far+f_near)/dz;
		M.data[3][3]=0;
		M.data[2][0]=(f_right+f_left)/dx;
		M.data[2][1]=(f_top+f_bottom)/dy;
		M.data[3][2]=-2*f_far*f_near/dz;
		M.data[2][3]=-1;
		this->Multiply(M);
	}

	void Matrix::Perspective(float fovy, float aspect, float nearZ, float farZ)
	{
		float frustumH = tanf( fovy / 360.0f * PI ) * nearZ;
		float frustumW = frustumH * aspect;
		Frustume(-frustumW, frustumW, -frustumH, frustumH, nearZ, farZ );
	}

	float* Matrix::GetData()
	{
		return (float*)data;
	}

	void Matrix::Inverse() //chua kiem tra, copy paste
	{
		float inv[16], det;
		inv[0] =   data[1][1]*data[2][2]*data[3][3] - data[1][1]*data[3][2]*data[2][3] - data[1][2]*data[2][1]*data[3][3]
		+ data[1][2]*data[3][1]*data[2][3] + data[1][3]*data[2][1]*data[3][2] - data[1][3]*data[3][1]*data[2][2];
		inv[1] =  -data[0][1]*data[2][2]*data[3][3] + data[0][1]*data[3][2]*data[2][3] + data[0][2]*data[2][1]*data[3][3]
		- data[0][2]*data[3][1]*data[2][3] - data[0][3]*data[2][1]*data[3][2] + data[0][3]*data[3][1]*data[2][2];
		inv[2] =   data[0][1]*data[1][2]*data[3][3] - data[0][1]*data[3][2]*data[1][3] - data[0][2]*data[1][1]*data[3][3]
		+ data[0][2]*data[3][1]*data[1][3] + data[0][3]*data[1][1]*data[3][2] - data[0][3]*data[3][1]*data[1][2];
		inv[3] = -data[0][1]*data[1][2]*data[2][3] + data[0][1]*data[2][2]*data[1][3] + data[0][2]*data[1][1]*data[2][3]
		- data[0][2]*data[2][1]*data[1][3] - data[0][3]*data[1][1]*data[2][2] + data[0][3]*data[2][1]*data[1][2];
		inv[4] =  -data[1][0]*data[2][2]*data[3][3] + data[1][0]*data[3][2]*data[2][3] + data[1][2]*data[2][0]*data[3][3]
		- data[1][2]*data[3][0]*data[2][3] - data[1][3]*data[2][0]*data[3][2] + data[1][3]*data[3][0]*data[2][2];
		inv[5] =   data[0][0]*data[2][2]*data[3][3] - data[0][0]*data[3][2]*data[2][3] - data[0][2]*data[2][0]*data[3][3]
		+ data[0][2]*data[3][0]*data[2][3] + data[0][3]*data[2][0]*data[3][2] - data[0][3]*data[3][0]*data[2][2];
		inv[6] =  -data[0][0]*data[1][2]*data[3][3] + data[0][0]*data[3][2]*data[1][3] + data[0][2]*data[1][0]*data[3][3]
		- data[0][2]*data[3][0]*data[1][3] - data[0][3]*data[1][0]*data[3][2] + data[0][3]*data[3][0]*data[1][2];
		inv[7] =  data[0][0]*data[1][2]*data[2][3] - data[0][0]*data[2][2]*data[1][3] - data[0][2]*data[1][0]*data[2][3]
		+ data[0][2]*data[2][0]*data[1][3] + data[0][3]*data[1][0]*data[2][2] - data[0][3]*data[2][0]*data[1][2];
		inv[8] =   data[1][0]*data[2][1]*data[3][3] - data[1][0]*data[3][1]*data[2][3] - data[1][1]*data[2][0]*data[3][3]
		+ data[1][1]*data[3][0]*data[2][3] + data[1][3]*data[2][0]*data[3][1] - data[1][3]*data[3][0]*data[2][1];
		inv[9] =  -data[0][0]*data[2][1]*data[3][3] + data[0][0]*data[3][1]*data[2][3] + data[0][1]*data[2][0]*data[3][3]
		- data[0][1]*data[3][0]*data[2][3] - data[0][3]*data[2][0]*data[3][1] + data[0][3]*data[3][0]*data[2][1];
		inv[10] =  data[0][0]*data[1][1]*data[3][3] - data[0][0]*data[3][1]*data[1][3] - data[0][1]*data[1][0]*data[3][3]
		+ data[0][1]*data[3][0]*data[1][3] + data[0][3]*data[1][0]*data[3][1] - data[0][3]*data[3][0]*data[1][1];
		inv[11] = -data[0][0]*data[1][1]*data[2][3] + data[0][0]*data[2][1]*data[1][3] + data[0][1]*data[1][0]*data[2][3]
		- data[0][1]*data[2][0]*data[1][3] - data[0][3]*data[1][0]*data[2][1] + data[0][3]*data[2][0]*data[1][1];
		inv[12] =  -data[1][0]*data[2][1]*data[3][2] + data[1][0]*data[3][1]*data[2][2] + data[1][1]*data[2][0]*data[3][2]
		- data[1][1]*data[3][0]*data[2][2] - data[1][2]*data[2][0]*data[3][1] + data[1][2]*data[3][0]*data[2][1];
		inv[13] =   data[0][0]*data[2][1]*data[3][2] - data[0][0]*data[3][1]*data[2][2] - data[0][1]*data[2][0]*data[3][2]
		+ data[0][1]*data[3][0]*data[2][2] + data[0][2]*data[2][0]*data[3][1] - data[0][2]*data[3][0]*data[2][1];
		inv[14] = -data[0][0]*data[1][1]*data[3][2] + data[0][0]*data[3][1]*data[1][2] + data[0][1]*data[1][0]*data[3][2]
		- data[0][1]*data[3][0]*data[1][2] - data[0][2]*data[1][0]*data[3][1] + data[0][2]*data[3][0]*data[1][1];
		inv[15] =  data[0][0]*data[1][1]*data[2][2] - data[0][0]*data[2][1]*data[1][2] - data[0][1]*data[1][0]*data[2][2]
		+ data[0][1]*data[2][0]*data[1][2] + data[0][2]*data[1][0]*data[2][1] - data[0][2]*data[2][0]*data[1][1];

		det = data[0][0]*inv[0] + data[1][0]*inv[1] + data[2][0]*inv[2] + data[3][0]*inv[3];
		if (det == 0)
				return;

		det = 1.0 / det;
		for (int i = 0; i < 16; i++)
				inv[i] = inv[i] * det;
		Matrix M(inv);
		*this = M;
	}

	void Matrix::Ortho(float left, float right, float bottom, float top, float nearZ, float farZ)
	{
		float       deltaX = right - left;
		float       deltaY = top - bottom;
		float       deltaZ = farZ - nearZ;
		Matrix    ortho;

		if ( (deltaX == 0.0f) || (deltaY == 0.0f) || (deltaZ == 0.0f) )
			return;

		ortho.data[0][0] = 2.0f / deltaX;
		ortho.data[3][0] = -(right + left) / deltaX;
		ortho.data[1][1] = 2.0f / deltaY;
		ortho.data[3][1] = -(top + bottom) / deltaY;
		ortho.data[2][2] = -2.0f / deltaZ;
		ortho.data[3][2] = -(nearZ + farZ) / deltaZ;

		this->Multiply(ortho);
	}

	Vector Matrix::MultVector(Vector v)
	{
		float result[4];
		float* vdata = v.GetData();
		result[0] = this->data[0][0]*vdata[0] + this->data[1][0]*vdata[1] + this->data[2][0]*vdata[2] +this->data[3][0]*vdata[3];
		result[1] = this->data[0][1]*vdata[0] + this->data[1][1]*vdata[1] + this->data[2][1]*vdata[2] +this->data[3][1]*vdata[3];
		result[2] = this->data[0][2]*vdata[0] + this->data[1][2]*vdata[1] + this->data[2][2]*vdata[2] +this->data[3][2]*vdata[3];
		result[3] = this->data[0][3]*vdata[0] + this->data[1][3]*vdata[1] + this->data[2][3]*vdata[2] +this->data[3][3]*vdata[3];
		return Vector(result);
	}

	Vector::Vector()
	{
		data[0] = 0;
		data[1] = 0;
		data[2] = 0;
		data[3] = 1;
	}

	Vector::Vector(float x, float y, float z, float w)
	{
		data[0]= x;
		data[1]= y;
		data[2]= z;
		data[3]= w;
	}

	Vector::Vector(float* InitData)
	{
		memcpy(data, InitData, sizeof(float)*4);
	}

	Vector Vector::operator = (const Vector v)
	{
		memcpy(data, v.data, sizeof(float)*4);
		return (*this);
	}

	float* Vector::GetData()
	{
		return data;
	}

	void Vector::Normalize()
	{
		if (data[3]!=0)
		{
			data[0]/=data[3];
			data[1]/=data[3];
			data[2]/=data[3];
			data[3]=1.0f;
		}
	}

/*	bool Matrix::Decompose_Pos_AngleZ(float &x, float &y, float &z, float &angle)
	{
		float a1 = acos(data[0][0]/data[2][2])/PI*180.0;
		if (a1<0) a1+=360;
		float a2 = asin(data[0][1]/data[2][2])/PI*180.0;
		if (a2<0) a2+=360;
		float a3 = acos(data[1][1]/data[2][2])/PI*180.0;
		if (a3<0) a3+=360;
		float a4 = -asin(data[1][0]/data[2][2])/PI*180.0;
		if (a4<0) a4+=360;
		if ((fabs(a1-a2)<0.001) && (fabs(a1-a3)<0.001) && (fabs(a1-a4)<0.001))
		{
			y = data[3][1]*data[0][0] - data[3][0]*data[0][1];
			x = data[3][0]*data[0][0] + data[3][1]*data[0][1];
			z = data[3][2];
			angle = a1;
			return true;
		}
		x=0;y=0;z=0;angle=0;
		return false;
	}
	*/
}
