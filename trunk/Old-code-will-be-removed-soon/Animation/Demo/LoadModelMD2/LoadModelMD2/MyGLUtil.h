#ifndef  _MYGLUTIL_H
#define _MYGLUTIL_H

#include "esUtil.h"

GLuint LoadShader ( GLenum type, const char *shaderSrc );
GLuint CreateProgram(GLuint _vertexShader, GLuint _fragmentShader);
void SetCamera(ESMatrix* result, float x, float y, float z, float xAngle, float yAngle, float zAngle);
void CreateTexture(GLuint *textureID, char* filePath, int* width, int* height);
void CreateTextureCubeMap(GLuint *textureID, char *topTextPath, char* bottomTextPath,
		char* leftTextPath, char* rightTextPath,
		char* backTextPath, char* frontTextPath);

#endif