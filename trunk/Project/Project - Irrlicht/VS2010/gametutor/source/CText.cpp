#include "CText.h"

namespace GameTutor
{
	CText::CText():m_strLang(0), m_iFontIndex(-1), m_pCurrentFont(0), m_pText(0), m_iLineSpacing(0), m_iCharSpacing(0)
	{}
	CText::~CText()
	{
		Deallocate();
	}

	void CText::SetFont(int fnt)
	{
		m_iFontIndex = fnt;
		if (!m_FontMapping.GetElement(fnt, m_pCurrentFont))
		{
			m_pCurrentFont = 0;
		}
		if (m_pCurrentFont)
		{
			m_pCurrentFont->SetCharSpacing(m_iCharSpacing);
			m_pCurrentFont->SetLineSpacing(m_iLineSpacing);
		}
	}

	void CText::DrawString(CGraphics2D*g, int text, int x, int y, ETextHAnchor HAnchor, ETextVAnchor VAnchor)
	{
		if (!m_pCurrentFont)
		{
			if (!m_FontMapping.GetElement(0, m_pCurrentFont))
			{
				return;
			}
		}
		if (m_pCurrentFont)
		{
			STextDataSegment seg;
			if (m_TextMapping.GetElement(text, seg))
			{
				m_pCurrentFont->DrawString(g, m_pText+seg.Offset, seg.Len, x, y, HAnchor, VAnchor);
			}
			
		}
	}

	void CText::Deallocate()
	{
		m_FontMapping.DeallocateElementPointer();
		m_TextMapping.Clear();
		m_FontMapping.Clear();
		SAFE_DEL(m_strLang);
		SAFE_DEL(m_pText);
	}

	void CText::SetLineSpacing(__INT32 val) 
	{
		m_iLineSpacing = val;
		if (m_pCurrentFont)
		{
			m_pCurrentFont->SetLineSpacing(m_iLineSpacing);
		}
	}

	void CText::SetCharSpacing(__INT32 val) 
	{
		m_iCharSpacing = val;
		if (m_pCurrentFont)
		{
			m_pCurrentFont->SetCharSpacing(m_iCharSpacing);
		}
	}
}