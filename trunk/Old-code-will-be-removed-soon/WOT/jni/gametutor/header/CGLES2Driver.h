#ifndef __CGLES2DRIVER_H__
#define __CGLES2DRIVER_H__

#include "Header.h"
#include "IVideoDriver.h"
#include "Matrix.h"



#define EGLES2_DEFAUL_MAX_INDICES 1000
#define EGLES2_DEFAUL_MAX_UNIFORMS 10



static const char vshader_texture2D[] = 
			"precision lowp float;\n"
			"attribute vec4 a_vertices;\n"
			"attribute vec2 a_texcoords;\n"
			"varying vec2 v_texcoords;\n"
			"uniform mat4 u_mvpMatrix;\n"
			"uniform sampler2D u_activeTex;\n"
			"void main()\n"
			"{\n"
			"	v_texcoords = a_texcoords;\n"
			"	gl_Position = u_mvpMatrix * a_vertices;\n"
			"}\n";
	static const char fshader_texture2D[] = 
			"precision lowp float;									\n"
			"varying vec2 v_texcoords;								\n"
			"uniform mat4 u_mvpMatrix;								\n"
			"uniform sampler2D u_activeTex;							\n"
			"uniform vec4 u_color;									\n"
			"void main()											\n"
			"{														\n"
			"	gl_FragColor = texture2D(u_activeTex,v_texcoords);	\n"
			//"	gl_FragColor *= vec4(1.0,1.0,1.0,1.0);				\n"
			"	gl_FragColor *= u_color;							\n"
			"}														\n";
		static const char vshader_color[] = 
			"precision lowp float;									\n"
			"attribute vec4 a_vertices;								\n"
			"attribute vec4 a_colors;								\n"
			"varying vec4 v_colors;									\n"
			"uniform mat4 u_mvpMatrix;								\n"
			"void main()											\n"
			"{														\n"
			"	v_colors = a_colors;								\n"
			"	gl_Position = u_mvpMatrix * a_vertices;				\n"
			//"	gl_Position = a_vertices;							\n"
			"}														\n";
	static const char fshader_color[] = 
			"precision lowp float;									\n"
			"varying vec4 v_colors;									\n"
			"uniform mat4 u_mvpMatrix;								\n"
			"void main()											\n"
			"{														\n"
			"	gl_FragColor = v_colors;							\n"
			"}														\n";
	static const char vshader_texture3D[] = 
			"precision lowp float;									\n"
			"attribute vec4 a_vertices;								\n"
			"attribute vec3 a_texcoords;							\n"
			"varying vec3 v_texcoords;								\n"
			"uniform mat4 u_mvpMatrix;								\n"
			"uniform samplerCube u_activeTex;						\n"
			"void main()											\n"
			"{														\n"
			"	v_texcoords = a_texcoords;							\n"
			"	gl_Position = u_mvpMatrix * a_vertices;				\n"
			"}														\n";
	static const char fshader_texture3D[] = 
			"precision lowp float;									\n"
			"varying vec3 v_texcoords;								\n"
			"uniform mat4 u_mvpMatrix;								\n"
			"uniform samplerCube u_activeTex;						\n"
			"void main()											\n"
			"{														\n"
			"	gl_FragColor = textureCube(u_activeTex,v_texcoords);\n"
			"}														\n";

	

namespace GameTutor
{

	enum EGLES2DriverAttribType
	{
		EGLES2_ATTRIB_VERTEX,
		EGLES2_ATTRIB_NORMAL,
		EGLES2_ATTRIB_COLOR,
		EGLES2_ATTRIB_TEXCOOR,
	};

	enum EGLES2DriverProgramType
	{
		EGLES2_PROGRAM_COLOR,
		EGLES2_PROGRAM_TEXTURE2D,
		EGLES2_PROGRAM_TEXTURE3D
	};

	enum EGLES2DriverUniformType
	{
		EGLES2_UNIFORM_MVP,
		EGLES2_UNIFORM_ACTIVETEXTURE,
		EGLES2_UNIFORM_COLOR,
	};

	enum EGLES2DriverMatrixMode
	{
		EGLES2_MATRIX_M,
		EGLES2_MATRIX_V,
		EGLES2_MATRIX_P
	};

	enum EGLES2DriverPrimaryType
	{
		EGLES2_PRITYPE_FLOAT = GL_FLOAT,
		EGLES2_PRITYPE_UINT = GL_UNSIGNED_INT,
	};

	enum EGLES2DriverRenderMode
	{
		EGLES2_RENDERMODE_LINE = GL_LINES,
		EGLES2_RENDERMODE_LINE_LOOP = GL_LINE_LOOP,
		EGLES2_RENDERMODE_TRIANGLE = GL_TRIANGLES,
		EGLES2_RENDERMODE_TRIANGLESTRIP = GL_TRIANGLE_STRIP,
	};

	enum EGLES2DriverPixelFormat
	{
		EGLES2_PIXFMT_R8G8B8 = GL_RGB,
		EGLES2_PIXFMT_R8G8B8A8 = GL_RGBA,
	};

	

	

	class CGLES2Driver:public IVideoDriver, public CSingleton<CGLES2Driver>
	{
		friend class  CSingleton<CGLES2Driver>;
	private:

		GLuint LoadShader ( GLenum type, const char *shaderSrc )
		{
			GLuint shader;
			GLint compiled;   
			shader = glCreateShader ( type );
			if ( shader == 0 )
			{
				return 0;
			}
			glShaderSource ( shader, 1, &shaderSrc, 0 );
			glCompileShader ( shader );
			glGetShaderiv ( shader, GL_COMPILE_STATUS, &compiled );
			if ( !compiled ) 
			{
				GLint infoLen = 0;
				glGetShaderiv ( shader, GL_INFO_LOG_LENGTH, &infoLen );
				if ( infoLen > 1 )
				{
					char* infoLog = new char[infoLen];
					glGetShaderInfoLog ( shader, infoLen, 0, infoLog );
					Log ( "Error compiling shader:\n%s\n", infoLog );            
					delete[] infoLog;
				}
				glDeleteShader ( shader );
				return 0;
			}
			return shader;
		}

		GLuint LoadProgram ( const char *vertShaderSrc, const char *fragShaderSrc )
		{
			GLuint vertexShader;
			GLuint fragmentShader;
			GLuint programObject;
			GLint linked;
			vertexShader = LoadShader ( GL_VERTEX_SHADER, vertShaderSrc );
			if ( vertexShader == 0 )
				return 0;
			fragmentShader = LoadShader ( GL_FRAGMENT_SHADER, fragShaderSrc );
			if ( fragmentShader == 0 )
			{
				glDeleteShader( vertexShader );
				return 0;
			}
			programObject = glCreateProgram ( );
			if ( programObject == 0 )
				return 0;
			glAttachShader ( programObject, vertexShader );
			glAttachShader ( programObject, fragmentShader );
			glLinkProgram ( programObject );
			glGetProgramiv ( programObject, GL_LINK_STATUS, &linked );
			if ( !linked ) 
			{
				GLint infoLen = 0;
				glGetProgramiv ( programObject, GL_INFO_LOG_LENGTH, &infoLen );      
				if ( infoLen > 1 )
				{
					char* infoLog = new char[infoLen];
					glGetProgramInfoLog ( programObject, infoLen, 0, infoLog );
					Log( "Error linking program:\n%s\n", infoLog );                     
					delete[] infoLog;
				}
				glDeleteProgram ( programObject );
				return 0;
			}
			glDeleteShader ( vertexShader );
			glDeleteShader ( fragmentShader );
			return programObject;
		}

		

	protected:
		CGLES2Driver():
			m_isUseAlpha(false), 
			blendmode(0),
			m_isUse2DTexture(false), 
			m_isUseDepthTest(true),
			m_isWriteDepthTest(true),
			IVideoDriver(EVIDEO_DRIVER_OGLES2)			
		{
			m_iProgramLocation[EGLES2_PROGRAM_COLOR] = LoadProgram(vshader_color,fshader_color);
			glUseProgram(m_iProgramLocation[EGLES2_PROGRAM_COLOR]);
			m_iAttribLocation[EGLES2_PROGRAM_COLOR][EGLES2_ATTRIB_VERTEX] = glGetAttribLocation(m_iProgramLocation[EGLES2_PROGRAM_COLOR], "a_vertices");
			m_iAttribLocation[EGLES2_PROGRAM_COLOR][EGLES2_ATTRIB_COLOR] = glGetAttribLocation(m_iProgramLocation[EGLES2_PROGRAM_COLOR], "a_colors");
			m_iAttribLocation[EGLES2_PROGRAM_COLOR][EGLES2_ATTRIB_TEXCOOR] =  glGetAttribLocation(m_iProgramLocation[EGLES2_PROGRAM_COLOR], "a_texcoords");
			m_iAttribLocation[EGLES2_PROGRAM_COLOR][EGLES2_ATTRIB_NORMAL] =  glGetAttribLocation(m_iProgramLocation[EGLES2_PROGRAM_COLOR], "a_normals");
			m_iUniformLocation[EGLES2_PROGRAM_COLOR][EGLES2_UNIFORM_MVP] = glGetUniformLocation(m_iProgramLocation[EGLES2_PROGRAM_COLOR], "u_mvpMatrix");
			m_iUniformLocation[EGLES2_PROGRAM_COLOR][EGLES2_UNIFORM_ACTIVETEXTURE] = glGetUniformLocation(m_iProgramLocation[EGLES2_PROGRAM_COLOR], "u_activeTex");
			m_iUniformLocation[EGLES2_PROGRAM_COLOR][EGLES2_UNIFORM_COLOR] = glGetUniformLocation(m_iProgramLocation[EGLES2_PROGRAM_COLOR], "u_color");


			m_iProgramLocation[EGLES2_PROGRAM_TEXTURE2D] = LoadProgram(vshader_texture2D,fshader_texture2D);
			glUseProgram(m_iProgramLocation[EGLES2_PROGRAM_TEXTURE2D]);
			m_iAttribLocation[EGLES2_PROGRAM_TEXTURE2D][EGLES2_ATTRIB_VERTEX] = glGetAttribLocation(m_iProgramLocation[EGLES2_PROGRAM_TEXTURE2D], "a_vertices");
			m_iAttribLocation[EGLES2_PROGRAM_TEXTURE2D][EGLES2_ATTRIB_COLOR] = glGetAttribLocation(m_iProgramLocation[EGLES2_PROGRAM_TEXTURE2D], "a_colors");
			m_iAttribLocation[EGLES2_PROGRAM_TEXTURE2D][EGLES2_ATTRIB_TEXCOOR] = glGetAttribLocation(m_iProgramLocation[EGLES2_PROGRAM_TEXTURE2D], "a_texcoords");
			m_iAttribLocation[EGLES2_PROGRAM_TEXTURE2D][EGLES2_ATTRIB_NORMAL] =  glGetAttribLocation(m_iProgramLocation[EGLES2_PROGRAM_TEXTURE2D], "a_normals");
			m_iUniformLocation[EGLES2_PROGRAM_TEXTURE2D][EGLES2_UNIFORM_MVP] = glGetUniformLocation(m_iProgramLocation[EGLES2_PROGRAM_TEXTURE2D], "u_mvpMatrix");
			m_iUniformLocation[EGLES2_PROGRAM_TEXTURE2D][EGLES2_UNIFORM_ACTIVETEXTURE] = glGetUniformLocation(m_iProgramLocation[EGLES2_PROGRAM_TEXTURE2D], "u_activeTex");
			m_iUniformLocation[EGLES2_PROGRAM_TEXTURE2D][EGLES2_UNIFORM_COLOR] = glGetUniformLocation(m_iProgramLocation[EGLES2_PROGRAM_TEXTURE2D], "u_color");


			m_iProgramLocation[EGLES2_PROGRAM_TEXTURE3D] = LoadProgram(vshader_texture3D,fshader_texture3D);
			glUseProgram(m_iProgramLocation[EGLES2_PROGRAM_TEXTURE3D]);
			m_iAttribLocation[EGLES2_PROGRAM_TEXTURE3D][EGLES2_ATTRIB_VERTEX] = glGetAttribLocation(m_iProgramLocation[EGLES2_PROGRAM_TEXTURE3D], "a_vertices");
			m_iAttribLocation[EGLES2_PROGRAM_TEXTURE3D][EGLES2_ATTRIB_COLOR] = glGetAttribLocation(m_iProgramLocation[EGLES2_PROGRAM_TEXTURE3D], "a_colors");
			m_iAttribLocation[EGLES2_PROGRAM_TEXTURE3D][EGLES2_ATTRIB_TEXCOOR] = glGetAttribLocation(m_iProgramLocation[EGLES2_PROGRAM_TEXTURE3D], "a_texcoords");
			m_iAttribLocation[EGLES2_PROGRAM_TEXTURE3D][EGLES2_ATTRIB_NORMAL] =  glGetAttribLocation(m_iProgramLocation[EGLES2_PROGRAM_TEXTURE3D], "a_normals");
			m_iUniformLocation[EGLES2_PROGRAM_TEXTURE3D][EGLES2_UNIFORM_MVP] = glGetUniformLocation(m_iProgramLocation[EGLES2_PROGRAM_TEXTURE3D], "u_mvpMatrix");
			m_iUniformLocation[EGLES2_PROGRAM_TEXTURE3D][EGLES2_UNIFORM_ACTIVETEXTURE] = glGetUniformLocation(m_iProgramLocation[EGLES2_PROGRAM_TEXTURE3D], "u_activeTex");
			m_iUniformLocation[EGLES2_PROGRAM_TEXTURE3D][EGLES2_UNIFORM_COLOR] = glGetUniformLocation(m_iProgramLocation[EGLES2_PROGRAM_TEXTURE3D], "u_color");

			
			


			m_UniformMatrix = new Matrix();

			m_iCurrentProgram = EGLES2_PROGRAM_COLOR;
			glUseProgram(m_iProgramLocation[EGLES2_PROGRAM_COLOR]);
			UseProgram(EGLES2_PROGRAM_COLOR);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glDisable(GL_BLEND);
			glEnable(GL_DEPTH_TEST);
			glDepthMask(true);
			for (int j = 0; j < EGLES2_PROGRAM_TEXTURE3D - EGLES2_PROGRAM_COLOR + 1; j++)
			for (int i = 0; i < EGLES2_ATTRIB_TEXCOOR - EGLES2_ATTRIB_VERTEX + 1; i++)
			{
				m_isUseAttribPointer[j][i] = false;
			}


			m_color = SColor<float>(0.0f,0.0f,0.0f,1.0f);

			for (int i = 0; i < EGLES2_DEFAUL_MAX_INDICES; i++)
			{
				m_iAutoIndices[i] = i;
			}
		}

		~CGLES2Driver()
		{
			glDeleteProgram(m_iProgramLocation[EGLES2_PROGRAM_COLOR]);
			glDeleteProgram(m_iProgramLocation[EGLES2_PROGRAM_TEXTURE2D]);
			glDeleteProgram(m_iProgramLocation[EGLES2_PROGRAM_TEXTURE3D]);
		}



	public:
		void PrintInfomation()
		{
			TODO("CGLES2Driver::PrintInfomation is not implemented");
		}
		__UINT32 GetError()
		{
			TODO("CGLES2Driver::GetError is not implemented");
			return 0;
		}

		void UseProgram(enum EGLES2DriverProgramType programType)
		{
			//if (m_iCurrentProgram != programType)
			{
				switch (programType)
				{
				case EGLES2_PROGRAM_COLOR:
					glUseProgram(m_iProgramLocation[EGLES2_PROGRAM_COLOR]);
					m_iCurrentProgram = programType;
					break;
				case EGLES2_PROGRAM_TEXTURE2D:
					glUseProgram(m_iProgramLocation[EGLES2_PROGRAM_TEXTURE2D]);
					m_iCurrentProgram = programType;
					break;
				case EGLES2_PROGRAM_TEXTURE3D:
					glUseProgram(m_iProgramLocation[EGLES2_PROGRAM_TEXTURE3D]);
					m_iCurrentProgram = programType;
					break;
				}
			}
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
				}
				else
				{
					glDisable(GL_BLEND);
				}
			}
			
		}

		void BlendMode(__INT32 mode)
		{
			if (mode!=blendmode)
			{
				switch (mode)
				{
				case 0:
					glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
					blendmode = mode;
					break;
				case 1:
					glBlendFunc(GL_SRC_ALPHA, GL_ONE);
					blendmode = mode;
					break;
				case 2:
					glBlendFunc(GL_SRC_ALPHA, GL_DST_ALPHA);
					blendmode = mode;
					break;
				}				
			}
		}
		
		//-----------------------------------------------
		// Attribute Pointer
		//-----------------------------------------------
		void VertexAttributePointer(enum EGLES2DriverAttribType attribType,int size, enum EGLES2DriverPrimaryType primType, bool normalized, __UINT32 stride, void* pointer)
		{
			if (primType==EGLES2_PRITYPE_FLOAT)
			{
				glVertexAttribPointer(m_iAttribLocation[m_iCurrentProgram][attribType], size, primType, normalized, stride, pointer);				
			}
			else
			{
				Log("Nothing's  drawn. Type should be GLfloat");
			}
		}

		//-----------------------------------------------
		// Enable client state (enable/disable attrib pointer)
		//-----------------------------------------------
		void EnableAttribPointer(enum EGLES2DriverAttribType attribType, bool isUse)
		{
			if (m_iAttribLocation[m_iCurrentProgram][attribType]!=-1)
			{
				if (isUse)
				{
					if (!m_isUseAttribPointer[m_iCurrentProgram][attribType])
					{
						m_isUseAttribPointer[m_iCurrentProgram][attribType] = true;
						glEnableVertexAttribArray(m_iAttribLocation[m_iCurrentProgram][attribType]);
					}
				}
				else
				{
					if (m_isUseAttribPointer[attribType])
					{
						m_isUseAttribPointer[m_iCurrentProgram][attribType] = false;
						glDisableVertexAttribArray(m_iAttribLocation[m_iCurrentProgram][attribType]);
					}
				}
			}
			
		}

		//-----------------------------------------------
		// Draw Array
		//-----------------------------------------------
		void DrawElements(enum EGLES2DriverRenderMode mode, __UINT32 numOfIndices, void *indices)
		{
			if (!indices)
			{
				DrawArrays(mode, 0, numOfIndices);
			}
			else
			{
				glDrawElements(mode, numOfIndices, EGLES2_PRITYPE_UINT, indices);
			}
		}
		void DrawArrays(enum EGLES2DriverRenderMode mode, __UINT32 first, __UINT32 numOfIndices)
		{
			glDrawArrays(mode, 0, numOfIndices);
		};
		//-----------------------------------------------
		// Clear Screen
		//-----------------------------------------------
		void Clear(float Red, float Green, float Blue, float Alpha)
		{
			glClearColor(Red, Green, Blue, Alpha);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			
			
		}

		//-----------------------------------------------
		// Set view port
		//-----------------------------------------------
		void Viewport(SRect<__INT32> rect)
		{
			glViewport(rect.X, rect.Y, rect.W, rect.H);
		}

		//-----------------------------------------------
		// TODO: Viet them cac ham ve camera (diem dat, huong nhin, projection/orthor, move/rotate camera
		//-----------------------------------------------
	/*private:
		Matrix* getMatrix(enum EGLES2DriverMatrixMode matrix)
		{
			switch(matrix)
			{
			case EGLES2_MATRIX_M:
				return &m_fMatrixM;
				break;
			case EGLES2_MATRIX_V:
				return &m_fMatrixV;
				break;
			case EGLES2_MATRIX_P:
				return &m_fMatrixP;
				break;
			default:
				return NULL;
				break;
			}
		}
	public:
		void LoadIdentity(enum EGLES2DriverMatrixMode matrix)
		{
			Matrix *current_matrix = getMatrix(matrix);
			current_matrix->LoadIdentity();
		}

		void Frustume(enum EGLES2DriverMatrixMode matrix, float left, float right, float bottom, float top, float near, float far)
		{
			Matrix *current_matrix = getMatrix(matrix);
			current_matrix->Frustume(left,right,bottom,top,near,far);
		}

		void Translate(enum EGLES2DriverMatrixMode matrix, float x, float y, float z)
		{
			Matrix *current_matrix = getMatrix(matrix);
			current_matrix->Translate(x,y,z);
		}

		void Rotate(enum EGLES2DriverMatrixMode matrix, float angle, AXIS axis)
		{
			Matrix *current_matrix = getMatrix(matrix);
			current_matrix->Rotate(angle, axis);
		}

		void Scale(enum EGLES2DriverMatrixMode matrix, float x, float y, float z)
		{
			Matrix *current_matrix = getMatrix(matrix);
			current_matrix->Scale(x,y,z);
		}

		GLfloat* getMVP(enum EGLES2DriverMatrixMode matrix)
		{
			Matrix *current_matrix = getMatrix(matrix);
			return current_matrix->GetData();
		}*/

		//-----------------------------------------------
		// TODO: Them cac ham ve ma tran mult, scale, perspective/frustume, ortho
		//-----------------------------------------------




		//-----------------------------------------------
		// Texture
		//-----------------------------------------------
		void EnableTexture2D(bool val)
		{
			if (val != m_isUse2DTexture)
			{
				m_isUse2DTexture = val;
			}
		}

		__UINT32 AddTexure2D(int level, EGLES2DriverPixelFormat format, int width, int height, int border, __UINT8 *pixel)
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
		
		bool WinTGALoad( const char *fileName, unsigned char **buffer, int *width, int *height )
		{
			typedef struct
			{
				unsigned char  IdSize,
								MapType,
								ImageType;
				unsigned short PaletteStart,
								PaletteSize;
				unsigned char  PaletteEntryDepth;
				unsigned short X,
								Y,
								Width,
								Height;
				unsigned char  ColorDepth,
								Descriptor;
         
			} TGA_HEADER;

			typedef struct tagRGBTRIPLE {
			unsigned char    rgbtBlue;
			unsigned char    rgbtGreen;
			unsigned char    rgbtRed;
			} RGBTRIPLE;

			FILE        *fp;
			TGA_HEADER   Header;
			fp = fopen (fileName, "rb" );
   
			if ( fp == NULL )
			{
				return false;
			}

		   fread ( &Header, sizeof(TGA_HEADER), 1, fp );

		   *width = Header.Width;
		   *height = Header.Height;
   
		   if ( Header.ColorDepth == 24 )
		   {
			  RGBTRIPLE *Buffer24;
			  Buffer24= (RGBTRIPLE*)malloc(sizeof(RGBTRIPLE) * (*width) * (*height));
			  if(Buffer24)
			  {
				 int i=0;
				 int x, y;
				 fread(Buffer24, sizeof(RGBTRIPLE), (*width) * (*height), fp);
				 *buffer= (unsigned char*) malloc(3 * (*width) * (*height));
				 for ( y = 0; y < *height; y++ )
					for( x = 0; x < *width; x++ )
					{
					   int Index= y * (*width) + x;
					   if(!(Header.Descriptor & (1<<5)))
						  Index= ((*height) - 1 - y) * (*width) + x;
					   (*buffer)[(i * 3)]=      Buffer24[Index].rgbtRed;
					   (*buffer)[(i * 3) + 1]=  Buffer24[Index].rgbtGreen;
					   (*buffer)[(i * 3) + 2]=  Buffer24[Index].rgbtBlue;        
					   i++;
					}         
				 fclose(fp);
				 free(Buffer24);
				 return(true);
			  }		
		   }
		   return(false);
		}
		
		__UINT32 AddTexure2D(int level, EGLES2DriverPixelFormat format, char* filename)
		{
			unsigned char *buffer;
			int width=0;
			int height=0;
			if ( WinTGALoad ( filename, &buffer, &width, &height ) )
			{
				return AddTexure2D(level, format, width, height, 0, buffer); 
			}
			return 0;
		}
		
		void BindTexture2D(__UINT32 texname)
		{
			glBindTexture(GL_TEXTURE_2D, texname);
		}

		void FreeTexture2D(__UINT32 texname)
		{
			glDeleteTextures(1, &texname );
		}

		void UniformMatrix(Matrix M)
		{
			*m_UniformMatrix = M;
			glUniformMatrix4fv(m_iUniformLocation[m_iCurrentProgram][EGLES2_UNIFORM_MVP], 1, GL_FALSE, m_UniformMatrix->GetData());
		}

		void UniformColor(SColor<float> color)
		{
			glUniform4f(m_iUniformLocation[m_iCurrentProgram][EGLES2_UNIFORM_COLOR],color.Red,color.Green,color.Blue,color.Alpha);
		}

		void EnableDepthTest(bool val)
		{
			if (val != m_isUseDepthTest)
			{
				m_isUseDepthTest = val;
				if (m_isUseDepthTest)
				{
					glEnable (GL_DEPTH_TEST);
				}
				else
				{
					glDisable(GL_DEPTH_TEST);
				}
			}
		}

		void EnableDepthWrite(bool val)
		{
			if (val != m_isWriteDepthTest)
			{
				m_isWriteDepthTest = val;
				if (m_isWriteDepthTest)
				{
					glDepthMask(true);
				}
				else
				{
					glDepthMask(false);
				}
			}
		}

		
	private:
		bool m_isUseAttribPointer[EGLES2_PROGRAM_TEXTURE3D-EGLES2_PROGRAM_COLOR+1][EGLES2_ATTRIB_TEXCOOR - EGLES2_ATTRIB_VERTEX + 1];
		int m_iAttribLocation[EGLES2_PROGRAM_TEXTURE3D-EGLES2_PROGRAM_COLOR+1][EGLES2_ATTRIB_TEXCOOR - EGLES2_ATTRIB_VERTEX + 1];
		int m_iUniformLocation[EGLES2_PROGRAM_TEXTURE3D-EGLES2_PROGRAM_COLOR+1][EGLES2_UNIFORM_COLOR - EGLES2_UNIFORM_MVP +1];
		unsigned int m_iAutoIndices[EGLES2_DEFAUL_MAX_INDICES];
		bool m_isUse2DTexture;
		bool m_isUseAlpha;
		__INT32 blendmode;
		bool m_isUseDepthTest;
		bool m_isWriteDepthTest;
		EGLES2DriverProgramType m_iCurrentProgram;
		__UINT32 m_iProgramLocation[EGLES2_PROGRAM_TEXTURE3D-EGLES2_PROGRAM_COLOR+1];
		SColor<float> m_color;
		Matrix *m_UniformMatrix;
	};

}

#endif