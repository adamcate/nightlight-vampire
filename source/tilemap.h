#ifndef TILEMAP_H
#define TILEMAP_H

#include <stdint.h>

/**   @brief Encodes information about tile behavior
 * 
 */
typedef enum{
    TILE_SOLID,
    TILE_TRANSPARENT,
    TILE_DEATH,
    TILE_FINISH
}tile_type;


// data is encoded as follows: N - page number, T - tile index, P - palette index, C - tile behavior, M - left-right mirroring
//
// NNTTTTPPPPCCCCCM
typedef uint16_t tile;

#define T_GET_PG(tile)				((tile & ((1 << 2) - 1)))
#define T_GET_INDEX(tile)			((tile & (((1 << 4) - 1) << 2)) >> 2)
#define T_GET_PALETTE(tile)			((tile & (((1 << 4) - 1) << 6)) >> 6)
#define T_GET_TYPE(tile)			((tile & (((1 << 5) - 1) << 10)) >> 10)
#define T_GET_MIRROR(tile)			((tile & (((1 << 1) - 1) << 15)) >> 15)

#define T_SET_PG(tile,page)			tile = ((tile & (~0x0003)) | page)
#define T_SET_INDEX(tile,index)		tile = ((tile & (~0x003C)) | (index << 2))
#define T_SET_PALETTE(tile,palette)	tile = ((tile & (~0x03C0)) | (palette << 6))
#define T_SET_TYPE(tile,type)		tile = ((tile & (~0x7C00)) | (type << 10))
#define T_SET_MIRROR(tile,mirrored) tile = ((tile & (~0x8000)) | (mirrored << 15))

#define LEVEL_MAX_WIDTH 100
#define LEVEL_MAX_HEIGHT 100

// the array for the current level in memory
extern tile level_map[LEVEL_MAX_WIDTH][LEVEL_MAX_HEIGHT];
// extern bool collision_map[LEVEL_MAX_WIDTH][LEVEL_MAX_HEIGHT];



#endif