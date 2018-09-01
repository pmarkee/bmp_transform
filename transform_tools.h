#ifndef TRANSFORM_TOOLS_H
#define TRANSFORM_TOOLS_H

#include "bmp_tools.h"

#define TRANSFORM_FUNCTION(color) void color(bitmap* bmap)

/* Color transformation functions. */

void grey(bitmap* bmap);
void red(bitmap* bmap);
void green(bitmap* bmap);
void blue(bitmap* bmap);
void turqoise(bitmap* bmap);
void yellow(bitmap* bmap);
void magenta(bitmap* bmap);

#endif /* TRANSFORM_TOOLS_H */
