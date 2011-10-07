#ifndef __CRANDOM_H__
#define __CRANDOM_H__

#include "Header.h"
#include "CDevice.h"

namespace GameTutor
{
// Additive congruential
// a[0] = seed
// a[i] = (b*a[i]) % m , i < c
// a[j] = (a[j-b] + a[j-c]) % m, j >= c
#define RND_MAX_VAL_SHIFT	30
#define RND_MAX_VAL_MASK	0x3fffffffl
#define RND_HALF_MAX_VAL_SHIFT	15
#define RND_HALF_MAX_VAL_MASK	0x7fffl
#define RND_C				55
#define RND_B				31
	class CRandom
	{
	public:
		CRandom();
		CRandom(__UINT64 seed);
		void SetSeed(__UINT64 seed);
		__UINT32 NextInt(__UINT32 max);
		__UINT32 NextTrueFalse();
		__UINT32 NextTrue(__UINT32 percent);
	private:
		__UINT64 m_Val[RND_C];
		__UINT32 m_iRandomIndex;
	private:
		__UINT64 Mult(__UINT64 a, __UINT64 b);
	};
}

#endif