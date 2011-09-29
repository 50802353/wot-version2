#ifndef __CGRAPHICS2D_H__
#define __CGRAPHICS2D_H__

#include "Header.h"
#include "CSingleton.h"
#include "SGraphics.h"
#include "IVideoDriver.h"
#include "CImage.h"
#include "Matrix.h"
#include "CCamera.h"

#define EG2D_PIPELINE_MAX_VERTEX_STACK		1000
#define EG2D_PIPELINE_MAX_ELEMENT_STACK		200
#define EG2D_LASTOBJ						-1


namespace GameTutor
{
	enum EG2DGLES2ElementType
	{
		EG2DP_ELETYPE_LINE,
		EG2DP_ELETYPE_TRIANGLE,
		EG2DP_ELETYPE_TRIANGLE_WIRE,
		EG2DP_ELETYPE_RECT,
		EG2DP_ELETYPE_RECT_WIRE,
		EG2DP_ELETYPE_IMG,
	};

	struct SGraphics2DGLES2VertexData
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
		void SetVideoDriver(IVideoDriver *vd);
		void Reset();
		void Clear(SColor<float>c);
		void Clear(SColor<__UINT8> c);
		void SetColor(SColor<float> c);
		void SetColor(SColor<__UINT8> c);
		void DrawRect(SRect<float> rect);
		void DrawRect(SRect<__INT32> rect);
		void DrawModel(int numTriangle, float* verticesAFrame, float* texCoordAFrame, GLuint textureID);

		void DrawMesh(int numTriangle,Matrix* MVPMatrix, float* verticesAFrame, float* texCoordAFrame, GLuint textureID);
		void DrawMeshTriangleStrip(int numIndices,Matrix* MMatrix, float* verticesAFrame, float* texCoordAFrame, __UINT32 *indices, GLuint textureID, SColor<float> color = SColor<float>(1.0f,1.0f,1.0f,1.0f));
		void DrawParticle(int numIndices,Matrix* MMatrix, float* verticesAFrame, float* texCoordAFrame, __UINT32 *indices, GLuint textureID, SColor<float> color = SColor<float>(1.0f,1.0f,1.0f,1.0f));


		void DrawMeshLine(int numIndices,Matrix* MMatrix, float* verticesAFrame, float* colorAFrame, __UINT32 *indices);


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
		void DrawImageRegion(SPosition2D<float> pos, CImage *img, SRect<float> region);
		void DrawImageRegion(SPosition2D<__INT32> pos, CImage *img, SRect<__INT32> region);
		void ObjectTranslate(__INT32 index, float x, float y, float z);
		void ObjectRotate(__INT32 index, float andlge, AXIS axis);
		void ObjectScale(__INT32 index, float x, float y, float z);
		void DrawLetter(CImage *texture, unsigned char x, SRect<float> rect);
		void DrawLetter(CImage *texture, unsigned char x, SRect<__INT32> rect);
		//void DrawString(CImage *texture, char* str, float size, float offsetX, float offsetY, int anchor);
		void DrawString(CImage *texture, char* str, float offsetX, float offsetY, int anchor, float size, float distance);
		void DrawString(CImage *texture, char* str, __INT32 offsetX, __INT32 offsetY, int anchor, float size, float distance);
		void DrawImageRegion(SRect<float> rect, CImage *img, SRect<float> region);
		void DrawImageRegion(SRect<__INT32> rect, CImage *img, SRect<__INT32> region);

		void ConvertPosition(SPosition2D<__INT32> pos,SPosition2D<float> &re);
		void ConvertPosition(SPosition2D<float> pos,SPosition2D<__INT32> &re);

		

		void Flush();

	protected:
		SColor<float> m_Color;
		int m_iNumberOfElement;
		int m_iStreamOffset;
		SGraphics2DGLES2VertexData m_pStream[EG2D_PIPELINE_MAX_VERTEX_STACK];


		GLfloat m_pVertexStream[EG2D_PIPELINE_MAX_VERTEX_STACK][2];
		GLfloat m_pColorStream[EG2D_PIPELINE_MAX_VERTEX_STACK][4];
		GLfloat m_pTexCoordStream[EG2D_PIPELINE_MAX_VERTEX_STACK][2];



		__UINT32 m_pTextureID[EG2D_PIPELINE_MAX_VERTEX_STACK];
		bool m_pIsUseAlpha[EG2D_PIPELINE_MAX_VERTEX_STACK];
		enum EG2DGLES2ElementType m_Type[EG2D_PIPELINE_MAX_VERTEX_STACK];

		Matrix m_fMatrixM[EG2D_PIPELINE_MAX_ELEMENT_STACK];
		Matrix m_fMatrixMVP;
		CCamera Camera2D;
		CCamera Camera3D;

	};
}
#endif