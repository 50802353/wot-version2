#ifndef _GRAPHICS_H_
#define _GRAPHICS_H_

#include "GLES2/gl2.h"
#include "MyMatrix.h"

#ifdef ANDROID
#include "GLES2/gl2.h"
#endif

enum MatrixMode
{
	MM_MODEL,
	MM_VIEW,
	MM_PROJECTION
};

class Graphics
{

private:

	static Graphics* instance;
	
	unsigned int texProgram;

	//Attribute and uniform location
	int a_vertices;
	int a_uv;
	int u_projection;
	int u_view;
	int u_world;
	int u_texture;	

	//Array
	float*	verticesArray;
	float*  textCoorArray; 

	int textID;

	//Matrix
	MyMatrix* mView;
	MyMatrix* mProjection;
	MyMatrix* mWorld;

	

public:

	static Graphics* GetInstance();
	~Graphics();

	void Init();

	static GLuint LoadShader ( GLenum type, const char *shaderSrc );
	static GLuint CreateProgram(GLuint _vertexShader, GLuint _fragmentShader);

	void SetViewMatrix(MyMatrix *_mView);
	void SetProjectionMatrix(MyMatrix *_mProjection);
	void SetWorldMatrix(MyMatrix *_mWorld);
	
	/*void Translate(int MM_MATRIX_MODE, float x, float y, float z);
	void Rotate(int MM_MATRIX_MODE, float angle, float x, float y, float z);
	void Perspective(float  fovy,  float aspect,  float zNear,  float zFar);*/
	//void MatrixLoadIdentity(int MM_MATRIX_MODE);


	
	void Clear();
	void ClearColor(float r, float g, float b, float a);

	void SetVerticesArray(float *_verticesArray);
	void SetTextCoorArray(float *_textCoorArray);
	void SetTextureID(int _textID);

	////Set textID, verticesArray, textCoorArray, textureID before draw, set World, View, Projection matrix if neccessary
	void DrawModel(int numFaces);
};

#endif