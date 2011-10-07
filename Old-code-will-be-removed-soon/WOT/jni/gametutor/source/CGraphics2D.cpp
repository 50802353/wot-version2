#include "CGraphics2D.h"
//#include "CGLPipelineDriver.h"
#include "CGLES2Driver.h"
#include "CViewController.h"
#include "Utils.h"


namespace GameTutor
{
	CGraphics2D::CGraphics2D()
	{
		//m_pVideoDriver = CGLPipelineDriver::GetInstance();
		m_iNumberOfElement = 0;
		m_iStreamOffset = 0;
		m_Color = SColor<float>(0.0, 0.0, 0.0, 1.0);
	}
	void CGraphics2D::SetVideoDriver(IVideoDriver *vd)
	{
		m_pVideoDriver = vd;
		Reset();
	}
	void CGraphics2D::Reset()
	{
		if (m_pVideoDriver->IsVideoDriver(EVIDEO_DRIVER_OGLES2))
		{
			CGLES2Driver* vd = (CGLES2Driver*)m_pVideoDriver;
			__UINT32 w = (CViewController<VIEWCLASS>::GetInstance()->GetView()->GetWidth());
			__UINT32 h = (CViewController<VIEWCLASS>::GetInstance()->GetView()->GetHeight());
			Clear(SColor<float>(0, 0, 0, 1));
			vd->Viewport(SRect<__INT32>(0, 0, w, h));
			//vd->LoadIdentity(EGLES2_MATRIXMODE_PROJECTION);
			//vd->Ortho(0, float(w), 0, float(h) , 0, 1000 );
			CCamera2D::GetInstance()->CameraLoadIdentity();
			CCamera2D::GetInstance()->CameraOrtho(-float(1.0f/h*w),float(1.0f/h*w),1.0f,-1.0f,1.0f,2.0f);
			CCamera2D::GetInstance()->CameraTranslate(0,0,-1.5f);

			CCamera3D::GetInstance()->CameraLoadIdentity();
			CCamera3D::GetInstance()->CameraPerspective(45,800.0f/480.0f, 1.0f, 10000.0f);
			CCamera3D::GetInstance()->CameraLookat(0,0,10,0,0,0,0,1,0);
			

			vd->EnableAttribPointer(EGLES2_ATTRIB_VERTEX, false);
			vd->EnableAttribPointer(EGLES2_ATTRIB_COLOR, false);
			vd->EnableAttribPointer(EGLES2_ATTRIB_NORMAL, false);
			vd->EnableAttribPointer(EGLES2_ATTRIB_TEXCOOR, false);
		}
	}

	void CGraphics2D::Clear(SColor<float>c)
	{
		if (m_pVideoDriver->IsVideoDriver(EVIDEO_DRIVER_OGLES2))
		{
			CGLES2Driver* vd = (CGLES2Driver*)m_pVideoDriver;
			m_iNumberOfElement = 0;
			m_iStreamOffset = 0;
			vd->Clear(c.Red,c.Green,c.Blue,c.Alpha);
		}
	}

	void CGraphics2D::Clear(SColor<__UINT8> c)
	{
		Clear(SColor<float>(((float)c.Red)/255,((float)c.Red)/255,((float)c.Red)/255,((float)c.Red)/255));
	}

	void CGraphics2D::SetColor(SColor<float> c) 
	{
		memcpy(&m_Color, &c, sizeof(m_Color));
	}

	void CGraphics2D::ConvertPosition(SPosition2D<__INT32> pos,SPosition2D<float> &re)
	{
		__UINT32 w = (CViewController<VIEWCLASS>::GetInstance()->GetView()->GetWidth());
		__UINT32 h = (CViewController<VIEWCLASS>::GetInstance()->GetView()->GetHeight());
		re.X = (float(pos.X)*2-w)/h;
		re.Y = (float(pos.Y)*2-h)/h;
	}
	void CGraphics2D::ConvertPosition(SPosition2D<float> pos,SPosition2D<__INT32> &re)
	{
		__UINT32 w = (CViewController<VIEWCLASS>::GetInstance()->GetView()->GetWidth());
		__UINT32 h = (CViewController<VIEWCLASS>::GetInstance()->GetView()->GetHeight());
		re.X = (__INT32(pos.X)*h+w)/2;
		re.Y = (__INT32(pos.Y)*h+h)/2;
	}

	float MapDistance(int dis)
	{
		__UINT32 h = (CViewController<VIEWCLASS>::GetInstance()->GetView()->GetHeight());
		return (float)dis/h*2.0f;
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
		m_Type[m_iNumberOfElement] = EG2DP_ELETYPE_RECT_WIRE;
		m_pIsUseAlpha[m_iNumberOfElement] = (m_Color.Alpha != 1);
		SGraphics2DGLES2VertexData vertex[4]  = {	
			{SPosition2D<float>(rect.X, rect.Y + rect.H), m_Color, SPosition2D<float>(0, 0)},
			{SPosition2D<float>(rect.X, rect.Y), m_Color, SPosition2D<float>(0, 0)},
			{SPosition2D<float>(rect.X + rect.W, rect.Y), m_Color, SPosition2D<float>(0, 0)},
			{SPosition2D<float>(rect.X + rect.W, rect.Y + rect.H), m_Color, SPosition2D<float>(0, 0)}
		};
		memcpy(m_pStream + m_iStreamOffset, vertex, sizeof(SGraphics2DGLES2VertexData)*4);
		m_fMatrixM[m_iNumberOfElement].LoadIdentity();
		m_iNumberOfElement++;
		m_iStreamOffset += 4;
	}



	void CGraphics2D::DrawRect(SRect<__INT32> rect) 
	{
		SPosition2D<__INT32> winpos(rect.X,rect.Y);
		SPosition2D<float> glpos;
		ConvertPosition(winpos,glpos);
		float X = glpos.X;
		float Y = glpos.Y;
		float W = MapDistance(rect.W);
		float H = MapDistance(rect.H);
		DrawRect(SRect<float>(X,Y,W,H));
	}

	void CGraphics2D::DrawLine(SPosition2D<float> startpoint, SPosition2D<float> endpoint) 
	{
		m_Type[m_iNumberOfElement] = EG2DP_ELETYPE_LINE;
		m_pIsUseAlpha[m_iNumberOfElement] = (m_Color.Alpha != 1);
		SGraphics2DGLES2VertexData vertex[2]  = {	
			{SPosition2D<float>(startpoint.X, startpoint.Y), m_Color, SPosition2D<float>(0, 0)},
			{SPosition2D<float>(endpoint.X, endpoint.Y), m_Color, SPosition2D<float>(0, 0)},
		};
		memcpy(m_pStream + m_iStreamOffset, vertex, sizeof(SGraphics2DGLES2VertexData)*2);
		m_fMatrixM[m_iNumberOfElement].LoadIdentity();
		m_iNumberOfElement++;
		m_iStreamOffset += 2;
	}

	void CGraphics2D::DrawLine(SPosition2D<__INT32> startpoint, SPosition2D<__INT32> endpoint) 
	{
		SPosition2D<float> spos;
		SPosition2D<float> epos;
		ConvertPosition(startpoint,spos);
		ConvertPosition(endpoint,epos);
		DrawLine(spos,epos);
	}

	void CGraphics2D::DrawTriangle(SPosition2D<float> p1, SPosition2D<float>p2, SPosition2D<float>p3) 
	{
		m_Type[m_iNumberOfElement] = EG2DP_ELETYPE_TRIANGLE_WIRE;
		m_pIsUseAlpha[m_iNumberOfElement] = (m_Color.Alpha != 1);
		SGraphics2DGLES2VertexData vertex[3]  = {	
			{SPosition2D<float>(p1.X, p1.Y), m_Color, SPosition2D<float>(0, 0)},
			{SPosition2D<float>(p2.X, p2.Y), m_Color, SPosition2D<float>(0, 0)},
			{SPosition2D<float>(p3.X, p3.Y), m_Color, SPosition2D<float>(0, 0)}
		};
		memcpy(m_pStream + m_iStreamOffset, vertex, sizeof(SGraphics2DGLES2VertexData)*3);
		m_fMatrixM[m_iNumberOfElement].LoadIdentity();
		m_iNumberOfElement++;
		m_iStreamOffset += 3;
	}

	void CGraphics2D::DrawTriangle(SPosition2D<__INT32> p1, SPosition2D<__INT32> p2, SPosition2D<__INT32> p3) 
	{
		SPosition2D<float> p1_;
		SPosition2D<float> p2_;
		SPosition2D<float> p3_;
		ConvertPosition(p1,p1_);
		ConvertPosition(p2,p2_);
		ConvertPosition(p3,p3_);
		DrawTriangle(p1_,p2_,p3_);
	}
	
	void CGraphics2D::FillRect(SRect<float> rect)
	{	
		m_Type[m_iNumberOfElement] = EG2DP_ELETYPE_RECT;
		m_pIsUseAlpha[m_iNumberOfElement] = (m_Color.Alpha != 1);
		SGraphics2DGLES2VertexData vertex[4]  = {	
			{SPosition2D<float>(rect.X, rect.Y + rect.H), m_Color, SPosition2D<float>(0, 0)},
			{SPosition2D<float>(rect.X, rect.Y), m_Color, SPosition2D<float>(0, 0)},
			{SPosition2D<float>(rect.X + rect.W, rect.Y + rect.H), m_Color, SPosition2D<float>(0, 0)},
			{SPosition2D<float>(rect.X + rect.W, rect.Y), m_Color, SPosition2D<float>(0, 0)}
		};

		memcpy(m_pStream + m_iStreamOffset, vertex, sizeof(SGraphics2DGLES2VertexData)*4);
		m_fMatrixM[m_iNumberOfElement].LoadIdentity();
		m_iNumberOfElement++;
		m_iStreamOffset += 4;
	}

	void CGraphics2D::FillRect(SRect<__INT32> rect)
	{
		SPosition2D<__INT32> winpos(rect.X,rect.Y);
		SPosition2D<float> glpos;
		ConvertPosition(winpos,glpos);
		float X = glpos.X;
		float Y = glpos.Y;
		float W = MapDistance(rect.W);
		float H = MapDistance(rect.H);
		FillRect(SRect<float>(X,Y,W,H));
	}

	void CGraphics2D::FillTriangle(SPosition2D<float> p1, SPosition2D<float>p2, SPosition2D<float>p3) 
	{
		m_Type[m_iNumberOfElement] = EG2DP_ELETYPE_TRIANGLE;
		m_pIsUseAlpha[m_iNumberOfElement] = (m_Color.Alpha != 1);
		SGraphics2DGLES2VertexData vertex[3]  = {	
			{p1, m_Color, SPosition2D<float>(0, 0)},
			{p2, m_Color, SPosition2D<float>(0, 0)},
			{p3, m_Color, SPosition2D<float>(0, 0)}
		};
		memcpy(m_pStream + m_iStreamOffset, vertex, sizeof(SGraphics2DGLES2VertexData)*3);
		m_fMatrixM[m_iNumberOfElement].LoadIdentity();
		m_iNumberOfElement++;
		m_iStreamOffset += 3;
	}

	void CGraphics2D::FillTriangle(SPosition2D<__INT32> p1, SPosition2D<__INT32> p2, SPosition2D<__INT32> p3) 
	{
		SPosition2D<float> p1_;
		SPosition2D<float> p2_;
		SPosition2D<float> p3_;
		ConvertPosition(p1,p1_);
		ConvertPosition(p2,p2_);
		ConvertPosition(p3,p3_);
		FillTriangle(p1_,p2_,p3_);
	}

	void CGraphics2D::DrawImage(SPosition2D<float> pos, CImage *img)
	{
		if (img)
		{
			img->BindGPU(this->m_pVideoDriver);
			m_Type[m_iNumberOfElement] = EG2DP_ELETYPE_IMG;
			
			SRect<float> rect(pos.X, pos.Y, MapDistance(img->GetWidth()), MapDistance(img->GetHeight()));
			SGraphics2DGLES2VertexData vertex[4]  = {	
				{SPosition2D<float>(rect.X, rect.Y + rect.H), m_Color, SPosition2D<float>(0, 1)},
				{SPosition2D<float>(rect.X, rect.Y), m_Color, SPosition2D<float>(0, 0)},
				{SPosition2D<float>(rect.X + rect.W, rect.Y + rect.H), m_Color, SPosition2D<float>(1, 1)},
				{SPosition2D<float>(rect.X + rect.W, rect.Y), m_Color, SPosition2D<float>(1, 0)}
			};
			m_pTextureID[m_iNumberOfElement] = img->GetTextureID();
			m_pIsUseAlpha[m_iNumberOfElement] = (img->GetPixelFormat() == EIMAGE_FORMAT_R8G8B8A8);
			memcpy(m_pStream + m_iStreamOffset, vertex, sizeof(SGraphics2DGLES2VertexData)*4);
			m_fMatrixM[m_iNumberOfElement].LoadIdentity();
			m_iNumberOfElement++;
			m_iStreamOffset += 4;
		}
	}

	void CGraphics2D::DrawImage(SPosition2D<__INT32> pos, CImage *img)
	{
		SPosition2D<float> pos2;
		ConvertPosition(pos,pos2);
		DrawImage(pos2, img);
	}

	void CGraphics2D::DrawImageRegion(SPosition2D<float> pos, CImage *img, SRect<float> region)
	{
		if (img)
		{
			__UINT32 w = (CViewController<VIEWCLASS>::GetInstance()->GetView()->GetWidth());
			__UINT32 h = (CViewController<VIEWCLASS>::GetInstance()->GetView()->GetHeight());
			img->BindGPU(this->m_pVideoDriver);
			m_Type[m_iNumberOfElement] = EG2DP_ELETYPE_IMG;

			float imgW = float(img->GetWidth());
			float imgH = float(img->GetHeight());

			SRect<float> rect(pos.X, pos.Y, MapDistance(region.W), MapDistance(region.H));
			SGraphics2DGLES2VertexData vertex[4]  = {	
				{SPosition2D<float>(rect.X, rect.Y + rect.H), m_Color, SPosition2D<float>(region.X/imgW, (region.Y + region.H)/imgH)},
				{SPosition2D<float>(rect.X, rect.Y), m_Color, SPosition2D<float>(region.X/imgW, region.Y/imgH)},
				{SPosition2D<float>(rect.X + rect.W, rect.Y + rect.H), m_Color, SPosition2D<float>((region.X + region.W)/imgW, (region.Y + region.H)/imgH)},
				{SPosition2D<float>(rect.X + rect.W, rect.Y), m_Color, SPosition2D<float>((region.X + region.W)/imgW, region.Y/imgH)}
			};
			m_pTextureID[m_iNumberOfElement] = img->GetTextureID();
			m_pIsUseAlpha[m_iNumberOfElement] = (img->GetPixelFormat() == EIMAGE_FORMAT_R8G8B8A8);
			memcpy(m_pStream + m_iStreamOffset, vertex, sizeof(SGraphics2DGLES2VertexData)*4);
			m_fMatrixM[m_iNumberOfElement].LoadIdentity();
			m_iNumberOfElement++;
			m_iStreamOffset += 4;
		}
	}

	void CGraphics2D::DrawImageRegion(SPosition2D<__INT32> pos, CImage *img, SRect<__INT32> region)
	{
		SPosition2D<float> pos2;
		ConvertPosition(pos,pos2);
		SRect<float> region_(float(region.X)/img->GetWidth(),float(region.Y)/img->GetHeight(),float(region.W)/img->GetWidth(),float(region.H)/img->GetHeight());
		DrawImageRegion(pos2, img, region_);
	}

	void CGraphics2D::DrawImageRegion(SRect<float> rect, CImage *img, SRect<float> region)
	{
		if (img)
		{
			__UINT32 w = (CViewController<VIEWCLASS>::GetInstance()->GetView()->GetWidth());
			__UINT32 h = (CViewController<VIEWCLASS>::GetInstance()->GetView()->GetHeight());
			img->BindGPU(this->m_pVideoDriver);
			m_Type[m_iNumberOfElement] = EG2DP_ELETYPE_IMG;

			float imgW = float(img->GetWidth());
			float imgH = float(img->GetHeight());

			SGraphics2DGLES2VertexData vertex[4]  = {	
				{SPosition2D<float>(rect.X, rect.Y + rect.H), m_Color, SPosition2D<float>(region.X, (region.Y + region.H))},
				{SPosition2D<float>(rect.X, rect.Y), m_Color, SPosition2D<float>(region.X, region.Y)},
				{SPosition2D<float>(rect.X + rect.W, rect.Y + rect.H), m_Color, SPosition2D<float>((region.X + region.W), (region.Y + region.H))},
				{SPosition2D<float>(rect.X + rect.W, rect.Y), m_Color, SPosition2D<float>((region.X + region.W), region.Y)}
			};
			m_pTextureID[m_iNumberOfElement] = img->GetTextureID();
			m_pIsUseAlpha[m_iNumberOfElement] = (img->GetPixelFormat() == EIMAGE_FORMAT_R8G8B8A8);
			memcpy(m_pStream + m_iStreamOffset, vertex, sizeof(SGraphics2DGLES2VertexData)*4);
			m_fMatrixM[m_iNumberOfElement].LoadIdentity();
			m_iNumberOfElement++;
			m_iStreamOffset += 4;
		}
	}

	void CGraphics2D::DrawImageRegion(SRect<__INT32> rect, CImage *img, SRect<__INT32> region)
	{
		__UINT32 w = (CViewController<VIEWCLASS>::GetInstance()->GetView()->GetWidth());
		__UINT32 h = (CViewController<VIEWCLASS>::GetInstance()->GetView()->GetHeight());
		SPosition2D<float> pos;
		ConvertPosition(SPosition2D<__INT32>(rect.X,rect.Y),pos);
		SRect<float> rect_(pos.X,pos.Y,MapDistance(rect.W),MapDistance(rect.H));
		SRect<float> region_(float(region.X)/img->GetWidth(),float(region.Y)/img->GetHeight(),float(region.W)/img->GetWidth(),float(region.H)/img->GetHeight());
		DrawImageRegion(rect_, img, region_);
	}

	void CGraphics2D::DrawLetter(CImage *texture, unsigned char x, SRect<float> rect)
	{		
		int r,c;
		decode(x,r,c);
		r++;
		float top = (float)r/16;
		float bottom = (float)(r+1)/16;
		float delta=0.15f;
		float left = (float)(c+delta)/16;
		float right = (float)(c+1-delta)/16;

		//SRect<float> region(left,top,right-left,bottom-top);
		//SRect<float> region(0,0,0.5,0.5);
		SRect<float> region(left,1-top,right-left,bottom-top);
		//SRect<float> region(left,bottom,right-left,top-bottom);
		DrawImageRegion(rect, texture, region);
	}

	void CGraphics2D::DrawString(CImage *texture, char* str, float offsetX, float offsetY, int anchor = (h_center | v_center), float size=0.05f, float distance=1.0f ) {
		if (!str) return;
		int n = strlen(str);
		int i;
		float height = 1.0f;

		if ((anchor & v_top) == v_top)
			offsetY -= size;
		if ((anchor & v_bottom) == v_bottom)
			offsetY += size;

		if ((anchor & h_right) == h_right)
			offsetX -= size*(n-1)*2.0f;

		if ((anchor & h_center) == h_center)
			offsetX -= size*(n-1);

		for (i=0;i<n;i++){
			/*GLfloat vVertices[] = {  -size+i*size*2 + offsetX,  size*height + offsetY,	//left top
			-size+i*size*2 + offsetX, -size*height + offsetY,	// left bottom
			size+i*size*2 + offsetX, size*height + offsetY,		// right top
			size+i*size*2 + offsetX, -size*height + offsetY};	//right bottom*/
			float	left	= -	size+i*size*distance	+ offsetX,
				right	=	size+i*size*distance	+ offsetX,
				bottom	= -	size*height		+ offsetY,
				top		=	size*height		+ offsetY;

			SRect<float> sVertices(left,bottom,right-left,top-bottom);
			DrawLetter(texture,str[i], sVertices);
		}
	}

	void CGraphics2D::DrawString(CImage *texture, char* str, __INT32 offsetX, __INT32 offsetY, int anchor = (h_center | v_center), float size=0.05f, float distance=1.0f ) {
		SPosition2D<float> result;
		ConvertPosition(SPosition2D<__INT32>(offsetX,offsetY),result);
		DrawString(texture, str, result.X, result.Y, anchor, size, distance);
	}

	

	/*void CGraphics2D::DrawImageRegion(SPosition2D<__INT32> pos, CImage *img, SRect<__INT32> region)
	{
	__UINT32 w = (CViewController<VIEWCLASS>::GetInstance()->GetView()->GetWidth());
	__UINT32 h = (CViewController<VIEWCLASS>::GetInstance()->GetView()->GetHeight());
	SPosition2D<float> pos2(ConvertPosition(pos.X,w), ConvertPosition(pos.Y,h));
	SRect<float> reg(float(region.X), float(region.Y), float(region.W), float(region.H));
	DrawImageRegion(pos2, img, reg);
	}*/

	void CGraphics2D::DrawModel(int numTriangle, float* verticesAFrame, float* texCoordAFrame, GLuint textureID)
	{
		Matrix MVP;

		CGLES2Driver* vd = (CGLES2Driver*)m_pVideoDriver;
		vd->UseProgram(EGLES2_PROGRAM_TEXTURE2D);
		vd->UniformColor(SColor<float>(1.0,1.0,1.0,1.0));
		vd->EnableTexture2D(true);
		vd->EnableBlending(true);
		vd->EnableDepthTest(true);
		vd->BlendMode(0);
		vd->EnableAttribPointer(EGLES2_ATTRIB_VERTEX, true);
		vd->EnableAttribPointer(EGLES2_ATTRIB_NORMAL, false);
		vd->EnableAttribPointer(EGLES2_ATTRIB_COLOR, false);
		vd->EnableAttribPointer(EGLES2_ATTRIB_TEXCOOR, true);
		vd->BindTexture2D(textureID);
		vd->UniformMatrix(MVP);
		vd->VertexAttributePointer(EGLES2_ATTRIB_TEXCOOR, 3, EGLES2_PRITYPE_FLOAT, GL_FALSE, 0, texCoordAFrame);
		vd->VertexAttributePointer(EGLES2_ATTRIB_VERTEX, 3, EGLES2_PRITYPE_FLOAT, GL_FALSE, 0, verticesAFrame);
		vd->DrawArrays(EGLES2_RENDERMODE_TRIANGLE, 0 , numTriangle*3);

	}

	void CGraphics2D::DrawMesh(int numTriangle,Matrix* MMatrix, float* verticesAFrame, float* texCoordAFrame, GLuint textureID)
	{
		Matrix MVP;
		MVP.Multiply(*(CCamera3D::GetInstance()->GetProjectMatrix()));
		MVP.Multiply(*(CCamera3D::GetInstance()->GetViewMatrix()));
		MVP.Multiply(*MMatrix);
		

		CGLES2Driver* vd = (CGLES2Driver*)m_pVideoDriver;
		vd->UseProgram(EGLES2_PROGRAM_TEXTURE2D);
		
		SetColor(SColor<float>(1.0f,0.0f,1.0f,1.0f));
		vd->EnableTexture2D(true);
		vd->EnableBlending(true);
		vd->EnableDepthTest(true);
		vd->BlendMode(0);
		vd->EnableAttribPointer(EGLES2_ATTRIB_VERTEX, true);
		vd->EnableAttribPointer(EGLES2_ATTRIB_NORMAL, false);
		vd->EnableAttribPointer(EGLES2_ATTRIB_COLOR, false);
		vd->EnableAttribPointer(EGLES2_ATTRIB_TEXCOOR, true);
		vd->BindTexture2D(textureID);

		vd->UniformMatrix(MVP);
		vd->UniformColor(SColor<float>(1.0,1.0,1.0,1.0));
		vd->VertexAttributePointer(EGLES2_ATTRIB_TEXCOOR, 3, EGLES2_PRITYPE_FLOAT, GL_FALSE, 0, texCoordAFrame);
		vd->VertexAttributePointer(EGLES2_ATTRIB_VERTEX, 3, EGLES2_PRITYPE_FLOAT, GL_FALSE, 0, verticesAFrame);
		vd->DrawArrays(EGLES2_RENDERMODE_TRIANGLE, 0 , numTriangle*3);
	}	

	void CGraphics2D::DrawMeshTriangleStrip(int numIndices,Matrix* MMatrix, float* verticesAFrame, float* texCoordAFrame, __UINT32 *indices, GLuint textureID, SColor<float> color)
	{
		Matrix MVP;
		MVP.Multiply(*(CCamera3D::GetInstance()->GetProjectMatrix()));
		MVP.Multiply(*(CCamera3D::GetInstance()->GetViewMatrix()));
		MVP.Multiply(*MMatrix);
		

		CGLES2Driver* vd = (CGLES2Driver*)m_pVideoDriver;
		vd->UseProgram(EGLES2_PROGRAM_TEXTURE2D);
		vd->EnableDepthTest(true);
		SetColor(SColor<float>(1.0f,0.0f,1.0f,1.0f));
		vd->EnableTexture2D(true);
		vd->EnableBlending(true);

		vd->BlendMode(0);
		vd->EnableAttribPointer(EGLES2_ATTRIB_VERTEX, true);
		vd->EnableAttribPointer(EGLES2_ATTRIB_NORMAL, false);
		vd->EnableAttribPointer(EGLES2_ATTRIB_COLOR, false);
		vd->EnableAttribPointer(EGLES2_ATTRIB_TEXCOOR, true);
		vd->BindTexture2D(textureID);

		vd->UniformMatrix(MVP);
		vd->UniformColor(color);
		vd->VertexAttributePointer(EGLES2_ATTRIB_TEXCOOR, 3, EGLES2_PRITYPE_FLOAT, GL_FALSE, 0, texCoordAFrame);
		vd->VertexAttributePointer(EGLES2_ATTRIB_VERTEX, 3, EGLES2_PRITYPE_FLOAT, GL_FALSE, 0, verticesAFrame);
		vd->DrawElements(EGLES2_RENDERMODE_TRIANGLESTRIP, numIndices, indices);


		//vd->DrawArrays(EGLES2_RENDERMODE_TRIANGLE, 0 , 3);
	}	

	void CGraphics2D::DrawParticle(int numIndices,Matrix* MMatrix, float* verticesAFrame, float* texCoordAFrame, __UINT32 *indices, GLuint textureID, SColor<float> color)
	{
		CGLES2Driver* vd = (CGLES2Driver*)m_pVideoDriver;
		vd->EnableDepthWrite(false);
		vd->EnableBlending(true);
		vd->BlendMode(1);

		DrawMeshTriangleStrip(numIndices,MMatrix,verticesAFrame,texCoordAFrame,indices,textureID,color);
		vd->EnableDepthWrite(true);
	}


	void CGraphics2D::DrawMeshLine(int numIndices,Matrix* MMatrix, float* verticesAFrame, float* colorAFrame, __UINT32 *indices)
	{
		Matrix MVP;
		MVP.Multiply(*(CCamera3D::GetInstance()->GetProjectMatrix()));
		MVP.Multiply(*(CCamera3D::GetInstance()->GetViewMatrix()));
		MVP.Multiply(*MMatrix);
		

		CGLES2Driver* vd = (CGLES2Driver*)m_pVideoDriver;
		vd->UseProgram(EGLES2_PROGRAM_COLOR);

		vd->EnableTexture2D(false);
		vd->EnableDepthTest(false);
		vd->BlendMode(0);
		vd->EnableBlending(true);
		vd->EnableAttribPointer(EGLES2_ATTRIB_VERTEX, true);
		vd->EnableAttribPointer(EGLES2_ATTRIB_NORMAL, false);
		vd->EnableAttribPointer(EGLES2_ATTRIB_COLOR, true);
		vd->EnableAttribPointer(EGLES2_ATTRIB_TEXCOOR, false);
		

		vd->UniformMatrix(MVP);
		vd->VertexAttributePointer(EGLES2_ATTRIB_COLOR, 3, EGLES2_PRITYPE_FLOAT, GL_FALSE, 0, colorAFrame);
		vd->VertexAttributePointer(EGLES2_ATTRIB_VERTEX, 3, EGLES2_PRITYPE_FLOAT, GL_FALSE, 0, verticesAFrame);
		vd->DrawElements(EGLES2_RENDERMODE_LINE, numIndices, indices);


		//vd->DrawArrays(EGLES2_RENDERMODE_TRIANGLE, 0 , 3);
	}	


	void CGraphics2D::ObjectTranslate(__INT32 index, float x, float y, float z)
	{
		if (index== EG2D_LASTOBJ)
		{
			index  = m_iNumberOfElement;
		}
		m_fMatrixM[index].Translate(x,y,z);
	}

	void CGraphics2D::ObjectRotate(__INT32 index, float angle, AXIS axis)
	{
		if (index== EG2D_LASTOBJ)
		{
			index  = m_iNumberOfElement-1;
		}
		m_fMatrixM[index].Rotate(angle,axis);
	}

	void CGraphics2D::ObjectScale(__INT32 index, float x, float y, float z)
	{
		if (index== EG2D_LASTOBJ)
		{
			index  = m_iNumberOfElement-1;
		}
		m_fMatrixM[index].Scale(x,y,z);
	}

	void CGraphics2D::Flush() 
	{
		__UINT32 w = (CViewController<VIEWCLASS>::GetInstance()->GetView()->GetWidth());
		__UINT32 h = (CViewController<VIEWCLASS>::GetInstance()->GetView()->GetHeight());

		CGLES2Driver* vd = (CGLES2Driver*)m_pVideoDriver;
		vd->EnableDepthTest(false);
		__UINT8 * bstream = (__UINT8 *)(m_pStream);
		__UINT32 stride = sizeof(SGraphics2DGLES2VertexData);
		BREAK_IF(m_iNumberOfElement >= EG2D_PIPELINE_MAX_VERTEX_STACK, "m_iNumberOfElement is out of range");

		int curVertex = 0;
		int numVertex = 0;


		for (int i = 0; i < m_iNumberOfElement; i++)
		{
			switch (m_Type[i])
			{
			case EG2DP_ELETYPE_RECT:case EG2DP_ELETYPE_RECT_WIRE:case EG2DP_ELETYPE_TRIANGLE:case EG2DP_ELETYPE_TRIANGLE_WIRE:case EG2DP_ELETYPE_LINE:
				vd->UseProgram(EGLES2_PROGRAM_COLOR);
				switch(m_Type[i])
				{
					case EG2DP_ELETYPE_RECT:
					case EG2DP_ELETYPE_RECT_WIRE:
						numVertex = 4;
						break;
					case EG2DP_ELETYPE_TRIANGLE:
					case EG2DP_ELETYPE_TRIANGLE_WIRE:
						numVertex = 3;
						break;
					case EG2DP_ELETYPE_LINE:
						numVertex =  2;
						break;
					default:
						break;













				}
				vd->EnableTexture2D(false);
				vd->EnableAttribPointer(EGLES2_ATTRIB_VERTEX, true);
				vd->EnableAttribPointer(EGLES2_ATTRIB_NORMAL, false);
				vd->EnableAttribPointer(EGLES2_ATTRIB_COLOR, true);
				vd->EnableAttribPointer(EGLES2_ATTRIB_TEXCOOR, false);
				vd->VertexAttributePointer(EGLES2_ATTRIB_COLOR, 4, EGLES2_PRITYPE_FLOAT, GL_FALSE, stride, bstream + sizeof(SPosition2D<float>));

				break;
			case EG2DP_ELETYPE_IMG:
				vd->UseProgram(EGLES2_PROGRAM_TEXTURE2D);
				vd->UniformColor(SColor<float>(1.0,1.0,1.0,1.0));
				SetColor(SColor<float>(1.0f,1.0f,1.0f,1.0f));
				vd->EnableTexture2D(true);
				vd->EnableAttribPointer(EGLES2_ATTRIB_VERTEX, true);
				vd->EnableAttribPointer(EGLES2_ATTRIB_NORMAL, false);
				vd->EnableAttribPointer(EGLES2_ATTRIB_COLOR, false);
				vd->EnableAttribPointer(EGLES2_ATTRIB_TEXCOOR, true);
				vd->BindTexture2D(m_pTextureID[i]);
				vd->VertexAttributePointer(EGLES2_ATTRIB_TEXCOOR, 2, EGLES2_PRITYPE_FLOAT, GL_FALSE, stride, bstream + sizeof(SPosition2D<float>) + sizeof(SColor<float>));
				numVertex = 4;
				break;
			}

			Matrix MVP;			
			MVP.Multiply(*(CCamera2D::GetInstance()->GetProjectMatrix()));
			MVP.Multiply(*(CCamera2D::GetInstance()->GetViewMatrix()));
			MVP.Multiply(m_fMatrixM[i]);
	

			vd->UniformMatrix(MVP);

			if (numVertex)
			{
				vd->BlendMode(0);
				vd->EnableBlending(m_pIsUseAlpha[i]);				
				vd->VertexAttributePointer(EGLES2_ATTRIB_VERTEX, 2, EGLES2_PRITYPE_FLOAT, GL_FALSE, stride, bstream);
				if ((m_Type[i]==EG2DP_ELETYPE_RECT_WIRE) || (m_Type[i]==EG2DP_ELETYPE_TRIANGLE_WIRE))
				{
					vd->DrawArrays(EGLES2_RENDERMODE_LINE_LOOP, 0, numVertex);
				}
				else if ((m_Type[i]==EG2DP_ELETYPE_RECT) || (m_Type[i]==EG2DP_ELETYPE_TRIANGLE) || (m_Type[i]==EG2DP_ELETYPE_IMG) )
				{
					vd->DrawArrays(EGLES2_RENDERMODE_TRIANGLESTRIP, 0, numVertex);
				}
				else
				{
					vd->DrawArrays(EGLES2_RENDERMODE_LINE, 0, numVertex);
				}
				bstream += stride*numVertex;
				curVertex += numVertex;
			}
		}
		m_iNumberOfElement = 0;
		m_iStreamOffset = 0;
		vd->EnableDepthTest(true);
	}
}