#include "CImage.h"
#include "CGLES2Driver.h"

namespace GameTutor
{
	CImage::CImage(int width, int height, EImagePixelFormat format ):m_iWidth(width), m_iHeight(height), m_eFormat(format), m_pData(0), m_iTextureID(0)
	{
		int dataSize = GetDataSize();
		m_pData = new __UINT8[dataSize];
	}	

	CImage::~CImage()
	{
		SAFE_DEL(m_pData);
	}

	void CImage::FreeBuffer()
	{
		SAFE_DEL(m_pData);
	}

	void CImage::GetPixel(__UINT32 row, __UINT32 col, SColor<__UINT8> &c)
	{
		if (m_pData)
		{
			int offset = 0;
			if (row >= 0 && row < m_iHeight && col >= 0 && col <m_iWidth)
			{
				switch (m_eFormat)
				{
				case EIMAGE_FORMAT_R8G8B8:
					offset = (row*m_iWidth + col)*3; //3 bytes per pixels
					memcpy(&c, m_pData + offset, 3);
					c.Alpha = 255;
					break;
				case EIMAGE_FORMAT_R8G8B8A8:
					offset = (row*m_iWidth + col)*4; //3 bytes per pixels
					memcpy(&c, m_pData + offset, 4);
					break;
				}
			}
		}
		else c = SColor<__UINT8>();
	}

	void CImage::SetPixel(__UINT32 row, __UINT32 col, SColor<__UINT8> c)
	{
		if (m_pData)
		{
			int offset = 0;
			if (row >= 0 && row < m_iHeight && col >= 0 && col <m_iWidth)
			{
				switch (m_eFormat)
				{
				case EIMAGE_FORMAT_R8G8B8:
					offset = (row*m_iWidth + col)*3; //3 bytes per pixels
					memcpy(m_pData + offset, &c, 3);
					break;
				case EIMAGE_FORMAT_R8G8B8A8:
					offset = (row*m_iWidth + col)*4; //3 bytes per pixels
					memcpy(m_pData + offset, &c, 4);
					break;
				}
			}
		}
	}

	void CImage::ClearColor(SColor<__UINT8> c)
	{
		int dataSize = GetDataSize();
		switch (m_eFormat)
		{
		case EIMAGE_FORMAT_R8G8B8:
			for (int i = 0; i < dataSize; i+=3)
			{
				memcpy(m_pData + i, &c, 3);
			}
			break;
		case EIMAGE_FORMAT_R8G8B8A8:
			for (int i = 0; i < dataSize; i+=4)
			{
				memcpy(m_pData + i, &c, 4);
			}
			break;
		}
	}

	void CImage::BindGPU(IVideoDriver *driver)
	{
		BREAK_IF(!driver, "Video driver is NULL");
		if (driver->IsVideoDriver(EVIDEO_DRIVER_OGLES2))
		{
			CGLES2Driver *glplDriver = (CGLES2Driver *)driver;
			if (m_iTextureID > 0)
			{
				//this->UnbindGPU(driver);
				return;
			}
			switch (m_eFormat)
			{
			case EIMAGE_FORMAT_R8G8B8:
				this->m_iTextureID = glplDriver->AddTexure2D(0, EGLES2_PIXFMT_R8G8B8, this->m_iWidth, this->m_iHeight, 0, this->m_pData);
				break;
			case EIMAGE_FORMAT_R8G8B8A8:
				this->m_iTextureID = glplDriver->AddTexure2D(0, EGLES2_PIXFMT_R8G8B8A8, this->m_iWidth, this->m_iHeight, 0, this->m_pData);
				break;
			default:
				break;
			}
		}
	}

	void CImage::UnbindGPU(IVideoDriver *driver)
	{
		BREAK_IF(!driver, "Video driver is NULL");
		if (driver->IsVideoDriver(EVIDEO_DRIVER_OGLES2))
		{
			CGLES2Driver *glplDriver = (CGLES2Driver *)driver;
			if (m_iTextureID > 0)
			{
				glplDriver->FreeTexture2D(this->m_iTextureID);
			}
		}
	}


	CImage* CImage::LoadTGA(IReadableStream* stream, bool auto_alpha)
	{

		TGA_Header header;
		//stream->Read((__UINT8*)(&header), 0, sizeof(header));
		stream->ReadInt8(header.idlength);
		stream->ReadInt8(header.colourmaptype);
		stream->ReadInt8(header.datatypecode);
		stream->ReadInt16(header.colourmaporigin);
		stream->ReadInt16(header.colourmaplength);
		stream->ReadInt8(header.colourmapdepth);
		stream->ReadInt16(header.x_origin);
		stream->ReadInt16(header.y_origin);
		stream->ReadInt16(header.width);
		stream->ReadInt16(header.height);
		stream->ReadInt8(header.bitsperpixel);
		stream->ReadInt8(header.imagedescriptor);

		CImage *img = 0;
		Log("[CImage::LoadTGA] Size of header %d, W %d, H %d", sizeof(TGA_Header), header.width, header.height);


		if (header.datatypecode != 2)
		{
			LogError("[CImage::LoadTGA] Unsupported TGA Format. Use non-compress only");
		}
		else if ((header.bitsperpixel != 24) && (header.bitsperpixel != 32))
		{
			LogError("[CImage::LoadTGA] Unsupported TGA Pixel Format. Use 24-, or 32-bpp only");
		}
		else
		{
			img = new CImage(header.width, header.height, (header.bitsperpixel == 24)?EIMAGE_FORMAT_R8G8B8:EIMAGE_FORMAT_R8G8B8A8);
			stream->Skip(header.idlength + header.colourmaptype * header.colourmaplength);
			__UINT8* ptr = img->m_pData;

			if (header.bitsperpixel == 24) 
			{

				for (int i=0; i<header.width*header.height;i++)
				{
					__UINT8 R,G,B;
					stream->ReadUInt8(B);
					stream->ReadUInt8(G);
					stream->ReadUInt8(R);
					*ptr = R; ptr++;
					*ptr = G; ptr++;
					*ptr = B; ptr++;
				}
			} else if (header.bitsperpixel == 32)
			{
				for (int i=0; i<header.width*header.height;i++)
				{
					__UINT8 R,G,B,A;
					stream->ReadUInt8(B);
					stream->ReadUInt8(G);
					stream->ReadUInt8(R);
					stream->ReadUInt8(A);					
					*ptr = R; ptr++;
					*ptr = G; ptr++;
					*ptr = B; ptr++;
					if (auto_alpha)
					{
						__UINT8 alpha = min(min(R,G),B);
						*ptr = 255-alpha; ptr++;
					}
					else 
					{
						*ptr = A; ptr++;
					}
				}
			}
			//img->VerticalFlip();
		}

		return img;
	}

	CImage* CImage::LoadPCX(IReadableStream* stream)
	{
		image_src *texinfo;
		__INT32 bitcount;
		PCX_Header header;

		//Read file header
		stream->Read((__UINT8*)(&header), 0, sizeof(header));
		//stream->ReadInt8(header.idlength);
		//stream->ReadInt8(header.colourmaptype);
		//stream->ReadInt8(header.datatypecode);
		//stream->ReadInt16(header.colourmaporigin);
		//stream->ReadInt16(header.colourmaplength);
		//stream->ReadInt8(header.colourmapdepth);
		//stream->ReadInt16(header.x_origin);
		//stream->ReadInt16(header.y_origin);
		//stream->ReadInt16(header.width);
		//stream->ReadInt16(header.height);
		//stream->ReadInt8(header.bitsperpixel);
		//stream->ReadInt8(header.imagedescriptor);
		if (header.manufacturer != 0x0a)
		{
			//      fprintf (stderr, "error: bad version number! (%i)\n",
			//               header.manufacturer);
			LogError("error: pcx file bad format!\n");
			return 0;
		}
		//Initialize texture parameters
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
			ReadPCX1bit (stream, &header, texinfo);
			break;

		case 4:
			/* 4 bits color index */
			ReadPCX4bits (stream, &header, texinfo);
			break;

		case 8:
			/* 8 bits color index */
			ReadPCX8bits (stream, &header, texinfo);
			break;

		case 24:
			/* 24 bits */
			ReadPCX24bits (stream, &header, texinfo);
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

		//texinfo->type=0;
		// texinfo->numMipmaps=0;
		// texinfo->bpc = 1;
		// return texinfo;
		//return new CImage(texinfo->width,texinfo->height,(char*)texinfo->texels);
		CImage* img = new CImage(texinfo->width,texinfo->height,EIMAGE_FORMAT_R8G8B8);
		img->m_pData = texinfo->texels;
		//delete texinfo
		free (texinfo);
		texinfo = 0;
		return img;
	}

	void CImage::ReadPCX1bit (IReadableStream* stream,  struct PCX_Header *hdr,  image_src *texinfo)
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
					__UINT8 c;
					stream->ReadUInt8(c);

					if (c < 0xc0)
					{	
						rle_count = 1;
						rle_value = c;
					}
					else
					{
						rle_count = c - 0xc0;
						stream->ReadUInt8(c);
						rle_value = c;
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

	void CImage::ReadPCX4bits (IReadableStream* stream,  struct PCX_Header *hdr, image_src *texinfo)
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
						__UINT8 c;
						stream->ReadUInt8(c);

						if (c < 0xc0)
						{	
							rle_count = 1;
							rle_value = c;
						}
						else
						{
							rle_count = c - 0xc0;
							stream->ReadUInt8(c);
							rle_value = c;
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

	void CImage::ReadPCX8bits (IReadableStream* stream,  struct PCX_Header *hdr, image_src *texinfo)
	{
		__INT32 rle_count = 0, rle_value = 0;
		__UINT8 palette[768];
		__UINT8 magic;
		__UINT8 *ptr;
		fpos_t curpos;
		__INT32 y, bytes;

		/* Read pixel data index */
		for (y = 0; y < texinfo->height; ++y)
		{
			ptr = (__UINT8*)&texinfo->texels[(texinfo->height - (y + 1)) * texinfo->width * 3];
			bytes = hdr->bytesPerScanLine;

			/* Decode line number y */
			while (bytes--)
			{
				if (rle_count == 0)
				{
					__UINT8 c;
					stream->ReadUInt8(c);

					if (c < 0xc0)
					{	
						rle_count = 1;
						rle_value = c;
					}
					else
					{
						rle_count = c - 0xc0;
						stream->ReadUInt8(c);
						rle_value = c;
					}
				}

				rle_count--;

				ptr[0] = rle_value;
				ptr[1] = rle_value;
				ptr[2] = rle_value;
				ptr += 3;
			}
		}

		stream->Goto(0);
		stream->Goto(stream->GetLength() - 769);
		// fseek (fp, -769, SEEK_END);
		//magic = fgetc (fp);
		stream->ReadUInt8(magic);

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
		//fread (palette, sizeof (__UINT8), 768, fp);		
		stream->Read(palette,0,768);
		//read data pixels
		for (y = 0; y < texinfo->height; ++y)
		{
			ptr = (__UINT8*)&texinfo->texels[(texinfo->height - (y + 1)) * texinfo->width * 3];
			bytes = hdr->bytesPerScanLine;

			 while (bytes--)
			 {
				 ptr[0] = palette[ptr[0] * 3 + 0];
				 ptr[1] = palette[ptr[1] * 3 + 1];
				 ptr[2] = palette[ptr[2] * 3 + 2];
				 ptr += 3;
			 }
		}

	}

	void CImage::ReadPCX24bits (IReadableStream* stream,  struct PCX_Header *hdr, image_src *texinfo)
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
						__UINT8 c;
						stream->ReadUInt8(c);

						if (c < 0xc0)
						{	
							rle_count = 1;
							rle_value = c;
						}
						else
						{
							rle_count = c - 0xc0;
							stream->ReadUInt8(c);
							rle_value = c;
						}
					}

					rle_count--;
					ptr[c] = (__UINT8)rle_value;
					ptr += 3;
				}
			}
		}
	}

	void CImage::VerticalFlip()
	{
		__UINT32 runlen = GetPixelSize()*m_iWidth;
		__UINT8* buff = new __UINT8[runlen];
		__UINT8* top = m_pData;
		__UINT8* bottom = m_pData + ((m_iHeight - 1)*runlen);
		for (int i = 0; i < m_iHeight>>1; i++)
		{
			memcpy(buff, top, runlen);
			memcpy(top, bottom, runlen);
			memcpy(bottom, buff, runlen);
			top += runlen;
			bottom -= runlen;
		}
		SAFE_DEL(buff);
	}
}