
#include <fstream>

#include "imageloader.h"
#include "md2model.h"
#include "Graphics.h"

using namespace std;

namespace {
	
	//Returns whether the system is little-endian
	bool littleEndian() {
		//The short value 1 has bytes (1, 0) in little-endian and (0, 1) in
		//big-endian
		short s = 1;
		return (((char*)&s)[0]) == 1;
	}
	
	//Converts a four-character array to an integer, using little-endian form
	int toInt(const char* bytes) {
		return (int)(((unsigned char)bytes[3] << 24) |
					 ((unsigned char)bytes[2] << 16) |
					 ((unsigned char)bytes[1] << 8) |
					 (unsigned char)bytes[0]);
	}
	
	//Converts a two-character array to a short, using little-endian form
	short toShort(const char* bytes) {
		return (short)(((unsigned char)bytes[1] << 8) |
					   (unsigned char)bytes[0]);
	}
	
	//Converts a two-character array to an unsigned short, using little-endian
	//form
	unsigned short toUShort(const char* bytes) {
		return (unsigned short)(((unsigned char)bytes[1] << 8) |
								(unsigned char)bytes[0]);
	}
	
	//Converts a four-character array to a float, using little-endian form
	float toFloat(const char* bytes) {
		float f;
		if (littleEndian()) {
			((char*)&f)[0] = bytes[0];
			((char*)&f)[1] = bytes[1];
			((char*)&f)[2] = bytes[2];
			((char*)&f)[3] = bytes[3];
		}
		else {
			((char*)&f)[0] = bytes[3];
			((char*)&f)[1] = bytes[2];
			((char*)&f)[2] = bytes[1];
			((char*)&f)[3] = bytes[0];
		}
		return f;
	}
	
	//Reads the next four bytes as an integer, using little-endian form
	int readInt(ifstream &input) {
		char buffer[4];
		input.read(buffer, 4);
		return toInt(buffer);
	}
	
	//Reads the next two bytes as a short, using little-endian form
	short readShort(ifstream &input) {
		char buffer[2];
		input.read(buffer, 2);
		return toShort(buffer);
	}
	
	//Reads the next two bytes as an unsigned short, using little-endian form
	unsigned short readUShort(ifstream &input) {
		char buffer[2];
		input.read(buffer, 2);
		return toUShort(buffer);
	}
	
	//Reads the next four bytes as a float, using little-endian form
	float readFloat(ifstream &input) {
		char buffer[4];
		input.read(buffer, 4);
		return toFloat(buffer);
	}
	
	//Calls readFloat three times and returns the results as a Vec3f object
	Vec3f readVec3f(ifstream &input) {
		float x = readFloat(input);
		float y = readFloat(input);
		float z = readFloat(input);
		return Vec3f(x, y, z);
	}
	
	//Makes the image into a texture, and returns the id of the texture
	GLuint loadTexture(Image *image) {
		GLuint textureId;
		glGenTextures(1, &textureId);
		glBindTexture(GL_TEXTURE_2D, textureId);
		glTexImage2D(GL_TEXTURE_2D,
					 0,
					 GL_RGB,
					 image->width, image->height,
					 0,
					 GL_RGB,
					 GL_UNSIGNED_BYTE,
					 image->pixels);
		return textureId;
	}
}

MD2Model::~MD2Model() {
	if (frames != NULL) {
		for(int i = 0; i < numFrames; i++) {
			delete[] frames[i].vertices;
		}
		delete[] frames;
	}
	
	if (texCoords != NULL) {
		delete[] texCoords;
	}
	if (triangles != NULL) {
		delete[] triangles;
	}

	if(verticesArrayAFrame)
		delete[] verticesArrayAFrame;

	if(textCoorArrayAFrame)
		delete[] textCoorArrayAFrame;
}

MD2Model::MD2Model() {
	frames = NULL;
	texCoords = NULL;
	triangles = NULL;
	time = 0;
}

//Loads the MD2 model
MD2Model* MD2Model::load(const char* filename, const char* texturePath) {
	ifstream input;
	input.open(filename, istream::binary);
	
	char buffer[64];
	input.read(buffer, 4); //Should be "IPD2", if this is an MD2 file
	if (buffer[0] != 'I' || buffer[1] != 'D' ||
		buffer[2] != 'P' || buffer[3] != '2') {
		return NULL;
	}
	if (readInt(input) != 8) { //The version number
		return NULL;
	}
	
	int textureWidth = readInt(input);   //The width of the textures
	int textureHeight = readInt(input);  //The height of the textures
	readInt(input);                      //The number of bytes per frame
	int numTextures = readInt(input);    //The number of textures
	if (numTextures != 1) {
		return NULL;
	}
	int numVertices = readInt(input);    //The number of vertices
	int numTexCoords = readInt(input);   //The number of texture coordinates
	int numTriangles = readInt(input);   //The number of triangles
	readInt(input);                      //The number of OpenGL commands
	int numFrames = readInt(input);      //The number of frames
	
	//Offsets (number of bytes after the beginning of the file to the beginning
	//of where certain data appear)
	int textureOffset = readInt(input);  //The offset to the textures
	int texCoordOffset = readInt(input); //The offset to the texture coordinates
	int triangleOffset = readInt(input); //The offset to the triangles
	int frameOffset = readInt(input);    //The offset to the frames
	readInt(input);                      //The offset to the OpenGL commands
	readInt(input);                      //The offset to the end of the file
	
	//Load the texture
	bool isBMP=false , isPCX = false;
	Image* image;
	input.seekg(textureOffset, ios_base::beg);
	input.read(buffer, 64);

	if (strlen(texturePath) < 5) 
		 {
		return NULL;
	}
	if(strcmp(texturePath + strlen(texturePath) - 4, ".bmp") == 0)
	{
		isBMP=true;
	}
	else if(strcmp(texturePath + strlen(texturePath) - 4, ".pcx") == 0)
	{
		isPCX=true;
	}



	if(isBMP)
		image = loadBMP(texturePath);
	else if(isPCX)
	{
		image = loadPCX(texturePath);
	}
	else return NULL;

	GLuint textureId = loadTexture(image);
	delete image;
	MD2Model* model = new MD2Model();
	model->textureId = textureId;
	
	//Load the texture coordinates
	input.seekg(texCoordOffset, ios_base::beg);
	model->texCoords = new MD2TexCoord[numTexCoords];
	for(int i = 0; i < numTexCoords; i++) {
		MD2TexCoord* texCoord = model->texCoords + i;
		texCoord->texCoordX = (float)readShort(input) / textureWidth;
		texCoord->texCoordY = 1 - (float)readShort(input) / textureHeight;
	}
	
	//Load the triangles
	input.seekg(triangleOffset, ios_base::beg);
	model->triangles = new MD2Triangle[numTriangles];
	model->numTriangles = numTriangles;
	for(int i = 0; i < numTriangles; i++) {
		MD2Triangle* triangle = model->triangles + i;
		for(int j = 0; j < 3; j++) {
			triangle->vertices[j] = readUShort(input);
		}
		for(int j = 0; j < 3; j++) {
			triangle->texCoords[j] = readUShort(input);
		}
	}
	
	//Load the frames
	input.seekg(frameOffset, ios_base::beg);
	model->frames = new MD2Frame[numFrames];
	model->numFrames = numFrames;
	for(int i = 0; i < numFrames; i++) {
		MD2Frame* frame = model->frames + i;
		frame->vertices = new MD2Vertex[numVertices];
		Vec3f scale = readVec3f(input);
		Vec3f translation = readVec3f(input);
		input.read(frame->name, 16);
		
		for(int j = 0; j < numVertices; j++) {
			MD2Vertex* vertex = frame->vertices + j;
			input.read(buffer, 3);
			Vec3f v((unsigned char)buffer[0],
					(unsigned char)buffer[1],
					(unsigned char)buffer[2]);
			vertex->pos = translation + Vec3f(scale[0] * v[0],
											  scale[1] * v[1],
											  scale[2] * v[2]);
			input.read(buffer, 1);
			int normalIndex = (int)((unsigned char)buffer[0]);
		}
	}
	
	model->verticesArrayAFrame=new float[numTriangles*3*3];
	model->textCoorArrayAFrame=new float[numTriangles*3*3];
	model->startFrame = 0;
	model->endFrame = numFrames - 1;
	return model;
}

void MD2Model::GetFirstLastFrameOfAnimation(char* aniName, int *outFirstIndex, int *outLastIndex)
{
	bool found = false;
	for(int i = 0; i < numFrames; i++) {
		MD2Frame* frame = frames + i;
		if (strlen(frame->name) > strlen(aniName) &&

			strncmp(frame->name, aniName, strlen(aniName)) == 0 &&
			!isalpha(frame->name[strlen(aniName)])) {
			if (!found) {
				found = true;
				*outFirstIndex = i;
			}
			else {
				*outLastIndex = i;
			}
		}
		else if (found) {
			break;
		}
	}
}

void MD2Model::draw(int frameIndex, int nextFrame, float frac) {

	Graphics* g=Graphics::GetInstance();
	
	//Figure out the two frames between which we are interpolating
	int frameIndex1 = frameIndex;
	int frameIndex2 = nextFrame;
	
	MD2Frame* frame1 = frames + frameIndex1;
	MD2Frame* frame2 = frames + frameIndex2;

	for(int i = 0; i < numTriangles; i++) {
		MD2Triangle* triangle = triangles + i;
		for(int j = 0; j < 3; j++) {
			MD2Vertex* v1 = frame1->vertices + triangle->vertices[j];
			MD2Vertex* v2 = frame2->vertices + triangle->vertices[j];
			Vec3f pos = v1->pos * (1 - frac) + v2->pos * frac;	
			
			MD2TexCoord* texCoord = texCoords + triangle->texCoords[j];
			textCoorArrayAFrame[9*i+3*j+0]=texCoord->texCoordX;
			textCoorArrayAFrame[9*i+3*j+1]=texCoord->texCoordY;
			textCoorArrayAFrame[9*i+3*j+2]=0;
			
			verticesArrayAFrame[9*i+3*j+0]=pos[0];
			verticesArrayAFrame[9*i+3*j+1]=pos[1];
			verticesArrayAFrame[9*i+3*j+2]=pos[2];
		}
	}

	g->SetVerticesArray(verticesArrayAFrame);
	g->SetTextCoorArray(textCoorArrayAFrame);
	g->SetTextureID(textureId);
	g->DrawModel(numTriangles);
}










