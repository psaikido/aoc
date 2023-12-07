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
long* parseSeeds(char* line, long* seedCount);
void loadMap(char* line, Map* map);
long findDest(long trav, long dest, long source, long len);


int main() 
{
	FILE *fp = getFile();
	char line[1024];
	long* seeds;
	long seedCount = 0;
	long lineCount = 0;
	
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

	// for (long i = 0; i < mapSeedToSoil.rangeCount; i++) {
	// 	printf("mapSeedToSoil: %ld, %ld, %ld\n", 
	// 		mapSeedToSoil.dest[i],
	// 		mapSeedToSoil.source[i],
	// 		mapSeedToSoil.len[i]
	// 	);
	// }
	//
	// for (long i = 0; i < mapSoilToFert.rangeCount; i++) {
	// 	printf("mapSoilToFert: %ld, %ld, %ld\n", 
	// 		mapSoilToFert.dest[i],
	// 		mapSoilToFert.source[i],
	// 		mapSoilToFert.len[i]
	// 	);
	// }
	//
	// for (long i = 0; i < mapFertToWater.rangeCount; i++) {
	// 	printf("mapFertToWater: %ld, %ld, %ld\n", 
	// 		mapFertToWater.dest[i],
	// 		mapFertToWater.source[i],
	// 		mapFertToWater.len[i]
	// 	);
	// }
	//
	// for (long i = 0; i < mapWaterToLight.rangeCount; i++) {
	// 	printf("mapWaterToLight: %ld, %ld, %ld\n", 
	// 		mapWaterToLight.dest[i],
	// 		mapWaterToLight.source[i],
	// 		mapWaterToLight.len[i]
	// 	);
	// }
	//
	// for (long i = 0; i < mapLightToTemp.rangeCount; i++) {
	// 	printf("mapLightToTemp: %ld, %ld, %ld\n", 
	// 		mapLightToTemp.dest[i],
	// 		mapLightToTemp.source[i],
	// 		mapLightToTemp.len[i]
	// 	);
	// }
	//
	// for (long i = 0; i < mapTempToHum.rangeCount; i++) {
	// 	printf("mapTempToHum: %ld, %ld, %ld\n", 
	// 		mapTempToHum.dest[i],
	// 		mapTempToHum.source[i],
	// 		mapTempToHum.len[i]
	// 	);
	// }
	//
	// for (long i = 0; i < mapHumToLoc.rangeCount; i++) {
	// 	printf("mapHumToLoc: %ld, %ld, %ld\n", 
	// 		mapHumToLoc.dest[i],
	// 		mapHumToLoc.source[i],
	// 		mapHumToLoc.len[i]
	// 	);
	// }

	// find corresponding soil number for a given seed
	// is seed num >= any source range num and within the range?
	// if yes then get the diff and add that to the source num
	// if no then soil num is seed num
	//
	// Seed 79, soil 81, fertilizer 81, water 81, light 74, temperature 78, humidity 78, location 82.
	// Seed 14, soil 14, fertilizer 53, water 49, light 42, temperature 42, humidity 43, location 43.
	// Seed 55, soil 57, fertilizer 57, water 53, light 46, temperature 82, humidity 82, location 86.
	// Seed 13, soil 13, fertilizer 52, water 41, light 34, temperature 34, humidity 35, location 35.

	// printf("seedCount %ld\n", seedCount);
	long soil = '\0';
	long fert = '\0';
	long water = '\0';
	long light = '\0';
	long temp = '\0';
	long hum = '\0';
	long loc = '\0';
	long totals[seedCount];

	for (long i = 1; i <= seedCount; i++) {
		printf("seed %ld\n", seeds[i]);

		for (long j = 0; j < mapSeedToSoil.rangeCount; j++) {
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

		for (long k = 0; k < mapSoilToFert.rangeCount; k++) {
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

		for (long l = 0; l < mapFertToWater.rangeCount; l++) {
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

		for (long m = 0; m < mapWaterToLight.rangeCount; m++) {
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

		for (long n = 0; n < mapLightToTemp.rangeCount; n++) {
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

		for (long o = 0; o < mapTempToHum.rangeCount; o++) {
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

		for (long p = 0; p < mapHumToLoc.rangeCount; p++) {
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

		printf("\n");
	}

	long winner = 1000000000;

	for (long i = 1; i <= seedCount; i++) {
		if (totals[i] < winner) {
			winner = totals[i];
		}
	}

	printf("the winner is %ld\n", winner);

	return 0;
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


long findDest(long trav, long dest, long source, long len)
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
