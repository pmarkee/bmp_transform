#include <stdio.h>
#include <string.h>

#include "bmp_tools.h"
#include "transform_tools.h"

/* Macro for determining which transform function we will use. */
#define SET_TRANSFORM_FUNC(input, color, func) \
    if(!strcmp((input), (color))) {\
        transform_func = (func);\
    }\

int main(int argc, char** argv) {
    if (argc != 3) {
        fprintf(stderr, "Usage: ./transform [INPUT_BMP] [SHADE]\n");
        return 1;
    }

    FILE *in = fopen(argv[1], "r");
    FILE *out = fopen("out.bmp", "w");

    const char* shade = argv[2];
    // Function pointer, will be set by the SET_TRANSFORM_FUNC macro to point to the
    // correct transform function.
    void (*transform_func)(bitmap* map);

    SET_TRANSFORM_FUNC(shade, "grey", &transform_grey)
    SET_TRANSFORM_FUNC(shade, "red", &transform_red)
    SET_TRANSFORM_FUNC(shade, "green", &transform_green)
    SET_TRANSFORM_FUNC(shade, "blue", &transform_blue)
    SET_TRANSFORM_FUNC(shade, "turqoise", &transform_turqoise)
    SET_TRANSFORM_FUNC(shade, "yellow", &transform_yellow)
    SET_TRANSFORM_FUNC(shade, "magenta", &transform_magenta)

    bmp_file bmp = read_bmp(in);    // Read the input file into a struct representing the bmp file.
    transform_func(&(bmp.map));     // Transform the pixels.
    write_bmp(in, out, bmp);        // Write everything into the output file.

    fclose(in);
    fclose(out);
    return 0;
}
