#ifndef __HEADER_H__
#define __HEADER_H__

#define PLATFORM_WIN32_VS	1
#define PLATFORM_ANDROID	2

#include "Config.h"

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

#if CONFIG_PLATFORM==PLATFORM_WIN32_VS
#	include <windows.h>
#	include <time.h>
#	include "../libs/ogl/gl2.h"
#	include "../libs/ogl/gl2ext.h"
#	include "esUtil.h"

//#	pragma comment(lib, "opengl32.lib")
#	pragma comment(lib, "esUtil.lib")
//#	pragma comment(lib, "esUtil_d.lib")
#	pragma comment(lib, "libEGL.lib")
#	pragma comment(lib, "libGLESv2.lib")
//#	pragma pack(1)
//#	include "../libs/vld/vld.h"
#elif CONFIG_PLATFORM==PLATFORM_ANDROID
	#ifdef WIN32DEBUG
	#include "c:\DevTools\android-ndk-r6\platforms\android-9\arch-x86\usr\include\jni.h";
	#else
	#	include <jni.h>
	#endif
#	include <GLES2/gl2.h>
#	include <GLES2/gl2ext.h>
#	include <GLES2/gl2platform.h>
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

#define v_top 0x1
#define v_bottom 0x10
#define v_center 0x100
#define h_left 0x1000
#define h_right 0x10000
#define h_center 0x100000
#endif

#if (CONFIG_PLATFORM==PLATFORM_WIN32_VS)
#	define		VIEWCLASS	CVSView
#else
#	define		VIEWCLASS	CAndroidView
#endif

#endif