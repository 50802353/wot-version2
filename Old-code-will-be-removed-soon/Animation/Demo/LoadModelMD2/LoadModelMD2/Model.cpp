#include "Model.h"
#include "esUtil.h"
#include "MyGLUtil.h"
#include "MyUtil.h"
#include "Graphics.h"

Model::Model(){}

Model::Model(char *objFilePath, char *tgaFilePath,GLuint _hProgram)
{
	x=y=z=xAngle=yAngle=zAngle=0;
	hProgram	=_hProgram;

	//Load texture
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);

	ReadObjFile(objFilePath,&verticesArray,0,&normalArray,0,&textCoorArray,0,&numFaces);

	int width, height;
	CreateTexture(&textureID,tgaFilePath,&width,&height);

	//Reset world matrix
	esMatrixLoadIdentity(&mWorld);
}

void Model::SetProjection(ESMatrix *_mView, ESMatrix *_mProjection)
{
	mView		=_mView;
	mProjection	=_mProjection;
}

Model::~Model()
{
	DELETE_SAFELY_ARRAY(verticesArray);
	DELETE_SAFELY_ARRAY(normalArray);
	DELETE_SAFELY_ARRAY(textCoorArray);
}

void Model::TranslateX(float _x)
{
	x+=_x;
	esTranslate(&mWorld,_x,0,0);
}

void Model::TranslateY(float _y)
{
	y+=_y;
	esTranslate(&mWorld,0,_y,0);
}

void Model::TranslateZ(float _z)
{
	z+=_z;
	esTranslate(&mWorld,0,0,_z);
}

void Model::SetLocation(float _x, float _y, float _z)
{
	x	=_x;
	y	=_y;
	z	=_z;

	esMatrixLoadIdentity(&mWorld);
	esTranslate(&mWorld,x,y,z);
}

void Model::RotateXAngle(float _xAngle)
{
	xAngle	+=_xAngle;
	esRotate(&mWorld,_xAngle,1,0,0);
}

void Model::RotateYAngle(float _yAngle)
{
	yAngle	+=_yAngle;
	esRotate(&mWorld,_yAngle,0,1,0);
}

void Model::RotateZAngle(float _zAngle)
{
	zAngle	+=_zAngle;
	esRotate(&mWorld,_zAngle,0,0,1);
}

void Model::Draw()
{
	/*glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D,textureID);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST); 

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
	glVertexAttribPointer(a_uv,3,GL_FLOAT,GL_FALSE,0,textCoorArray);

	glEnableVertexAttribArray ( a_vertices );
	glEnableVertexAttribArray(a_uv);

	glDrawArrays ( GL_TRIANGLES, 0, numFaces*3);*/
	
	
	Graphics* g=Graphics::GetInstance();
	//g->Init();
	MyMatrix mmWorld, mmView, mmProjection;
	mmWorld.Copy(&mWorld.m[0][0]);
	mmView.Copy(&mView->m[0][0]);
	mmProjection.Copy(&mProjection->m[0][0]);
	g->SetWorldMatrix(&mmWorld);
	g->SetViewMatrix(&mmView);
	g->SetProjectionMatrix(&mmProjection);
	g->SetTextureID(textureID);
	g->SetVerticesArray(verticesArray);
	g->SetTextCoorArray(textCoorArray);
	g->DrawModel(numFaces);


}

float Model::GetX()
{
	return x;
}

float Model::GetY()
{
	return y;
}

float Model::GetZ()
{
	return z;
}

float Model::GetXAngle()
{
	return xAngle;
}

float Model::GetYAngle()
{
	return yAngle;
}

float Model::GetZAngle()
{
	return zAngle;
}