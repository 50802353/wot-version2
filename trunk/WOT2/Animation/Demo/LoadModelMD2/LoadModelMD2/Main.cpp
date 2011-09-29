
#include <stdlib.h>
#include <stdio.h>
#include "esUtil.h"
#include "MyGLUtil.h"
#include "MyUtil.h"
#include "Model.h"
#include "Camera.h"
#include "Skybox.h"
#include "Graphics.h"
#include "md2model.h"
#include "Animation.h"


Model* woman1;
Model* woman2;
Skybox *sky;
MD2Model* tallMan;
Animation* aniTallMan;
Animation* aniTallMan2;


Camera *cam;
Camera *camSky;
float RCam;

int hProgramModel;
int hProgramSky;

//Camera

void KeyPressed (ESContext *context,unsigned char key, int x, int y);

///
// Initialize the shader and program object
//

int Init ( ESContext *esContext )
{

	//Data
	cam=new Camera();
	cam->SetProjection(45,4.0f/3.0f,0.2f,10.0f);
	cam->SetLocation(0.0f,0.5f,4.0f);

	camSky=new Camera();
	cam->SetProjection(45,4.0f/3.0f,0.2f,10.0f);

	//-------------------Data-End-------------------

	GLuint vertexShader;
	GLuint fragmentShader;
	GLuint programObject;
	char * vShaderStr;
	char * fShaderStr;

	//---------- Load program for model----------------

	vShaderStr = ReadFile("./Shader/vshader.glsl");
	fShaderStr = ReadFile("./Shader/fshader.glsl");

	// Load the vertex/fragment shaders
	vertexShader = LoadShader ( GL_VERTEX_SHADER, (char*)vShaderStr );
	fragmentShader = LoadShader ( GL_FRAGMENT_SHADER, (char*)fShaderStr );

	//Create model program
	programObject=CreateProgram(vertexShader,fragmentShader);
	if(programObject==0)
	   return 0;
	hProgramModel=programObject;
	//---------- Load program for model-End----------------


	//---------- Load program for sky----------------
	vShaderStr = ReadFile("./Shader/vshader_sky.glsl");
	fShaderStr = ReadFile("./Shader/fshader_sky.glsl");

	// Load the vertex/fragment shaders
	vertexShader = LoadShader ( GL_VERTEX_SHADER, (char*)vShaderStr );
	fragmentShader = LoadShader ( GL_FRAGMENT_SHADER, (char*)fShaderStr );

	//Create model program
	programObject=CreateProgram(vertexShader,fragmentShader);
	if(programObject==0)
	   return 0;
	hProgramSky=programObject;
	//---------- Load program for sky-End----------------

	//---------Enable/Disable--------------
	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);

	//glEnable(GL_BLEND);
	//glBlendFunc(GL_ONE,GL_SRC_COLOR);
	
	glEnable(GL_TEXTURE_2D);
	//---------Enable/Disable-End----------

	glClearColor ( 0.0f, 0.0f, 0.0f, 0.0f );

	//------------------MyData-----------------

	woman1=new Model("Model/Woman1.obj","Model/Woman1.tga",hProgramModel);
	woman2=new Model("Model/Woman2.obj","Model/Woman2.tga",hProgramModel);
	woman1->TranslateX(0.7f);
	woman2->TranslateX(-0.7f);

	sky=new Skybox("Model/Skybox/cube.obj","Model/Skybox/skybox_top.tga","Model/Skybox/skybox_bottom.tga",
					"Model/Skybox/skybox_left.tga","Model/Skybox/skybox_right.tga",
					"Model/Skybox/skybox_back.tga","Model/Skybox/skybox_front.tga",hProgramSky);

	tallMan=MD2Model::load("tris.MD2","blue.pcx");
	
	//First man
	int first=0, last=0;
	//if (tallMan!= NULL) 
		//tallMan->GetFirstLastFrameOfAnimation("jump",&first,&last);

	
	aniTallMan=new Animation(tallMan);
	aniTallMan->setAction("jump");
	aniTallMan->SetTimePerFrame(0.5f);
	


	//Second man
	aniTallMan2 = new Animation(tallMan);
	aniTallMan2->setAction("death");
	aniTallMan2->SetTimePerFrame(1.0f);

	//------------------MyData-End-----------------

	Graphics::GetInstance()->Init();
	
	return TRUE;
}

///
// Draw a triangle using the shader pair created in Init()
//

void Draw ( ESContext *esContext )
{
	
	// Set the viewport
	glViewport ( 0, 0, esContext->width, esContext->height );
	
	glClear ( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );	

	//Rotate camera
	cam->RotateYAngle(0.1f);
	camSky->RotateYAngle(0.1f);

	//Draw
	sky->SetProjection(camSky->GetViewMat(), camSky->GetProjectionMat());
	sky->Draw();
	woman1->SetProjection(cam->GetViewMat(),cam->GetProjectionMat());
	woman1->Draw();
	woman2->SetProjection(cam->GetViewMat(),cam->GetProjectionMat());
	woman2->Draw();

	//Draw tallman
	//tallMan->advance(0.0025);
	aniTallMan->CreateAnimation(0.01f);
	aniTallMan2->CreateAnimation(0.01f);
	Graphics* g=Graphics::GetInstance();
	
	MyMatrix  mView, mProjection, mWorld;
	mWorld.LoadIndentity();
	mWorld.Scale(0.05f,0.05f,0.05f);
	mView.Copy(&cam->GetViewMat()->m[0][0]);
	mProjection.Copy(&cam->GetProjectionMat()->m[0][0]);
	
	g->SetViewMatrix(&mView);
	g->SetProjectionMatrix(&mProjection);
	g->SetWorldMatrix(&mWorld);
	//aniTallMan->draw();
	aniTallMan2->draw();
	
	
	eglSwapBuffers ( esContext->eglDisplay, esContext->eglSurface );
}

int main ( int argc, char *argv[] )
{
   ESContext esContext;

   esInitContext ( &esContext );

   esCreateWindow ( &esContext, "Hello Triangle", 800, 600, ES_WINDOW_RGB );
   
   if ( !Init ( &esContext ) )
      return 0;

   esRegisterKeyFunc(&esContext,KeyPressed);
   esRegisterDrawFunc ( &esContext, Draw );
   
   esMainLoop ( &esContext );

   DELETE_SAFELY(woman1);
   DELETE_SAFELY(woman2);
   DELETE_SAFELY(sky);
   DELETE_SAFELY(cam);
   DELETE_SAFELY(camSky);
}


void KeyPressed (ESContext *context,unsigned char key, int arg1, int arg2) 
{
	switch(key)
	{
	case 'w':
		cam->TranslateY(0.1f);
		break;
	case 's':
		cam->TranslateY(-0.1f);
		break;
	case 'r':
		woman1->RotateXAngle(10.0f);
	}
}