#ifndef __CGRAPHICS2D_H__
#define __CGRAPHICS2D_H__

#include "Header.h"
#include "CSingleton.h"
#include "SGraphics.h"
#include "IVideoDriver.h"
#include "CImage.h"

#define EG2D_PIPELINE_MAX_VERTEX_STACK		1000

namespace GameTutor
{
	enum EG2DGLPipelineElementType
	{
		EG2DP_ELETYPE_LINE,
		EG2DP_ELETYPE_TRIANGLE,
		EG2DP_ELETYPE_RECT,
		EG2DP_ELETYPE_IMG,
	};

	struct SGraphics2DGLPipelineVertexData
	{
		SPosition2D<float> Pos;
		SColor<float> Color;
		SPosition2D<float> TexCoor;
	};

	class CGraphics2D:public CSingleton<CGraphics2D>
	{
		friend class CSingleton<CGraphics2D>;
	protected:
		CGraphics2D();
		IVideoDriver *m_pVideoDriver;
	public:
		void Reset();
		void Clear(SColor<float>c);
		void Clear(SColor<__UINT8> c);
		void SetColor(SColor<float> c);
		void SetColor(SColor<__UINT8> c);
		void DrawRect(SRect<float> rect);
		void DrawRect(SRect<__INT32> rect);
		void DrawLine(SPosition2D<float> startpoint, SPosition2D<float> endpoint);
		void DrawLine(SPosition2D<__INT32> startpoint, SPosition2D<__INT32> endpoint);
		void DrawTriangle(SPosition2D<float> p1, SPosition2D<float>p2, SPosition2D<float>p3);
		void DrawTriangle(SPosition2D<__INT32> p1, SPosition2D<__INT32> p2, SPosition2D<__INT32> p3);
		void FillRect(SRect<float> rect);
		void FillRect(SRect<__INT32> rect);
		void FillTriangle(SPosition2D<float> p1, SPosition2D<float>p2, SPosition2D<float>p3) ;
		void FillTriangle(SPosition2D<__INT32> p1, SPosition2D<__INT32> p2, SPosition2D<__INT32> p3);
		void DrawImage(SPosition2D<float> pos, CImage *img);
		void DrawImage(SPosition2D<__INT32> pos, CImage *img);
		void CGraphics2D::DrawImageRegion(SPosition2D<float> pos, CImage *img, SRect<float> region);
		void CGraphics2D::DrawImageRegion(SRect<float> rect, CImage *img, SRect<float> region);
		void CGraphics2D::DrawImageRegion(SPosition2D<__INT32> pos, CImage *img, SRect<__INT32> region);
		void Flush();

	protected:
		SColor<float> m_Color;
		int m_iNumberOfElement;
		int m_iStreamOffset;
		SGraphics2DGLPipelineVertexData m_pStream[EG2D_PIPELINE_MAX_VERTEX_STACK];
		__UINT32 m_pTextureID[EG2D_PIPELINE_MAX_VERTEX_STACK];
		bool m_pIsUseAlpha[EG2D_PIPELINE_MAX_VERTEX_STACK];
		enum EG2DGLPipelineElementType m_Type[EG2D_PIPELINE_MAX_VERTEX_STACK];
	};
}
#endif