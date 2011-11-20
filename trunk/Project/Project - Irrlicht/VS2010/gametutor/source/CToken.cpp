#include "CToken.h"

namespace GameTutor
{
	CToken::CToken()
	{
		m_pString = 0;
		m_Token = new CList<STokenSegment>();
	}

	CToken::CToken(char* strPointer)
	{
		m_pString = strPointer;
		m_Token = new CList<STokenSegment>();
		this->ParseToken();
	}

	CToken::~CToken()
	{
		SAFE_DEL(m_Token);
	}

	void CToken::DeallocateStringPointer()
	{
		SAFE_DEL(m_pString);
	}

	void CToken::ParseToken()
	{
		m_Token->Clear();

		int len = strlen(m_pString);

		if (len == 0)
		{
			return;
		}

		int last = 0;
		int i = 0;
		for (i = 0; i < len-1; i++)
		{
			if (!IS_MATCH_TOKEN(m_pString[i]) && IS_MATCH_TOKEN(m_pString[i+1])) //break
			{
				int len = i - last + 1;
				STokenSegment tok = {last, len};
				m_Token->AddItem(tok);
			}
			else if (IS_MATCH_TOKEN(m_pString[i]) && !IS_MATCH_TOKEN(m_pString[i+1])) //break
			{
				last = i + 1;
			}
		}
		if (m_pString[i] != 32 && last <= i)
		{
			int len = i - last + 1;
			STokenSegment tok = {last, len};
			m_Token->AddItem(tok);
		}
	}

	void CToken::GetToken(int index, char * ref, int size)
	{
		char *buf = m_pString;
		if (m_Token->GetCount() > 0)
		{
			STokenSegment tok = m_Token->GetElement(index);
			if (size <= 0)
			{
				size = tok.iLength;
			}
			else
			{
				if (size > tok.iLength)
				{
					size = tok.iLength;
				}
			}

			memcpy(ref, buf + tok.iOffset, size);
			ref[size] = '\0';
		}
	}

	bool  CToken::IsTokenEqual(int index, const char *st)
	{
		char *buf = m_pString;
		if (m_Token->GetCount() > 0)
		{
			STokenSegment tok = m_Token->GetElement(index);
			if (strlen(st)==tok.iLength)
			{
				if (memcmp(st, buf + tok.iOffset, tok.iLength)==0)
				{
					return true;
				}
			}
		}
		return false;
	}

	void CToken::SetStringPointer(char* pointer)
	{
		m_Token->Clear();
		m_pString = pointer;
		this->ParseToken();
	}

	int CToken::GetTokenCount()
	{
		return m_Token->GetCount();
	}

	int CToken::GetTokenValueAsInt(int index)
	{
		char buf[1024];
		this->GetToken(index, buf);
		return atoi(buf);
	}
}