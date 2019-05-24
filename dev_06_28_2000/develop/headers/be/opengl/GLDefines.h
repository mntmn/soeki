#ifndef GLDEFINES_H
#define GLDEFINES_H


#define BGL_BUFFER_BIT_MASK		0xFF

#define BGL_NONE				0x0
#define BGL_ANY 				0x1
#define BGL_FASTEST 			0x2
#define BGL_HIGH_QUAILTY 		0x3

#define BGL_8_BIT 				0x100
#define BGL_15_BIT 				0x101
#define BGL_16_BIT 				0x102
#define BGL_24_BIT 				0x103
#define BGL_32_BIT 				0x104
#define BGL_48_BIT 				0x105
#define BGL_64_BIT 				0x106
#define BGL_128_BIT 			0x107

#define BGL_BIT_DEPTH_MASK		0xFFF

/* Color buffer defs */
#define BGL_COLOR_BUFFER_MASK	0xF0000
#define BGL_SINGLE 				0x10000
#define BGL_DOUBLE 				0x20000

/* Devices */
#define BGL_DEVICE_SOFTWARE			0x00000

/* Video modes */
#define BGL_WINDOWED			0x00000


/* Monitors */
/* We use the lower 8 bits for the monitor number.  */
/* Note: I only define the first 4. */
#define BGL_MONITOR_PRIMARY			0x0000
#define BGL_MONITOR_2				0x0001
#define BGL_MONITOR_3				0x0002
#define BGL_MONITOR_4				0x0003
#define BGL_MONITOR_NOT_PRIMARY		0x0100
#define BGL_MONITOR_ANY				0x0101




/* Errors */
#define BGL_NO_ERROR				0x0000
#define BGL_UNSUPORTED_COLOR_MODE	0x0001
#define BGL_UNSUPORTED_DEPTH_MODE	0x0002
#define BGL_UNSUPORTED_STENCIL_MODE	0x0004
#define BGL_UNSUPORTED_ACCUM_MODE	0x0008
#define BGL_INVALID_COMBINATION		0x0010
#define BGL_UNKNOWN_DEVICE_ID		0x0011



/* Be Extensions */
#define GL_USE_TEMP_COLOR_BE	0x7500 
#define GL_USE_TEMP_TEX_BE		0x7501 
#define GL_USE_TEMP_NORMAL_BE	0x7502 
#define GL_USE_TEX2_BE			0x7503 
#define GL_USE_TEX3_BE			0x7504 



#endif

