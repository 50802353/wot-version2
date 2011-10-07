#ifndef __HEADER_H__
#define __HEADER_H__

#define PLATFORM_WIN32_VS	1
#define PLATFORM_ANDROID	2

#include "Config.h"

#include <stdio.h>

#if CONFIG_PLATFORM==PLATFORM_WIN32_VS
#	include <windows.h>
#	include <time.h>

#	include "../libs/ogl/gl.h"
#	include "../libs/ogl/glext.h"
#	pragma comment(lib, "opengl32.lib")

#	include "../libs/oal/al.h"
#	include "../libs/oal/alc.h"
#	pragma comment(lib, "openal32.lib")

#	include "../libs/vorbis/codec.h"
#	include "../libs/vorbis/ogg.h"
#	include "../libs/vorbis/os_types.h"
#	include "../libs/vorbis/vorbisenc.h"
#	include "../libs/vorbis/vorbisfile.h"
#	pragma comment(lib, "libogg_static.lib")
#	pragma comment(lib, "libvorbis_static.lib")
#	pragma comment(lib, "libvorbisfile_static.lib")

//#	include "../libs/vld/vld.h"
#endif

#include "Macros.h"

#if (CONFIG_PLATFORM==PLATFORM_WIN32_VS) || (CONFIG_PLATFORM==PLATFORM_ANDROID)
typedef unsigned long long	__UINT64;
typedef long long			__INT64;
typedef int					__INT32;
typedef unsigned int		__UINT32;
typedef signed short		__INT16;
typedef unsigned short		__UINT16;
typedef signed char			__INT8;
typedef unsigned char		__UINT8;
#endif

#if (CONFIG_PLATFORM==PLATFORM_WIN32_VS)
#	define		VIEWCLASS	CVSView
#else
#	define		VIEWCLASS	
#endif

enum ETextHAnchor
{
	ETEXTANCHOR_LEFT,
	ETEXTANCHOR_RIGHT,
	ETEXTANCHOR_HCENTER,
};

enum ETextVAnchor
{
	ETEXTANCHOR_TOP,
	ETEXTANCHOR_BOTTOM,
	ETEXTANCHOR_BASELINE,
};

#endif