#include "CGraphics2D.h"
#include "CGLPipelineDriver.h"
#include "CViewController.h"
#include "SGameConfig.h"

namespace GameTutor
{
	extern SGameConfig Configuation;
	CGraphics2D::CGraphics2D()
	{
		m_pVideoDriver = Configuation.pVideoDriver;
		m_iNumberOfElement = 0;
		m_iStreamOffset = 0;
		m_Color = SColor<float>(0.0, 0.0, 0.0, 1.0);
		isLastGraphic = true;
		memset( m_ProjectionMatrix, 0, sizeof(float)*16);
	}

	void CGraphics2D::Reset()
	{
		if (m_pVideoDriver->IsVideoDriver(EVIDEO_DRIVER_OGLPIPELINE))
		{
			CGLPipelineDriver* vd = (CGLPipelineDriver*)m_pVideoDriver;
			__UINT32 w = (CViewController::GetInstance()->GetView()->GetWidth());
			__UINT32 h = (CViewController::GetInstance()->GetView()->GetHeight());
			Clear(SColor<float>(0, 0, 0, 1));
			vd->LoadIdentity(EGLPD_MATRIXMODE_MODELVIEW);

			vd->LoadIdentity(EGLPD_MATRIXMODE_PROJECTION);
			vd->Viewport(SRect<__INT32>(0, 0, w, h));			
			vd->Ortho(0, float(w), 0, float(h) , 0, 1000 );
			vd->SaveMatrix(EGLPD_MATRIXMODE_PROJECTION, m_ProjectionMatrix);

			vd->EnableAttribPointer(EGLPD_ATTRIB_VERTEX, false);
			vd->EnableAttribPointer(EGLPD_ATTRIB_COLOR, false);
			vd->EnableAttribPointer(EGLPD_ATTRIB_NORMAL, false);
			vd->EnableAttribPointer(EGLPD_ATTRIB_TEXCOOR, false);

			vd->EnableBlending(false);
			vd->EnableTexture2D(false);

			
		}
	}

	void CGraphics2D::Clear(SColor<float>c)
	{
		if (m_pVideoDriver->IsVideoDriver(EVIDEO_DRIVER_OGLPIPELINE))
		{
			CGLPipelineDriver* vd = (CGLPipelineDriver*)m_pVideoDriver;
			m_iNumberOfElement = 0;
			m_iStreamOffset = 0;
			vd->Clear(c);
		}
	}

	void CGraphics2D::Clear(SColor<__UINT8> c)
	{
		if (m_pVideoDriver->IsVideoDriver(EVIDEO_DRIVER_OGLPIPELINE))
		{
			CGLPipelineDriver* vd = (CGLPipelineDriver*)m_pVideoDriver;
			vd->Clear(SColor<float>(c.Red/255.0f, c.Green/255.0f, c.Blue/255.0f, c.Alpha/255.0f));
		}
	}

	void CGraphics2D::SetColor(SColor<float> c) 
	{
		memcpy(&m_Color, &c, sizeof(m_Color));
	}

	void CGraphics2D::SetColor(SColor<__UINT8> c) 
	{
		m_Color.Alpha = c.Alpha/255.0f;
		m_Color.Blue = c.Blue/255.0f;
		m_Color.Green = c.Green/255.0f;
		m_Color.Red = c.Red/255.0f;
	}

	void CGraphics2D::DrawRect(SRect<float> rect) 
	{
		TODO("DrawRect is not implemented");
	}

	void CGraphics2D::DrawRect(SRect<__INT32> rect) 
	{
		TODO("DrawRect is not implemented");
	}

	void CGraphics2D::DrawLine(SPosition2D<float> startpoint, SPosition2D<float> endpoint) 
	{
		TODO("DrawLine is not implemented");
	}

	void CGraphics2D::DrawLine(SPosition2D<__INT32> startpoint, SPosition2D<__INT32> endpoint) 
	{
		TODO("DrawLine is not implemented");
	}

	void CGraphics2D::DrawTriangle(SPosition2D<float> p1, SPosition2D<float>p2, SPosition2D<float>p3) 
	{
		TODO("DrawTriangle is not implemented");
	}

	void CGraphics2D::DrawTriangle(SPosition2D<__INT32> p1, SPosition2D<__INT32> p2, SPosition2D<__INT32> p3) 
	{
		TODO("DrawTriangle is not implemented");
	}

	void CGraphics2D::FillRect(SRect<float> rect)
	{	
		m_Type[m_iNumberOfElement] = EG2DP_ELETYPE_RECT;
		m_pIsUseAlpha[m_iNumberOfElement] = (m_Color.Alpha != 1);
		SGraphics2DGLPipelineVertexData vertex[4]  = {	
			{SPosition2D<float>(rect.X, rect.Y + rect.H), m_Color, SPosition2D<float>(0, 0)},
			{SPosition2D<float>(rect.X, rect.Y), m_Color, SPosition2D<float>(0, 0)},
			{SPosition2D<float>(rect.X + rect.W, rect.Y + rect.H), m_Color, SPosition2D<float>(0, 0)},
			{SPosition2D<float>(rect.X + rect.W, rect.Y), m_Color, SPosition2D<float>(0, 0)}
		};

		memcpy(m_pStream + m_iStreamOffset, vertex, sizeof(SGraphics2DGLPipelineVertexData)*4);
		m_iNumberOfElement++;
		m_iStreamOffset += 4;
	}

	void CGraphics2D::FillRect(SRect<__INT32> rect)
	{
		SRect<float> rect2(float(rect.X), float(rect.Y), float(rect.W), float(rect.H));
		FillRect(rect2);
	}

	void CGraphics2D::FillTriangle(SPosition2D<float> p1, SPosition2D<float>p2, SPosition2D<float>p3) 
	{
		m_Type[m_iNumberOfElement] = EG2DP_ELETYPE_TRIANGLE;
		m_pIsUseAlpha[m_iNumberOfElement] = (m_Color.Alpha != 1);
		SGraphics2DGLPipelineVertexData vertex[3]  = {	
			{p1, m_Color, SPosition2D<float>(0, 0)},
			{p2, m_Color, SPosition2D<float>(0, 0)},
			{p3, m_Color, SPosition2D<float>(0, 0)}
		};

		memcpy(m_pStream + m_iStreamOffset, vertex, sizeof(SGraphics2DGLPipelineVertexData)*3);
		m_iNumberOfElement++;
		m_iStreamOffset += 3;
	}

	void CGraphics2D::FillTriangle(SPosition2D<__INT32> p1, SPosition2D<__INT32> p2, SPosition2D<__INT32> p3) 
	{
		FillTriangle(SPosition2D<float>(float(p1.X), float(p1.Y)), SPosition2D<float>(float(p2.X), float(p2.Y)), SPosition2D<float>(float(p3.X), float(p3.Y)));
	}

	void CGraphics2D::DrawImage(SPosition2D<float> pos, CImage *img)
	{
		if (img)
		{
			img->BindGPU();
			m_Type[m_iNumberOfElement] = EG2DP_ELETYPE_IMG;

			SRect<float> rect(pos.X, pos.Y, float(img->GetWidth()), float(img->GetHeight()));
			SGraphics2DGLPipelineVertexData vertex[4]  = {	
				{SPosition2D<float>(rect.X, rect.Y + rect.H), m_Color, SPosition2D<float>(0, 1)},
				{SPosition2D<float>(rect.X, rect.Y), m_Color, SPosition2D<float>(0, 0)},
				{SPosition2D<float>(rect.X + rect.W, rect.Y + rect.H), m_Color, SPosition2D<float>(1, 1)},
				{SPosition2D<float>(rect.X + rect.W, rect.Y), m_Color, SPosition2D<float>(1, 0)}
			};
			m_pTextureID[m_iNumberOfElement] = img->GetTextureID();
			m_pIsUseAlpha[m_iNumberOfElement] = (img->GetPixelFormat() == EIMAGE_FORMAT_R8G8B8A8);
			memcpy(m_pStream + m_iStreamOffset, vertex, sizeof(SGraphics2DGLPipelineVertexData)*4);
			m_iNumberOfElement++;
			m_iStreamOffset += 4;
		}
	}

	void CGraphics2D::DrawImage(SPosition2D<__INT32> pos, CImage *img)
	{
		SPosition2D<float> pos2(float(pos.X), float(pos.Y));
		DrawImage(pos2, img);
	}

	void CGraphics2D::DrawImageRegion(SPosition2D<float> pos, CImage *img, SRect<float> region)
	{
		if (img)
		{
			img->BindGPU();
			m_Type[m_iNumberOfElement] = EG2DP_ELETYPE_IMG;

			float imgW = float(img->GetWidth());
			float imgH = float(img->GetHeight());

			SRect<float> rect(pos.X, pos.Y, region.W, region.H);
			SGraphics2DGLPipelineVertexData vertex[4]  = {	
				{SPosition2D<float>(rect.X, rect.Y + rect.H), m_Color, SPosition2D<float>(region.X/imgW, (region.Y + region.H)/imgH)},
				{SPosition2D<float>(rect.X, rect.Y), m_Color, SPosition2D<float>(region.X/imgW, region.Y/imgH)},
				{SPosition2D<float>(rect.X + rect.W, rect.Y + rect.H), m_Color, SPosition2D<float>((region.X + region.W)/imgW, (region.Y + region.H)/imgH)},
				{SPosition2D<float>(rect.X + rect.W, rect.Y), m_Color, SPosition2D<float>((region.X + region.W)/imgW, region.Y/imgH)}
			};
			m_pTextureID[m_iNumberOfElement] = img->GetTextureID();
			m_pIsUseAlpha[m_iNumberOfElement] = (img->GetPixelFormat() == EIMAGE_FORMAT_R8G8B8A8);
			memcpy(m_pStream + m_iStreamOffset, vertex, sizeof(SGraphics2DGLPipelineVertexData)*4);
			m_iNumberOfElement++;
			m_iStreamOffset += 4;
		}
	}

	void CGraphics2D::DrawImageRegion(SRect<float> rect, CImage *img, SRect<float> region)
	{
		if (img)
		{
			img->BindGPU();
			m_Type[m_iNumberOfElement] = EG2DP_ELETYPE_IMG;

			float imgW = float(img->GetWidth());
			float imgH = float(img->GetHeight());

			SGraphics2DGLPipelineVertexData vertex[4]  = {	
				{SPosition2D<float>(rect.X, rect.Y + rect.H), m_Color, SPosition2D<float>(region.X/imgW, (region.Y + region.H)/imgH)},
				{SPosition2D<float>(rect.X, rect.Y), m_Color, SPosition2D<float>(region.X/imgW, region.Y/imgH)},
				{SPosition2D<float>(rect.X + rect.W, rect.Y + rect.H), m_Color, SPosition2D<float>((region.X + region.W)/imgW, (region.Y + region.H)/imgH)},
				{SPosition2D<float>(rect.X + rect.W, rect.Y), m_Color, SPosition2D<float>((region.X + region.W)/imgW, region.Y/imgH)}
			};
			m_pTextureID[m_iNumberOfElement] = img->GetTextureID();
			m_pIsUseAlpha[m_iNumberOfElement] = (img->GetPixelFormat() == EIMAGE_FORMAT_R8G8B8A8);
			memcpy(m_pStream + m_iStreamOffset, vertex, sizeof(SGraphics2DGLPipelineVertexData)*4);
			m_iNumberOfElement++;
			m_iStreamOffset += 4;
		}
	}

	void CGraphics2D::DrawImageRegion(SPosition2D<__INT32> pos, CImage *img, SRect<__INT32> region)
	{
		SPosition2D<float> pos2(float(pos.X), float(pos.Y));
		SRect<float> reg(float(region.X), float(region.Y), float(region.W), float(region.H));
		DrawImageRegion(pos2, img, reg);
	}

	void CGraphics2D::Flush() 
	{
		if (m_pVideoDriver->IsVideoDriver(EVIDEO_DRIVER_OGLPIPELINE))
		{
			CGLPipelineDriver* vd = (CGLPipelineDriver*)m_pVideoDriver;
			if (!isLastGraphic)
			{
				isLastGraphic = true;
				vd->LoadMatrix(EGLPD_MATRIXMODE_PROJECTION,m_ProjectionMatrix);
			}

			__UINT8 * bstream = (__UINT8 *)(m_pStream);
			__UINT32 stride = sizeof(SGraphics2DGLPipelineVertexData);
			BREAK_IF(m_iNumberOfElement >= EG2D_PIPELINE_MAX_VERTEX_STACK, "m_iNumberOfElement is out of range");

			int numVertex = 0;
			for (int i = 0; i < m_iNumberOfElement; i++)
			{
				switch (m_Type[i])
				{
				case EG2DP_ELETYPE_RECT:
				case EG2DP_ELETYPE_TRIANGLE:
					vd->EnableTexture2D(false);
					vd->EnableAttribPointer(EGLPD_ATTRIB_VERTEX, true);
					vd->EnableAttribPointer(EGLPD_ATTRIB_NORMAL, false);
					vd->EnableAttribPointer(EGLPD_ATTRIB_COLOR, true);
					vd->EnableAttribPointer(EGLPD_ATTRIB_TEXCOOR, false);
					numVertex = 4;
					if (m_Type[i] == EG2DP_ELETYPE_TRIANGLE)
					{
						numVertex = 3;
					}		
					vd->AttributePointer(
						EGLPD_ATTRIB_COLOR, 
						4, 
						EGLPD_PRIYTPE_FLOAT, 
						stride, 
						bstream + sizeof(SPosition2D<float>));
					break;
				case EG2DP_ELETYPE_IMG:
					vd->SetColor<float>(1, 1, 1, 1);
					vd->EnableTexture2D(true);
					vd->EnableAttribPointer(EGLPD_ATTRIB_VERTEX, true);
					vd->EnableAttribPointer(EGLPD_ATTRIB_NORMAL, false);
					vd->EnableAttribPointer(EGLPD_ATTRIB_COLOR, false);
					vd->EnableAttribPointer(EGLPD_ATTRIB_TEXCOOR, true);
					vd->BindTexture2D(m_pTextureID[i]);
					vd->AttributePointer(
						EGLPD_ATTRIB_TEXCOOR, 
						2, 
						EGLPD_PRIYTPE_FLOAT, 
						stride, 
						bstream + sizeof(SPosition2D<float>) + sizeof(SColor<float>));
					numVertex = 4;
					break;
				}
				if (numVertex)
				{
					vd->EnableBlending(m_pIsUseAlpha[i]);
					vd->AttributePointer(
						EGLPD_ATTRIB_VERTEX, 
						2, 
						EGLPD_PRIYTPE_FLOAT, 
						stride, 
						bstream);

					vd->DrawElements(EGLPD_RENDERMODE_TRIANGLESTRIP, numVertex);
					bstream += stride*numVertex;
				}
			}
			m_iNumberOfElement = 0;
			m_iStreamOffset = 0;
		}
	}
}