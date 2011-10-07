#include "Skybox.h"
#include "MyUtil.h"
#include "MyGLUtil.h"

Skybox::Skybox(char *objFilePath, char *topTextPath, char* bottomTextPath,
		char* leftTextPath, char* rightTextPath,
		char* backTextPath, char* frontTextPath,
		GLuint _hProgram)
{
	hProgram	=_hProgram;

	//Load texture
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);

	ReadObjFile(objFilePath,&verticesArray,0,0,0,0,0,&numFaces);

	int width, height;
	/*CreateTexture(&topTextID,topTextPath,&width,&height);
	CreateTexture(&bottomTextID,bottomTextPath,&width,&height);
	CreateTexture(&leftTextID,leftTextPath,&width,&height);
	CreateTexture(&rightTextID,rightTextPath,&width,&height);
	CreateTexture(&backTextID,backTextPath,&width,&height);
	CreateTexture(&frontTextID,frontTextPath,&width,&height);*/
	CreateTextureCubeMap(&textureID,topTextPath,bottomTextPath,leftTextPath,rightTextPath,backTextPath,frontTextPath);
	//Reset world matrix
	esMatrixLoadIdentity(&mWorld);

	/*float tFrontCoorArray[]={
							
		//Front
							0.0f,0.0f,1.0f,
							1.0f,0.0f,1.0f,
							0.0f,1.0f,1.0f,

							1.0f,0.0f,1.0f,
							1.0f,1.0f,1.0f,
							0.0f,1.0f,1.0f,

						};

	memcpy(frontTextCoorArray,tFrontCoorArray,sizeof(tTextCoorArray));*/

	//float 
}

void Skybox::SetProjection(ESMatrix *_mView, ESMatrix *_mProjection)
{
	mView		=_mView;
	mProjection	=_mProjection;
}

void Skybox::Draw()
{
	glDisable(GL_DEPTH_TEST);
	

	glUseProgram(hProgram);
	
	a_vertices = glGetAttribLocation ( hProgram , "a_position");
	a_uv= glGetAttribLocation(hProgram,"a_uv");

	u_projection = glGetUniformLocation(hProgram,"u_mvpMatrixProjection");
	u_view = glGetUniformLocation(hProgram,"u_mvpMatrixView");
	u_world = glGetUniformLocation(hProgram,"u_mvpMatrixWorld");
	u_texture= glGetUniformLocation(hProgram,"u_texture");

	glUniformMatrix4fv(u_projection,1,GL_FALSE,&mProjection->m[0][0]);
	glUniformMatrix4fv(u_view,1,GL_FALSE,&mView->m[0][0]);
	glUniformMatrix4fv(u_world,1,GL_FALSE,&mWorld.m[0][0]);
	glUniform1i(u_texture,0);
	
	glVertexAttribPointer ( a_vertices, 3, GL_FLOAT, GL_FALSE, 0, verticesArray );
	glVertexAttribPointer(a_uv,3,GL_FLOAT,GL_FALSE,0,verticesArray);

	glEnableVertexAttribArray ( a_vertices );
	glEnableVertexAttribArray(a_uv);
	
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP,textureID);
	glTexParameteri(GL_TEXTURE_CUBE_MAP,GL_TEXTURE_MIN_FILTER,GL_NEAREST); 
	
	glDrawArrays ( GL_TRIANGLES, 0, numFaces*3);

	glEnable(GL_DEPTH_TEST);

}

Skybox::~Skybox()
{
	DELETE_SAFELY_ARRAY(verticesArray);
}