#ifndef __MACROS_H__
#define __MACROS_H__

#include "Header.h"

#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)

// compile - runtime helper
#if CONFIG_PLATFORM==PLATFORM_WIN32_VS
#	include <stdlib.h>
#	define TODO(x) ;//__pragma(message("[TODO]:" __FILE__ "("TOSTRING(__LINE__)") " TOSTRING(x))); Log(x);
#	define BREAK_IF(cond, _message) if (cond) {LogError(_message); _asm int 3}
#	define BREAK(_message) BREAK_IF(true, _message)
#	define EXEC(command)	system(command)
#elif CONFIG_PLATFORM==PLATFORM_ANDROID
#	include <jni.h>
#	define TODO(x) Log(x);
#	define BREAK_IF(cond, _message) ;
#	define BREAK(_message) ;
#	define EXEC(command) ;
#	define WARNING(x) ;
#	define ERR(x) ;
#else
#	define TODO(x) ;
#	define WARNING(x) ;
#	define ERR(x) ;
#	define BREAK_IF(cond, _message) ;
#	define BREAK(_message) ;
#	define EXEC(command)	;
#endif

// log helper
#define  LOG_TAG    "WOT"
#if CONFIG_PLATFORM==PLATFORM_WIN32_VS
extern void SetCommandTextColor(WORD);
#	define Log(...)			SetCommandTextColor(0x07);printf(__VA_ARGS__);printf("\n")
#	define LogError(...)	SetCommandTextColor(0x0c);printf(__VA_ARGS__);printf("\n");SetCommandTextColor(0x07)
#	define LogWarning(...)	SetCommandTextColor(0x0e);printf(__VA_ARGS__);printf("\n");SetCommandTextColor(0x07)
#elif CONFIG_PLATFORM==PLATFORM_ANDROID
#ifdef WIN32DEBUG
#	include "c:\DevTools\android-ndk-r6\platforms\android-9\arch-x86\usr\include\android\log.h"
#else
#	include <android/log.h>
#endif

#	define Log(...)  __android_log_print(ANDROID_LOG_INFO, LOG_TAG ,__VA_ARGS__)
#	define LogError(...)  __android_log_print(ANDROID_LOG_ERROR, LOG_TAG ,__VA_ARGS__)
#endif


#if CONFIG_PLATFORM==PLATFORM_WIN32_VS
	#	define PATH_RESOURCE_GRAPHIC "../resources/graphic/"
	#	define PATH_GRAPHIC(X) PATH_RESOURCE_GRAPHIC ## X

	#	define PATH_RESOURCE_AUDIO "../resources/audio/"
	#	define PATH_AUDIO(X) PATH_RESOURCE_AUDIO ## X

#elif CONFIG_PLATFORM==PLATFORM_ANDROID
	#	define PATH_RESOURCE_GRAPHIC "./mnt/sdcard/WOT/resources/graphic/"
	#	define PATH_GRAPHIC(X) (char*) PATH_RESOURCE_GRAPHIC X

	#	define PATH_RESOURCE_AUDIO "./mnt/sdcard/WOT/resources/audio/"
	#	define PATH_AUDIO(X) (char*) PATH_RESOURCE_AUDIO X
#endif

//#	define PATH_AUDIO(X) PATH_RESOURCE ## "audio/" ## X
//#	define PATH_GRAPHIC(X) PATH_RESOURCE ## "graphic/" ## X
//#	define PATH_OTHER(X) PATH_RESOURCE ## "other/" ## X




// struct alignment
#if CONFIG_PLATFORM==PLATFORM_WIN32_VS
#	define __PACK__
#else
#	define __PACK__		
#endif


#define SAFE_DEL(a)					{if(a){delete (a);(a) = NULL;}}
#define SAFE_DEL_ARRAY(a)			{if(a){delete[] (a);(a) = NULL;}}
#define SAFE_DEL_ARRAY_TYPE(a, t)	{if((t)a){delete[] ((t)(a));(a) = NULL;}}
#define SAFE_DEL_ARRAY_OBJ(p, n)	{if ((p)!=NULL) {for (int __i = 0; __i < (n); __i++) SAFE_DEL((p)[__i]); SAFE_DEL_ARRAY(p);}}
#define SAFE_DEL_ARRAY_ARRAY(p, n)	{if ((p)!=NULL) {for (int __i = 0; __i < (n); __i++) SAFE_DEL_ARRAY((p)[__i]); SAFE_DEL_ARRAY(p);}}

#endif