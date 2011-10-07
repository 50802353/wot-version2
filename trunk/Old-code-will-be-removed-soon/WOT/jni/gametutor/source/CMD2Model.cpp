#include "CMD2Model.h"

namespace GameTutor
{
	
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
	int readInt(FILE* fp) {
		char buffer[4];
		fread(buffer,4,1,fp);
		//input.read(buffer, 4);
		return toInt(buffer);
	}
	
	//Reads the next two bytes as a short, using little-endian form
	short readShort(FILE* fp) {
		char buffer[2];
		fread(buffer,2,1,fp);
		//input.read(buffer, 2);
		return toShort(buffer);
	}
	
	//Reads the next two bytes as an unsigned short, using little-endian form
	unsigned short readUShort(FILE* fp) {
		char buffer[2];
		fread(buffer,2,1,fp);
		//input.read(buffer, 2);
		return toUShort(buffer);
	}
	
	//Reads the next four bytes as a float, using little-endian form
	float readFloat(FILE* fp) {
		char buffer[4];
		fread(buffer,4,1,fp);
		//input.read(buffer, 4);
		return toFloat(buffer);
	}
	
	//Calls readFloat three times and returns the results as a Vec3f object
	Vec3f readVec3f(FILE* fp) {
		float x = readFloat(fp);
		float y = readFloat(fp);
		float z = readFloat(fp);
		return Vec3f(x, y, z);
	}

	MD2Model::~MD2Model() {
		SAFE_DEL_ARRAY(frames);
		SAFE_DEL_ARRAY(texCoords);
		SAFE_DEL_ARRAY(triangles);
		SAFE_DEL_ARRAY(verticesArrayAFrame);
		SAFE_DEL_ARRAY(textCoorArrayAFrame);
		SAFE_DEL_ARRAY(nameArrayAFrame);
	}

	MD2Model::MD2Model() {
		frames = 0;
		texCoords = 0;
		triangles = 0;
		mModelMatrix = 0;
		verticesArrayAFrame = 0;
		textCoorArrayAFrame = 0;
	}

	//Loads the MD2 model
	void MD2Model::Load(const char* filename, const char* texturePath) {
		//ifstream input;
		FILE* fp;
		//input.open(filename, istream::binary);
		fp = fopen(filename,"rb");
		if(fp == 0)
		{
			return;
		}
	
		char buffer[64];
		fread(buffer,4,1,fp);
		//input.read(buffer, 4); //Should be "IPD2", if this is an MD2 file
		if (buffer[0] != 'I' || buffer[1] != 'D' ||
			buffer[2] != 'P' || buffer[3] != '2') {
			return;
		}
		if (readInt(fp) != 8) { //The version number
			return;
		}
	
		int textureWidth = readInt(fp);   //The width of the textures
		int textureHeight = readInt(fp);  //The height of the textures
		readInt(fp);                      //The number of bytes per frame
		int numTextures = readInt(fp);    //The number of textures
		int numVertices = readInt(fp);    //The number of vertices
		int numTexCoords = readInt(fp);   //The number of texture coordinates
		int numTriangles = readInt(fp);   //The number of triangles
		readInt(fp);                      //The number of OpenGL commands
		int numFrames = readInt(fp);      //The number of frames
	
		//Offsets (number of bytes after the beginning of the file to the beginning
		//of where certain data appear)
		int textureOffset = readInt(fp);  //The offset to the textures
		int texCoordOffset = readInt(fp); //The offset to the texture coordinates
		int triangleOffset = readInt(fp); //The offset to the triangles
		int frameOffset = readInt(fp);    //The offset to the frames
		readInt(fp);                      //The offset to the OpenGL commands
		readInt(fp);                      //The offset to the end of the file
	
		//Load the texture

		//image = loadPCX(texturePath);
		//im = CImage::LoadPCX(new CReaderStream<CFileWin32Driver>(texturePath));
		//im->BindGPU();
		CImageManager::GetInstance()->AddImage<CFileWin32Driver>(texturePath,true);
		GLuint textureId = (CImageManager::GetInstance()->Get(texturePath))->GetTextureID();
		//loadTexture(image);
		this->textureId = textureId;
	
		//Load the texture coordinates
		fseek(fp,texCoordOffset,SEEK_SET);
		//input.seekg(texCoordOffset, ios_base::beg);
		this->texCoords = new MD2TexCoord[numTexCoords];
		for(int i = 0; i < numTexCoords; i++) {
			MD2TexCoord* texCoord = this->texCoords + i;
			texCoord->texCoordX = (float)readShort(fp) / textureWidth;
			texCoord->texCoordY = 1 - (float)readShort(fp) / textureHeight;
		}
	
		//Load the triangles
		fseek(fp,triangleOffset,SEEK_SET);
		//input.seekg(triangleOffset, ios_base::beg);
		this->triangles = new MD2Triangle[numTriangles];
		this->numTriangles = numTriangles;
		for(int i = 0; i < numTriangles; i++) {
			MD2Triangle* triangle = this->triangles + i;
			for(int j = 0; j < 3; j++) {
				triangle->vertices[j] = readUShort(fp);
			}
			for(int j = 0; j < 3; j++) {
				triangle->texCoords[j] = readUShort(fp);
			}
		}
	
		//Load the frames
		fseek(fp,frameOffset,SEEK_SET);
		//input.seekg(frameOffset, ios_base::beg);
		this->frames = new MD2Frame[numFrames];
		this->numFrames = numFrames;
		for(int i = 0; i < numFrames; i++) {
			MD2Frame* frame = this->frames + i;
			frame->vertices = new MD2Vertex[numVertices];
			Vec3f scale = readVec3f(fp);
			Vec3f translation = readVec3f(fp);
			fread(frame->name,16,1,fp);
			//input.read(frame->name, 16);
		
			for(int j = 0; j < numVertices; j++) {
				MD2Vertex* vertex = frame->vertices + j;
				fread(buffer,3,1,fp);
				//input.read(buffer, 3);
				Vec3f v((unsigned char)buffer[0],
						(unsigned char)buffer[1],
						(unsigned char)buffer[2]);
				vertex->pos = translation + Vec3f(scale[0] * v[0],
												  scale[1] * v[1],
												  scale[2] * v[2]);
				fread(buffer,1,1,fp);
				//input.read(buffer, 1);
				int normalIndex = (int)((unsigned char)buffer[0]);
			}
		}
	
		this->verticesArrayAFrame=new float[numFrames*numTriangles*3*3];
		this->textCoorArrayAFrame=new float[numFrames*numTriangles*3*3];
		this->nameArrayAFrame= new char[numFrames*16];
		memset(nameArrayAFrame,0,sizeof(char)*numFrames*16);
		this->startFrame = 0;
		this->endFrame = numFrames - 1;

		//update range of model
		//--init
		mRange.xMax = 0.0f;
		mRange.xMin = 0.0f;

		mRange.yMax = 0.0f;
		mRange.yMin = 0.0f;

		mRange.zMax = 0.0f;
		mRange.zMin = 0.0f;
		//--update Range for this model
		MD2Frame* frame = this->frames;
		for(int i = 0; i < numVertices; i++)
		{
			MD2Vertex* vertice = frame->vertices + i;
			if(vertice->pos[0] > mRange.xMax) mRange.xMax = vertice->pos[0];
			if(vertice->pos[0] < mRange.xMin) mRange.xMin = vertice->pos[0];

			if(vertice->pos[1] > mRange.yMax) mRange.yMax = vertice->pos[1];
			if(vertice->pos[1] < mRange.yMin) mRange.yMin = vertice->pos[1];

			if(vertice->pos[2] > mRange.zMax) mRange.zMax = vertice->pos[2];
			if(vertice->pos[2] < mRange.zMin) mRange.zMin = vertice->pos[2];
		}
		BuildFrameData();
		SAFE_DEL_ARRAY(frames);
		SAFE_DEL_ARRAY(texCoords);
		SAFE_DEL_ARRAY(triangles);
	}

	void MD2Model::GetFirstLastFrameOfAnimation(char* aniName, int *outFirstIndex, int *outLastIndex)
	{
		bool found = false;
		for(int i = 0; i < numFrames; i++) {
			MD2Frame* frame = frames + i;
			if (strlen(&nameArrayAFrame[i*16]) > strlen(aniName) &&

				strncmp(&nameArrayAFrame[i*16], aniName, strlen(aniName)) == 0 &&
				!isalpha((&nameArrayAFrame[i*16])[strlen(aniName)])) {
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

	void MD2Model::BuildFrameData()
	{
		for (int iframe=0; iframe<numFrames; iframe++)
		{
			MD2Frame* frame = frames + iframe;
			for (int itriangle=0; itriangle<numTriangles; itriangle++)
			{
				MD2Triangle* triangle = triangles + itriangle;
				for (int i=0; i<3; i++)
				{
					MD2Vertex* v = frame->vertices + triangle->vertices[i];
					MD2TexCoord* texCoord = texCoords + triangle->texCoords[i];

					textCoorArrayAFrame[iframe*numTriangles*9 +9*itriangle+3*i+0]=texCoord->texCoordX;
					textCoorArrayAFrame[iframe*numTriangles*9 +9*itriangle+3*i+1]=texCoord->texCoordY;
					textCoorArrayAFrame[iframe*numTriangles*9 +9*itriangle+3*i+2]=0;
			
					verticesArrayAFrame[iframe*numTriangles*9 +9*itriangle+3*i+0]=v->pos[0];
					verticesArrayAFrame[iframe*numTriangles*9 +9*itriangle+3*i+1]=v->pos[1];
					verticesArrayAFrame[iframe*numTriangles*9 +9*itriangle+3*i+2]=v->pos[2];

					strcpy(&nameArrayAFrame[iframe*16],frame->name);
				}
			}
		}
	}

	void MD2Model::Draw(int frameIndex, int nextFrame, float frac, Matrix* worldMatrix) {
		//Figure out the two frames between which we are interpolating
		/*int frameIndex1 = frameIndex;
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
		}*/

		GameTutor::CGraphics2D::GetInstance()->DrawMesh(numTriangles,worldMatrix,&verticesArrayAFrame[frameIndex*numTriangles*9],&textCoorArrayAFrame[frameIndex*numTriangles*9],textureId);
	}


}







