/*
https://adventofcode.com/2023/day/3
Add up numbers 'adjacent' to symbols.
*/
#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
	int row;
	int start;
	int end;
	int val;
} item;


FILE* getFile();
item* parseForNumbers(int rowNum, char *line);
item* parseForSymbols(int rowNum, char *line);
bool isSymbol(char c);


int main() 
{
	FILE *fp = getFile();
	char line[150];
	char **schema = malloc(sizeof(char *) * 150);
	int count = 0;
	// int total = 0;

	// Read input into local array because we'll need to query rows before
	// and after the current row.
	while (fgets(line, sizeof(line), fp)) {
	  schema[count] = malloc(strlen(line));
	  strcpy(schema[count], line);
	  count++;
	}

	schema = realloc(schema, sizeof(char *) * count);

	for (int i = 0; i < count; i++) {
		// printf("%s\n", schema[i]);
		parseForNumbers(i, schema[i]);
		parseForSymbols(i, schema[i]);
	}

	// Test each number for an 'adjacent' symbol including diagonally.

	// printf("total %d\n", total);
	// Total should be .
}


item* parseForNumbers(int rowNum, char *line)
{ 
	item thing;
	item *things = malloc(sizeof(thing) * 150);
	int thingCntr = 0;
	char tmpNum[4];
	int tmpCntr = 0;

	// printf("rowNum: %d, %s", rowNum, line);

	for (int i = 0; i < strlen(line); i++) {
		if (isdigit(line[i])) {
			tmpNum[tmpCntr] = line[i];
			things[thingCntr].row = rowNum;

			if (tmpCntr == 0) {
				things[thingCntr].start = i;
			}

			tmpCntr++;
		} else {
			// Something is already in the temporary number so we are ending it and 
			// getting ready for a new one.
			if (tmpCntr > 0) {
				tmpNum[tmpCntr] = '\0';
				tmpCntr = 0;
				things[thingCntr].end = i - 1;
				things[thingCntr].val = (int)strtol(tmpNum, NULL, 10);
				thingCntr++;
			}
		}
	}

	// for (int j = 0; j < thingCntr; j++) {
	// 	printf("r: %d, s: %d, e: %d, v: %d\n", things[j].row, things[j].start, things[j].end, things[j].val);
	// }

	return things;
}


item* parseForSymbols(int rowNum, char *line)
{ 
	item thing;
	item *things = malloc(sizeof(thing) * 150);
	int thingCntr = 0;

	for (int i = 0; i < strlen(line); i++) {
		if (
			!isdigit(line[i]) 
			&& line[i] != '.'
			&& line[i] != '\n'
		) {
			things[thingCntr].row = rowNum;
			things[thingCntr].start = i;
			thingCntr++;
		}
	}

	// for (int j = 0; j < thingCntr; j++) {
	// 	printf("r: %d, s: %d\n", things[j].row, things[j].start);
	// }

	return things;
}


FILE* getFile()
{
	char filename[100];
	strcpy (filename, getenv("HOME"));
	strcat (filename, "/code/aoc/2023/day3/input1.txt");

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
