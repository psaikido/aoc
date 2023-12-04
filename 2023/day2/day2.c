/*
https://adventofcode.com/2023/day/2
Determine which games would have been possible if the bag had been loaded with
only 12 red cubes, 13 green cubes, and 14 blue cubes. What is the sum of the IDs
of those games?
*/
#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct {
	int green;
	int red;
	int blue;
	int id;
} bag;


FILE* getFile();
bag parseLine(int count, char *line);
int getClrVal(char* cube, char* clr);


int main() 
{
	int REDMAX = 12;
	int GREENMAX = 13;
	int BLUEMAX = 14;

	FILE *fp = getFile();
	char line[1024];
	bag bags[101];
	int count = 0;
	int total = 0;

	while (fgets(line, sizeof(line), fp)) {
		bags[count] = parseLine(count, line);
		// printf("id: %d, red %d, green %d, blue %d\n", 
		//  bags[count].id, 
		//  bags[count].red, 
		//  bags[count].green,
		//  bags[count].blue);
		if (
			bags[count].red <= REDMAX
			&& bags[count].green <= GREENMAX
			&& bags[count].blue <= BLUEMAX
		) {
			total += bags[count].id;
		}

		count++;
	}

	printf("total %d\n", total);
	// Total should be 2439.
}


bag parseLine(int id, char *line)
{ 
	char* row = strdup(line);
	char* token;
	char* tokenComma;
	char* games = "";
	char* throw = "";
	int count = 0;
	int red = 0;
	int maxRed = 0;
	int green = 0;
	int maxGreen = 0;
	int blue = 0;
	int maxBlue = 0;

	bag b;
	b.id = id + 1;

	// Take off the 'Game x:' part.
	while((token = strtok_r(row, ":\n", &row)) != NULL) {
		if (count == 1) {
			games = malloc(strlen(token));
			strcpy(games, token);
		}

		count++;
	}

	count = 0;

	// Split by semicolons.
	while((token = strtok_r(games, ";\n", &games)) != NULL) {
		// printf("count: %d, %s\n", count, token);
		count++;

		throw = malloc(strlen(token));
		strcpy(throw, token);

		// Split by commas.
		while((tokenComma = strtok_r(throw, ",\n", &throw)) != NULL) {
			// printf("throw: %s\n", tokenComma);
			red = getClrVal(tokenComma, "red");
			if (red > maxRed) {
				maxRed = red;
			}

			green = getClrVal(tokenComma, "green");
			if (green > maxGreen) {
				maxGreen = green;
			}

			blue = getClrVal(tokenComma, "blue");
			if (blue > maxBlue) {
				maxBlue = blue;
			}
		}

		b.red = maxRed;
		b.green = maxGreen;
		b.blue = maxBlue;
	}

	return b;
}


int getClrVal(char* cube, char* clr)
{
	char* ptr;
	char strClr[4];
	int clrVal = 0;

	ptr = strstr(cube, clr);

	if (ptr != NULL) {
		sscanf(cube, "%s ", strClr);
		clrVal = (int)strtol(strClr, NULL, 10);
		return clrVal;
	}

	return 0;
}


FILE* getFile()
{
	char filename[100];
	strcpy (filename, getenv("HOME"));
	strcat (filename, "/code/aoc/2023/day2/input.txt");

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
