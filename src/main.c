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
	#define strlcat(_src, _dst, _len) \
		strncat(_src, _dst, _len - 1); \
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
		printf("Usage: %s <input PGM filename> [output CHR filename]\n", argv[0]);
		printf("- Missing input image\n");
		return 1;
	}
	return 0;
}

int main(
	int argc,
	char *argv[]
) {
	printf(PROGRAM_NAME " v" PROGRAM_VERSION "\n");
	printf("Created by StevenSYS\n");
	
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