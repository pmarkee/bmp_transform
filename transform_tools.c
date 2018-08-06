 #include "bmp_tools.h"
#include "transform_tools.h"

/* Macros for iterating the map and setting the color values. */

#define ITER_MAP(arg) \
        uint8_t avg = 0;\
        uint64_t i = 0;\
        for (i = 0; i < (arg)->x * (arg)->y; i++) {\
            avg = (((arg)->map[i].blue) + ((arg)->map[i].green) + ((arg)->map[i].red)) / 3;\

#define SET_BLUE(map_arg, num) \
        (map_arg)->map[i].blue = (num);

#define SET_GREEN(map_arg, num) \
        (map_arg)->map[i].green = (num);

#define SET_RED(map_arg, num) \
        (map_arg)->map[i].red = (num);

#define ITER_MAP_END() }


/* Color transformation funcions. */

void transform_grey(bitmap* bmap) {
    ITER_MAP (bmap)
    SET_BLUE (bmap, avg)
    SET_GREEN (bmap, avg)
    SET_RED (bmap, avg)
    ITER_MAP_END ()
}

void transform_red(bitmap* bmap) {
    ITER_MAP (bmap)
    SET_BLUE (bmap, 0)
    SET_GREEN (bmap, 0)
    SET_RED (bmap, avg)
    ITER_MAP_END ()
}

void transform_green(bitmap* bmap) {
    ITER_MAP (bmap)
    SET_BLUE (bmap, 0)
    SET_GREEN (bmap, avg)
    SET_RED (bmap, 0)
    ITER_MAP_END ()
}

void transform_blue(bitmap* bmap) {
    ITER_MAP (bmap)
    SET_BLUE (bmap, avg)
    SET_GREEN (bmap, 0)
    SET_RED (bmap, 0)
    ITER_MAP_END ()
}

void transform_yellow(bitmap* bmap) {
    ITER_MAP (bmap)
    SET_BLUE (bmap, 0)
    SET_GREEN (bmap, avg)
    SET_RED (bmap, avg)
    ITER_MAP_END ()
}

void transform_turqoise(bitmap* bmap) {
    ITER_MAP (bmap)
    SET_BLUE (bmap, avg)
    SET_GREEN (bmap, avg)
    SET_RED (bmap, 0)
    ITER_MAP_END ()
}

void transform_magenta(bitmap* bmap) {
    ITER_MAP (bmap)
    SET_BLUE (bmap, avg)
    SET_GREEN( bmap, 0)
    SET_RED (bmap, avg)
    ITER_MAP_END ()
}
