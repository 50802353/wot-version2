#pragma once

#include "esUtil.h"
#include "vec3f.h"
#include "ObjectFileReader.h"

typedef struct
{
	Vec3f vA;
	Vec3f vB;
	Vec3f vC;
	Vec3f vD;
	Vec3f vE;
	Vec3f vF;
	Vec3f vG;
	Vec3f vH;
} BoundBox;

typedef struct
{
	float xMax;
	float xMin;
	float yMax;
	float yMin;
	float zMax;
	float zMin;
} PositionInfo;

class CModel
{
public:
	CModel(const char* filename);
	~CModel(void);
	//-----------------------------------
	GLint numVertices;
	GLfloat* afVertices;
	GLint numNormal;
	GLfloat* afNormal;
	GLint numTextcoord;
	GLfloat* afTextCoord;
	GLint numFace;
	GLfloat *afFaceVertices,*afFaceTextcoord,*afFaceNormal;
	ESMatrix mWorldMatrix;
	//collisions
	BoundBox boundBox;
	PositionInfo* posInfo;

	//-----------------------------------
	
	void updateModel(ESMatrix matrix);

private:
	void updatePosition();
	void initBoundBox();
	Vec3f multiplyVertice(Vec3f vertice, float* matrix); 
	float findMax(float a, float b, float c, float d, float e, float f, float g, float h);
	float findMin(float a, float b, float c, float d, float e, float f, float g, float h);
};
