// https://adventofcode.com/2023/day/5
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>
#include <stdbool.h>

typedef struct {
	long dest[1024];
	long source[1024];
	long len[1024];
	long rangeCount;
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

	bool soilToFert = false;
	int soilToFertStart = 0;
	Map mapSoilToFert;
	mapSoilToFert.rangeCount = 0;

	bool fertToWater = false;
	int fertToWaterStart = 0;
	Map mapFertToWater;
	mapFertToWater.rangeCount = 0;

	bool waterToLight = false;
	int waterToLightStart = 0;
	Map mapWaterToLight;
	mapWaterToLight.rangeCount = 0;

	bool lightToTemp = false;
	int lightToTempStart = 0;
	Map mapLightToTemp;
	mapLightToTemp.rangeCount = 0;

	bool tempToHum = false;
	int tempToHumStart = 0;
	Map mapTempToHum;
	mapTempToHum.rangeCount = 0;

	bool humToLoc = false;
	int humToLocStart = 0;
	Map mapHumToLoc;
	mapHumToLoc.rangeCount = 0;


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
				// printf("ms2s %d: %s", lineCount, line);
				loadMap(line, &mapSeedToSoil);
			}
		}

		if (strcmp(line, "soil-to-fertilizer map:\n") == 0) {
			soilToFertStart = lineCount + 1;
			soilToFert = true;
		}

		if (soilToFert == true && lineCount >= soilToFertStart) {
			if (strcmp(line, "\n") == 0) {
				soilToFert = false;
			} else {
				// printf("mstf %d: %s", lineCount, line);
				loadMap(line, &mapSoilToFert);
			}
		}

		if (strcmp(line, "fertilizer-to-water map:\n") == 0) {
			fertToWaterStart = lineCount + 1;
			fertToWater = true;
		}

		if (fertToWater == true && lineCount >= fertToWaterStart) {
			if (strcmp(line, "\n") == 0) {
				fertToWater = false;
			} else {
				// printf("mstf %d: %s", lineCount, line);
				loadMap(line, &mapFertToWater);
			}
		}

		if (strcmp(line, "water-to-light map:\n") == 0) {
			waterToLightStart = lineCount + 1;
			waterToLight = true;
		}

		if (waterToLight == true && lineCount >= waterToLightStart) {
			if (strcmp(line, "\n") == 0) {
				waterToLight = false;
			} else {
				// printf("mstf %d: %s", lineCount, line);
				loadMap(line, &mapWaterToLight);
			}
		}

		if (strcmp(line, "light-to-temperature map:\n") == 0) {
			lightToTempStart = lineCount + 1;
			lightToTemp = true;
		}

		if (lightToTemp == true && lineCount >= lightToTempStart) {
			if (strcmp(line, "\n") == 0) {
				lightToTemp = false;
			} else {
				// printf("mstf %d: %s", lineCount, line);
				loadMap(line, &mapLightToTemp);
			}
		}

		if (strcmp(line, "temperature-to-humidity map:\n") == 0) {
			tempToHumStart = lineCount + 1;
			tempToHum = true;
		}

		if (tempToHum == true && lineCount >= tempToHumStart) {
			if (strcmp(line, "\n") == 0) {
				tempToHum = false;
			} else {
				// printf("mstf %d: %s", lineCount, line);
				loadMap(line, &mapTempToHum);
			}
		}

		if (strcmp(line, "humidity-to-location map:\n") == 0) {
			humToLocStart = lineCount + 1;
			humToLoc = true;
		}

		if (humToLoc == true && lineCount >= humToLocStart) {
			if (strcmp(line, "\n") == 0) {
				humToLoc = false;
			} else {
				// printf("mstf %d: %s", lineCount, line);
				loadMap(line, &mapHumToLoc);
			}
		}

		lineCount++;
	}

	printf("seedCount %d\n", seedCount);
	for (int i = 1; i <= seedCount; i++) {
		printf("s%d %d\n", i, seeds[i]);
	}

	for (long i = 0; i < mapSeedToSoil.rangeCount; i++) {
		printf("mapSeedToSoil: %ld, %ld, %ld\n", 
			mapSeedToSoil.dest[i],
			mapSeedToSoil.source[i],
			mapSeedToSoil.len[i]
		);
	}

	for (long i = 0; i < mapSoilToFert.rangeCount; i++) {
		printf("mapSoilToFert: %ld, %ld, %ld\n", 
			mapSoilToFert.dest[i],
			mapSoilToFert.source[i],
			mapSoilToFert.len[i]
		);
	}

	for (long i = 0; i < mapFertToWater.rangeCount; i++) {
		printf("mapFertToWater: %ld, %ld, %ld\n", 
			mapFertToWater.dest[i],
			mapFertToWater.source[i],
			mapFertToWater.len[i]
		);
	}

	for (long i = 0; i < mapWaterToLight.rangeCount; i++) {
		printf("mapWaterToLight: %ld, %ld, %ld\n", 
			mapWaterToLight.dest[i],
			mapWaterToLight.source[i],
			mapWaterToLight.len[i]
		);
	}

	for (long i = 0; i < mapLightToTemp.rangeCount; i++) {
		printf("mapLightToTemp: %ld, %ld, %ld\n", 
			mapLightToTemp.dest[i],
			mapLightToTemp.source[i],
			mapLightToTemp.len[i]
		);
	}

	for (long i = 0; i < mapTempToHum.rangeCount; i++) {
		printf("mapTempToHum: %ld, %ld, %ld\n", 
			mapTempToHum.dest[i],
			mapTempToHum.source[i],
			mapTempToHum.len[i]
		);
	}

	for (long i = 0; i < mapHumToLoc.rangeCount; i++) {
		printf("mapHumToLoc: %ld, %ld, %ld\n", 
			mapHumToLoc.dest[i],
			mapHumToLoc.source[i],
			mapHumToLoc.len[i]
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
	int lineCount = 0;
	long idx = map->rangeCount;

	while((token = strtok_r(line, " \n", &line)) != NULL) {
		if (lineCount == 0) {
			map->dest[idx] = strtol(token, NULL, 10);
		}

		if (lineCount == 1) {
			map->source[idx] = strtol(token, NULL, 10);
		}

		if (lineCount == 2) {
			map->len[idx] = strtol(token, NULL, 10);
		}

		lineCount++;
	}

	// printf("map: %ld, %ld, %ld, %ld\n", 
	// 	map->dest[idx], 
	// 	map->source[idx], 
	// 	map->len[idx], 
	// 	map->rangeCount
	// );

	map->rangeCount++;
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
