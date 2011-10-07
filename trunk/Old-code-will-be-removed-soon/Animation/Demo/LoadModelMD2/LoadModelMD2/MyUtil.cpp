#include <vector>
#include <vector>
#include <string>
using namespace std;
#include "MyUtil.h"
#include <windows.h>

char * ReadFile(char *fileName)
{
	FILE * pFile;
	long lSize;
	char * buffer;
	size_t result;

	pFile = fopen (fileName, "r" );
	if (pFile==NULL) 
	{
		fputs ("File error",stderr); exit (1);
	}

	fseek (pFile , 0 , SEEK_END);
	lSize = ftell (pFile);
	rewind (pFile);

	buffer = (char*) malloc (sizeof(char)*lSize + 1);
	memset(buffer, 0, sizeof(char)*lSize + 1);

	if (buffer == NULL) 
	{
		fputs ("Memory error",stderr); exit (2);
	}

	result = fread (buffer,1,lSize,pFile);
	buffer[sizeof(char)*lSize] = '\0';

	//printf("readfile: %s \n", buffer);
	fclose (pFile);
	return buffer;
}

int SplitStr(vector<string>& result, const string& input, const string& AllSeperator, bool isRemoveBlank )
{
	typedef string::size_type ST;
	string delims = AllSeperator;
	string STR;
	if(delims.empty()) delims = "\n\r";
	if(isRemoveBlank) delims += " ";
	 
	ST pos=0, LEN = input.size();
	while(pos < LEN ){
		
		STR=""; // Init/clear the STR token buffer
		
		// remove any delimiters including optional (white)spaces
		while( (delims.find(input[pos]) != string::npos) && (pos < LEN) ) ++pos;
		
		// leave if @eos
		if(pos==LEN) return result.size();
		
		// Save token data
		while( (delims.find(input[pos]) == string::npos) && (pos < LEN) ) STR += input[pos++];
		
		// put valid STR buffer into the supplied vector
		//cout << "[" << STR << "]";
		
		if( ! STR.empty() ) result.push_back(STR);
		
	}
	return result.size();
}



void ReadObjFile(char* filePath,float** vertices, int *reNumVertices,
				 float** normalVectors, int *reNumNormalVector,
				 float** textureCoor,int *reNumTextureCoordinate,
				 int *reNumFace)
{
	char* cInput=ReadFile(filePath);
	string sInput(cInput);
	string sEnterSeperator("\n");		
	vector<string> lLines;							//vector line in file
	vector<string> lWords;							//vector word in a line
	vector<string> lLineFace;

	vector<float> lVertices;
	vector<float> lNormalVectors;
	vector<float> lTextureCoors;

	vector<float> lVerticesIndexed;					//vector vertices with index (become face).
	vector<float> lNormalVectorsIndexed;
	vector<float> lTextureCoorsIndexed;

	int numNormolVertex;
	int numTextureCoordinate;

	SplitStr(lLines,sInput,sEnterSeperator,false);
	
	vector<string>::iterator i, j;
	for(i=lLines.begin();i!=lLines.end();i++)
	{
		
		string line=(*i);
		if(line.find("#")==0) continue;				//Abort Comment

		//if this line is vertices
		if(line.find("v ")==0)
		{
			lWords.clear();
			SplitStr(lWords,line,"",true);
			for(j=lWords.begin(),j++;j!=lWords.end();j++)
			{
				string word=(*j);
				float numFloat=atof(word.c_str());
				lVertices.push_back(numFloat);
			}
		}

		//if this line is normal vector
		if(line.find("vn ")==0)
		{
			lWords.clear();
			SplitStr(lWords,line,"",true);
			for(j=lWords.begin(),j++;j!=lWords.end();j++)
			{
				string word=(*j);
				float numFloat=atof(word.c_str());
				lNormalVectors.push_back(numFloat);
			}
		}

		//if this line is texture coordinate
		if(line.find("vt ")==0)
		{
			lWords.clear();
			SplitStr(lWords,line,"",true);
			for(j=lWords.begin(),j++;j!=lWords.end();j++)
			{
				string word=(*j);
				float numFloat=atof(word.c_str());
				lTextureCoors.push_back(numFloat);
			}
		}

		if(line.find("f ")==0)
		{
			lLineFace.push_back(line);
		}
	}
	
	vector<string> lIndex;
	vector<string>::iterator m;
	//vector
	string splash("/");
	for(i=lLineFace.begin();i!=lLineFace.end();i++)
	{
		string line=(*i);
		lWords.clear();
		SplitStr(lWords,line,"",true);
		for(j=lWords.begin(),j++;j!=lWords.end();j++)
		{
			lIndex.clear();
			string word=(*j);
			SplitStr(lIndex,word,splash,false);

			int index=atoi(lIndex[0].c_str());
			lVerticesIndexed.push_back(lVertices[(index-1)*3]);
			lVerticesIndexed.push_back(lVertices[(index-1)*3+1]);
			lVerticesIndexed.push_back(lVertices[(index-1)*3+2]);

			index=atoi(lIndex[2].c_str());
			lNormalVectorsIndexed.push_back(lNormalVectors[(index-1)*3]);
			lNormalVectorsIndexed.push_back(lNormalVectors[(index-1)*3+1]);
			lNormalVectorsIndexed.push_back(lNormalVectors[(index-1)*3+2]);

			index=atoi(lIndex[1].c_str());
			lTextureCoorsIndexed.push_back(lTextureCoors[(index-1)*3]);
			lTextureCoorsIndexed.push_back(lTextureCoors[(index-1)*3+1]);
			lTextureCoorsIndexed.push_back(lTextureCoors[(index-1)*3+2]);

		}
	}


	//Allocate memory for pointer
	
	
	

	//Copy float from vector to memory allocated
	int num;
	vector<float>::iterator k;

	if(vertices!=0)
	{
		num=0;
		*vertices=new float[lVerticesIndexed.size()];
		for(k=lVerticesIndexed.begin();k!=lVerticesIndexed.end();k++)
		{
			(*vertices)[num++]=(*k);
		}
		if(reNumVertices!=0)
			*reNumVertices=lVerticesIndexed.size();
	}

	if(normalVectors!=0)
	{
		*normalVectors=new float[lNormalVectorsIndexed.size()];
		num=0;
		for(k=lNormalVectorsIndexed.begin();k!=lNormalVectorsIndexed.end();k++)
		{
			(*normalVectors)[num++]=(*k);
		}
		if(reNumNormalVector!=0)
			*reNumNormalVector=lNormalVectorsIndexed.size();
	}

	if(textureCoor!=0)
	{
		*textureCoor=new float[lTextureCoorsIndexed.size()];
		num=0;
		for(k=lTextureCoorsIndexed.begin();k!=lTextureCoorsIndexed.end();k++)
		{
			(*textureCoor)[num++]=(*k);
		}
		if(reNumTextureCoordinate!=0)
			*reNumTextureCoordinate=lTextureCoorsIndexed.size();
	}

	if(reNumFace!=0)
		*reNumFace=lLineFace.size();
}


typedef struct
{
   byte  IdSize,
                  MapType,
                  ImageType;
   unsigned short PaletteStart,
                  PaletteSize;
   byte PaletteEntryDepth;
   unsigned short X,
                  Y,
                  Width,
                  Height;
   byte  ColorDepth,
                  Descriptor;
         
} TGA_HEADER;

#define INVERTED_BIT            (1 << 5)

int MWinTGALoad( const char *fileName, char **buffer, int *width, int *height )
{
   FILE        *fp;
   TGA_HEADER   Header;

   if ( fopen_s ( &fp, fileName, "rb" ) != 0 )
   {
      return FALSE;
   }

   if ( fp == NULL )
   {
      return FALSE;
   }

   fread ( &Header, sizeof(TGA_HEADER), 1, fp );

   *width = Header.Width;
   *height = Header.Height;
   
   if ( Header.ColorDepth == 24 )
   {
      RGBTRIPLE *Buffer24;

      Buffer24= (RGBTRIPLE*)malloc(sizeof(RGBTRIPLE) * (*width) * (*height));

      if(Buffer24)
      {
         int i=0;
         int x,
             y;

         fread(Buffer24, sizeof(RGBTRIPLE), (*width) * (*height), fp);

         *buffer= (LPSTR) malloc(3 * (*width) * (*height));

         for ( y = 0; y < *height; y++ )
            for( x = 0; x < *width; x++ )
            {
               int Index= y * (*width) + x;

               if(!(Header.Descriptor & INVERTED_BIT))
                  Index= ((*height) - 1 - y) * (*width) + x;

               (*buffer)[(i * 3)]=      Buffer24[Index].rgbtRed;
               (*buffer)[(i * 3) + 1]=  Buffer24[Index].rgbtGreen;
               (*buffer)[(i * 3) + 2]=  Buffer24[Index].rgbtBlue;
        
               i++;
            }
         
         fclose(fp);
         free(Buffer24);
         return(TRUE);
      }		
   }

   return(FALSE);
}