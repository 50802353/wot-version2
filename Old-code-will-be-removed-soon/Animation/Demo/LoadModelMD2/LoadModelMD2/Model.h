#include "esUtil.h"

#pragma once

class Model
{
private :

	//Program, attribute and uniform
	GLuint		hProgram;
	int		a_vertices;
	int		a_uv;

	int		u_projection;
	int		u_view;
	int		u_world;
	int		u_texture;

	//Texture
	GLuint		textureID;

	//Matrix
	ESMatrix	mWorld;
	ESMatrix*	mView;
	ESMatrix*	mProjection;

	//Position
	float x, y, z;
	float xAngle, yAngle, zAngle;

	//Array
	float *verticesArray;
	float *normalArray;
	float *textCoorArray;

	int numVertices;
	int numFaces;

public :

	Model();
	Model(char *objFilePath, char *tgaFilePath,GLuint _hProgram);
	~Model();

	void Draw();

	void SetProjection(ESMatrix *_mView, ESMatrix *_mProjection);
	void SetLocation(float _x, float _y, float _z);
	void SetIdentityWorldMat();
	
	void RotateXAngle(float _xAngle);
	void RotateYAngle(float _yAngle);
	void RotateZAngle(float _zAngle);

	void TranslateX(float _x);
	void TranslateY(float _y);
	void TranslateZ(float _z);

	float GetX();
	float GetY();
	float GetZ();
	float GetXAngle();
	float GetYAngle();
	float GetZAngle();
};