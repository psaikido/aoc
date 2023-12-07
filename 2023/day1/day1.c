// https://adventofcode.com/2023/day/1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>

FILE* getFile();

int main() 
{
	FILE *fp = getFile();
	char c;
	int count = 0;
	int digitsOnRow[1024];
	int firstDigit = 0;
	int lastDigit = 0;
	int total = 0;
	char strSum[1024];

	while ((c = fgetc(fp)) != EOF) {
		if (c != '\n') {
			if (isdigit(c)) {
				digitsOnRow[count] = (int)c - '0';
				// printf("%d", digitsOnRow[count]);
				count++;
			}
		} else {
			// for (int i = 0; i < count; i++) {
			// 	printf("%d", digitsOnRow[i]);
			// }
			
			firstDigit = digitsOnRow[0];
			lastDigit = digitsOnRow[count - 1];
			sprintf(strSum, "%d%d", firstDigit, lastDigit);

			count = 0;
			printf("%s\n", strSum);
			total += strtol(strSum, NULL, 10);
		}
	}

	printf("%d\n", total);
	// should be 54239
}



FILE* getFile()
{
	char filename[100];
	strcpy (filename, getenv("HOME"));
	strcat (filename, "/code/aoc/2023/day1/example1.txt");
	// strcat (filename, "/code/aoc/2023/day1/input.txt");

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
