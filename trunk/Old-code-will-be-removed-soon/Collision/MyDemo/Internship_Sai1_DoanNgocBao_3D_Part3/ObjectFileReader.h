#ifndef _OBJECT_FILE_READER_H
#define _OBJECT_FILE_READER_H

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

void readObjectFile(const char* cFileName, int &numVertices, float* &afVertices, int &numNormal, float* &afNormal, int &numTextcoord, float* &afTextcoord, int &numFace, float* &afFaceVertices, float* &afFaceNormal, float* &afFaceTextcoord);

#endif