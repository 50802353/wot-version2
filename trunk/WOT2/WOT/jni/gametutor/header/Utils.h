#ifndef __UTILS_H__
#define __UTILS_H__

#include "Header.h"
#include "CDevice.h"
using namespace std;

namespace GameTutor
{
	template<class T>
	inline T Math_Abs(T a)
	{
		return (a<0?-a:a);
	}

	template<class T>
	void Math_GetLog2(T input, __UINT32 &val, __UINT32 &mod)
	{
		__UINT32 num = __UINT32(input);
		val = 0;
		mod = 0;
		if (num == 0)
		{
			return;
		}
		else if (num == 1)
		{
			val = 0;
			mod = 1;
			return;
		}
		else
		{
			__UINT32 tmp = num;
			while (tmp > 1)
			{
				val++;
				tmp>>=1;
			}
			mod = num - (1<<val);
		}
	}

	template<class T>
	inline T Math_Min(T a, T b)
	{
		return (a<b?a:b);
	}

	template<class T>
	inline T Math_Max(T a, T b)
	{
		return (a>b?a:b);
	}

	template<class T>
	inline bool Math_IsPO2(T a)
	{
		if (a < 0) return false;
		__INT32 num = __UINT32(a);
		return ((num&(-num))==num);
	}

	inline
	void Str_ToUpper(char *input, __INT32 size)
	{
		if (input)
		{
			for (int i = 0; i < size; i++)
			{
				if (input[i] >= 'a' && input[i] <= 'z')
				{
					input[i] += 'A' - 'a';
				}
			}
		}
	}

	inline
	void Str_ToLower(char *input, __INT32 size)
	{
		if (input)
		{
			for (int i = 0; i < size; i++)
			{
				if (input[i] >= 'A' && input[i] <= 'Z')
				{
					input[i] += 'a' - 'A';
				}
			}
		}
	}
	inline
	void decode(unsigned char x, int &row, int& column) {
		row = x/16;
		column = x%16;
	}
	inline
	float length(float x1, float y1, float x2, float y2) {
		float x = x2-x1;
		float y = y2-y1;
		return sqrt(x*x+y*y);
	}
}

#endif