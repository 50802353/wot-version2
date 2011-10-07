#ifndef __CIMAGE_H__
#define __CIMAGE_H__

#include "Header.h"
#include "SGraphics.h"
#include "IVideoDriver.h"
#include "Stream.h"
#include "SGameConfig.h"

namespace GameTutor
{
	enum EImagePixelFormat
	{
		EIMAGE_FORMAT_R8G8B8,
		EIMAGE_FORMAT_R8G8B8A8,
	};
	// TGA Header
	struct TGA_Header {
		__INT8  idlength;
		__INT8  colourmaptype;
		__INT8  datatypecode;
		__INT16 colourmaporigin;
		__INT16 colourmaplength;
		__INT8  colourmapdepth;
		__INT16 x_origin;
		__INT16 y_origin;
		__INT16 width;
		__INT16 height;
		__INT8  bitsperpixel;
		__INT8  imagedescriptor;
	};
	// PCX header
	struct PCX_Header
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
	//-- image src struct for LoadPCX function only
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


	extern SGameConfig Configuation;
	class CImage
	{
	public:
		CImage(int width, int height, EImagePixelFormat format);
		virtual ~CImage();
		__UINT32 GetDataSize() 
		{
			return GetPixelSize()*m_iWidth*m_iHeight;
		}
		__UINT32 GetPixelSize()
		{
			switch (m_eFormat)
			{
			case EIMAGE_FORMAT_R8G8B8:
				return 3;
			case EIMAGE_FORMAT_R8G8B8A8:
				return 4;
			default:
				return 0;
			}
		}
		void GetPixel(__UINT32 row, __UINT32 col, SColor<__UINT8> &c);
		void SetPixel(__UINT32 row, __UINT32 col, SColor<__UINT8> c);
		void ClearColor(SColor<__UINT8> c);
		__UINT32 GetTextureID() {return m_iTextureID;}
		__UINT32 GetWidth() {return this->m_iWidth;}
		__UINT32 GetHeight() {return this->m_iHeight;}
		EImagePixelFormat GetPixelFormat() {return m_eFormat;}
		static CImage* LoadTGA(IReadableStream* stream, bool auto_alpha = false);
		static CImage* LoadPCX(IReadableStream* stream);
		void VerticalFlip();
	public:
		void BindGPU(IVideoDriver *driver = Configuation.pVideoDriver);
		void UnbindGPU(IVideoDriver *driver = Configuation.pVideoDriver);
		void FreeBuffer();
	protected:
		__UINT32 m_iWidth;
		__UINT32 m_iHeight;
		EImagePixelFormat m_eFormat;
		__UINT8 *m_pData;
		__UINT32 m_iTextureID;
	private:
		static void ReadPCX1bit (IReadableStream* stream,  struct PCX_Header *hdr,  image_src *texinfo);

		static void ReadPCX4bits (IReadableStream* stream,  struct PCX_Header *hdr, image_src *texinfo);

		static void ReadPCX8bits (IReadableStream* stream,  struct PCX_Header *hdr, image_src *texinfo);

		static void ReadPCX24bits (IReadableStream* stream,  struct PCX_Header *hdr, image_src *texinfo);
	};
}

#endif