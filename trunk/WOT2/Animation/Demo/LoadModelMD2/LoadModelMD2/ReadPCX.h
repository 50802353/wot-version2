#ifndef _READ_PCX_H
#define _READ_PCX_H

#include "stdlib.h"
#include "stdio.h"
#include "string.h"


struct pcx_header_t
{
  unsigned char manufacturer;
  unsigned char version;
  unsigned char encoding;
  unsigned char bitsPerPixel;

  unsigned short xmin, ymin;
  unsigned short xmax, ymax;
  unsigned short horzRes, vertRes;

  unsigned char palette[48];
  unsigned char reserved;
  unsigned char numColorPlanes;

  unsigned short bytesPerScanLine;
  unsigned short paletteType;
  unsigned short horzSize, vertSize;

  unsigned char padding[54];
};

struct image_src
{
	int width;
	int height;
	int format;
	int internalFormat;
	int type;
	int numMipmaps;
	int bpc;
	unsigned char* texels;
};

void ReadPCX1bit (FILE *fp,  struct pcx_header_t *hdr,  image_src *texinfo);

void ReadPCX4bits (FILE *fp,  struct pcx_header_t *hdr, image_src *texinfo);

void ReadPCX8bits (FILE *fp,  struct pcx_header_t *hdr, image_src *texinfo);

void ReadPCX24bits (FILE *fp,  struct pcx_header_t *hdr, image_src *texinfo);

image_src * ReadPCXFile (const char *filename);


#endif