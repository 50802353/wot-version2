
#include <stdlib.h>
#include <stdio.h>
#include "esUtil.h"
#include "MyGLUtil.h"
#include "MyUtil.h"


#define DELETE_SAFELY_ARRAY(x) if((x)!=0) delete[](x); (x)=0;

typedef struct
{
   // Handle to a program object
   GLuint programObject;
   GLuint iVerticesLoc;
   GLuint iColorLoc;
   GLuint iUniformProjection;
   GLuint iUniformView;
   GLuint iUniformWorld;
   GLuint u_texture;
   GLuint a_uv;

} UserData;

struct ObjectData
{
	float x, y, z;
	float xAngle, yAngle, zAngle;
	
	float	*verticesArray;
	int		numElementVA;
	GLuint	*verticesIndex;
	
	float	*colorArray;
	int		numElementCA;
	
	float	*normalArray;
	int		numElementNA;
	
	float	*texttureCoorArray;
	int		numElementTA;

	GLuint textureID;
	
	ObjectData()
	{
		x=y=z=xAngle=yAngle=zAngle=0;
	}

	void Destroy()
	{
		DELETE_SAFELY_ARRAY(verticesArray);
		DELETE_SAFELY_ARRAY(verticesIndex);
		DELETE_SAFELY_ARRAY(colorArray);
	}
};

ObjectData boxData;
ObjectData cameraData;

ESMatrix mWorld;
ESMatrix mProjection;
ESMatrix mView;
int numFaces;
void KeyPressed (ESContext *context,unsigned char key, int x, int y);

///
// Initialize the shader and program object
//

int Init ( ESContext *esContext )
{

	//Data
	UserData *userData = (UserData *)esContext->userData;
	cameraData.z=-2.0f;

	ReadObjFile("./Model/Woman1.obj",&boxData.verticesArray,0,&boxData.normalArray,0,&boxData.texttureCoorArray,0,&numFaces);

	int width, height;

	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	CreateTexture(&boxData.textureID,"Model\\Woman2.tga",&width,&height);

	//-------------------Data-----------------------

	////Triangle color
	GLfloat colorArray[] = {0.0f, 0.0f, 0.0f, 0.0f,
						0.0f, 0.0f, 0.0f, 0.0f,
						0.0f, 0.0f, 0.0f, 0.0f,
						};
	boxData.colorArray=new float[12];
	memcpy(boxData.colorArray,colorArray,sizeof(colorArray));


	//-------------------Data-End-------------------

	GLuint vertexShader;
	GLuint fragmentShader;
	GLuint programObject;
	char * vShaderStr;
	char * fShaderStr;

	//---------- Load program for shape 1

	vShaderStr = ReadFile("./Shader/vshader.glsl");
	fShaderStr = ReadFile("./Shader/fshader.glsl");

	// Load the vertex/fragment shaders
	vertexShader = LoadShader ( GL_VERTEX_SHADER, (char*)vShaderStr );
	fragmentShader = LoadShader ( GL_FRAGMENT_SHADER, (char*)fShaderStr );

	//Create first program
	programObject=CreateProgram(vertexShader,fragmentShader);
	if(programObject==0)
	   return 0;
	userData->programObject=programObject;

	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);

	glEnable(GL_BLEND);
	glBlendFunc(GL_ONE,GL_SRC_COLOR);
	
	glEnable(GL_TEXTURE_2D);

	glClearColor ( 0.0f, 0.0f, 0.0f, 0.0f );
	return TRUE;
}



///
// Draw a triangle using the shader pair created in Init()
//

void Draw ( ESContext *esContext )
{
	UserData *userData = (UserData *)esContext->userData;
	
	// Set the viewport
	glViewport ( 0, 0, esContext->width, esContext->height );
	
	glClear ( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );	

	//------------------Camera---------------------

	//Projection matrix
	esMatrixLoadIdentity(&mProjection);
	esPerspective(&mProjection,45,4.0f/3.0f,0.2f,10.0f);

	//View matrix
	esMatrixLoadIdentity(&mView);
	SetCamera(&mView,cameraData.x,cameraData.y,cameraData.z,cameraData.xAngle,cameraData.yAngle,cameraData.zAngle);

	//-------------------Camera-End------------------
	

	//Draw box

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D,boxData.textureID);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST); 
	
	//glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST); 
	

	esMatrixLoadIdentity(&mWorld);			//World matrix
	//esRotate(&mWorld,boxData.xAngle,0,1,0);
	
	glUseProgram ( userData->programObject );
	userData->iVerticesLoc = glGetAttribLocation ( userData->programObject , "a_position");
	//userData->iColorLoc = glGetAttribLocation ( userData->programObject , "a_color");
	userData->iUniformProjection = glGetUniformLocation(userData->programObject,"u_mvpMatrixProjection");
	userData->iUniformView = glGetUniformLocation(userData->programObject,"u_mvpMatrixView");
	userData->iUniformWorld = glGetUniformLocation(userData->programObject,"u_mvpMatrixWorld");
	userData->u_texture= glGetUniformLocation(userData->programObject,"u_texture");
	userData->a_uv= glGetAttribLocation(userData->programObject,"a_uv");


	glVertexAttribPointer ( userData->iVerticesLoc, 3, GL_FLOAT, GL_FALSE, 0, boxData.verticesArray );
	//glVertexAttribPointer ( userData->iColorLoc, 4, GL_FLOAT, GL_FALSE, 0, boxData.colorArray );
	glVertexAttribPointer(userData->a_uv,3,GL_FLOAT,GL_FALSE,0,boxData.texttureCoorArray);
	
	glUniformMatrix4fv(userData->iUniformProjection,1,GL_FALSE,&mProjection.m[0][0]);
	glUniformMatrix4fv(userData->iUniformView,1,GL_FALSE,&mView.m[0][0]);
	glUniformMatrix4fv(userData->iUniformWorld,1,GL_FALSE,&mWorld.m[0][0]);

	
	glUniform1i(userData->u_texture,0);
	
	glEnableVertexAttribArray ( userData->iVerticesLoc );
	//glEnableVertexAttribArray ( userData->iColorLoc );
	glEnableVertexAttribArray(userData->a_uv);

	glDrawArrays ( GL_TRIANGLES, 0, numFaces*3);
	
	eglSwapBuffers ( esContext->eglDisplay, esContext->eglSurface );
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

   esRegisterKeyFunc(&esContext,KeyPressed);
   esRegisterDrawFunc ( &esContext, Draw );
   
   esMainLoop ( &esContext );

   cameraData.Destroy();
   boxData.Destroy();

	/*float* vertices=0, *normalVectors=0, *textureCoor=0;
	int numVertices, numNormal, numText,numFace;
	ReadObjFile("./Model/box.obj",&vertices,&numVertices,&normalVectors,&numNormal,&textureCoor,&numText,&numFace);
	
	printf("\nVertices : %d\n",numVertices);
	for(int i=0;i<numVertices;i++)
		printf("%.2f ",vertices[i]);

	printf("\nNormal : %d\n",numNormal);
	for(int i=0;i<numNormal;i++)
		printf("%.2f ",normalVectors[i]);

	printf("\nTexture coordinate : %d \n",numText);
	for(int i=0;i<numText;i++)
		printf("%.2f ",textureCoor[i]);

	printf("\nNumface : %d \n",numFace);*/

}


void KeyPressed (ESContext *context,unsigned char key, int arg1, int arg2) 
{
	switch(key)
	{
	case 'w':
		cameraData.y-=0.1f;
		break;
	case 's':
		cameraData.y+=0.1f;
		break;
	case 'a':
		cameraData.x-=0.1f;
		break;
	case 'd':
		cameraData.x+=0.1f;
		break;
	case 'r':
		cameraData.y-=0.1f;
		break;
	case 'f':
		cameraData.y+=0.1f;
		break;
	}
}