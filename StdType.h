
//target Dependant int and long
#ifndef STDTYPE_H_
#define STDTYPE_H_

typedef unsigned char       u8;
typedef unsigned short      u16;
typedef unsigned long       u32;
typedef unsigned long long  u64;

typedef signed char         s8;
typedef signed short        s16;
typedef signed long         s32;
typedef signed long long    s64;

typedef float f32;

#define   NULL       0
#define   NULLPTR    ((void*)0)

typedef enum{
	FALSE,
	TRUE
	}bool_type;
	
#define  MAX_U16     ((u16)65535)
#define  MAX_S16     ((s16)32767)   //0X7FFF
#define  MIN_S16     ((s16)-32768)
#define  MIN_U16     ((u16)0)         //casting because compiler number as default int and target may be int 4byte




#endif /* STDTYPE_H_ */