#ifndef  _MYUTIL_H
#define _MYUTIL_H

#include <vector>
#include <string>
using namespace std;

#define DELETE_SAFELY(x) if((x)!=0) delete(x); (x)=0;
#define DELETE_SAFELY_ARRAY(x) if((x)!=0) delete[](x); (x)=0;

char * ReadFile(char *fileName);
int SplitStr(vector<string>& result, const string& input, const string& AllSeperator, bool isRemoveBlank );
void ReadObjFile(char* filePath,float** vertices, int *reNumVertices,
				 float** normalVectors, int *reNumNormalVector,
				 float** textureCoor,int *reNumTextureCoordinate,
				 int *reNumFace);

#endif