
#include <stdlib.h>
#include <stdio.h>
#include "esUtil.h"
#include "load_Shader.h"
#include "Model.h"
#include "CollisionManager.h"

typedef struct
{
   // Handle to a program object
   GLuint programObject;
   GLuint programObjectSky;

	//mvp matrix
   ESMatrix mViewMatrix;
   ESMatrix mProjectionMatrix;

   ESMatrix mViewMatrixSky;
   ESMatrix mProjectionMatrixSky;

   GLint iVerticesLoc;
   GLint u_texture_loc;
   GLint u_textcoord_loc;
   GLint mWorldMatrixLoc;
   GLint mViewMatrixLoc;
   GLint mProjectionMatrixLoc;
   
   GLuint u_texture[2];
   GLuint u_skyTexture;
	

   //object attributes
		//model 1
   CModel* model1;
   CModel* model2;
		//skydom
	GLint numVertices3;
	GLfloat* afVertices3;
	GLint numNormal3;
	GLfloat* afNormal3;
	GLint numTextcoord3;
	GLfloat* afTextCoord3;
	GLint numFace3;
	GLfloat *afFaceVertices3,*afFaceTextcoord3,*afFaceNormal3;
	ESMatrix mWorldMatrix3;

} UserData;

///
// Create a shader object, load the shader source, and
// compile the shader.
//
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


///
// Initialize the shader and program object
//
int Init ( ESContext *esContext )
{
   UserData *userData = (UserData *)esContext->userData;
   //-----------------Initialize MVP Matrix--------------------------------]
   userData->model1 = new CModel("./Woman1.obj");
   ESMatrix temp;
   esMatrixLoadIdentity(&temp);
   esScale(&temp,0.1,0.1,0.1);
   userData->model1->updateModel(temp);
   esMatrixLoadIdentity(&temp);
   esTranslate(&temp,3.0,0.0,0.0);
   userData->model1->updateModel(temp);

   userData->model2 = new CModel("./Woman2.obj");
   esMatrixLoadIdentity(&temp);
   esScale(&temp,0.1,0.1,0.1);
   userData->model2->updateModel(temp);
   esMatrixLoadIdentity(&temp);
   esTranslate(&temp,-3.0,0.0,0.0);
   userData->model2->updateModel(temp);


   esMatrixLoadIdentity(&userData->mWorldMatrix3);
   esScale(&userData->mWorldMatrix3,20.0,20.0,20.0);

   esMatrixLoadIdentity(&userData->mViewMatrix);
   esTranslate(&userData->mViewMatrix,0.0,0.0,-2.0);

   esMatrixLoadIdentity(&userData->mViewMatrixSky);
   esTranslate(&userData->mViewMatrixSky,0.0,0.0,-1.0);

   esMatrixLoadIdentity(&userData->mProjectionMatrix);
   esMatrixLoadIdentity(&userData->mProjectionMatrixSky);

   //-----------------Initialize Projection Matrix--------------------------
   //esFrustum(&userData->mProjectionMatrix,-3.0,3.0,-3.0,3.0,1.0,10.0);
   //esOrtho(&userData->mProjectionMatrix,-3.0,3.0,-3.0,3.0,1.0,10.0);
   esPerspective(&userData->mProjectionMatrix,70.0,4.0/3.0,1.0,50.0);
   esPerspective(&userData->mProjectionMatrixSky,70.0,4.0/3.0,1.0,50.0);

  
   //-------Skybox-----------------
	readObjectFile("./cube.obj",
	   userData->numVertices3,userData->afVertices3,
	   userData->numNormal3,userData->afNormal3,
	   userData->numTextcoord3,userData->afTextCoord3,
	   userData->numFace3,userData->afFaceVertices3,userData->afFaceNormal3,userData->afFaceTextcoord3);

   //create texture
   glGenTextures(2,userData->u_texture);
   glGenTextures(1,&userData->u_skyTexture);
   int w,h;

		//Sarah
   char* imgSarah = esLoadTGA("sarah_color.tga",&w,&h);
   glActiveTexture(GL_TEXTURE0);
   glBindTexture(GL_TEXTURE_2D, userData->u_texture[0]);
   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0,GL_RGB, GL_UNSIGNED_BYTE, imgSarah);
   glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST); 
   glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST); 
   glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT); 
   glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);

		//Betty
   char* imgBetty = esLoadTGA("betty_color.tga",&w,&h);
   glActiveTexture(GL_TEXTURE0);
   glBindTexture(GL_TEXTURE_2D, userData->u_texture[1]);
   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0,GL_RGB, GL_UNSIGNED_BYTE, imgBetty);
   glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST); 
   glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST); 
   glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT); 
   glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT); 

   //skybox
   glActiveTexture(GL_TEXTURE1);
   glBindTexture(GL_TEXTURE_CUBE_MAP, userData->u_skyTexture);
   glTexParameteri(GL_TEXTURE_CUBE_MAP,GL_TEXTURE_MIN_FILTER,GL_NEAREST); 
   glTexParameteri(GL_TEXTURE_CUBE_MAP,GL_TEXTURE_MAG_FILTER,GL_NEAREST); 
   glTexParameteri(GL_TEXTURE_CUBE_MAP,GL_TEXTURE_WRAP_S,GL_REPEAT); 
   glTexParameteri(GL_TEXTURE_CUBE_MAP,GL_TEXTURE_WRAP_T,GL_REPEAT); 
   //Back Face
   char* imgSkyBack = esLoadTGA("skybox_back.tga",&w,&h);
   glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, GL_RGB, w, h, 0,GL_RGB, GL_UNSIGNED_BYTE, imgSkyBack);

   //Bottom Face
   char* imgSkyBot = esLoadTGA("skybox_bottom.tga",&w,&h);
   glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, GL_RGB, w, h, 0,GL_RGB, GL_UNSIGNED_BYTE, imgSkyBot);

   //Front Face
   char* imgSkyFront = esLoadTGA("skybox_front.tga",&w,&h);
   glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, GL_RGB, w, h, 0,GL_RGB, GL_UNSIGNED_BYTE, imgSkyFront);

   //Left Face
   char* imgSkyLeft = esLoadTGA("skybox_left.tga",&w,&h);
   glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, GL_RGB, w, h, 0,GL_RGB, GL_UNSIGNED_BYTE, imgSkyLeft);

   //Right Face
   char* imgSkyRight = esLoadTGA("skybox_right.tga",&w,&h);
   glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, GL_RGB, w, h, 0,GL_RGB, GL_UNSIGNED_BYTE, imgSkyRight); 

   //Top Face
   char* imgSkyTop = esLoadTGA("skybox_top.tga",&w,&h);
   glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, GL_RGB, w, h, 0,GL_RGB, GL_UNSIGNED_BYTE, imgSkyTop);

   //-----------------Load PROGRAM ----------------------------------------
	char * vShaderStr = ReadFile("./vshader.glsl");
	char * fShaderStr = ReadFile("./fshader.glsl");

   GLuint vertexShader;
   GLuint fragmentShader;
   GLuint programObject;
   GLint linked;

   // Load the vertex/fragment shaders
   vertexShader = LoadShader ( GL_VERTEX_SHADER, (char*)vShaderStr );
   fragmentShader = LoadShader ( GL_FRAGMENT_SHADER, (char*)fShaderStr );

   // Create the program object
   programObject = glCreateProgram ( );
   
   if ( programObject == 0 )
      return 0;

   glAttachShader ( programObject, vertexShader );
   glAttachShader ( programObject, fragmentShader );

  
  // Bind vPosition to attribute 0   
  // glBindAttribLocation ( programObject, iVerticesLoc, "a_position" );

   // Link the program
   glLinkProgram ( programObject );

   // Check the link status
   glGetProgramiv ( programObject, GL_LINK_STATUS, &linked );

   if ( !linked ) 
   {
      GLint infoLen = 0;

      glGetProgramiv ( programObject, GL_INFO_LOG_LENGTH, &infoLen );
      
      if ( infoLen > 1 )
      {
         char* infoLog = (char*)malloc (sizeof(char) * infoLen );

         glGetProgramInfoLog ( programObject, infoLen, NULL, infoLog );
         esLogMessage ( "Error linking program:\n%s\n", infoLog );            
         
         free ( infoLog );
      }

      glDeleteProgram ( programObject );
      return FALSE;
   }

   // Store the program object
   userData->programObject = programObject;

   //-----------------Load PROGRAM FOR SKY -----------------------------------
	char * vShaderStrSky = ReadFile("./vshader_skyBox.glsl");
	char * fShaderStrSky = ReadFile("./fshader_skyBox.glsl");

   GLuint vertexShaderSky;
   GLuint fragmentShaderSky;
   GLuint programObjectSky;
   GLint linkedSky;

   // Load the vertex/fragment shaders
   vertexShaderSky = LoadShader ( GL_VERTEX_SHADER, (char*)vShaderStrSky );
   fragmentShaderSky = LoadShader ( GL_FRAGMENT_SHADER, (char*)fShaderStrSky );

   // Create the program object
   programObjectSky = glCreateProgram ( );
   
   if ( programObjectSky == 0 )
      return 0;

   glAttachShader ( programObjectSky, vertexShaderSky );
   glAttachShader ( programObjectSky, fragmentShaderSky );

  
  // Bind vPosition to attribute 0   
  // glBindAttribLocation ( programObject, iVerticesLoc, "a_position" );

   // Link the program
   glLinkProgram ( programObjectSky );

   // Check the link status
   glGetProgramiv ( programObjectSky, GL_LINK_STATUS, &linkedSky );

   if ( !linkedSky ) 
   {
      GLint infoLen = 0;

      glGetProgramiv ( programObjectSky, GL_INFO_LOG_LENGTH, &infoLen );
      
      if ( infoLen > 1 )
      {
         char* infoLog = (char*)malloc (sizeof(char) * infoLen );

         glGetProgramInfoLog ( programObjectSky, infoLen, NULL, infoLog );
         esLogMessage ( "Error linking program:\n%s\n", infoLog );            
         
         free ( infoLog );
      }

      glDeleteProgram ( programObjectSky );
      return FALSE;
   }

   // Store the program object
   userData->programObjectSky = programObjectSky;
   //----------------------------------------------------------------------------
   glClearColor ( 0.0f, 0.0f, 0.0f, 0.0f );
   return TRUE;
}

///
// Draw a triangle using the shader pair created in Init()
//
void Draw ( ESContext *esContext )
{
	UserData *userData = (UserData *)esContext->userData;
	
	//Enable Blending
	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	//Enable Depth Test Mode
	glEnable(GL_DEPTH_TEST);
	//Enable Culling Face
	//glEnable(GL_CULL_FACE);
	// Set the viewport
	glViewport ( 0, 0, esContext->width, esContext->height );

	glClear ( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );	

	//glDepthMask(GL_FALSE);

	// Use the program object 1
	glUseProgram ( userData->programObject );
	//get location
	userData->iVerticesLoc = glGetAttribLocation ( userData->programObject , "a_position");
	userData->u_texture_loc = glGetUniformLocation(userData->programObject, "u_texture");
	userData->u_textcoord_loc = glGetAttribLocation(userData->programObject, "a_uv");
	userData->mWorldMatrixLoc = glGetUniformLocation(userData->programObject, "u_mWorldMatrix");
	userData->mViewMatrixLoc = glGetUniformLocation(userData->programObject, "u_mViewMatrix");
	userData->mProjectionMatrixLoc = glGetUniformLocation(userData->programObject, "u_mProjectionMatrix");
	glEnableVertexAttribArray ( userData->iVerticesLoc );
	glEnableVertexAttribArray(userData->u_textcoord_loc); 

	//draw woman1
	//active texture
	glActiveTexture(GL_TEXTURE0); 
	glUniform1i(userData->u_texture_loc, 0);
	
	glBindTexture(GL_TEXTURE_2D, userData->u_texture[0]); 
	glVertexAttribPointer ( userData->iVerticesLoc, 3, GL_FLOAT, GL_FALSE, 0, userData->model1->afFaceVertices );
	glVertexAttribPointer(userData->u_textcoord_loc,3,GL_FLOAT,GL_FALSE,0, userData->model1->afFaceTextcoord);

	glUniformMatrix4fv(userData->mWorldMatrixLoc,1,GL_FALSE,&userData->model1->mWorldMatrix.m[0][0]);
	glUniformMatrix4fv(userData->mViewMatrixLoc,1,GL_FALSE,&userData->mViewMatrix.m[0][0]);
	glUniformMatrix4fv(userData->mProjectionMatrixLoc,1,GL_FALSE,&userData->mProjectionMatrix.m[0][0]);

	glDrawArrays ( GL_TRIANGLES, 0, 3*userData->model1->numFace );

	//draw woman2
	//active texture
	glActiveTexture(GL_TEXTURE0); 
	glUniform1i(userData->u_texture_loc, 0);
	
	glBindTexture(GL_TEXTURE_2D, userData->u_texture[1]); 
	glVertexAttribPointer ( userData->iVerticesLoc, 3, GL_FLOAT, GL_FALSE, 0, userData->model2->afFaceVertices );
	glVertexAttribPointer(userData->u_textcoord_loc,3,GL_FLOAT,GL_FALSE,0, userData->model2->afFaceTextcoord);

	glUniformMatrix4fv(userData->mWorldMatrixLoc,1,GL_FALSE,&userData->model2->mWorldMatrix.m[0][0]);
	glUniformMatrix4fv(userData->mViewMatrixLoc,1,GL_FALSE,&userData->mViewMatrix.m[0][0]);
	glUniformMatrix4fv(userData->mProjectionMatrixLoc,1,GL_FALSE,&userData->mProjectionMatrix.m[0][0]);

	glDrawArrays ( GL_TRIANGLES, 0, 3*userData->model2->numFace );

	//draw skybox
	// Use the program object sky
	glUseProgram ( userData->programObjectSky );
	//get location
	userData->iVerticesLoc = glGetAttribLocation ( userData->programObjectSky , "a_position");
	userData->u_texture_loc = glGetUniformLocation(userData->programObjectSky, "u_texture");
	userData->u_textcoord_loc = glGetAttribLocation(userData->programObjectSky, "a_uv");
	userData->mWorldMatrixLoc = glGetUniformLocation(userData->programObjectSky, "u_mWorldMatrix");
	userData->mViewMatrixLoc = glGetUniformLocation(userData->programObjectSky, "u_mViewMatrix");
	userData->mProjectionMatrixLoc = glGetUniformLocation(userData->programObjectSky, "u_mProjectionMatrix");

	glEnableVertexAttribArray ( userData->iVerticesLoc );
	glEnableVertexAttribArray(userData->u_textcoord_loc); 

	glActiveTexture(GL_TEXTURE0);
	glUniform1i(userData->u_texture_loc,0);

	glBindTexture(GL_TEXTURE_CUBE_MAP, userData->u_skyTexture); 
	
	glVertexAttribPointer ( userData->iVerticesLoc, 3, GL_FLOAT, GL_FALSE, 0, userData->afFaceVertices3 );
	glVertexAttribPointer(userData->u_textcoord_loc,3,GL_FLOAT,GL_FALSE,0, userData->afFaceVertices3);

	glUniformMatrix4fv(userData->mWorldMatrixLoc,1,GL_FALSE,&userData->mWorldMatrix3.m[0][0]);
	glUniformMatrix4fv(userData->mViewMatrixLoc,1,GL_FALSE,&userData->mViewMatrixSky.m[0][0]);
	glUniformMatrix4fv(userData->mProjectionMatrixLoc,1,GL_FALSE,&userData->mProjectionMatrixSky.m[0][0]);

	//glCullFace(GL_BACK);
	glDrawArrays ( GL_TRIANGLES, 0, userData->numFace3*3);
	//glCullFace(GL_FRONT);
	eglSwapBuffers ( esContext->eglDisplay, esContext->eglSurface );
}

void Key(ESContext *esContext,unsigned char esKey, int esX, int esY){
	UserData* userData = (UserData*) esContext->userData;
	ESMatrix view;
	esMatrixLoadIdentity(&view);
	ESMatrix model;
	esMatrixLoadIdentity(&model);
	ESMatrix projection;
	esMatrixLoadIdentity(&projection);
	if(esKey == 'w')
	{
		//UserData* userDate = (UserData*) esContext->userData;
		esTranslate(&view,0.0,0.1,0.0);
		userData->model1->updateModel(view);
		if (occurCollision(userData->model1->posInfo,userData->model2->posInfo))
		{
			userData->model2->updateModel(view);
		}
		//esMatrixMultiply(&userData->mViewMatrix,&view,&userData->mViewMatrix);
	}
	else if(esKey == 's')
	{
		esTranslate(&view,0.0,-0.1,0.0);
		userData->model1->updateModel(view);
		if (occurCollision(userData->model1->posInfo,userData->model2->posInfo))
		{
			userData->model2->updateModel(view);
		}
		//esMatrixMultiply(&userData->mViewMatrix,&view,&userData->mViewMatrix);
	}
	else if(esKey == 'a')
	{
		esTranslate(&view,-0.1,0.0,0.0);
		userData->model1->updateModel(view);
		if (occurCollision(userData->model1->posInfo,userData->model2->posInfo))
		{
			userData->model2->updateModel(view);
		}
		//esMatrixMultiply(&userData->mViewMatrix,&view,&userData->mViewMatrix);
	}
	else if(esKey == 'd')
	{
		esTranslate(&view,0.1,0.0,0.0);
		userData->model1->updateModel(view);
		if (occurCollision(userData->model1->posInfo,userData->model2->posInfo))
		{
			userData->model2->updateModel(view);
		}
		//esMatrixMultiply(&userData->mViewMatrix,&view,&userData->mViewMatrix);
	}
	else if(esKey == 'j')
	{
		esScale(&view,1.1,1.1,1.1);
		esMatrixMultiply(&userData->mViewMatrix,&view,&userData->mViewMatrix);
	}
	else if(esKey == 'k')
	{
		esScale(&view,0.9,0.9,0.9);
		esMatrixMultiply(&userData->mViewMatrix,&view,&userData->mViewMatrix);
	}
	else if(esKey == 'r')
	{
		esRotate(&view,10.0,0.0,1.0,0.0);
		esMatrixMultiply(&userData->mViewMatrix,&view,&userData->mViewMatrix);
	}
	else if(esKey == 't')
	{
		esRotate(&view,10.0,1.0,0.0,0.0);
		esMatrixMultiply(&userData->mViewMatrix,&view,&userData->mViewMatrix);
	}
	else if(esKey == 'i')
	{
		esRotate(&view,10.0,0.0,1.0,0.0);
		esMatrixMultiply(&userData->mViewMatrixSky,&view,&userData->mViewMatrixSky);
	}
	else if(esKey == 'o')
	{
		esRotate(&view,10.0,1.0,0.0,0.0);
		esMatrixMultiply(&userData->mViewMatrixSky,&view,&userData->mViewMatrixSky);
	}
	
}

void Update(ESContext *esContext, float deltaTime){

	UserData* userData = (UserData*) esContext->userData;
	ESMatrix view;
	esMatrixLoadIdentity(&view);
	esRotate(&view,0.05,0.0,1.0,0.0);
	
	esMatrixMultiply(&userData->mViewMatrixSky,&view,&userData->mViewMatrixSky);
}

int main ( int argc, char *argv[] )
{
   ESContext esContext;
   UserData  userData;

   esInitContext ( &esContext );
   esContext.userData = &userData;

   esCreateWindow ( &esContext, "Hello Triangle", 800, 600, ES_WINDOW_RGB );
   
   if ( !Init ( &esContext ) )
      return 0;

   esRegisterDrawFunc ( &esContext, Draw );
   esRegisterKeyFunc(&esContext,Key);
   esRegisterUpdateFunc(&esContext,Update);
   esMainLoop ( &esContext );
}
