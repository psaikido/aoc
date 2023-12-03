// https://adventofcode.com/2023/day/1#part2
// Look for numbers as words too.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>

FILE* getFile();
void parseLine(char *line);
int firstWordNum(char *line);
int lastWordNum(char *line);
const char *wordNums[] = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
const char *wordNumsRev[] = {"eno", "owt", "eerht", "ruof", "evif", "xis", "neves", "thgie", "enin"};

int main() 
{
	FILE *fp = getFile();
	char line[255];

	while (fgets(line, sizeof(line), fp)) {
		parseLine(line);
	}
}


void parseLine(char *line)
{
	int fwn = firstWordNum(line);
	int lwn = lastWordNum(line);

	printf("%s\n", line);
	printf("%d\n", fwn);
	printf("%d\n\n", lwn);
}


int firstWordNum(char *line)
{
	char *ptr;
	int x = 0;
	int min = 255;
	int lowest = 0;

	for (int i = 0; i < 9; i++) {
		ptr = strstr(line, wordNums[i]);

		if (ptr != NULL) {
			x = ptr - line;
			
			if (x < min) {
				min = x;
				lowest = i;
				// printf("%s\n", wordNums[x + 1]);
			}
		}
	}

	// index to wordNums is offset by 1 as 'one' is at index [0].
	return lowest + 1;
}


int lastWordNum(char *line)
{
	char *ptr;
	int x = 0;
	int min = 255;
	int lowest = 0;

	// reverse line
	char reversed[255];
	int count = 0;

	for (int i = strlen(line) - 1; i >= 0; i--) {
		reversed[count++] = line[i];
	}

	reversed[count] = '\0';

	for (int i = 0; i < 9; i++) {
		ptr = strstr(reversed, wordNumsRev[i]);

		if (ptr != NULL) {
			x = ptr - line;
			
			if (x < min) {
				min = x;
				lowest = i;
				// printf("%s\n", wordNums[x + 1]);
			}
		}
	}

	// index to wordNums is offset by 1 as 'one' is at index [0].
	return lowest + 1;
}


FILE* getFile()
{
	char filename[100];
	strcpy (filename, getenv("HOME"));
	strcat (filename, "/code/aoc/2023/day1/input1.txt");

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
