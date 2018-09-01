#include <stdio.h>
#include <string.h>

#include "bmp_tools.h"
#include "transform_tools.h"

/* Macro for determining which transform function we will use. */
#define GET_FUNCTION(color, func) \
    if(!strcmp (shade, (color))) {\
        transform_func = (func);\
    }\

int main(int argc, char** argv) {
    if (argc != 3) {
        fprintf (stderr, "Usage: ./transform [INPUT_BMP] [SHADE]\n");
        return 1;
    }

    FILE *in = fopen (argv[1], "r");
    FILE *out = fopen ("out.bmp", "w");

    const char* shade = argv[2];
    // Function pointer, will be set by the GET_FUNCTION macro to point to the
    // correct transform function.
    void (*transform_func)(bitmap* map);

    GET_FUNCTION ("grey", &grey)
    GET_FUNCTION ("red", &red)
    GET_FUNCTION ("green", &green)
    GET_FUNCTION ("blue", &blue)
    GET_FUNCTION ("turqoise", &turqoise)
    GET_FUNCTION ("yellow", &yellow)
    GET_FUNCTION ("magenta", &magenta)

    bmp_file bmp = read_bmp (in);    // Read the input file into a struct representing the bmp file.
    transform_func (&(bmp.map));     // Transform the pixels.
    write_bmp (in, out, bmp);        // Write everything into the output file.

    fclose (in);
    fclose (out);
    return 0;
}
