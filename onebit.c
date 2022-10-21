#include <error.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STB_IMAGE_IMPLEMENTATION
#define STBI_FAILURE_USERMSG
#include "stb_image.h"

#define STBI_GREYSCALE 1

// Packs a buffer of 8 bytes into a single byte
uint8_t pack(const unsigned char in[static 8]) {
	uint8_t out = 0;
	for (int i = 0; i < 8; i++) {
		if (in[i]) {
			out |= 1 << (7 - i);
		}
	}
	return out;
}

int main(int argc, char *argv[])
{
	if (argc < 2) {
		fprintf(stderr, "Usage: onebit <input filename> [...other input filenames]\n");
		exit(EXIT_FAILURE);
	}

	// Iterate over input files
	for (char **filename = &argv[1]; filename < &argv[argc]; filename++) {
		// Load image
		int x,y,n;
		unsigned char *data = stbi_load(*filename, &x, &y, &n, STBI_GREYSCALE);
		if (!data) {
			// Failed to load image
			error(EXIT_FAILURE, 0, "Failed to load image: %s", stbi_failure_reason());
		}

		int inbytes = x * y;
		int outbytes = inbytes/8;
		// Round up instead of down if our pixels aren't a multiple of 8
		if (inbytes % 8 != 0) outbytes += 1;

		unsigned char *p = data;
		unsigned char *end = data + inbytes;
		unsigned char buffer[8];
		for (int j = 0; j < outbytes; j++) {
			memset(buffer,0,8);
			// Fill the buffer only if we have remaining bytes to read
			for (int i = 0; i < 8; i++) {
				if (p >= end) break;
				buffer[i] = *p;
				p++;
			}
			printf("0x%.2x, ", pack(buffer));
		}
		printf("\n");

		// Cleanup
		stbi_image_free(data);
	}
}
