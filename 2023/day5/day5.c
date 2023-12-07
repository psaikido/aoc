// https://adventofcode.com/2023/day/5
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>
#include <stdbool.h>

FILE* getFile();
int* parseSeeds(char* line, int* seedCount);


int main() 
{
	FILE *fp = getFile();
	char line[1024];
	int* seeds;
	int seedCount = 0;
	int lineCount = 0;
	
	bool seedToSoil = false;
	int seedToSoilStart = 0;

	while (fgets(line, sizeof(line), fp)) {
		if (lineCount == 0) {
			seeds = parseSeeds(line, &seedCount);
		}

		if (strcmp(line, "seed-to-soil map:\n") == 0) {
			seedToSoilStart = lineCount + 1;
			seedToSoil = true;
		}

		if (seedToSoil == true && lineCount >= seedToSoilStart) {
			if (strcmp(line, "\n") == 0) {
				seedToSoil = false;
			} else {
				printf("%d: %s", lineCount, line);
			}
		}

		lineCount++;
	}

	printf("seedCount %d\n", seedCount);
	for (int i = 1; i <= seedCount; i++) {
		printf("s%d %d\n", i, seeds[i]);
	}

	return 0;
}


int* parseSeeds(char* line, int* seedCount)
{
	char* token;
	int count = 0;
	int* seeds = calloc(1024, sizeof(int));
	int* ptr;

	while((token = strtok_r(line, " \n", &line)) != NULL) {
		if (count > 0) {
			seeds[count] = (int)strtol(token, NULL, 10);
		}

		count++;
	}

	*seedCount = count - 1;
	ptr = seeds;
	return ptr;
}


FILE* getFile()
{
	char filename[100];
	strcpy (filename, getenv("HOME"));
	strcat (filename, "/code/aoc/2023/day5/example.txt");
	// strcat (filename, "/code/aoc/2023/day5/input.txt");

	FILE *fp = NULL;
	
	errno = 0;
	fp = fopen(filename, "r");

	if (fp == NULL) {
		fprintf(stderr, "Error opening %s for reading, errno: %d\n", filename, errno);
		exit(1);
	} else {
		return fp;
	}
}
