#ifndef __MD2_MODEL_H__
#define __MD2_MODEL_H__

#include <fstream>
#include "vec3f.h"
#include "gametutor.h"

namespace GameTutor
{
	struct MD2Vertex {
		Vec3f pos;
		Vec3f normal;
	};

	struct MD2Frame {
		char name[16];
		MD2Vertex* vertices;
	};

	struct MD2TexCoord {
		float texCoordX;
		float texCoordY;
	};

	struct MD2Triangle {
		int vertices[3];  //The indices of the vertices in this triangle
		int texCoords[3]; //The indices of the texture coordinates of the triangle
	};

	struct RangeModel
	{
		float xMax;
		float xMin;

		float yMax;
		float yMin;

		float zMax;
		float zMin;
	};

	class MD2Model {
		public:
			MD2Model();
			~MD2Model();
		private:
			MD2Frame* frames;
			__INT32 numFrames;
			MD2TexCoord* texCoords;
			GLuint textureId;
			MD2Triangle* triangles;
			__INT32 numTriangles;
			//for render
			float *verticesArrayAFrame;			
			float *textCoorArrayAFrame;		
			char* nameArrayAFrame;
		public:
			int startFrame; //The first frame of the current Animation
			int endFrame;   //The last frame of the current Animation
			Matrix* mModelMatrix; //model matrix for THIS MODEL <use to set Model Matrix at (0,0) in real World
			RangeModel mRange; //use to fix length for this Model

			//Get offset of frame for action
			void GetFirstLastFrameOfAnimation(char* aniName, int *outFirstIndex, int *outLastIndex);
			//Draws the current state of the animated model.
			void Draw(int frameIndex, int nextFrame, float frac, Matrix* worldMatrix);
		
			//Loads an MD2Model from the specified file
			void Load(const char* filename, const char* textureFileName);
			void BuildFrameData();

	};
}
#endif
