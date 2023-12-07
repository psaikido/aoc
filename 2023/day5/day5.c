// https://adventofcode.com/2023/day/5
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>
#include <stdbool.h>

typedef struct {
	long dest;
	long source;
	long len;
} Range;

typedef struct {
	Range* range;
	int rangeCount;
} Map;

FILE* getFile();
int* parseSeeds(char* line, int* seedCount);
void loadMap(char* line, Map* map);


int main() 
{
	FILE *fp = getFile();
	char line[1024];
	int* seeds;
	int seedCount = 0;
	int lineCount = 0;
	
	bool seedToSoil = false;
	int seedToSoilStart = 0;
	Map mapSeedToSoil;
	mapSeedToSoil.rangeCount = 0;


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
				loadMap(line, &mapSeedToSoil);
			}
		}

		lineCount++;
	}

	// printf("seedCount %d\n", seedCount);
	// for (int i = 1; i <= seedCount; i++) {
	// 	printf("s%d %d\n", i, seeds[i]);
	// }

	for (long i = 0; i < mapSeedToSoil.rangeCount; i++) {
		printf("mapSeedToSoil: %ld, %ld, %ld\n", 
			mapSeedToSoil.range[i].dest,
			mapSeedToSoil.range[i].source,
			mapSeedToSoil.range[i].len
		);
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


void loadMap(char* line, Map* map)
{
	char* token;
	Range* range = calloc(1, sizeof(Range));
	int count = 0;

	while((token = strtok_r(line, " \n", &line)) != NULL) {
		if (count == 0) {
			range->dest = strtol(token, NULL, 10);
		}

		if (count == 1) {
			range->source = strtol(token, NULL, 10);
		}

		if (count == 2) {
			range->len = strtol(token, NULL, 10);
		}

		count++;
	}

	map->range[map->rangeCount] = *range;
	map->rangeCount++;

	// int idx = map->rangeCount - 1;
	// printf("map: %ld, %ld, %ld, %d\n", 
	// 	map->range[idx].dest, 
	// 	map->range[idx].source, 
	// 	map->range[idx].len, 
	// 	map->rangeCount);
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
