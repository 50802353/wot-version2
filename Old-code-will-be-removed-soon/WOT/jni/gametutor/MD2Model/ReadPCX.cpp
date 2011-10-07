#include "ReadPCX.h"

void ReadPCX1bit (FILE *fp,  struct pcx_header_t *hdr,  image_src *texinfo)
{
  __INT32 y, i, bytes;
  __INT32 colorIndex;
  __INT32 rle_count = 0, rle_value = 0;
  __UINT8 *ptr = texinfo->texels;

  for (y = 0; y < texinfo->height; ++y)
    {
      ptr = &texinfo->texels[(texinfo->height - (y + 1)) * texinfo->width * 3];
      bytes = hdr->bytesPerScanLine;

      /* Decode line number y */
      while (bytes--)
        {
          if (rle_count == 0)
            {
              if ( (rle_value = fgetc (fp)) < 0xc0)
                {
                  rle_count = 1;
                }
              else
                {
                  rle_count = rle_value - 0xc0;
                  rle_value = fgetc (fp);
                }
            }

          rle_count--;

          for (i = 7; i >= 0; --i, ptr += 3)
            {
              colorIndex = ((rle_value & (1 << i)) > 0);

              ptr[0] = hdr->palette[colorIndex * 3 + 0];
              ptr[1] = hdr->palette[colorIndex * 3 + 1];
              ptr[2] = hdr->palette[colorIndex * 3 + 2];
            }
        }
    }
}

void ReadPCX4bits (FILE *fp,  struct pcx_header_t *hdr, image_src *texinfo)
{
  __UINT8 *colorIndex, *line;
  __UINT8 *pLine, *ptr;
  __INT32 rle_count = 0, rle_value = 0;
  __INT32 x, y, c;
  __INT32 bytes;

  colorIndex = (__UINT8 *)malloc (sizeof (__UINT8) * texinfo->width);
  line = (__UINT8 *)malloc (sizeof (__UINT8) * hdr->bytesPerScanLine);

  for (y = 0; y < texinfo->height; ++y)
    {
      ptr = (__UINT8*)&texinfo->texels[(texinfo->height - (y + 1)) * texinfo->width * 3];

      memset (colorIndex, 0, texinfo->width * sizeof (__UINT8));

      for (c = 0; c < 4; ++c)
        {
          pLine = line;
          bytes = hdr->bytesPerScanLine;

          /* Decode line number y */
          while (bytes--)
            {
              if (rle_count == 0)
                {
                  if ( (rle_value = fgetc (fp)) < 0xc0)
                    {
                      rle_count = 1;
                    }
                  else
                    {
                      rle_count = rle_value - 0xc0;
                      rle_value = fgetc (fp);
                    }
                }

              rle_count--;
              *(pLine++) = rle_value;
            }

          /* Compute line's color indexes */
          for (x = 0; x < texinfo->width; ++x)
            {
              if (line[x / 8] & (128 >> (x % 8)))
                colorIndex[x] += (1 << c);
            }
        }

      /* Decode scan line.  color index => rgb  */
      for (x = 0; x < texinfo->width; ++x, ptr += 3)
        {
          ptr[0] = hdr->palette[colorIndex[x] * 3 + 0];
          ptr[1] = hdr->palette[colorIndex[x] * 3 + 1];
          ptr[2] = hdr->palette[colorIndex[x] * 3 + 2];
        }
    }

  /* Release memory */
  free (colorIndex);
  free (line);
}

void ReadPCX8bits (FILE *fp,  struct pcx_header_t *hdr, image_src *texinfo)
{
  __INT32 rle_count = 0, rle_value = 0;
  __UINT8 palette[768];
  __UINT8 magic;
  __UINT8 *ptr;
  fpos_t curpos;
  __INT32 y, bytes;

  /* The palette is contained in the last 769 bytes of the file */
  fgetpos (fp, &curpos);
  fseek (fp, -769, SEEK_END);
  magic = fgetc (fp);

  /* First byte must be equal to 0x0c (12) */
  if (magic != 0x0c)
    {
      //fprintf (stderr, "error: colormap's first byte must be 0x0c! "
      //         "(%#x)\n", magic);
	  LogError("error: colormap's first byte must be 0x0c!\n");
      free (texinfo->texels);
      texinfo->texels = NULL;
      return;
    }

  /* Read palette */
  fread (palette, sizeof (__UINT8), 768, fp);
  fsetpos (fp, &curpos);

  /* Read pixel data */
  for (y = 0; y < texinfo->height; ++y)
    {
      ptr = (__UINT8*)&texinfo->texels[(texinfo->height - (y + 1)) * texinfo->width * 3];
      bytes = hdr->bytesPerScanLine;

      /* Decode line number y */
      while (bytes--)
        {
          if (rle_count == 0)
            {
              if( (rle_value = fgetc (fp)) < 0xc0)
                {
                  rle_count = 1;
                }
              else
                {
                  rle_count = rle_value - 0xc0;
                  rle_value = fgetc (fp);
                }
            }

          rle_count--;

          ptr[0] = palette[rle_value * 3 + 0];
          ptr[1] = palette[rle_value * 3 + 1];
          ptr[2] = palette[rle_value * 3 + 2];
          ptr += 3;
        }
    }
}

void ReadPCX24bits (FILE *fp,  struct pcx_header_t *hdr, image_src *texinfo)
{
  __UINT8 *ptr = texinfo->texels;
  __INT32 rle_count = 0, rle_value = 0;
  __INT32 y, c;
  __INT32 bytes;

  for (y = 0; y < texinfo->height; ++y)
    {
      /* For each color plane */
      for (c = 0; c < 3; ++c)
        {
          ptr = &texinfo->texels[(texinfo->height - (y + 1)) * texinfo->width * 3];
          bytes = hdr->bytesPerScanLine;

          /* Decode line number y */
          while (bytes--)
            {
              if (rle_count == 0)
                {
                  if( (rle_value = fgetc (fp)) < 0xc0)
                    {
                      rle_count = 1;
                    }
                  else
                    {
                      rle_count = rle_value - 0xc0;
                      rle_value = fgetc (fp);
                    }
                }

              rle_count--;
              ptr[c] = (__UINT8)rle_value;
              ptr += 3;
            }
        }
    }
}

image_src * ReadPCXFile (const char *filename)
{
  image_src *texinfo;
  struct pcx_header_t header;
  FILE *fp = NULL;
  __INT32 bitcount;

  /* Open image file */
//  errno_t err;
  __INT32 err;
  err = fopen_s (&fp,filename, "rb");
  if (err!=0)
    {
		//fprintf (stderr, "error: couldn't open \"%s\"!\n", filename);
		LogError("error: pcx file error!\n");
		return NULL;
    }

  /* Read header file */
  fread (&header, sizeof (struct pcx_header_t), 1, fp);
  if (header.manufacturer != 0x0a)
    {
//      fprintf (stderr, "error: bad version number! (%i)\n",
//               header.manufacturer);
		LogError("error: pcx file bad format!\n");
		return 0;
    }

  /* Initialize texture parameters */
  texinfo = (image_src *)malloc (sizeof (image_src));
  texinfo->width = header.xmax - header.xmin + 1;
  texinfo->height = header.ymax - header.ymin + 1;
  texinfo->format = 0;
  texinfo->internalFormat = 3;
  texinfo->texels = (__UINT8 *)
    malloc (sizeof (__UINT8) * texinfo->width
            * texinfo->height * texinfo->internalFormat);

  bitcount = header.bitsPerPixel * header.numColorPlanes;

  /* Read image data */
  switch (bitcount)
    {
    case 1:
      /* 1 bit color index */
      ReadPCX1bit (fp, &header, texinfo);
      break;

    case 4:
      /* 4 bits color index */
      ReadPCX4bits (fp, &header, texinfo);
      break;

    case 8:
      /* 8 bits color index */
      ReadPCX8bits (fp, &header, texinfo);
      break;

    case 24:
      /* 24 bits */
      ReadPCX24bits (fp, &header, texinfo);
      break;

    default:
      /* Unsupported */
    //  fprintf (stderr, "error: unknown %i bitcount pcx files\n", bitcount);
		LogError("error: pcx file format is not supported!\n");
		free (texinfo->texels);
		free (texinfo);
		texinfo = 0;
      break;
    }

  fclose (fp);
  texinfo->type=0;
  texinfo->numMipmaps=0;
  texinfo->bpc = 1;
  return texinfo;
}
