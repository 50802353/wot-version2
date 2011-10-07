#pragma once

#include "esUtil.h"

class Skybox
{
	GLuint		hProgram;
	int		a_vertices;
	int		a_uv;

	int		u_projection;
	int		u_view;
	int		u_world;
	int		u_texture;

	//Texture
	/*GLuint		topTextID;
	GLuint		bottomTextID;
	GLuint		leftTextID;
	GLuint		rightTextID;
	GLuint		backTextID;
	GLuint		frontTextID;*/
	
	GLuint		textureID;

	//float textCoor[

	//Matrix
	ESMatrix	mWorld;
	ESMatrix*	mView;
	ESMatrix*	mProjection;

	float *verticesArray;
	/*float frontTextCoorArray[18];
	float topTextCoorArray[18];*/
	
	int numVertices;
	int numFaces;

public:
	Skybox(char *objFilePath, char *topTextPath, char* bottomTextPath,
		char* leftTextPath, char* rightTextPath,
		char* backTextPath, char* frontTextPath,
		GLuint _hProgram);
	~Skybox();

	void Draw();
	void SetProjection(ESMatrix *_mView, ESMatrix *_mProjection);
};