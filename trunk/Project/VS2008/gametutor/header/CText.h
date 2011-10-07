#ifndef __CTEXT_H__
#define __CTEXT_H__

#include "Header.h"
#include "CCompressor.h"
#include "Stream.h"
#include "CLookupTableI.h"
#include "CImage.h"
#include "CSingleton.h"
#include "CFont.h"

namespace GameTutor
{
	class CFont;
	class CGraphics2D;

	struct STextDataSegment
	{
		__INT32 Offset;
		__INT16 Len;
		__INT16 Size;
	};
	class CText: public CSingleton<CText>
	{
	friend class CSingleton<CText>;
	protected:
		CText();
	public:
		~CText();
		template <class IODriver> void Load(char *Lang);
		char* GetLanguage() {return m_strLang;}
		void SetFont(int fnt);
		void DrawString(CGraphics2D*g, int text, int x, int y, ETextHAnchor HAnchor, ETextVAnchor VAnchor);
		void SetLineSpacing(__INT32 val);
		void SetCharSpacing(__INT32 val);
		__INT32 GetLineSpacing() {return m_iLineSpacing;}
		__INT32 GetCharSpacing() {return m_iCharSpacing;}
	private:
		CLutI<STextDataSegment> m_TextMapping;
		CLutI<CFont*> m_FontMapping;
		__INT32* m_pText;
		char* m_strLang;
		int m_iFontIndex;
		CFont* m_pCurrentFont;
		void Deallocate();
		__INT32 m_iCharSpacing;
		__INT32 m_iLineSpacing;
	};

	template <class IODriver>
	void CText::Load(char* Lang)
	{
		Deallocate();

		char* filename = new char[strlen(Lang) + 5 +1];
		memset(filename, 0, strlen(Lang) + 5 +1);
		memcpy(filename, Lang, strlen(Lang) + 1);
		memcpy(filename + strlen(Lang), ".lang", 5);
		CReaderStream<IODriver>* stream = new CReaderStream<IODriver>(filename);
		if (stream->GetStatus() == EStreamStatus::ESTREAM_ERROR)
		{
			SAFE_DEL(filename);
			SAFE_DEL(stream);
			return;
		}

			m_strLang = new char[strlen(Lang) + 1];
		memcpy(m_strLang, Lang, strlen(Lang) + 1);
		__INT8 version = 0;
		stream->ReadInt8(version);
		if (version == 1)
		{
			__INT32 numOfText = 0;
			__INT16 numOfFont = 0;
			stream->ReadInt32(numOfText);
			stream->ReadInt16(numOfFont);

			//read font		
			for (int i = 0; i < numOfFont; i++)
			{
				__INT16 fontIndex = 0;
				char fntName[49];
				memset(fntName, 0, 49);
				stream->ReadInt16(fontIndex);
				stream->Read((__UINT8*)fntName, 0, 48);
				CReaderStream<IODriver>* F = new CReaderStream<IODriver>(fntName);
				if (F->GetStatus() == ESTREAM_OPEN)
				{
					CFont *fnt = CFont::Import(F);
					m_FontMapping.AddItem(fontIndex, fnt);
					delete F;
				}
				else
				{
					delete F;
				}
			}

			//read text offset
			int numOfBytes = 0;
			int numOfLetter = 0;
			for (int i = 0; i < numOfText; i++)
			{
				STextDataSegment seg = {0, 0, 0};
				stream->ReadInt32(seg.Offset);
				stream->ReadInt16(seg.Len);
				stream->ReadInt16(seg.Size);
				m_TextMapping.AddItem(i, seg);
				numOfBytes += seg.Size;
				numOfLetter += seg.Len;
			}

			char* text = new char[numOfBytes];
			stream->Read((__UINT8*)text, 0, numOfBytes);
			m_pText = new __INT32[numOfLetter];
			int*tmp = m_pText;

			int i = 0;
			while (i < numOfBytes)
			{
				//utf8 decode
				int bytecode = 0;
				int c = text[i]&0xFF;
				if ((c >> 7) == 0)
				{
					bytecode = (c & 0x7F);
					i++;
				}
				else if ((c >> 5) == 0x6)
				{
					bytecode = ((c & 0x1F) << 6) | (text[i+1] & 0x3F);
					i+=2;
				}
				else if ((c >> 4) == 0xe)
				{
					bytecode = ((c & 0xF) << 12) | ((text[i+1] & 0x3F) << 6) | (text[i+2] & 0x3F);
					i+=3;
				}
				else if ((c >> 3) == 0x1e)
				{
					bytecode = ((c & 0x7) << 18) | ((text[i+1] & 0x3F) << 12) | ((text[i+2] & 0x3F) << 6) | (text[i+3] & 0x3F);
					i+=4;
				}
				(*tmp) = bytecode;
				tmp++;
			}
			SAFE_DEL(text);
		}
		SAFE_DEL(filename);
		SAFE_DEL(stream);
	}
}

#endif