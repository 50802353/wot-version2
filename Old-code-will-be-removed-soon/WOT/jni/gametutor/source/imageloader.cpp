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



#include <assert.h>
#include <fstream>

#include "imageloader.h"

using namespace std;
namespace GameTutor
{
	Image::Image(char* ps, __INT32 w, __INT32 h) : pixels(ps), width(w), height(h) {
	
	}

	Image::~Image() {
		delete[] pixels;
	}

	namespace {
		//Converts a four-character array to an integer, using little-endian form
		__INT32 toInt(const char* bytes) {
			return (__INT32)(((unsigned char)bytes[3] << 24) |
						 ((unsigned char)bytes[2] << 16) |
						 ((unsigned char)bytes[1] << 8) |
						 (unsigned char)bytes[0]);
		}
	
		//Converts a two-character array to a short, using little-endian form
		short toShort(const char* bytes) {
			return (short)(((unsigned char)bytes[1] << 8) |
						   (unsigned char)bytes[0]);
		}
	
		//Reads the next four bytes as an integer, using little-endian form
		__INT32 readInt(FILE* input) {
			char buffer[4];
			fread(buffer,4,1,input);
			input.read(buffer, 4);
			return toInt(buffer);
		}
	
		//Reads the next two bytes as a short, using little-endian form
		short readShort(ifstream &input) {
			char buffer[2];
			input.read(buffer, 2);
			return toShort(buffer);
		}
	
		//Just like auto_ptr, but for arrays
		template<class T>
		class auto_array {
			private:
				T* array;
				mutable bool isReleased;
			public:
				explicit auto_array(T* array_ = NULL) :
					array(array_), isReleased(false) {
				}
			
				auto_array(const auto_array<T> &aarray) {
					array = aarray.array;
					isReleased = aarray.isReleased;
					aarray.isReleased = true;
				}
			
				~auto_array() {
					if (!isReleased && array != NULL) {
						delete[] array;
					}
				}
			
				T* get() const {
					return array;
				}
			
				T &operator*() const {
					return *array;
				}
			
				void operator=(const auto_array<T> &aarray) {
					if (!isReleased && array != NULL) {
						delete[] array;
					}
					array = aarray.array;
					isReleased = aarray.isReleased;
					aarray.isReleased = true;
				}
			
				T* operator->() const {
					return array;
				}
			
				T* release() {
					isReleased = true;
					return array;
				}
			
				void reset(T* array_ = NULL) {
					if (!isReleased && array != NULL) {
						delete[] array;
					}
					array = array_;
				}
			
				T* operator+(__INT32 i) {
					return array + i;
				}
			
				T &operator[](__INT32 i) {
					return array[i];
				}
		};
	}

	Image* loadBMP(const char* filename) {
		ifstream input;
		input.open(filename, ifstream::binary);
		//assert(!input.fail() || !"Could not find file");
		LogError("Could not find file BMP");
		char buffer[2];
		input.read(buffer, 2);
		assert(buffer[0] == 'B' && buffer[1] == 'M' || !"Not a bitmap file");
		input.ignore(8);
		__INT32 dataOffset = readInt(input);
	
		//Read the header
		__INT32 headerSize = readInt(input);
		__INT32 width;
		__INT32 height;
		switch(headerSize) {
			case 40:
				//V3
				width = readInt(input);
				height = readInt(input);
				input.ignore(2);
				/*assert(readShort(input) == 24 || !"Image is not 24 bits per pixel");
				assert(readShort(input) == 0 || !"Image is compressed");*/
				if(readShort(input) != 24) LogError("Image is not 24 bits per pixel");
				if(readShort(input) != 0) LogError("Image is compressed");
				break;
			case 12:
				//OS/2 V1
				width = readShort(input);
				height = readShort(input);
				input.ignore(2);
				/*assert(readShort(input) == 24 || !"Image is not 24 bits per pixel");*/
				if(readShort(input) != 24) LogError("Image is not 24 bits per pixel");
				break;
			case 64:
				//OS/2 V2
				/*assert(!"Can't load OS/2 V2 bitmaps");*/
				LogError("Can't load OS/2 V2 bitmaps");
				break;
			case 108:
				//Windows V4
				/*assert(!"Can't load Windows V4 bitmaps");*/
				LogError("Can't load Windows V4 bitmaps");
				break;
			case 124:
				//Windows V5
				/*assert(!"Can't load Windows V5 bitmaps");*/
				LogError("Can't load Windows V5 bitmaps");
				break;
			default:
				/*assert(!"Unknown bitmap format");*/
				LogError("Unknown bitmap format");
		}
	
		//Read the data
		__INT32 bytesPerRow = ((width * 3 + 3) / 4) * 4 - (width * 3 % 4);
		__INT32 size = bytesPerRow * height;
		auto_array<char> pixels(new char[size]);
		input.seekg(dataOffset, ios_base::beg);
		input.read(pixels.get(), size);
	
		//Get the data into the right format
		auto_array<char> pixels2(new char[width * height * 3]);
		for(__INT32 y = 0; y < height; y++) {
			for(__INT32 x = 0; x < width; x++) {
				for(__INT32 c = 0; c < 3; c++) {
					pixels2[3 * (width * y + x) + c] =
						pixels[bytesPerRow * y + 3 * x + (2 - c)];
				}
			}
		}
	
		input.close();
		return new Image(pixels2.release(), width, height);
	}

	Image* loadPCX(const char* filename)
	{
		image_src* img;
		img = ReadPCXFile(filename);
		return new Image((char*)img->texels,img->width,img->height);
	}


}




