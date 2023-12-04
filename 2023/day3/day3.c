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

FILE* getFile();
void parseLine(int count, char *line);


int main() 
{
	FILE *fp = getFile();
	char line[1024];
	int count = 0;
	// int total = 0;

	while (fgets(line, sizeof(line), fp)) {
		parseLine(count, line);
		count++;
	}

	// printf("total %d\n", total);
	// Total should be .
}


void parseLine(int rowCount, char *line)
{ 
	char* row = strdup(line);
	printf("rowCount: %d, %s\n", rowCount, row);
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
