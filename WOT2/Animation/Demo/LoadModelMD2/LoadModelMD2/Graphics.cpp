#include "Graphics.h"
#include "stdio.h"
#include <stdlib.h>
//#include "Header.h"
#include "MyMatrix.h"

#ifdef ANDROID
#include "GLES2/gl2.h"
#endif


Graphics* Graphics::GetInstance()
{
	if(!instance)
	{
		instance=new Graphics();
	}
	return instance;
}

void Graphics::Init()
{
	unsigned int vertexShader, fragmentShader;

	char fShaderStr[] = ""
		"precision lowp float;								\n"
		"uniform sampler2D u_texture;						\n"
		"varying vec2 v_uv;									\n"
		"void main()										\n"
		"{													\n"
		"	gl_FragColor=texture2D(u_texture,v_uv);			\n"
		"} 												\n";


	char vShaderStr[] = ""
		"uniform mat4 u_mvpMatrixProjection;				\n"
		"uniform mat4 u_mvpMatrixView;						\n"
		"uniform mat4 u_mvpMatrixWorld;						\n"
		"attribute vec4 a_position;							\n"
		"attribute vec2 a_uv;								\n"
		"varying vec2 v_uv;									\n"

		"void main()		\n"
		"{					\n"
		"	gl_Position = u_mvpMatrixProjection * u_mvpMatrixView * u_mvpMatrixWorld *  a_position;\n"
		"	v_uv=a_uv;		\n"
		"}					\n";


	// Load the vertex/fragment shaders
	vertexShader = LoadShader ( GL_VERTEX_SHADER, (char*)vShaderStr );
	fragmentShader = LoadShader ( GL_FRAGMENT_SHADER, (char*)fShaderStr );

	//Create model program
	texProgram=CreateProgram(vertexShader,fragmentShader);

	mWorld=mView=mProjection=0;
	
}

Graphics::~Graphics()
{
	delete instance;
}

GLuint Graphics::LoadShader ( GLenum type, const char *shaderSrc )
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

#ifdef WIN32
         //esLogMessage ( "Error compiling shader:\n%s\n", infoLog );            
#else
		 LOGE( "Error compiling shader:\n%s\n", infoLog );
#endif
         
         free ( infoLog );
      }

      glDeleteShader ( shader );
      return 0;
   }

   return shader;

}

//Create Program
GLuint Graphics::CreateProgram(GLuint _vertexShader, GLuint _fragmentShader)
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

#ifdef WIN32
		 //esLogMessage ( "Error linking program:\n%s\n", infoLog );
#else
		LOGE( "Error linking program:\n%s\n", infoLog );
#endif
		 free ( infoLog );
	  }

	  glDeleteProgram ( hProgram );
	  return 0;
	}

	return hProgram;
}

void Graphics::Clear()
{
	glClear( GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
}

void Graphics::ClearColor(float r, float g, float b, float a)
{
	glClearColor(r,g,b,a);
}


void Graphics::DrawModel(int numFaces)
{
	if(mView==0) mView->LoadIndentity();
	if(mProjection==0) mProjection->LoadIndentity();
	if(mWorld==0) mWorld->LoadIndentity();

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D,textID);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST); 

	glUseProgram(texProgram);
	
	a_vertices = glGetAttribLocation ( texProgram , "a_position");
	a_uv= glGetAttribLocation(texProgram,"a_uv");

	u_projection = glGetUniformLocation(texProgram,"u_mvpMatrixProjection");
	u_view = glGetUniformLocation(texProgram,"u_mvpMatrixView");
	u_world = glGetUniformLocation(texProgram,"u_mvpMatrixWorld");
	u_texture= glGetUniformLocation(texProgram,"u_texture");

	glUniformMatrix4fv(u_projection,1,GL_FALSE,&mProjection->m[0][0]);
	glUniformMatrix4fv(u_view,1,GL_FALSE,&mView->m[0][0]);
	glUniformMatrix4fv(u_world,1,GL_FALSE,&mWorld->m[0][0]);
	glUniform1i(u_texture,0);
	
	glVertexAttribPointer ( a_vertices, 3, GL_FLOAT, GL_FALSE, 0, verticesArray );
	glVertexAttribPointer(a_uv,3,GL_FLOAT,GL_FALSE,0,textCoorArray);

	glEnableVertexAttribArray ( a_vertices );
	glEnableVertexAttribArray(a_uv);

	glDrawArrays ( GL_TRIANGLES, 0, numFaces*3);

}

/*void Graphics::Translate(int MM_MATRIX_MODE, float x, float y, float z)
{
	switch(MM_MATRIX_MODE)
	{
	case MM_MODEL:
		mWorld.Translation(x,y,z);
		break;
	case MM_PROJECTION:
		mProjection.Translation(x,y,z);
		break;
	case MM_VIEW:
		mView.Translation(x,y,z);
	}
}

void Graphics::Rotate(int MM_MATRIX_MODE, float angle, float x, float y, float z)
{
	switch(MM_MATRIX_MODE)
	{
	case MM_MODEL:
		mWorld.Rotate(angle, x,y,z);
		break;
	case MM_PROJECTION:
		mProjection.Rotate(angle,x,y,z);
		break;
	case MM_VIEW:
		mView.Rotate(angle,x,y,z);
	}
}

void Graphics::Perspective(float  fovy,  float aspect,  float zNear,  float zFar)
{
	mProjection.CreatePerspective(fovy,aspect,zNear,zFar);
}

void Graphics::MatrixLoadIdentity(int MM_MATRIX_MODE)
{
	switch(MM_MATRIX_MODE)
	{
	case MM_VIEW:
		mView.LoadIndentity();
		break;
	case MM_MODEL:
		mWorld.LoadIndentity();
		break;
	case MM_PROJECTION:
		mProjection.LoadIndentity();
		break;
	}
}*/

void Graphics::SetViewMatrix (MyMatrix *_mView)
{
	mView	=_mView;
}

void Graphics::SetProjectionMatrix(MyMatrix *_mProjection)
{
	mProjection	=_mProjection;
}

void Graphics::SetWorldMatrix(MyMatrix *_mWorld)
{
	mWorld	=_mWorld;
}

void Graphics::SetTextCoorArray(float *_textCoorArray)
{
	textCoorArray=_textCoorArray;
}

void Graphics::SetVerticesArray(float *_verticesArray)
{
	 verticesArray	=_verticesArray;
}

void Graphics::SetTextureID(int _textID)
{
	textID	=_textID;
}

Graphics* Graphics::instance=0;

