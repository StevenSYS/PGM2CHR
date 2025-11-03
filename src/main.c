/*
	MIT License
	
	Copyright (c) 2025 StevenSYS
	
	Permission is hereby granted, free of charge, to any person obtaining a copy
	of this software and associated documentation files (the "Software"), to deal
	in the Software without restriction, including without limitation the rights
	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
	copies of the Software, and to permit persons to whom the Software is
	furnished to do so, subject to the following conditions:
	
	The above copyright notice and this permission notice shall be included in all
	copies or substantial portions of the Software.
	
	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
	SOFTWARE.
*/

#include <stdio.h>
#include <string.h>

#include "progInfo.h"
#include "chr.h"

static char inputFilename[LENGTH_FILENAME];
static char outputFilename[LENGTH_FILENAME];

static chr_t chr;

#ifdef MISSING_L_FUNCS
	#define strlcpy(_src, _dst, _len) \
		strncpy(_src, _dst, _len - 1); \
		_src[sizeof(_src) - 1] = 0;
#endif

char loadArgs(
	int argc,
	char *argv[]
) {
	if (argc > 1) {
		if (argc > 2) {
			strlcpy(
				outputFilename,
				argv[2],
				LENGTH_FILENAME
			);
		} else {
			strlcpy(
				outputFilename,
				DEFAULT_OUTPUTFILE,
				LENGTH_FILENAME
			);
		}
		
		strlcpy(
			inputFilename,
			argv[1],
			LENGTH_FILENAME
		);
	} else {
		printf("- Missing input image\n");
		printf("Usage: %s <input PGM filename> [output CHR filename]\n", argv[0]);
		return 1;
	}
	return 0;
}

int main(
	int argc,
	char *argv[]
) {
	printf(PROGRAM_NAME " v" PROGRAM_VERSION "\n");
	printf("Created by StevenSYS - 2025\n");
	
	printf("- Loading arguments\n");
	
	if (loadArgs(argc, argv)) {
		return 1;
	}
	
	printf("- Loaded arguments\n");
	
	printf("- Input: \"%s\"\n", inputFilename);
	printf("- Output: \"%s\"\n", outputFilename);
	
	printf("- Converting PGM file to CHR tile set\n");
	
	if (chr_pgmToCHR(&chr, inputFilename)) {
		return 1;
	}
	
	printf("- Conversion complete\n");
	
	printf("- Creating CHR file\n");
	
	if (chr_toFile(chr, outputFilename)) {
		return 1;
	}
	
	printf("- Created CHR file\n");
	return 0;
}