#include "ObjectFileReader.h"


///
//Read object file
//

void readObjectFile(const char* cFileName, int &numVertices, float* &afVertices, int &numNormal, float* &afNormal, int &numTextcoord, float* &afTextcoord, int &numFace, float* &afFaceVertices, float* &afFaceNormal, float* &afFaceTextcoord)
{
	FILE *stream;
	char** buff_v = new char*[1000];
	char** buff_vn = new char*[1000];
	char** buff_vt = new char*[1000];
	char** buff_f = new char*[1000];

	numVertices = 0;
	numNormal = 0;
	numTextcoord = 0;
	numFace  = 0;

	stream = fopen(cFileName,"r");
	if(stream == 0){
		fputs("File error!",stderr);
		return;
	}

	//get line
	while(!feof(stream))
	{
		char* buff = new char[500];
		//memset(buff, 0, sizeof(char)*500);
		fgets(buff,500,stream);
		if(buff[0] == 'v')
		{
			if(buff[1] == 'n')
			{
				buff_vn[numNormal] = buff;
				numNormal++;
			}
			else if(buff[1] == 't')
			{
				buff_vt[numTextcoord] = buff;
				numTextcoord++;
			}
			else
			{
				buff_v[numVertices] = buff;
				numVertices++;
			}
		}
		else if(buff[0] == 'f')
		{
			buff_f[numFace] = buff;
			numFace++;
		}
		else 
		{
			delete[] buff;
		}

	}

	//get vertices
	afVertices = new float[3*numVertices];
	for(int i = 0; i < numVertices; i++)
	{
		char *acTemp = buff_v[i];
		//remove v in acTemp - vertices have format "v  float float float\n"
		acTemp = acTemp + 3;

		//get X,Y,Z
		int iTemp = 3*i;
		sscanf(acTemp,"%f %f %f", &afVertices[iTemp],&afVertices[iTemp+1],&afVertices[iTemp+2]);
	}

	//get Normal
	afNormal = new float[3*numNormal];
	for(int i = 0; i < numNormal; i++)
	{
		char *acTemp = buff_vn[i];
		//remove vn in acTemp - vNormal have format "vn float float float\n"
		acTemp = acTemp + 3;

		//get X,Y,Z
		int iTemp = 3*i;
		sscanf(acTemp,"%f %f %f", &afNormal[iTemp],&afNormal[iTemp+1],&afNormal[iTemp+2]);
	}

	//get textcoord
	afTextcoord = new float[3*numTextcoord];
	for(int i = 0; i < numTextcoord; i++)
	{
		char *acTemp = buff_vt[i];
		//remove vt in acTemp - textcoord have format "vt float float float\n"
		acTemp = acTemp + 3;

		//get X,Y,Z
		int iTemp = 3*i;
		sscanf(acTemp,"%f %f %f", &afTextcoord[iTemp],&afTextcoord[iTemp+1],&afTextcoord[iTemp+2]);
	}

	//get Face
	afFaceVertices = new float[9*numFace];
	afFaceNormal = new float[9*numFace];
	afFaceTextcoord = new float[9*numFace];

	for(int i = 0; i < numFace; i++)
	{
		int temp = i*9;

		char *acTemp = buff_f[i];
		//remove f in acTemp - face have format "f float float float\n"
		acTemp = acTemp + 2;
		
		int p1,n1,t1,p2,n2,t2,p3,n3,t3;
		sscanf(acTemp,"%d/%d/%d %d/%d/%d %d/%d/%d",&p1,&t1,&n1,&p2,&t2,&n2,&p3,&t3,&n3);
		p1--;
		n1--;
		t1--;
		p2--;
		n2--;
		t2--;
		p3--;
		n3--;
		t3--;
		//get 1st vertices's atributes
			//get vertices's position
		afFaceVertices[temp] = afVertices[3*p1];
		afFaceVertices[temp+1] = afVertices[3*p1+1];
		afFaceVertices[temp+2] = afVertices[3*p1+2];
			//get vertices's normal
		afFaceNormal[temp] = afNormal[3*n1];
		afFaceNormal[temp+1] = afNormal[3*n1+1];
		afFaceNormal[temp+2] = afNormal[3*n1+2];
			//get vertices's textcoord
		afFaceTextcoord[temp] = afTextcoord[3*t1];
		afFaceTextcoord[temp+1] = afTextcoord[3*t1+1];
		afFaceTextcoord[temp+2] = afTextcoord[3*t1+2];

		//get 2nd vertices's atributes
			//get vertices's position
		afFaceVertices[temp+3] = afVertices[3*p2];
		afFaceVertices[temp+4] = afVertices[3*p2+1];
		afFaceVertices[temp+5] = afVertices[3*p2+2];
			//get vertices's normal
		afFaceNormal[temp+3] = afNormal[3*n2];
		afFaceNormal[temp+4] = afNormal[3*n2+1];
		afFaceNormal[temp+5] = afNormal[3*n2+2];
			//get vertices's textcoord
		afFaceTextcoord[temp+3] = afTextcoord[3*t2];
		afFaceTextcoord[temp+4] = afTextcoord[3*t2+1];
		afFaceTextcoord[temp+5] = afTextcoord[3*t2+2];

		//get 3rd vertices's atributes
			//get vertices's position
		afFaceVertices[temp+6] = afVertices[3*p3];
		afFaceVertices[temp+7] = afVertices[3*p3+1];
		afFaceVertices[temp+8] = afVertices[3*p3+2];
			//get vertices's normal
		afFaceNormal[temp+6] = afNormal[3*n3];
		afFaceNormal[temp+7] = afNormal[3*n3+1];
		afFaceNormal[temp+8] = afNormal[3*n3+2];
			//get vertices's textcoord
		afFaceTextcoord[temp+6] = afTextcoord[3*t3];
		afFaceTextcoord[temp+7] = afTextcoord[3*t3+1];
		afFaceTextcoord[temp+8] = afTextcoord[3*t3+2];
	}
	delete[] buff_v;
	delete[] buff_vt;
	delete[] buff_vn;
	delete[] buff_f;
}