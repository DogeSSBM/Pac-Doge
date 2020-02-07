#pragma once

typedef unsigned char uchar;
typedef unsigned int uint;
typedef unsigned long ul;
typedef unsigned long long ull;

typedef FILE File;
typedef time_t Time;
// typedef void(*Callback)(void);

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

#define I8MIN INT8_MIN
#define I8MAX INT8_MAX
#define I16MIN INT16_MIN
#define I16MAX INT16_MAX
#define I32MIN INT32_MIN
#define I32MAX INT32_MAX
#define I64MIN INT64_MIN
#define I64MAX INT64_MAX

#define U8MAX UINT8_MAX
#define U16MAX UINT16_MAX
#define U32MAX UINT32_MAX
#define U64MAX UINT64_MAX

typedef u32 Epoch;

#ifdef DOGE_GFX
typedef SDL_Rect Rect;
typedef SDL_Color Color;
typedef SDL_Surface Img;
typedef SDL_Keycode Key;
#endif

typedef enum{DIR_U=0, DIR_R, DIR_D, DIR_L, DIR_NUM}Direction;

typedef union{
	bool arr[4];
	struct{
		bool U;
		bool R;
		bool D;
		bool L;
	};
	struct{
		bool D;
		bool L;
		bool U;
		bool R;
	}inverse;
}bool4;

typedef union{
	uint arr[4];
	struct{
		uint U;
		uint R;
		uint D;
		uint L;
	};
	struct{
		uint D;
		uint L;
		uint U;
		uint R;
	}inverse;
}uint4;

typedef union{
	char arr[4];
	struct{
		char U;
		char R;
		char D;
		char L;
	};
	struct{
		char D;
		char L;
		char U;
		char R;
	}inverse;
}char4;

typedef union{
	uint arr[2];
	struct{
		uint x;
		uint y;
	};
	struct{
		uint y;
		uint x;
	}inverse;
}uint2;
