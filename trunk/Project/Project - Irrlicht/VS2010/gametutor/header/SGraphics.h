#ifndef __SGRAPHICS_H__
#define __SGRAPHICS_H__

#include "Header.h"

namespace GameTutor
{
	template <class T>
	struct SColor
	{
		SColor (T r=0, T g=0, T b=0, T a=0) 
		{
			Red = r; Green = g; Blue = b; Alpha = a;
		}
		T Red;
		T Green;
		T Blue;
		T Alpha;
	};

	template <class T>
	struct SRect
	{
		SRect(T x=0, T y=0, T w=0, T h=0) 
		{
			X = x; Y = y; W = w; H = h;
		}
		T X;
		T Y;
		T W;
		T H;
	};

	template <class T>
	struct SDimension2D
	{
		SDimension2D(T w = 0, T h = 0)
		{
			H = h;
			W = w;
		}
		T W;
		T H;
	};



	template <class T>
	struct SPosition2D
	{
		SPosition2D(T x=0, T y=0) {X = x; Y = y;}
		T X;
		T Y;
	};

	template <class T>
	struct SPosition3D
	{
		SPosition3D(T x=0, T y=0, T z=0) {X = x; Y = y; Z = z;}
		T X;
		T Y;
		T Z;
	};
}
#endif