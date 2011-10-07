#include "CRandom.h"
#include "CDevice.h"

namespace GameTutor
{
	CRandom::CRandom()
	{
		SetSeed(CDevice::GetInstance()->GetTimer());
	}

	CRandom::CRandom(__UINT64 seed)
	{
		SetSeed(seed);
	}

	void CRandom::SetSeed(__UINT64 seed)
	{
		m_Val[0] = seed;
		for (m_iRandomIndex = 1; m_iRandomIndex < RND_C; m_iRandomIndex++)
		{
			m_Val[m_iRandomIndex] = (Mult(RND_B, m_Val[m_iRandomIndex - 1])) & RND_MAX_VAL_MASK;
		}
	}

	__UINT32 CRandom::NextInt(__UINT32 max)
	{
		m_iRandomIndex = (m_iRandomIndex + 1) % RND_C;
		int shift1 = (m_iRandomIndex + (RND_C - 1) - RND_B) % RND_C;
		int shift2 = (m_iRandomIndex + (RND_C - 1)) % RND_C;

		m_Val[m_iRandomIndex] = (m_Val[shift1] + m_Val[shift2]) & RND_MAX_VAL_MASK;
		__UINT64 rint = ((m_Val[m_iRandomIndex] >> RND_HALF_MAX_VAL_SHIFT)*max) >> RND_HALF_MAX_VAL_SHIFT;
		return __UINT32(rint);
	}

	__UINT32 CRandom::NextTrueFalse()
	{
		return  NextInt(100) > 50?1:0;
	}

	__UINT32 CRandom::NextTrue(__UINT32 percent)
	{
		return NextInt(100) < percent?1:0;
	}

	__UINT64 CRandom::Mult(__UINT64 a, __UINT64 b) // mul 2 number without overflow. Assume a, b are 30bits integers.
	{
		__UINT64 a1 = a>>RND_HALF_MAX_VAL_SHIFT;
		__UINT64 a0 = a&RND_HALF_MAX_VAL_MASK;
		__UINT64 b1 = b>>RND_HALF_MAX_VAL_SHIFT;
		__UINT64 b0 = b&RND_HALF_MAX_VAL_MASK;

		__UINT64 mul = (((((a0*b1) + (a1*b0)) & RND_HALF_MAX_VAL_MASK) << RND_HALF_MAX_VAL_SHIFT) + a0*b0) & RND_MAX_VAL_MASK;

		return mul;
	}
}
