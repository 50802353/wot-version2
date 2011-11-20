#include "CCompressor.h"

namespace GameTutor
{
	void CCompressor::RLECompress(SCompressorData &data)
	{
		__INT8* source = data.m_pOriginalData;

		if (source == 0)
		{
			return;
		}
		int sourcelength = data.m_iOriginalDataSize;
		int* RLEPos = new int[sourcelength];
		int* RLELen = new int[sourcelength];
		int iSegIndex = 0;
		int iSegLen = 0;
		for (int i = 1; i < sourcelength; i++)
		{
			if (source[i] == source[i-1])
			{
				iSegLen++;
			}
			else
			{
				if (iSegLen > 0)
				{
					int repeat_pos = i - iSegLen - 1;
					int repeat_len = iSegLen + 1;

					if (iSegIndex == 0)
					{
						RLEPos[iSegIndex] = 0;
						RLELen[iSegIndex] = repeat_pos;    
					}
					else
					{
						RLEPos[iSegIndex] = RLEPos[iSegIndex - 1] + RLELen[iSegIndex - 1];
						RLELen[iSegIndex] = repeat_pos - RLEPos[iSegIndex];
					}
					iSegIndex++;

					RLEPos[iSegIndex] = repeat_pos;
					RLELen[iSegIndex] = repeat_len;
					iSegIndex++;
					iSegLen = 0;
				}
			}
		}
		RLEPos[iSegIndex] = RLEPos[iSegIndex - 1] + RLELen[iSegIndex - 1];
		RLELen[iSegIndex] = sourcelength - RLEPos[iSegIndex];
		iSegIndex++;

		int outlen = 0;
		for (int i = 0; i < iSegIndex; i++)
		{
			if (RLELen[i] == 0) continue;
			if (i%2 == 0) //count non-repeat
			{
				//len + k byte for signing k block, 1 block -> RLE_MAX_BLOCK_LEN bytes max
				outlen += RLELen[i] + ((RLELen[i]-1)/RLE_MAX_BLOCK_LEN) + 1;
			}
			else
			{
				outlen += ((RLELen[i]-1)/RLE_MAX_BLOCK_LEN + 1)<<1; //2 bytes signed for each block (RLE info: [n-repeat][value]
			}
		}

		data.m_iCompressedDataSize = outlen;
		if (data.m_isEmbedOriginalSizeInCompressedData)
		{
			outlen += 4;
		}
		data.m_pCompressedData = new __INT8[data.m_iCompressedDataSize];
		

		__INT8* des = data.m_pCompressedData;
		int index = 0;
		if (data.m_isEmbedOriginalSizeInCompressedData)
		{
			des[index++] = (__INT8)(sourcelength&0xFF);
			des[index++] = (__INT8)((sourcelength>>8)&0xFF);
			des[index++] = (__INT8)((sourcelength>>16)&0xFF);
			des[index++] = (__INT8)((sourcelength>>24)&0xFF);
		}

		for (int i = 0; i < iSegIndex; i++)
		{
			int n = RLELen[i];
			int size = n>RLE_MAX_BLOCK_LEN?RLE_MAX_BLOCK_LEN:n;
			if (size == 0) continue;

			if (i%2 == 0)// non-compressed data
			{
				while (n > 0)
				{
					size = n>RLE_MAX_BLOCK_LEN?RLE_MAX_BLOCK_LEN:n;
					des[index++] = (__INT8)(size);
					for (int j = RLEPos[i]; j < RLEPos[i] + size; j++)
					{
						des[index++] = source[j];
					}
					RLEPos[i] += size;
					n -= size;
				}
			}
			else //compressed data
			{
				while (n > 0)
				{
					size = n>RLE_MAX_BLOCK_LEN?RLE_MAX_BLOCK_LEN:n;
					des[index++] = (__INT8)(size | RLE_SIGN_MASK);
					des[index++] = source[RLEPos[i]];
					n -= size;
				}
			}

		}
		delete RLEPos;
		delete RLELen;
	}

	void CCompressor::RLEDecompress(SCompressorData &data)
	{
		__INT8* source = data.m_pCompressedData;
		int sourcelength = data.m_iCompressedDataSize;
		if (source == 0)
		{
			return;
		}
		int outsize = 10*1024*1024; //maximun 10MB
		if (data.m_isEmbedOriginalSizeInCompressedData)
		{
			outsize = (int)(source[0]&0xFF) | ((int)(source[1]&0xFF)<<8) | ((int)(source[2]&0xFF)<<16) | ((int)(source[3]&0xFF)<<24);
		}
		__INT8* des = new __INT8 [outsize];
		int n = sourcelength;
		int des_index = 0;
		int src_index = data.m_isEmbedOriginalSizeInCompressedData?4:0;
		while (src_index < n)
		{
			int nb = source[src_index++];
			if ((nb & RLE_SIGN_MASK) == 0) // non-compressed
			{
				for (int i = 0; i < nb; i++)
				{
					des[des_index ++] = source[src_index++];
				}
			}
			else //compressed
			{
				int nnb = (nb & RLE_MAX_BLOCK_LEN);
				for (int i = 0; i < nnb; i++)
				{
					des[des_index ++] = source[src_index];
				}
				src_index++;
			}
		}
		data.m_iOriginalDataSize = des_index;
		data.m_pOriginalData = new __INT8[des_index];
		memcpy(data.m_pOriginalData, des, des_index);
		delete des;
	}
}