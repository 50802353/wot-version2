#ifndef __MACROS_H__
#define __MACROS_H__

#include "Header.h"

#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)

// compile - runtime helper

#	include <stdlib.h>
#	define TODO(x) __pragma(message("[TODO]:" __FILE__ "("TOSTRING(__LINE__)") " TOSTRING(x))); Log(x);
#	define BREAK_IF(cond, _message) if (cond) {LogError(_message); _asm int 3}
#	define BREAK(_message) BREAK_IF(true, _message)
#	define EXEC(command)	system(command)


// log helper

extern void SetCommandTextColor(WORD);
#	define Log(...)			SetCommandTextColor(0x07);printf(__VA_ARGS__);printf("\n")
#	define LogError(...)	SetCommandTextColor(0x0c);printf(__VA_ARGS__);printf("\n");SetCommandTextColor(0x07);
#	define LogWarning(...)	SetCommandTextColor(0x0e);printf(__VA_ARGS__);printf("\n");SetCommandTextColor(0x07);




// struct alignment
#	define __PACK__

#define SAFE_DEL(a)					{if(a){delete (a);(a) = NULL;}}
#define SAFE_DEL_ARRAY(a)			{if(a){delete[] (a);(a) = NULL;}}
#define SAFE_DEL_ARRAY_TYPE(a, t)	{if((t)a){delete[] ((t)(a));(a) = NULL;}}
#define SAFE_DEL_ARRAY_OBJ(p, n)	{if ((p)!=NULL) {for (int __i = 0; __i < (n); __i++) SAFE_DEL((p)[__i]); SAFE_DEL_ARRAY(p);}}
#define SAFE_DEL_ARRAY_ARRAY(p, n)	{if ((p)!=NULL) {for (int __i = 0; __i < (n); __i++) SAFE_DEL_ARRAY((p)[__i]); SAFE_DEL_ARRAY(p);}}

#define ForeachP(__list, __type, __var)		\
	(__list)->BeginTravel(); \
	__type __var = (__list)->IsEndOfTravel()?0:(__list)->Travel(); \
	__INT32 __FEi = 0; \
	__INT32 __FEmax = (__list)->GetCount(); \
	for(;__FEi < __FEmax; __var = __FEi < __FEmax-1?(__list)->Travel():0, __FEi++)

#define Foreach(__list, __type, __var)		\
	(__list).BeginTravel(); \
	__type __var = (__list).IsEndOfTravel()?0:(__list).Travel(); \
	__INT32 __FEi = 0; \
	__INT32 __FEmax = (__list).GetCount(); \
	for(;__FEi < __FEmax; __var = __FEi < __FEmax-1?(__list).Travel():0, __FEi++)

#endif