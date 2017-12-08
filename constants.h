#ifndef CONSTANT_H
#define CONSTANT_H

#define MAP_MEMORY_BASE         0x10000000
#define MAP_MEMORY_LENGTH       0x00015400

#define MAP_LCD_BASE            0x10015400
#define MAP_LCD_LENGTH          0x0000000C

#define MAP_ROM_BASE            0x1001540C
#define MAP_ROM_LENGTH          0x00009600



#define MAP_VIDEO_MEMORY_OFF    0x00002800
#define MAP_VIDEO_MEMORY_BASE   MAP_MEMORY_BASE + MAP_VIDEO_MEMORY_OFF

#define IMG_WIDTH                320
#define IMG_HEIGHT               240

#define IMG_SIZE                IMG_WIDTH * IMG_HEIGHT

#define PXL_4_WHITE             0xFFFFFFFF


#endif // CONSTANT_H
