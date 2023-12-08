// https://adventofcode.com/2023/day/5 part 2
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>
#include <stdbool.h>

typedef struct {
	unsigned long dest[2048];
	unsigned long source[2048];
	unsigned long len[2048];
	unsigned long rangeCount;
} Map;

FILE* getFile();
unsigned long* parseSeeds(char* line, unsigned long* seedCount);
void loadMap(char* line, Map* map);
unsigned long findDest(unsigned long trav, unsigned long dest, unsigned long source, unsigned long len);


int main() 
{
	FILE *fp = getFile();
	char line[2048];
	unsigned long* seeds;
	unsigned long seedCount = 0;
	unsigned long lineCount = 0;
	
	bool seedToSoil = false;
	unsigned long seedToSoilStart = 0;
	Map mapSeedToSoil;
	mapSeedToSoil.rangeCount = 0;

	bool soilToFert = false;
	unsigned long soilToFertStart = 0;
	Map mapSoilToFert;
	mapSoilToFert.rangeCount = 0;

	bool fertToWater = false;
	unsigned long fertToWaterStart = 0;
	Map mapFertToWater;
	mapFertToWater.rangeCount = 0;

	bool waterToLight = false;
	unsigned long waterToLightStart = 0;
	Map mapWaterToLight;
	mapWaterToLight.rangeCount = 0;

	bool lightToTemp = false;
	unsigned long lightToTempStart = 0;
	Map mapLightToTemp;
	mapLightToTemp.rangeCount = 0;

	bool tempToHum = false;
	unsigned long tempToHumStart = 0;
	Map mapTempToHum;
	mapTempToHum.rangeCount = 0;

	bool humToLoc = false;
	unsigned long humToLocStart = 0;
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

	// printf("seedCount %ld\n", seedCount);
	unsigned long soil = '\0';
	unsigned long fert = '\0';
	unsigned long water = '\0';
	unsigned long light = '\0';
	unsigned long temp = '\0';
	unsigned long hum = '\0';
	unsigned long loc = '\0';
	unsigned long totals[seedCount];

	for (unsigned long i = 1; i <= seedCount; i++) {
		printf("seed %ld\n", seeds[i]);

		for (unsigned long j = 0; j < mapSeedToSoil.rangeCount; j++) {
			if ((soil = findDest(
				seeds[i], 
				mapSeedToSoil.dest[j],
				mapSeedToSoil.source[j],
				mapSeedToSoil.len[j]
			)) != '\0') {
				break;
			};
		}

		if (soil == '\0') {
			soil = seeds[i];
		}

		// printf("soil: %ld\n", soil);

		for (unsigned long k = 0; k < mapSoilToFert.rangeCount; k++) {
			if ((fert = findDest(
				soil,
				mapSoilToFert.dest[k],
				mapSoilToFert.source[k],
				mapSoilToFert.len[k]
			)) != '\0') {
				break;
			};
		}

		if (fert == '\0') {
			fert = soil;
		}

		// printf("fertilizer: %ld\n", fert);

		for (unsigned long l = 0; l < mapFertToWater.rangeCount; l++) {
			if ((water = findDest(
				fert,
				mapFertToWater.dest[l],
				mapFertToWater.source[l],
				mapFertToWater.len[l]
			)) != '\0') {
				break;
			};
		}

		if (water == '\0') {
			water = fert;
		}

		// printf("water: %ld\n", water);

		for (unsigned long m = 0; m < mapWaterToLight.rangeCount; m++) {
			if ((light = findDest(
				water,
				mapWaterToLight.dest[m],
				mapWaterToLight.source[m],
				mapWaterToLight.len[m]
			)) != '\0') {
				break;
			};
		}

		if (light == '\0') {
			light = water;
		}

		// printf("light: %ld\n", light);

		for (unsigned long n = 0; n < mapLightToTemp.rangeCount; n++) {
			if ((temp = findDest(
				light,
				mapLightToTemp.dest[n],
				mapLightToTemp.source[n],
				mapLightToTemp.len[n]
			)) != '\0') {
				break;
			};
		}

		if (temp == '\0') {
			temp = light;
		}

		// printf("temp: %ld\n", temp);

		for (unsigned long o = 0; o < mapTempToHum.rangeCount; o++) {
			if ((hum = findDest(
				temp,
				mapTempToHum.dest[o],
				mapTempToHum.source[o],
				mapTempToHum.len[o]
			)) != '\0') {
				break;
			};
		}

		if (hum == '\0') {
			hum = temp;
		}

		// printf("hum: %ld\n", hum);

		for (unsigned long p = 0; p < mapHumToLoc.rangeCount; p++) {
			if ((loc = findDest(
				hum,
				mapHumToLoc.dest[p],
				mapHumToLoc.source[p],
				mapHumToLoc.len[p]
			)) != '\0') {
				break;
			};
		}

		if (loc == '\0') {
			loc = hum;
		}

		printf("loc: %ld\n", loc);
		totals[i] = loc;

		// printf("\n");
	}

	unsigned long winner = 10000000;

	for (unsigned long i = 1; i <= seedCount; i++) {
		if (totals[i] < winner) {
			winner = totals[i];
		}
	}

	printf("the winner is %ld\n", winner);

	free(seeds);
	return 0;
}


unsigned long* parseSeeds(char* line, unsigned long* seedCount)
{
	char* token;
	unsigned long pairCount = 0;
	unsigned long localSeedCount = 0;
	unsigned long localRangeCount = 0;
	unsigned long* pairs = malloc(sizeof(unsigned long*) * 100000);
	unsigned long* seeds = malloc(sizeof(unsigned long*) * 100000);
	unsigned long* starts = malloc(sizeof(unsigned long*) * 100000);
	unsigned long* ranges = malloc(sizeof(unsigned long*) * 100000);
	unsigned long* ptr;

	while((token = strtok_r(line, " \n", &line)) != NULL) {
		if (pairCount > 0) {
			pairs[pairCount] = strtol(token, NULL, 10);
		}

		pairCount++;
	}

	for (unsigned long i = 1; i < pairCount; i++) {
		// printf("%ld: %ld\n", i, pairs[i]);

		if (i % 2 > 0) {
			// odd so it's a starting num
			starts[localSeedCount] = pairs[i];
		} else {
			// even so it's a range
			ranges[localSeedCount] = pairs[i];
			localSeedCount++;
		}
	}

	for (unsigned long j = 0; j < localSeedCount; j++) {
		// printf("%ld, %ld\n", starts[j], ranges[j]);
		for (unsigned long k = starts[j]; k < starts[j] + ranges[j]; k++) {
			// printf("k: %ld\n", k);
			seeds[localRangeCount++] = k;
		}
	}

	free(pairs);
	free(starts);
	free(ranges);

	*seedCount = localRangeCount - 1;
	ptr = seeds;
	return ptr;
}


unsigned long findDest(unsigned long trav, unsigned long dest, unsigned long source, unsigned long len)
{
	// printf("%ld %ld %ld %ld\n", trav, dest, source, len);
	if (trav >= source 
	 && trav <= (source + len)) {
		return dest + (trav - source);
	} else {
		return '\0';
	}
}


void loadMap(char* line, Map* map)
{
	char* token;
	int lineCount = 0;
	unsigned long idx = map->rangeCount;

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
