#ifndef __CBUFFERREADERSTREAM_H__
#define __CBUFFERREADERSTREAM_H__

#include "Header.h"
#include "Stream.h"
#include "CList.h"
#include "CToken.h"

namespace GameTutor
{
	class CStringBufferStream
	{
	public:
		CStringBufferStream(IReadableStream *stream);
		virtual ~CStringBufferStream();
		char* GetLinePointer(int index);
		char* operator [] (int index); 
		__INT32 GetNumOfLine();
		CToken *GetLineToken(int index);
	protected:
		CList<char*>*m_listLines;
		CToken* m_pCachedToken;
	};
}

#endif