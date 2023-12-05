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
	int pos;
	int val;
} item;

int itemCntr = 0;
int symCntr = 0;

FILE* getFile();
item** parseForNumbers(int rowNum, char *line);
item** parseForSymbols(int rowNum, char *line);
bool isSymbol(char c);


int main() 
{
	FILE *fp = getFile();
	char line[150];
	char **schema = malloc(sizeof(char *) * 150);
	int rowCount = 0;
	int numCount = 0;
	int symCount = 0;
	int total = 0;

	// Read input into local array because we'll need to query rows before
	// and after the current row.
	while (fgets(line, sizeof(line), fp)) {
	  schema[rowCount] = malloc(strlen(line));
	  strcpy(schema[rowCount], line);
	  rowCount++;
	}

	schema = realloc(schema, sizeof(char *) * rowCount);
	item **numbers = malloc(sizeof(item *) * rowCount);
	item **symbols = malloc(sizeof(item *) * rowCount);
	item **parsedRowNumbers = malloc(sizeof(item *) * 10);
	item **parsedRowSymbols = malloc(sizeof(item *) * 10);

	for (int i = 0; i < rowCount; i++) {
		// printf("r: %d, %s", i, schema[i]);
		parsedRowNumbers = parseForNumbers(i, schema[i]);

		for (int j = 0; j < itemCntr; j++) {
			numbers = realloc(numbers, sizeof(item *) * (numCount + rowCount));
			numbers[numCount] = malloc(sizeof(item *) * numCount + 1);
			numbers[numCount] = parsedRowNumbers[j];
			numCount++;
		}

		parsedRowSymbols = parseForSymbols(i, schema[i]);

		for (int k = 0; k < symCntr; k++) {
			symbols = realloc(symbols, sizeof(item *) * (symCount + rowCount));
			symbols[symCount] = malloc(sizeof(item *) * symCount + 1);
			symbols[symCount] = parsedRowSymbols[k];
			symCount++;
		}

	}

	// Test each number for an 'adjacent' symbol including diagonally.
	for (int i = 0; i < numCount; i++) {
		printf("r: %d, s: %d, e: %d, v: %d\n", numbers[i]->row, numbers[i]->start, numbers[i]->end, numbers[i]->val);

		// Look for a symbol at either side on the same row.
		for (int j = 0; j < symCount; j++) {
			// Right row.
			if (symbols[j]->row == numbers[i]->row) {
				// Start.
				if (symbols[j]->pos == numbers[i]->start - 1) {
					// printf("found start r: %d, p: %d\n", symbols[j]->row, symbols[j]->pos);
					total += numbers[i]->val;
				}

				// End.
				if (symbols[j]->pos == numbers[i]->end + 1) {
					// printf("found end r: %d, p: %d\n", symbols[j]->row, symbols[j]->pos);
					total += numbers[i]->val;
				}
			}

			// Search row above (not first row obvs).
			if (numbers[i]->row > 0) {
				if (symbols[j]->row == numbers[i]->row - 1) {
					if (
						symbols[j]->pos >= numbers[i]->start - 1
				  	 && symbols[j]->pos <= numbers[i]->end + 1
					) {
						// printf("found above r: %d, p: %d\n", symbols[j]->row, symbols[j]->pos);
						total += numbers[i]->val;
					}
				}
			}

			// Search row below (not last row obvs).
			if (numbers[i]->row < rowCount) {
				if (symbols[j]->row == numbers[i]->row + 1) {
					if (
						symbols[j]->pos >= numbers[i]->start - 1
				  	 && symbols[j]->pos <= numbers[i]->end + 1
					) {
						// printf("found below r: %d, p: %d\n", symbols[j]->row, symbols[j]->pos);
						total += numbers[i]->val;
					}
				}
			}

		}
	}

	// for (int l = 0; l < symCount; l++) {
	// 	printf("r: %d, p: %d\n", symbols[l]->row, symbols[l]->pos);
	// }

	printf("total %d\n", total);
	// Total should be 543867.
}


item** parseForNumbers(int rowNum, char *line)
{ 
	item **numbers = malloc(sizeof(item *) * 1024);
	int thingCntr = 0;
	int tmpCntr = 0;
	char tmpNum[4];

	// printf("rowNum: %d, %s", rowNum, line);

	for (int i = 0; i < strlen(line); i++) {
		if (isdigit(line[i])) {
			tmpNum[tmpCntr] = line[i];

			if (tmpCntr == 0) {
				numbers[thingCntr] = malloc(sizeof(item *) * thingCntr + 1);
				numbers[thingCntr]->row = rowNum;
				numbers[thingCntr]->start = i;
			}

			tmpCntr++;
		} else {
			// Something is already in the temporary numbers so we are ending it and 
			// getting ready for a new one.
			if (tmpCntr > 0) {
				tmpNum[tmpCntr] = '\0';
				tmpCntr = 0;

				numbers[thingCntr]->end = i - 1;
				numbers[thingCntr]->val = (int)strtol(tmpNum, NULL, 10);
				thingCntr++;
				// numbers = realloc(numbers, sizeof(item *) * thingCntr);
			}
		}
	}

	// for (int j = 0; j < thingCntr; j++) {
	// 	printf("r: %d, s: %d, e: %d, v: %d\n", numbers[j]->row, numbers[j]->start, numbers[j]->end, numbers[j]->val);
	// }

	itemCntr = thingCntr;

	return numbers;
}


item** parseForSymbols(int rowNum, char *line)
{ 
	item **symbols = malloc(sizeof(item *) * 1024);
	int thingCntr = 0;

	for (int i = 0; i < strlen(line); i++) {
		if (
			!isdigit(line[i]) 
			&& line[i] != '.'
			&& line[i] != '\n'
		) {
			// symbols = realloc(symbols, sizeof(item *) * thingCntr + 1);
			symbols[thingCntr] = malloc(sizeof(item *));

			symbols[thingCntr]->row = rowNum;
			symbols[thingCntr]->pos = i;
			thingCntr++;
		}
	}

	// for (int j = 0; j < thingCntr; j++) {
	// 	printf("r: %d, s: %d\n", symbols[j]->row, symbols[j]->start);
	// }

	symCntr = thingCntr;

	return symbols;
}


FILE* getFile()
{
	char filename[100];
	strcpy (filename, getenv("HOME"));
	strcat (filename, "/code/aoc/2023/day3/input.txt");

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
