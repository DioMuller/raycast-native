#ifndef _CONSTANTS_H_

#define _CONSTANTS_H_

typedef char BOOL;
typedef char TILE;
typedef char DIRECTION;

#define NONE		0
#define LEFT	   -1
#define RIGHT		1
#define BACK	   -1
#define FRONT		1


#define FALSE	0
#define TRUE	1

#define PI				3.14159265
#define TWO_PI			6.28318530
#define RAD				(PI / 180)

#define TILE_SIZE		64
#define MAP_NUM_ROWS	13
#define MAP_NUM_COLS	20

#define MINIMAP_SCALE_FACTOR 1.0f

#define WINDOW_WIDTH	(MAP_NUM_COLS * TILE_SIZE)
#define WINDOW_HEIGHT	(MAP_NUM_ROWS * TILE_SIZE)

#define FOV_ANGLE (60 * (PI / 180))

#define NUM_RAYS WINDOW_WIDTH

#define FPS 30
#define FRAME_TIME_LENGTH 1000/FPS

#endif // !_CONSTANTS_H_