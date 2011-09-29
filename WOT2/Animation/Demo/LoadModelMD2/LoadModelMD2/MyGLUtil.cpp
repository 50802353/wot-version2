#include "MyGLUtil.h"
#include "esUtil.h"
#include <stdlib.h>
#include <stdio.h>
#include "esUtil_win.h"
#include "MyUtil.h"

GLuint LoadShader ( GLenum type, const char *shaderSrc )
{
   GLuint shader;
   GLint compiled;
   
   // Create the shader object
   shader = glCreateShader ( type );

   if ( shader == 0 )
   	return 0;

   // Load the shader source
   glShaderSource ( shader, 1, &shaderSrc, NULL );
   
   // Compile the shader
   glCompileShader ( shader );

   // Check the compile status
   glGetShaderiv ( shader, GL_COMPILE_STATUS, &compiled );

   if ( !compiled ) 
   {
      GLint infoLen = 0;

      glGetShaderiv ( shader, GL_INFO_LOG_LENGTH, &infoLen );
      
      if ( infoLen > 1 )
      {
         char* infoLog = (char*)malloc (sizeof(char) * infoLen );

         glGetShaderInfoLog ( shader, infoLen, NULL, infoLog );
         esLogMessage ( "Error compiling shader:\n%s\n", infoLog );            
         
         free ( infoLog );
      }

      glDeleteShader ( shader );
      return 0;
   }

   return shader;

}

//Load Program
GLuint CreateProgram(GLuint _vertexShader, GLuint _fragmentShader)
{
	GLuint hProgram;
	int linked;

	// Create the program object
	hProgram = glCreateProgram ( );

	if ( hProgram == 0 )
	  return 0;

	glAttachShader ( hProgram, _vertexShader );
	glAttachShader ( hProgram, _fragmentShader );


	// Link the program
	glLinkProgram ( hProgram );

	// Check the link status
	glGetProgramiv ( hProgram, GL_LINK_STATUS, &linked );

	if ( !linked ) 
	{
	  GLint infoLen = 0;

	  glGetProgramiv ( hProgram, GL_INFO_LOG_LENGTH, &infoLen );
	  
	  if ( infoLen > 1 )
	  {
		 char* infoLog = (char*)malloc (sizeof(char) * infoLen );

		 glGetProgramInfoLog ( hProgram, infoLen, NULL, infoLog );
		 esLogMessage ( "Error linking program:\n%s\n", infoLog );            
	     
		 free ( infoLog );
	  }

	  glDeleteProgram ( hProgram );
	  return 0;
	}

	return hProgram;
}

void SetCamera(ESMatrix* result, float x, float y, float z, float xAngle, float yAngle, float zAngle)
{

	ESMatrix temp;
	esMatrixLoadIdentity(&temp);
	esMatrixLoadIdentity(result);
	
	esRotate(&temp,xAngle,1.0f,0.0f,0.0f);
	esMatrixMultiply(result,&temp,result);

	esRotate(&temp,yAngle,0.0f,1.0f,0.0f);
	esMatrixMultiply(result,&temp,result);

	esRotate(&temp,zAngle,0.0f,0.0f,1.0f);
	esMatrixMultiply(result,&temp,result);

	esTranslate(&temp,x,y,z);
	esMatrixMultiply(result,&temp,result);
}

void CreateTexture(GLuint *textureID, char* filePath, int* width, int* height)
{
	char* buffer;
	glGenTextures(1,textureID);
	glBindTexture(GL_TEXTURE_2D,*textureID);
	buffer = esLoadTGA(filePath,width,height);
	glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,*width,*height,0,GL_RGB,GL_UNSIGNED_BYTE,buffer);
	free(buffer);
}

void CreateTextureCubeMap(GLuint *textureID, char *topTextPath, char* bottomTextPath,
		char* leftTextPath, char* rightTextPath,
		char* backTextPath, char* frontTextPath)
{
	char* buffer;
	int width, height;

	glGenTextures(1,textureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP,*textureID);
	
	buffer = esLoadTGA(rightTextPath,&width,&height);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X,0,GL_RGB,width,height,0,GL_RGB,GL_UNSIGNED_BYTE,buffer);
	free(buffer);

	buffer = esLoadTGA(leftTextPath,&width,&height);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X,0,GL_RGB,width,height,0,GL_RGB,GL_UNSIGNED_BYTE,buffer);
	free(buffer);

	buffer = esLoadTGA(topTextPath,&width,&height);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y,0,GL_RGB,width,height,0,GL_RGB,GL_UNSIGNED_BYTE,buffer);
	free(buffer);

	buffer = esLoadTGA(bottomTextPath,&width,&height);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,0,GL_RGB,width,height,0,GL_RGB,GL_UNSIGNED_BYTE,buffer);
	free(buffer);

	buffer = esLoadTGA(frontTextPath,&width,&height);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z,0,GL_RGB,width,height,0,GL_RGB,GL_UNSIGNED_BYTE,buffer);
	free(buffer);

	buffer = esLoadTGA(backTextPath,&width,&height);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z,0,GL_RGB,width,height,0,GL_RGB,GL_UNSIGNED_BYTE,buffer);
	free(buffer);
}