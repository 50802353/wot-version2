#ifndef __CTOKEN_H__
#define __CTOKEN_H__

#include "Header.h"
#include "CList.h"

#define IS_MATCH_TOKEN(ref) (((ref)==32) || ((ref)==9))

namespace GameTutor
{
	struct STokenSegment
	{
		int iOffset;
		int iLength;
	} ;

	class CToken
	{
	public:
		CToken(char* pointer);
		CToken();
		virtual ~CToken();
		void DeallocateStringPointer();			
		void GetToken(int index, char * ref, int size = -1);
		bool IsTokenEqual(int index, const char *st);
		void SetStringPointer(char* pointer);
		int GetTokenCount();
		int GetTokenValueAsInt(int index);
	private:
		CList<STokenSegment>* m_Token;
		char* m_pString;
		void ParseToken();
	};
}
#endif