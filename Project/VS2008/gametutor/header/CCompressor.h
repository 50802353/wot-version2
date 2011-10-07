#ifndef __CCOMPRESSOR_H__
#define __CCOMPRESSOR_H__
#include "Header.h"
namespace GameTutor
{
#define RLE_MAX_BLOCK_LEN 127
#define RLE_SIGN_MASK     0x80

	struct SCompressorData
	{
		SCompressorData()
		{
			m_pOriginalData = 0;
			m_pOriginalData = 0;
			m_isEmbedOriginalSizeInCompressedData = true;
			m_iCompressedDataSize = 0;
			m_iOriginalDataSize = 0;
		}
		__INT8* m_pOriginalData;
		__INT8* m_pCompressedData;
		__INT32 m_iCompressedDataSize;
		__INT32 m_iOriginalDataSize;
		bool m_isEmbedOriginalSizeInCompressedData;
	};
	class CCompressor
	{
	public:
		static void RLECompress(SCompressorData &data);
		static void RLEDecompress(SCompressorData &data);
	};
}

#endif