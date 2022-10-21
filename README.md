onebit
======

Overview
--------
Convert greyscale images to 1-bit hex text files suitable for use in simple
1-bit displays such as cheap epaper displays.

White pixels will become set (1) bits and black pixels will become empty (0)
bits. For true greyscale images the cutoff is at a value of 128. The input image
can have any dimensions but the image is treated as a linear stream of data in
the output; no dimension data is encoded. Each input file will produce an
integer number of output bytes. If the number of pixels are not a multiple of 8,
trailing zero bits will make up the difference in the output.

Files are printed in the format `0xff, 0xff, ` etc. Each input file maps to a
line of the output. The output is big-endian: the first byte will become the
most significant bit.

Theoretically supported image formats from stb_image:
- JPG
- PNG
- TGA
- BMP
- PSD
- GIF
- HDR
- PIC

Build
-----
Run `make` from root directory

Installation
------------
None implmented, the resulting `onebit` binary is standalone and can be run
directly or moved to a convenient location.

Usage
-----

    onebit <infile 1> [infile2 infile3 ... infileN]

Output is printed to standard output and in the common case will need to be
redirected to the desired file.

Examples
--------
Convert icon.png to 1 bit hex codes:

    onebit icon.png > icon.c

Convert a series of files `image001.gif` to `imageXXX.gif` to 1 bit hex codes

    onebit image*.gif > image.c
