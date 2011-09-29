/* Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above notice and this permission notice shall be included in all copies
 * or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
/* File for "Animation" lesson of the OpenGL tutorial on
 * www.videotutorialsrock.com
 */



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

	class MD2Model {
		public:
			MD2Model();
		private:
			MD2Frame* frames;
			__INT32 numFrames;

			MD2TexCoord* texCoords;
			MD2Triangle* triangles;
			__INT32 numTriangles;
			GLuint textureId;

			//By me
			float *verticesArrayAFrame;			//for a frame;
			float *textCoorArrayAFrame;		
		
		
			/* The position in the current Animation.  0 indicates the beginning of
			 * the Animation, which is at the starting frame, and 1 indicates the
			 * end of the Animation, which is right when the starting frame is
			 * reached again.  It always lies between 0 and 1.
			 */
			float time;
		
		
		public:
			int startFrame; //The first frame of the current Animation
			int endFrame;   //The last frame of the current Animation

			~MD2Model();
		
			//Switches to the given Animation
			//void setAnimation(const char* name);
			void GetFirstLastFrameOfAnimation(char* aniName, int *outFirstIndex, int *outLastIndex);
			//Advances the position in the current Animation.  The entire Animation
			//lasts one unit of time.
			//void advance(float dt);
			//Draws the current state of the animated model.
			void draw(int frameIndex, int nextFrame, float frac);
		
			//Loads an MD2Model from the specified file.  Returns NULL if there was
			//an error loading it.
			void load(const char* filename, const char* texturePath);
	};
}
#endif
