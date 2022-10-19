#include <stdlib.h>
#include <error.h>
#include <stdio.h>
#include <string.h>

#define STB_IMAGE_IMPLEMENTATION
#define STBI_FAILURE_USERMSG
#include "stb_image.h"

#define STBI_GREYSCALE 1

// Swap an existing extension for ".c"
// Caller must free the return value
char *outfile(const char *infile) {
	int n = strlen(infile);
	const char *ext = ".c";
	// We will append to the end if we don't find a final dot
	int dotpos = n;
	// Ignore initial dots so as to treat "dotfile" style names appropriately
	for (int i = n-1; i > 0; i--) {
		if (infile[i] == '.') {
			dotpos = i;
			break;
		}
	}
	char *out = malloc(dotpos + strlen(ext) + 1);
	memcpy(out, infile, dotpos);
	memcpy(out + dotpos, ext, strlen(ext) + 1);
	return out;
}

// Packs a buffer of 8 bytes into a single byte
uint8_t pack(const unsigned char in[static 8]) {
	uint8_t out = 0;
	for (int i = 0; i < 8; i++) {
		if (in[i]) {
			out |= 1 << (7 - i);
			//out |= 1 << i;
		}
	}
	return out;
}

int main(int argc, char *argv[])
{
	if (argc < 2) {
		fprintf(stderr, "Usage: bit1 <input filename> [...other input filenames]\n");
		exit(EXIT_FAILURE);
	}

	for (char **filename = &argv[1]; filename < &argv[argc]; filename++) {
		int x,y,n;
		unsigned char *data = stbi_load(*filename, &x, &y, &n, STBI_GREYSCALE);
		if (!data) {
			// Failed to load image
			error(EXIT_FAILURE, 0, "Failed to load image: %s", stbi_failure_reason());
		}

		int pixels = x * y;
		int finalbytes = pixels/8;
		if (pixels % 8 != 0) {
			// Add some space if we don't have an even number of bytes
			finalbytes += 1;
		}

		unsigned char *begin = data;
		unsigned char *end = data + x*y;
		unsigned char *p = begin;
		unsigned char buffer[8] = {};
		char *outname = outfile(*filename);
		FILE *file = fopen(outname, "w");
		free(outname);


		for (int j = 0; j < finalbytes; j++) {
			memset(buffer,0,8);
			for (int i = 0; i < 8; i++) {
				if (p >= end) break;
				buffer[i] = *p;
				p++;
			}
			fprintf(file, "%#x, ", pack(buffer));
		}

		// Write result to file with name from outfile
		fclose(file);

		stbi_image_free(data);
	}
}
