#include "BKImage.h"

BKImage::BKImage(void)
{
	iwidth = 0;
	iheight = 0;
	pixels = 0;
}


BKImage::~BKImage(void)
{
	if(m_cpixels != 0)
	{
		delete[] m_cpixels;
	}
}

void BKImage::getImage(const char *filename)
{
	int t = 0;
	while(filename[t] != '.')
	{
		t++;
	}

	if((filename[t+1] == 'B' || filename[t+1] == 'b') && (filename[t+2] == 'M' || filename[t+2] == 'm') && (filename[t+3] == 'P' || filename[t+3] == 'p'))
	{
		//this file is BMP format
		getImageBMP(filename);
	}

	else if((filename[t+1] == 'P' || filename[t+1] == 'p') && (filename[t+2] == 'C' || filename[t+2] == 'c') && (filename[t+3] == 'X' || filename[t+3] == 'x'))
	{
		//this file is PCX format
		getImagePCX(filename);
	}

	else if((filename[t+1] == 'T' || filename[t+1] == 't') && (filename[t+2] == 'G' || filename[t+2] == 'g') && (filename[t+3] == 'A' || filename[t+3] == 'a'))
	{
		//this file is TGA format
		getImageTGA(filename);
	}
}

void BKImage::getImageFromPCX(const char* filename)
{
	char c;
	FILE* fp;
	fp = fopen(filename,"rb");
	if(fp == 0)
	{
		printf("File error!\n");
		return;
	}

	//check Image type
	fread(&c,1,1,fp);
	if(c != 0x0A)
	{
		printf("This file do not format PCX");
		fclose(fp);
		return;
	}

	//get width and height of Image
	fseek(fp,4,SEEK_SET);
	unsigned short xMin = BKReadUShort(fp);
	unsigned short yMin = BKReadUShort(fp);
	unsigned short xMax = BKReadUShort(fp);
	unsigned short yMax = BKReadUShort(fp);
	iwidth = (int) xMax - xMin + 1;
	iheight = (int) yMax - yMin + 1;

	//get pixels
	int idx = 0;
	int numRepeat = 0;
	pixels = (unsigned char*)malloc(iwidth*iheight);
	fseek(fp,128,SEEK_SET);
	while(idx < iwidth*iheight)
	{
		fread(&c,1,1,fp);
		if(c > 0xbf)
		{
			numRepeat = 0x3f & c;
			fread(&c,1,1,fp);
			for(int i = 0; i < numRepeat; i++)
			{
				pixels[idx++] = c;
			}
		}
		else pixels[idx++] = c;
		fflush(stdout);
	}
	//Scale....... don't finish

}

void BKImage::getImageFromBMP(const char* filename)
{
	//don't finish
}

void BKImage::getImageFromTGA(const char* filename)
{
	//don't finish
}