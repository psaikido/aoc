// https://adventofcode.com/2023/day/1#part2
// Look for numbers as words too.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>

typedef struct {
	char *line;
	int fwnum;
	int fwpos;
	int lwnum;
	int lwpos;
} result;

typedef struct {
	int num;
	int pos;
} wordNum;


const char *wordNums[] = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
const char *wordNumsRev[] = {"eno", "owt", "eerht", "ruof", "evif", "xis", "neves", "thgie", "enin"};


FILE* getFile();
result parseLine(char *line);
wordNum firstWordNum(char *line);
wordNum lastWordNum(char *line);


int main() 
{
	FILE *fp = getFile();
	char line[255];
	result res;
	result results[1024];

	int count = 0;

	while (fgets(line, sizeof(line), fp)) {
		res = parseLine(line);
		results[count++] = res;
	}

	for (int i = 0; i < count; i++) {
		printf("%s", results[i].line);
		printf("fwnum: %d\n", results[i].fwnum);
		printf("fwpos: %d\n", results[i].fwpos);
		printf("lwnum %d\n", results[i].lwnum);
		printf("lwpos %d\n", results[i].lwpos);
		printf("\n");
	}
}


result parseLine(char *line)
{
	result res;
	res.line = malloc(strlen(line) + 1);
	strcpy(res.line, line);

	wordNum fwn = firstWordNum(line);
	res.fwnum = fwn.num;
	res.fwpos = fwn.pos;

	wordNum lwn = lastWordNum(line);
	res.lwnum = lwn.num;
	res.lwpos = lwn.pos;

	return res;
}


wordNum firstWordNum(char *line)
{
	char *ptr;
	int x = 0;
	int min = 255;
	int lowest = 0;
	wordNum wn;

	for (int i = 0; i < 9; i++) {
		ptr = strstr(line, wordNums[i]);

		if (ptr != NULL) {
			x = ptr - line;
			
			if (x < min) {
				min = x;
				lowest = i;
			}
		}
	}

	// index to wordNums is offset by 1 as 'one' is at index [0].
	wn.num = lowest + 1;
	wn.pos = min;

	return wn;
}


wordNum lastWordNum(char *line)
{
	char *ptr;
	int x = 0;
	int min = 255;
	int lowest = 0;
	wordNum wn;

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
			x = ptr - reversed;
			
			if (x < min) {
				min = x;
				lowest = i;
				// printf("%s\n", wordNums[x + 1]);
			}
		}
	}

	// index to wordNums is offset by 1 as 'one' is at index [0].
	wn.num = lowest + 1;

	// The position of the found string is in reverse so we have to know how
	// long the string was to find out what position it started.
	if (wordNumsRev[lowest] != NULL) {
		int lenReversedNum = (int)strlen(wordNumsRev[lowest]);
		wn.pos = strlen(line) - lenReversedNum - min;
	} else {
		wn.pos = 99;
	}

	return wn;
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
