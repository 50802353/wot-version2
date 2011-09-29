#include "CStringBufferStream.h"

namespace GameTutor
{
	CStringBufferStream::CStringBufferStream(IReadableStream *stream)
	{
		m_listLines = new CList<char*>();
		char* buf = new char[stream->GetLength()+1];
		stream->Read((__UINT8*)buf, 0, stream->GetLength());
		buf[stream->GetLength()] = '\0';

		//split buf in to lines
		int last = 0;
		int i;
		for (i = 0; i < strlen(buf); i++)
		{
			if (buf[i] == 13)
			{
				int len = i - last;
				char* st = new char[len + 1];
				memcpy(st, buf + last, len);
				st[len] = '\0';
				m_listLines->AddItem(st);

				if ((i < strlen(buf) - 1) && (buf[i+1] == 10)) //LF --> WINDOWS :CRLF
				{
					i++; //skip LF
				}
				last = i + 1;
			}
			else if (buf[i] == 10) //LF
			{
				int len = i - last;
				char* st = new char[len + 1];
				memcpy(st, buf + last, len);
				st[len] = '\0';
				last = i + 1;
				m_listLines->AddItem(st);
			}
		}
		if (last < i)
		{
			int len = i - last + 1;
			if (buf[i] == 10 || buf[i] == 13)
			{
				len --; //ignore last if is LF or CR
			}
			char* st = new char[len+1];
			memcpy(st, buf + last, len);
			st[len] = '\0';
			last = i + 1;
			m_listLines->AddItem(st);
		}

		SAFE_DEL(buf);

		m_pCachedToken = new CToken();
	}


	CStringBufferStream::~CStringBufferStream()
	{
		m_listLines->DeallocateElementPointer();
		SAFE_DEL(m_listLines);
		SAFE_DEL(m_pCachedToken);
	}

	char* CStringBufferStream::GetLinePointer(int index)
	{
		return m_listLines->GetElement(index);
	}

	char* CStringBufferStream::operator[] (int index)
	{
		return GetLinePointer(index);
	}

	__INT32 CStringBufferStream::GetNumOfLine()
	{
		return m_listLines->GetCount();
	}

	CToken *CStringBufferStream::GetLineToken(int index)
	{
		m_pCachedToken->SetStringPointer(m_listLines->GetElement(index));
		return m_pCachedToken;
	}
}

