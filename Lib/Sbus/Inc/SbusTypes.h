#ifndef __SbusTypes_h__
#define __SbusTypes_h__

#include <stdint.h>

#define SBUS_CONST_HEAD 0x0f

typedef struct SbusChannel {
	uint16_t _0 : 11;
	uint16_t _1 : 11;
	uint16_t _2 : 11;
	uint16_t _3 : 11;
	uint16_t _4 : 11;
	uint16_t _5 : 11;
	uint16_t _6 : 11;
	uint16_t _7 : 11;
	uint16_t _8 : 11;
	uint16_t _9 : 11;
	uint16_t _10 : 11;
	uint16_t _11 : 11;
	uint16_t _12 : 11;
	uint16_t _13 : 11;
	uint16_t _14 : 11;
	uint16_t _15 : 11;
} __attribute__((packed, aligned(1))) SbusChannel_t;

typedef struct SbusFlag {
	uint8_t d_16 : 1;
	uint8_t d_17 : 1;
	uint8_t FrameLost : 1;
	uint8_t FailSafe : 1;
	uint8_t free_0 : 1;
	uint8_t free_1 : 1;
	uint8_t free_2 : 1;
	uint8_t free_3 : 1;
} __attribute__((packed, aligned(1))) SbusFlag_t;

typedef struct SbusFrame {
	uint8_t head;
	SbusChannel_t ch;
	SbusFlag_t flag;
	uint8_t tail;
} SbusFrame_t;

#endif //__SbusTypes_h__
