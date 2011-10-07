#include "CImage.h"
#include "CGLPipelineDriver.h"

namespace GameTutor
{
	extern SGameConfig Configuation;
	CImage::CImage(int width, int height, EImagePixelFormat format ):m_iWidth(width), m_iHeight(height), m_eFormat(format), m_pData(0), m_iTextureID(0)
	{
		int dataSize = GetDataSize();
		m_pData = new __UINT8[dataSize];
	}	

	CImage::~CImage()
	{
		SAFE_DEL(m_pData);
	}

	void CImage::GetPixel(__UINT32 row, __UINT32 col, SColor<__UINT8> &c)
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

	void CImage::SetPixel(__UINT32 row, __UINT32 col, SColor<__UINT8> c)
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

	void CImage::BindGPU()
	{
		IVideoDriver *driver = Configuation.pVideoDriver;
		BREAK_IF(!driver, "Video driver is NULL");
		if (driver->IsVideoDriver(EVIDEO_DRIVER_OGLPIPELINE))
		{
			CGLPipelineDriver *glplDriver = (CGLPipelineDriver *)driver;
			if (m_iTextureID > 0)
			{
				//this->UnbindGPU(driver);
				return;
			}
			switch (m_eFormat)
			{
			case EIMAGE_FORMAT_R8G8B8:
				this->m_iTextureID = glplDriver->AddTexure2D(0, EGLPD_PIXFMT_R8G8B8, this->m_iWidth, this->m_iHeight, 0, this->m_pData);
				break;
			case EIMAGE_FORMAT_R8G8B8A8:
				this->m_iTextureID = glplDriver->AddTexure2D(0, EGLPD_PIXFMT_R8G8B8A8, this->m_iWidth, this->m_iHeight, 0, this->m_pData);
				break;
			default:
				break;
			}
		}
	}

	void CImage::UnbindGPU()
	{
		IVideoDriver *driver = Configuation.pVideoDriver;
		BREAK_IF(!driver, "Video driver is NULL");
		if (driver->IsVideoDriver(EVIDEO_DRIVER_OGLPIPELINE))
		{
			CGLPipelineDriver *glplDriver = (CGLPipelineDriver *)driver;
			if (m_iTextureID > 0)
			{
				glplDriver->FreeTexture2D(this->m_iTextureID);
			}
		}
	}

	CImage* CImage::LoadRGBA(int width, int height, __INT8* rgba)
	{
		if (!rgba) return 0;
		CImage *re = new CImage(width, height, EIMAGE_FORMAT_R8G8B8A8);
		delete re->m_pData;
		re->m_pData = new __UINT8[width*height*4];
		memcpy(re->m_pData, rgba, width*height*4);
		return re;
	}

	CImage* CImage::LoadTGA(IReadableStream* stream)
	{
		TGA_Header header;
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
			stream->Read(img->m_pData, 0, header.width*header.height*header.bitsperpixel/8);
			img->VerticalFlip();
		}

		return img;
	}

	void CImage::VerticalFlip()
	{
		__UINT32 runlen = GetPixelSize()*m_iWidth;
		__UINT8* buff = new __UINT8[runlen];
		__UINT8* top = m_pData;
		__UINT8* bottom = m_pData + ((m_iHeight - 1)*runlen);
		for (__UINT32 i = 0; i < m_iHeight>>1; i++)
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