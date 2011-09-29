#ifndef _READ_PCX_H
#define _READ_PCX_H

#include "Header.h"
#include "stdlib.h"
#include "stdio.h"
#include "string.h"


struct pcx_header_t
{
  __UINT8 manufacturer;
  __UINT8 version;
  __UINT8 encoding;
  __UINT8 bitsPerPixel;

  __UINT16 xmin, ymin;
  __UINT16 xmax, ymax;
  __UINT16 horzRes, vertRes;

  __UINT8 palette[48];
  __UINT8 reserved;
  __UINT8 numColorPlanes;

  __UINT16 bytesPerScanLine;
  __UINT16 paletteType;
  __UINT16 horzSize, vertSize;

  __UINT8 padding[54];
};

struct image_src
{
	__INT32 width;
	__INT32 height;
	__INT32 format;
	__INT32 internalFormat;
	__INT32 type;
	__INT32 numMipmaps;
	__INT32 bpc;
	__UINT8* texels;
};

void ReadPCX1bit (FILE *fp,  struct pcx_header_t *hdr,  image_src *texinfo);

void ReadPCX4bits (FILE *fp,  struct pcx_header_t *hdr, image_src *texinfo);

void ReadPCX8bits (FILE *fp,  struct pcx_header_t *hdr, image_src *texinfo);

void ReadPCX24bits (FILE *fp,  struct pcx_header_t *hdr, image_src *texinfo);

image_src * ReadPCXFile (const char *filename);


#endif