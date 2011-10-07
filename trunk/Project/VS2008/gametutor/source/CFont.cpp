#include "CFont.h"
#include "CImageManager.h"
#include "CImage.h"
#include "CGraphics2D.h"
namespace GameTutor
{
	__INT32 CFont::s_iFontCounter = 0;
	CFont::CFont(): m_iCharSpacing(0), m_strImageName(0), m_iLineSpacing(0)
	{
	}

	CFont::~CFont()
	{
		m_LetterLUT.Clear();
		if (CImageManager::IsAvailable())	CImageManager::GetInstance()->Free(m_strImageName);
		SAFE_DEL(m_strImageName);
	}

	CFont* CFont::Import(IReadableStream* F)
	{
		CFont *re = new CFont;
		__INT8 version = 0;
		F->ReadInt8(version);
		if (version == 1)
		{
			//load font table
			SCompressorData fntTableData;
			F->ReadInt32(fntTableData.m_iCompressedDataSize);
			fntTableData.m_pCompressedData = new __INT8[fntTableData.m_iCompressedDataSize];
			F->Read((__UINT8*)fntTableData.m_pCompressedData, 0, fntTableData.m_iCompressedDataSize);
			CCompressor::RLEDecompress(fntTableData);
			CReaderStream<CStreamDriverBuffer>* fntBuf = new CReaderStream<CStreamDriverBuffer>("");
			fntBuf->Init((__UINT8*)fntTableData.m_pOriginalData, fntTableData.m_iOriginalDataSize, false);

			__INT16 numOfLetters = 0;
			__INT8 TextureWidthBits = 0;
			__INT8 TextureHeightBits = 0;
			__INT8 TextureWidth = 0;
			__INT8 TextureHeight = 0;
			__INT8 FntBaseHeight = 0;
			__INT8 FntHeight = 0;
			fntBuf->ReadInt16(numOfLetters);
			fntBuf->ReadInt8(TextureWidthBits);
			fntBuf->ReadInt8(TextureHeightBits);
			fntBuf->ReadInt8(FntBaseHeight);
			fntBuf->ReadInt8(FntHeight);
			TextureWidth = 1<<TextureWidthBits;
			FntBaseHeight = 1<<TextureHeightBits;

			re->m_iNumberOfLetter = (__INT32)numOfLetters;
			re->m_iFontBaseHeight = (__INT32)FntBaseHeight;
			re->m_iFontHeight = (__INT32)FntHeight;

			re->m_LetterLUT.Clear();
			for (int i = 0; i < numOfLetters; i++)
			{
				__INT32 code = 0;
				SLetterInfo LI = {0, 0, 0, 0};
				fntBuf->ReadInt32(code);
				fntBuf->ReadInt16(LI.FrameX);
				fntBuf->ReadInt16(LI.FrameY);
				fntBuf->ReadInt16(LI.FrameW);
				fntBuf->ReadInt16(LI.FrameH);
				re->m_LetterLUT.AddItem(code, LI);

			}
			SAFE_DEL(fntTableData.m_pCompressedData);
			SAFE_DEL(fntTableData.m_pOriginalData);
			SAFE_DEL(fntBuf);

			//load image
			__INT16 imgWitdh = 0;
			__INT16 imgHeight = 0;
			SCompressorData ImgData;
			F->ReadInt16(imgWitdh);
			F->ReadInt32(ImgData.m_iCompressedDataSize);
			ImgData.m_pCompressedData = new __INT8[ImgData.m_iCompressedDataSize];
			F->Read((__UINT8*)ImgData.m_pCompressedData, 0, ImgData.m_iCompressedDataSize);
			CCompressor::RLEDecompress(ImgData);
			imgHeight = (ImgData.m_iOriginalDataSize / imgWitdh)>>2;
			
			char name[] = {'C', 'F', 'O', 'N', 'T', ':', '0' + s_iFontCounter/100, '0' + (s_iFontCounter/10)%10, '0' + s_iFontCounter%10, '\0'};
			s_iFontCounter++;
			re->m_strImageName = new char[10];
			memcpy(re->m_strImageName, name, 10);
			re->m_fntImage = CImage::LoadRGBA(imgWitdh, imgHeight, ImgData.m_pOriginalData);
			CImageManager::GetInstance()->Add(re->m_strImageName, re->m_fntImage);
			re->m_fntImage->BindGPU();
			SAFE_DEL(ImgData.m_pCompressedData);
			SAFE_DEL(ImgData.m_pOriginalData);

		}
		else
		{
			LogError("Font version is not supported!");
			delete F;
			delete re;
			return 0;
		}
		return re;
	}

	void CFont::DrawLetter(CGraphics2D*g, int letterCode, int x, int y)
	{
		SLetterInfo info;
		if (this->m_LetterLUT.GetElement(letterCode, info))
		{
			g->DrawImageRegion(SPosition2D<__INT32>(x, y), this->m_fntImage, SRect<__INT32>(info.FrameX, info.FrameY, info.FrameW, info.FrameH));
			//g->DrawImage(SPosition2D<__INT32>(0, 0), this->m_fntImage);
		}
	}

	void CFont::DrawString(CGraphics2D*g, int* text, int len, int x, int y,  ETextHAnchor HAnchor, ETextVAnchor VAnchor)
	{
		if (VAnchor == ETEXTANCHOR_BASELINE)
		{
			y -= this->m_iFontBaseHeight;
		}
		else if (VAnchor == ETEXTANCHOR_BOTTOM)
		{
			y -= this->m_iFontHeight;
		}

		int w = 0;
		SLetterInfo info;
		if (HAnchor == ETEXTANCHOR_RIGHT || HAnchor == ETEXTANCHOR_RIGHT)
		{
			for (int i = 0; i < len; i++)
			{
				
				if (this->m_LetterLUT.GetElement(text[i], info))
				{
					w += info.FrameW + m_iCharSpacing;
				}
			}
			if (HAnchor == ETEXTANCHOR_RIGHT)
			{
				x -= w;
			}
			else
			{
				x -= w>>1;
			}
		}

		int savex = x;

		for (int i = 0; i < len; i++)
		{
			if (text[i] == 10) //new line
			{
				y+= this->m_iFontHeight + m_iLineSpacing;
				x = savex;
			}
			else if (this->m_LetterLUT.GetElement(text[i], info))
			{
				DrawLetter(g, text[i], x, y);
				x += info.FrameW + m_iCharSpacing;
			}
		}
	}

	void CFont::DrawString(CGraphics2D*g, char* text, int len, int x, int y,  ETextHAnchor HAnchor, ETextVAnchor VAnchor)
	{
		if (VAnchor == ETEXTANCHOR_BASELINE)
		{
			y -= this->m_iFontBaseHeight;
		}
		else if (VAnchor == ETEXTANCHOR_BOTTOM)
		{
			y -= this->m_iFontHeight;
		}

		int w = 0;
		SLetterInfo info;
		if (HAnchor == ETEXTANCHOR_RIGHT || HAnchor == ETEXTANCHOR_RIGHT)
		{
			for (int i = 0; i < len; i++)
			{

				if (this->m_LetterLUT.GetElement(text[i], info))
				{
					w += info.FrameW + m_iCharSpacing;
				}
			}
			if (HAnchor == ETEXTANCHOR_RIGHT)
			{
				x -= w;
			}
			else
			{
				x -= w>>1;
			}
		}

		int savex = x;

		for (int i = 0; i < len; i++)
		{
			if (text[i] == 10) //new line
			{
				y+= this->m_iFontHeight + m_iLineSpacing;
				x = savex;
			}
			else if (this->m_LetterLUT.GetElement(text[i], info))
			{
				DrawLetter(g, (int)(text[i]&0xFF), x, y);
				x += info.FrameW + m_iCharSpacing;
			}
		}
	}
}