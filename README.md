# BMP conversion
SZTE TTIK programtervező informatika, 2017 őszi félév, programozás alapjai tehetséggondozó beanandó feladat #2 (átdolgozva)  

This program transforms a .bmp file into shades of grey, red, green, blue, yellow, turqoise or magenta. Only works with 24 bit color depth, windows style bmp files.

Also check out the [oxidized version](https://github.com/pmarkee/bmp_transform_rust/)!

## Usage

### Building
```sh
$ make
```
Alternatively, for some debug info:
```sh
$ make debug
```

### Running
```sh
$ ./transform [BMP_FILE] [SHADE]
```
`SHADE` can be one of the following values:
- grey
- red
- green
- blue
- yellow
- turqoise
- magenta

The program will transform the input bmp file to the shade that you chose. If you type in anything else, the program will just segfault.

## How it works

A bmp file consists of 2 (or rather 3) things: a file header, a DIB header, and a bitmap. (https://en.wikipedia.org/wiki/BMP_file_format#File_structure)  
The file header and the DIB header contain information about the file itself, and the content is largely dependent on the application / operating system. See the above link for info.  
A bitmap is basically just a list of all the pixels that make up the picture. Each pixel is described by a pre-determined number of bytes, usually 3 bites for the 3 colors (blue, green, red). Each line has a so called padding at the end, to make the line length a multiple or 4 bytes.  
This is a rather easy structure to work with. The whole program consists of a few simple steps:
1. Read the input file.
2. Transform each pixel as the user has requested.
3. Write the transformed pixels to the output file.

Steps 1) and 3) are rather obvious, you just read everything from the input byte by byte, and output everything byte by byte after step 2) is done. (The header sections can just be copied without any sort of calculation.)  

Step 2) isn't that hard either. Each pixel is described by 3 bytes, aka 3 numbers between 0 and 255. (Note: the order of the colors is swapped in bmp files, so it's blue-green-red instead of red-green-blue). We simply calculate the average of these numbers. If we make all of the 3 bytes equal to this average, we get a grey pixel. So for example, if the old pixel is (60, 90, 240), a purple-ish color, then the new pixel will be (130, 130, 130), which is a dark-ish grey. (You can try this with any hex color picker, with any color, it will always produce a grey color.) If we want a different shades, we can set some of the color values to 0. For example if you we want to transform to a red shade, we will set blue and green to 0, for example (60, 90, 150) -> (130, 0, 0). If we want yellow, we will only set blue to 0, for example (60, 90, 150) -> (130, 130, 0).  

This is of course just a basic overview, for details see the link above and the source code.
