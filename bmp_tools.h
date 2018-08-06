#ifndef BMP_TOOLS_H
#define BMP_TOOLS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

/* Type to represent pixels.*/
typedef struct {
    uint8_t red;
    uint8_t green;
    uint8_t blue;
} pixel;

/* Type to represent bitmap file headers.*/
typedef struct {
    uint16_t signature;
    uint64_t other_bytes;
    uint32_t offset;
} bitmap_file_header;

/* Type to represent bitmaps.*/
typedef struct {
    uint32_t x;
    uint32_t y;
    pixel *map;
} bitmap;

/* Type to represent BMP files.*/
typedef struct {
    bitmap_file_header header;
    bitmap map;
} bmp_file;

pixel read_pixel(FILE* in);
bitmap_file_header read_bitmap_file_header(FILE* in);
bitmap read_bitmap(FILE* in, bitmap_file_header header);
bmp_file read_bmp(FILE* in);

void write_bitmap_file_header(FILE* out, bitmap_file_header header);
void write_bitmap(FILE* out, bitmap bmap);
void write_bmp(FILE* in, FILE* out, bmp_file bmp);
void copy_dib_header(FILE* in, FILE* out, uint32_t offset);
#endif /* IMAGE_FUNCTIONS_H */
