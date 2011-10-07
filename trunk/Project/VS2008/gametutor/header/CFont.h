#ifndef __CFONT_H__
#define __CFONT_H__
#include "Header.h"
#include "CCompressor.h"
#include "Stream.h"
#include "CLookupTableI.h"
#include "CImage.h"
#include "CText.h"
namespace GameTutor
{
	class CGraphics2D;
	struct SLetterInfo
	{
		__INT16 FrameX;
		__INT16 FrameY;
		__INT16 FrameW;
		__INT16 FrameH;
	};

	class CFont
	{
	public:
		CFont();
		virtual ~CFont();
		void DrawLetter(CGraphics2D*g, int letterCode, int x, int y);
		void DrawString(CGraphics2D*g, int* text, int len, int x, int y, ETextHAnchor HAnchor, ETextVAnchor VAnchor);
		void DrawString(CGraphics2D*g, char* text, int len, int x, int y, ETextHAnchor HAnchor, ETextVAnchor VAnchor);
		static CFont* Import(IReadableStream* stream);
		void SetCharSpacing(int val) {m_iCharSpacing = val;}
		int GetCharSpacing() {return m_iCharSpacing;}
		void SetLineSpacing(int val) {m_iLineSpacing = val;}
		int SetLineSpacing() {return m_iLineSpacing;}
	protected:
		int m_iCharSpacing;
		int m_iLineSpacing;
		int m_iNumberOfLetter;
		int m_iFontBaseHeight;
		int m_iFontHeight;
		CLutI<SLetterInfo> m_LetterLUT;
		char* m_strImageName;
		CImage* m_fntImage;
		static __INT32 s_iFontCounter;
	};
}
#endif