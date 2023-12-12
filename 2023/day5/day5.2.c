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
	long delta[1024];
	long rangeCount;
} Map;

typedef struct {
	long start;
	long range;
} SeedPair;

FILE* getFile();
long* parseSeeds(char* line, long* seedCount);
void parseForMap(FILE** fp, Map* map, char* target);
void loadMap(char* line, Map* map);
long getSourceNum(Map* map, long i);
int comparator (const void* a, const void* b);


int main() 
{
	FILE *fp = getFile();
	char line[1024];
	long* seeds;
	SeedPair* seedPairs = calloc(4, sizeof(SeedPair));
	long seedCount = 0;
	long lineCount = 0;
	
	Map mapSeedToSoil;
	mapSeedToSoil.rangeCount = 0;

	Map mapSoilToFert;
	mapSoilToFert.rangeCount = 0;

	Map mapFertToWater;
	mapFertToWater.rangeCount = 0;

	Map mapWaterToLight;
	mapWaterToLight.rangeCount = 0;
	
	Map mapLightToTemp;
	mapLightToTemp.rangeCount = 0;
	
	Map mapTempToHum;
	mapTempToHum.rangeCount = 0;

	Map mapHumToLoc;
	mapHumToLoc.rangeCount = 0;

	while (fgets(line, sizeof(line), fp)) {
		if (lineCount++ == 0) {
			seeds = parseSeeds(line, &seedCount);
		} else {
			break;
		}
	}

	// for (long i = 1; i <= seedCount; i++) {
	// 	printf("seed %ld\n", seeds[i]);
	// }

	parseForMap(&fp, &mapSeedToSoil, "seed-to-soil map:\n");
	// for (long i = 0; i < mapSeedToSoil.rangeCount; i++) {
	// 	printf("mapSeedToSoil: %ld, %ld, %ld\n", 
	// 		mapSeedToSoil.dest[i],
	// 		mapSeedToSoil.source[i],
	// 		mapSeedToSoil.len[i]
	// 	);
	// }

	parseForMap(&fp, &mapSoilToFert, "soil-to-fertilizer map:\n");
	// for (long i = 0; i < mapSoilToFert.rangeCount; i++) {
	// 	printf("mapSoilToFert: %ld, %ld, %ld\n", 
	// 		mapSoilToFert.dest[i],
	// 		mapSoilToFert.source[i],
	// 		mapSoilToFert.len[i]
	// 	);
	// }

	parseForMap(&fp, &mapFertToWater, "fertilizer-to-water map:\n");
	// for (long i = 0; i < mapFertToWater.rangeCount; i++) {
	// 	printf("mapFertToWater: %ld, %ld, %ld\n", 
	// 		mapFertToWater.dest[i],
	// 		mapFertToWater.source[i],
	// 		mapFertToWater.len[i]
	// 	);
	// }

	parseForMap(&fp, &mapWaterToLight, "water-to-light map:\n");
	// for (long i = 0; i < mapWaterToLight.rangeCount; i++) {
	// 	printf("mapWaterToLight: %ld, %ld, %ld\n", 
	// 		mapWaterToLight.dest[i],
	// 		mapWaterToLight.source[i],
	// 		mapWaterToLight.len[i]
	// 	);
	// }
	
	parseForMap(&fp, &mapLightToTemp, "light-to-temperature map:\n");
	// for (long i = 0; i < mapLightToTemp.rangeCount; i++) {
	// 	printf("mapLightToTemp: %ld, %ld, %ld\n", 
	// 		mapLightToTemp.dest[i],
	// 		mapLightToTemp.source[i],
	// 		mapLightToTemp.len[i]
	// 	);
	// }

	parseForMap(&fp, &mapTempToHum, "temperature-to-humidity map:\n");
	// for (long i = 0; i < mapTempToHum.rangeCount; i++) {
	// 	printf("mapTempToHum: %ld, %ld, %ld, %ld\n", 
	// 		mapTempToHum.dest[i],
	// 		mapTempToHum.source[i],
	// 		mapTempToHum.len[i],
	// 		mapTempToHum.delta[i]
	// 	);
	// }

	parseForMap(&fp, &mapHumToLoc, "humidity-to-location map:\n");
	// for (long i = 0; i < mapHumToLoc.rangeCount; i++) {
	// 	printf("mapHumToLoc: %ld, %ld, %ld, %ld\n", 
	// 		mapHumToLoc.dest[i],
	// 		mapHumToLoc.source[i],
	// 		mapHumToLoc.len[i],
	// 		mapHumToLoc.delta[i]
	// 	);
	// }

	long seed = '\0';
	long soil = '\0';
	long fert = '\0';
	long water = '\0';
	long light = '\0';
	long temp = '\0';
	long hum = '\0';
	long loc = '\0';
	long lowest = 1000000000;
	long seedPairCount = 0;

	for (long i = 1; i <= seedCount; i++) {
		if (i % 2 == 0) {
			seedPairs[seedPairCount].range = seeds[i];
			seedPairCount++;
		} else {
			seedPairs[seedPairCount].start = seeds[i];
		}
	}

	// qsort(seedPairs, seedPairCount, sizeof(SeedPair), comparator);

	// the lowest location number can be obtained from
	// seed number 82, which corresponds to soil 84, fertilizer 84, water
	// 84, light 77, temperature 45, humidity 46, and location 46. So, the
	// lowest location number is 46.

	// long s;
	// long e;
	// for (long i = 0; i < seedPairCount; i++) {
	// 	s = seedPairs[i].start;
	// 	e = s + seedPairs[i].range - 1;
	// 	printf("range start: %ld, end %ld\n", s, e);
	// }

	for (loc = 0; loc < 104070864; loc++) {
		// printf("i: %ld\n", loc);

		hum = getSourceNum(&mapHumToLoc, loc);
		// printf("hum: %ld\n", hum);

		temp = getSourceNum(&mapTempToHum, hum);
		// printf("temp: %ld\n", temp);

		light = getSourceNum(&mapLightToTemp, temp);
		// printf("light: %ld\n", light);

		water = getSourceNum(&mapWaterToLight, light);
		// printf("water: %ld\n", water);

		fert = getSourceNum(&mapFertToWater, water);
		// printf("fert: %ld\n", fert);

		soil = getSourceNum(&mapSoilToFert, fert);
		// printf("soil: %ld\n", soil);

		seed = getSourceNum(&mapSeedToSoil, soil);

		for (long j = 0; j < seedPairCount; j++) {
			if (seed >= seedPairs[j].start
			&& seed < seedPairs[j].start + seedPairs[j].range - 1) {
				printf("loc: %ld\n", loc);
				printf("hum: %ld\n", hum);
				printf("temp: %ld\n", temp);
				printf("light: %ld\n", light);
				printf("water: %ld\n", water);
				printf("fert: %ld\n", fert);
				printf("soil: %ld\n", soil);
				printf("seed: %ld\n", seed);

				if (loc < lowest) {
					lowest = loc;
				}

				printf("lowest: %ld\n\n", loc);
				exit(0);
			}
		}

		// printf("\n");
	}

	return 0;
}


long getSourceNum(Map* map, long idx)
{
	for (long i = 0; i < map->rangeCount; i++) {
		long delta = map->source[i] - map->dest[i];

		if (idx >= map->dest[i] 
		&& idx <= (map->dest[i] + map->len[i])) {
			map->delta[i] = delta;
			return idx + delta;
		}
	}

	return idx;
}


FILE* getFile()
{
	char filename[100];
	strcpy (filename, getenv("HOME"));
	// strcat (filename, "/code/aoc/2023/day5/example.txt");
	strcat (filename, "/code/aoc/2023/day5/input.txt");

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


long* parseSeeds(char* line, long* seedCount)
{
	char* token;
	long count = 0;
	long* seeds = calloc(1024, sizeof(long));
	long* ptr;

	while((token = strtok_r(line, " \n", &line)) != NULL) {
		if (count > 0) {
			seeds[count] = strtol(token, NULL, 10);
		}

		count++;
	}

	*seedCount = count - 1;
	ptr = seeds;
	return ptr;
}


void parseForMap(FILE** fp, Map* map, char* target)
{
	char line[1024];
	bool b_found = false;
	int start = 0;
	long lineCount = 0;

	// printf("t: %s\n", target);
	while (fgets(line, sizeof(line), *fp)) {
		if (strcmp(line, target) == 0) {
			start = lineCount + 1;
			b_found = true;
		}

		if (b_found == true && lineCount >= start) {
			if (strcmp(line, "\n") == 0) {
				b_found = false;
			} else {
				loadMap(line, map);
			}
		}

		lineCount++;
	}

	rewind(*fp);
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


int comparator (const void* a, const void* b)
{
    SeedPair arg1 = *(const SeedPair*)a;
    SeedPair arg2 = *(const SeedPair*)b;

	if (arg1.start < arg2.start) return -1;
	if (arg1.start > arg2.start) return 1;

	return 0;
}
