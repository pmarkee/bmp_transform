#include "bmp_tools.h"

bitmap_file_header read_bitmap_file_header(FILE* in) {
    /* Read the bitmap file header from a bmp file. */
    bitmap_file_header ret;

    fread (&(ret.signature), 2, 1, in);
    fread (&(ret.other_bytes), 8, 1, in);
    fread (&(ret.offset), 4, 1, in);

#ifdef DEBUG
    printf ("----- -----------\nReading bmp file\n----------------\n");
    printf ("signature: %#x\nother bytes: %#x\noffset: %#x\n", ret.signature, ret.other_bytes, ret.offset);
#endif

    return ret;
}

bitmap read_bitmap (FILE* in, bitmap_file_header header) {
    /* Read the bitmap from a BMP file. */
    bitmap ret;
    fseek (in, 0x12, SEEK_SET);
    fread (&(ret.x), 4, 1, in);
    fread (&(ret.y), 4, 1, in);

    ret.map = (pixel*)malloc (ret.x * ret.y * sizeof(pixel));

    uint8_t padding_size = ret.x * 3 % 4;

#ifdef DEBUG
    printf ("-----------\nBitmap info\n-----------\n");
    printf ("x: %d\ny: %d\n", ret.x, ret.y);
    printf ("padding_size: %d\n", padding_size);
#endif

    fseek (in, header.offset, SEEK_SET);
    for (int i = 0; i < ret.y; i++) {
        for (int j = 0; j < ret.x; j++) {
            (ret.map + i * ret.x + j) -> blue = fgetc (in);
            (ret.map + i * ret.x + j) -> green = fgetc (in);
            (ret.map + i * ret.x + j) -> red = fgetc (in);
        }
        fseek (in, padding_size, SEEK_CUR);
    }

    return ret;
}

bmp_file read_bmp(FILE* in) {
    /* Read a bmp input file. */
    bmp_file ret;
    ret.header = read_bitmap_file_header (in);
    ret.map = read_bitmap (in, ret.header);

    return ret;
}

void write_bitmap_file_header(FILE* out, bitmap_file_header header) {
    /* Write a bitmap header to a file. */
    fseek (out, 0, SEEK_SET);

    fwrite (&(header.signature), 2, 1, out);    // Write the header first.
    fwrite (&(header.other_bytes), 8, 1, out);  // Then the bytes we didn't use.
    fwrite (&(header.offset), 4, 1, out);       // Then the offset.
}

void write_bitmap(FILE* out, bitmap bmap) {
    /* Write a bitmap to a file. */
    uint8_t padding_size = bmap.x * 3 % 4;

    for (int i = 0; i < bmap.y; i++) {
        for (int j = 0; j < bmap.x; j++) {
            fputc ((bmap.map + i * bmap.x + j)->blue, out);
            fputc ((bmap.map + i * bmap.x + j)->green, out);
            fputc ((bmap.map + i * bmap.x + j)->red, out);
        }
        fwrite (0, 1, padding_size, out);    // Write 'padding_size' empty bytes.
    }

    free (bmap.map);
}

void copy_dib_header(FILE* in, FILE* out, uint32_t offset) {
    /* Copy the dib header to the output file. */
    fseek (in, 0x0e, SEEK_SET);
    for (int pos = 0x0e; pos < offset; pos++) {
        fputc (fgetc (in), out);
    }
}

void write_bmp(FILE* in, FILE* out, bmp_file bmp) {
    /* Write out the bmp file into the output file. */
#ifdef DEBUG
    printf ("----------------\nWriting bmp file\n----------------\n");
    printf ("Header:\nsignature: %#x\noffset: %#x\n", bmp.header.signature, bmp.header.offset);
#endif

    write_bitmap_file_header (out, bmp.header);
    copy_dib_header (in, out, bmp.header.offset);
    write_bitmap (out, bmp.map);
}
