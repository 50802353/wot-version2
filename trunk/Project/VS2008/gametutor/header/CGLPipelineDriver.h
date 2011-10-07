#ifndef __CGLPIPELINEDRIVER_H__
#define __CGLPIPELINEDRIVER_H__

#include "Header.h"
#include "IVideoDriver.h"

#define EGLPD_DEFAUL_MAX_INDICES 1000
namespace GameTutor
{
	enum EGLPipelineDriverAttribType
	{
		EGLPD_ATTRIB_VERTEX,
		EGLPD_ATTRIB_NORMAL,
		EGLPD_ATTRIB_COLOR,
		EGLPD_ATTRIB_TEXCOOR,
	};

	enum EGLPipelineDriverMatrixMode
	{
		EGLPD_MATRIXMODE_PROJECTION = GL_PROJECTION,
		EGLPD_ATTRIB_MODELVIEW = GL_MODELVIEW,
	};

	enum EGLPipelineDriverPrimaryType
	{
		EGLPD_PRIYTPE_FLOAT = GL_FLOAT,
		EGLPD_PRIYTPE_UINT = GL_UNSIGNED_INT,
	};

	enum EGLPipelineDriverRenderMode
	{
		EGLPD_RENDERMODE_TRIANGLE = GL_TRIANGLES,
		EGLPD_RENDERMODE_TRIANGLESTRIP = GL_TRIANGLE_STRIP,
	};

	enum EGLPipelineDriverPixelFormat
	{
		EGLPD_PIXFMT_R8G8B8 = GL_RGB,
		EGLPD_PIXFMT_R8G8B8A8 = GL_RGBA,
	};

	class CGLPipelineDriver:public IVideoDriver, public CSingleton<CGLPipelineDriver>
	{
		friend class  CSingleton<CGLPipelineDriver>;
	protected:
		CGLPipelineDriver():m_CurrentMatrixMode(EGLPD_MATRIXMODE_PROJECTION),
			m_isUseAlpha(false), m_isUse2DTexture(false), IVideoDriver(EVIDEO_DRIVER_OGLPIPELINE)
		{
			glDisable(GL_BLEND | GL_TEXTURE_2D);
			for (int i = 0; i < EGLPD_ATTRIB_TEXCOOR - EGLPD_ATTRIB_VERTEX + 1; i++)
			{
				m_isUseAttribPointer[i] = false;
			}
			m_iAttribMapping[EGLPD_ATTRIB_VERTEX] = GL_VERTEX_ARRAY;
			m_iAttribMapping[EGLPD_ATTRIB_NORMAL] = GL_NORMAL_ARRAY;
			m_iAttribMapping[EGLPD_ATTRIB_COLOR] = GL_COLOR_ARRAY;
			m_iAttribMapping[EGLPD_ATTRIB_TEXCOOR] = GL_TEXTURE_COORD_ARRAY;

			for (int i = 0; i < EGLPD_DEFAUL_MAX_INDICES; i++)
			{
				m_iAutoIndices[i] = i;
			}
		}
	public:
		void PrintInfomation()
		{
			TODO("CGLPipelineDriver::PrintInfomation is not implemented");
		}
		__UINT32 GetError()
		{
			TODO("CGLPipelineDriver::GetError is not implemented");
			return 0;
		}

		//-----------------------------------------------
		// Set Color
		//-----------------------------------------------
		template <class T>
		void SetColor(T alpha, T red, T green, T blue)
		{
			if (sizeof(T) == 1)
			{
				SetColor<__UINT8>(__UINT8(alpha), __UINT8(red), __UINT8(green), __UINT8(blue));
			}
			else
			{
				BREAK("Invalid type");
			}
		}
		template <>
		void SetColor<float>(float alpha, float red, float green, float blue)
		{
			glColor4f(red, green, blue, alpha);
		}
		template <>
		void SetColor<__UINT8>(__UINT8 alpha, __UINT8 red, __UINT8 green, __UINT8 blue)
		{
			glColor4f(red/255.0f, green/255.0f, blue/255.0f, alpha/255.0f);
		}

		//-----------------------------------------------
		// Set Blending
		//-----------------------------------------------
		void EnableBlending(bool val)
		{
			if (val != m_isUseAlpha)
			{
				m_isUseAlpha = val;
				if (m_isUseAlpha)
				{
					glEnable (GL_BLEND);
					glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
				}
				else
				{
					glDisable(GL_BLEND);
				}
			}
			
		}
		
		//-----------------------------------------------
		// Attribute Pointer
		//-----------------------------------------------
		void AttributePointer(enum EGLPipelineDriverAttribType attribType, int size, enum EGLPipelineDriverPrimaryType primType, __UINT32 stride, void* pointer)
		{
			float *xx = (float*)pointer;
			switch (attribType)
			{
			case EGLPD_ATTRIB_VERTEX:
				glVertexPointer(size, __INT32(primType), stride, pointer );
				break;
			case EGLPD_ATTRIB_NORMAL:
				glNormalPointer(__INT32(primType), stride, pointer);
				break;
			case EGLPD_ATTRIB_COLOR:
				glColorPointer(size, __INT32(primType), stride, pointer);
				break;
			case EGLPD_ATTRIB_TEXCOOR:
				glTexCoordPointer(size, __INT32(primType), stride, pointer);
				break;
			}

		}

		//-----------------------------------------------
		// Enable client state (enable/disable attrib pointer)
		//-----------------------------------------------
		void EnableAttribPointer(enum EGLPipelineDriverAttribType attribType, bool isUse)
		{
			if (isUse)
			{
				if (!m_isUseAttribPointer[attribType])
				{
					m_isUseAttribPointer[attribType] = true;
					glEnableClientState(m_iAttribMapping[attribType]);
				}
			}
			else
			{
				if (m_isUseAttribPointer[attribType])
				{
					m_isUseAttribPointer[attribType] = false;
					glDisableClientState(m_iAttribMapping[attribType]);
				}
			}
			
		}

		//-----------------------------------------------
		// Draw Array
		//-----------------------------------------------
		void DrawElements(enum EGLPipelineDriverRenderMode mode, __UINT32 numOfIndices, enum EGLPipelineDriverPrimaryType primType, void *indices)
		{
			if (!indices)
			{
				indices = m_iAutoIndices;
				primType = EGLPD_PRIYTPE_UINT;
			}
			BREAK_IF(numOfIndices > EGLPD_DEFAUL_MAX_INDICES, "numOfIndices is bigger than EGLPD_DEFAUL_MAX_INDICES");
			glDrawElements(mode, numOfIndices, primType, indices);
		}
		void DrawElements(enum EGLPipelineDriverRenderMode mode, __UINT32 numOfIndices)
		{
			DrawElements(mode, numOfIndices, EGLPD_PRIYTPE_UINT, 0);
		};
		//-----------------------------------------------
		// Clear Screen
		//-----------------------------------------------
		void Clear(SColor<float> c)
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glClearColor(c.Red, c.Green, c.Blue, c.Alpha);
		}

		//-----------------------------------------------
		// Set view port
		//-----------------------------------------------
		void Viewport(SRect<__INT32> rect)
		{
			glViewport(rect.X, rect.Y, rect.W, rect.H);
		}

		//-----------------------------------------------
		// Othor
		//-----------------------------------------------
		void Ortho(float left, float right, float top, float bottom, float znear, float zfar)
		{
			glOrtho(left, right, bottom, top, znear, zfar);
		}

		//-----------------------------------------------
		// Matrix mode
		//-----------------------------------------------
		void EnableMatrixMode(enum EGLPipelineDriverMatrixMode mode)
		{
			if (mode != m_CurrentMatrixMode)
			{
				glMatrixMode(mode);
				m_CurrentMatrixMode = mode;
			}
		}
		void PushMatrix(enum EGLPipelineDriverMatrixMode mode)
		{
			EnableMatrixMode(mode);
			glPushMatrix();
		}
		void PopMatrix(enum EGLPipelineDriverMatrixMode mode)
		{
			EnableMatrixMode(mode);
			glPopMatrix();
		}
		void LoadIdentity(enum EGLPipelineDriverMatrixMode mode)
		{
			EnableMatrixMode(mode);
			glLoadIdentity();
		}


		//-----------------------------------------------
		// Texture
		//-----------------------------------------------
		void EnableTexture2D(bool val)
		{
			if (val != m_isUse2DTexture)
			{
				m_isUse2DTexture = val;
				if (m_isUse2DTexture)
				{
					glEnable (GL_TEXTURE_2D);
				}
				else
				{
					glDisable(GL_TEXTURE_2D);
				}
			}
		}

		__UINT32 AddTexure2D(int level, EGLPipelineDriverPixelFormat format, int width, int height, int border, __UINT8 *pixel)
		{
			EnableTexture2D(true);
			__UINT32 texname = 0;
			glGenTextures(1, &texname);
			glBindTexture(GL_TEXTURE_2D, texname);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);//GL_LINEAR
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);//GL_LINEAR
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexImage2D(GL_TEXTURE_2D, level, format, width, height, border, format, GL_UNSIGNED_BYTE, pixel);
			return texname;
		}


		void BindTexture2D(__UINT32 texname)
		{
			glBindTexture(GL_TEXTURE_2D, texname);
		}

		void FreeTexture2D(__UINT32 texname)
		{
			glDeleteTextures(1, &texname );
		}


	private:
		bool m_isUseAttribPointer[EGLPD_ATTRIB_TEXCOOR - EGLPD_ATTRIB_VERTEX + 1];
		__UINT32 m_iAttribMapping[EGLPD_ATTRIB_TEXCOOR - EGLPD_ATTRIB_VERTEX + 1];
		__UINT32 m_iAutoIndices[EGLPD_DEFAUL_MAX_INDICES];
		enum EGLPipelineDriverMatrixMode m_CurrentMatrixMode;
		bool m_isUseAlpha;
		bool m_isUse2DTexture;
	};
}

#endif