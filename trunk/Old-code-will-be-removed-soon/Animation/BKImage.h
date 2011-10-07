#include<stdio.h>
#include"ReadBinaryToolkit.h"

enum ImageType
{
	PCX,
	BMP,
	TGA
};


class BKImage
{
private:
	void getImagePCX(const char* filename);
	void getImageBMP(const char* filename);
	void getImageTGA(const char* filename);
public:
	int iwidth;
	int iheight;
	unsigned char* pixels;

	BKImage(void);
	~BKImage(void);
	//This function support for PCX, BMP, TGA file
	void getImage(const char* filename);
};

typedef struct
{
	unsigned char manufacturer;
	unsigned char version;
	unsigned char encoding;
	unsigned char bits;
	unsigned char xMin;
	unsigned char yMin;
	unsigned char xMax;
	unsigned char yMax;
	unsigned char *palette;
} PCXHeader;