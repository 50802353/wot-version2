#include "Model.h"

CModel::CModel(const char* filename)
{
	posInfo = new PositionInfo();
	//initialize world matrix for object
	esMatrixLoadIdentity(&mWorldMatrix);

	//Load object file
	readObjectFile(filename,this->numVertices,this->afVertices,this->numNormal,this->afNormal,this->numTextcoord,this->afTextCoord,this->numFace,this->afFaceVertices,this->afFaceNormal,this->afFaceTextcoord);
	//get bound box
	initBoundBox();
	updatePosition();
}

CModel::~CModel(void)
{
}

void CModel::updateModel(ESMatrix matrix)
{
	esMatrixMultiply(&mWorldMatrix,&matrix,&mWorldMatrix);
	//function use to update the value of xMax,xMin,...
	updatePosition();
}

void CModel::updatePosition()
{
	Vec3f vtA,vtB,vtC,vtD,vtE,vtF,vtG,vtH;
	vtA = multiplyVertice(boundBox.vA,&mWorldMatrix.m[0][0]);
	vtB = multiplyVertice(boundBox.vB,&mWorldMatrix.m[0][0]);
	vtC = multiplyVertice(boundBox.vC,&mWorldMatrix.m[0][0]);
	vtD = multiplyVertice(boundBox.vD,&mWorldMatrix.m[0][0]);
	vtE = multiplyVertice(boundBox.vE,&mWorldMatrix.m[0][0]);
	vtF = multiplyVertice(boundBox.vF,&mWorldMatrix.m[0][0]);
	vtG = multiplyVertice(boundBox.vG,&mWorldMatrix.m[0][0]);
	vtH = multiplyVertice(boundBox.vH,&mWorldMatrix.m[0][0]);

	posInfo->xMax = findMax(vtA[0],vtB[0],vtC[0],vtD[0],vtE[0],vtF[0],vtG[0],vtH[0]);
	posInfo->xMin = findMin(vtA[0],vtB[0],vtC[0],vtD[0],vtE[0],vtF[0],vtG[0],vtH[0]);

	posInfo->yMax = findMax(vtA[1],vtB[1],vtC[1],vtD[1],vtE[1],vtF[1],vtG[1],vtH[1]);
	posInfo->yMin = findMin(vtA[1],vtB[1],vtC[1],vtD[1],vtE[1],vtF[1],vtG[1],vtH[1]);

	posInfo->zMax = findMax(vtA[2],vtB[2],vtC[2],vtD[2],vtE[2],vtF[2],vtG[2],vtH[2]);
	posInfo->zMin = findMin(vtA[2],vtB[2],vtC[2],vtD[2],vtE[2],vtF[2],vtG[2],vtH[2]);
}

Vec3f CModel::multiplyVertice(Vec3f vertice, float* matrix)
{
	Vec3f result;
	result[0] = matrix[0]*vertice[0] + matrix[4]*vertice[1] + matrix[8]*vertice[2] + matrix[12];
	result[1] = matrix[1]*vertice[0] + matrix[5]*vertice[1] + matrix[9]*vertice[2] + matrix[13];
	result[2] = matrix[2]*vertice[0] + matrix[6]*vertice[1] + matrix[10]*vertice[2]+ matrix[14];
	return result;
}

float CModel::findMax(float a, float b, float c, float d, float e, float f, float g, float h)
{
	a = a>b?a:b;
	c = c>d?c:d;
	a = a>c?a:c;
	//-----------
	e = e>f?e:f;
	g = g>h?g:h;
	e = e>g?e:g;

	return (a>e?a:e);
}

float CModel::findMin(float a, float b, float c, float d, float e, float f, float g, float h)
{
	a = a<b?a:b;
	c = c<d?c:d;
	a = a<c?a:c;
	//-----------
	e = e<f?e:f;
	g = g<h?g:h;
	e = e<g?e:g;

	return (a<e?a:e);
}

void CModel::initBoundBox()
{
	float xMax,xMin,yMax,yMin,zMax,zMin;
	xMax = afVertices[0];
	xMin = xMax;

	yMax = afVertices[1];
	yMin = xMax;

	zMax = afVertices[2];
	zMin = xMax;

	for(int i = 3; i < 3*numVertices; i++)
	{
		int z = i % 3;
		switch(z)
		{
		case 0:
			if(afVertices[i] > xMax) xMax = afVertices[i];
			if(afVertices[i] < xMin) xMin = afVertices[i];
			break;
		case 1:
			if(afVertices[i] > yMax) yMax = afVertices[i];
			if(afVertices[i] < yMin) yMin = afVertices[i];
			break;
		case 2:
			if(afVertices[i] > zMax) zMax = afVertices[i];
			if(afVertices[i] < zMin) zMin = afVertices[i];
			break;
		}
		float xDeff = (xMax - xMin)/10;
		xDeff = xDeff > 0? xDeff:-xDeff;
		float yDeff = (yMax - yMin)/10;
		yDeff = yDeff > 0? yDeff:-yDeff;
		float zDeff = (zMax - zMin)/10;
		zDeff = zDeff > 0? zDeff:-zDeff;
		xMax -= xDeff;
		xMin += xDeff;
		yMax -= yDeff;
		yMin += yDeff;
		zMax -= zDeff;
		zMin += zDeff;
		//create bound box
		//--A
		boundBox.vA[0] = xMin;
		boundBox.vA[1] = yMax;
		boundBox.vA[2] = zMin;
		//--B
		boundBox.vB[0] = xMax;
		boundBox.vB[1] = yMax;
		boundBox.vB[2] = zMin;
		//--C
		boundBox.vC[0] = xMax;
		boundBox.vC[1] = yMax;
		boundBox.vC[2] = zMax;
		//--D
		boundBox.vD[0] = xMin;
		boundBox.vD[1] = yMax;
		boundBox.vD[2] = zMax;
		//--E
		boundBox.vE[0] = xMin;
		boundBox.vE[1] = yMin;
		boundBox.vE[2] = zMin;
		//--F
		boundBox.vF[0] = xMax;
		boundBox.vF[1] = yMin;
		boundBox.vF[2] = zMin;
		//--G
		boundBox.vG[0] = xMax;
		boundBox.vG[1] = yMin;
		boundBox.vG[2] = zMax;
		//--H
		boundBox.vH[0] = xMin;
		boundBox.vH[1] = yMin;
		boundBox.vH[2] = zMax;
	}
}