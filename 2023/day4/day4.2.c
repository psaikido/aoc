// https://adventofcode.com/2023/day/4 part 2
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>
#include <math.h>


#define MAXROWS 300

typedef struct {
	int cardNum;
	int matches;
} Card;


FILE* getFile();
int* parseWinners(char* line);
int* parsePlays(char* line);
void calc(Card*, int);


int main() 
{
	FILE *fp = getFile();
	char line[1024];
	int matches = 0;
	int cardTotal = 0;
	int total = 0;
	int cardCount = 1;

	Card* cards = calloc(300, sizeof(Card));

	while (fgets(line, sizeof(line), fp)) {
		// printf("%s", line);
		int* winners = parseWinners(line);
		int* plays = parsePlays(line);

		matches = 0;
		cardTotal = 0;

		// printf("winners\n");
		for (int i = 0; i < MAXROWS; i++) {
			if (winners[i] != '\0') {
				// printf("%d\n", winners[i]);

				for (int j = 0; j < MAXROWS; j++) {
					if (plays[j] != '\0') {
						if (winners[i] == plays[j]) {
							// printf("match: %d\n", plays[j]);
							matches++;
						}
					} else {
						break;
					}
				}
			} else {
				if (matches > 1) {
					cardTotal = pow(2, (double)matches - 1);
				} else {
					cardTotal = matches;
				}

				// printf("c: %d, m: %d, ct: %d, t: %d\n", cardCount, matches, cardTotal, total);

				cards[cardCount].cardNum = cardCount;
				cards[cardCount].matches = matches;
				break;
			}
		}

		cardCount++;
	}

	calc(cards, cardCount);

	// printf("%d\n", total);
	return 0;
}


void calc(Card* cards, int cardCount)
{
	int total[cardCount + 1][1024];
	int count = 0;

	for (int i = 1; i <= cardCount; i++) {

		if (cards[i].cardNum != '\0') {
			total[i][0]++;
			printf("i: %d, m: %d, t: %d\n", cards[i].cardNum, cards[i].matches, total[i][0]);
			count += total[i][0];

			if (cards[i].matches > 0) {
				for (int j = i + 1; j <= i + cards[i].matches; j++) {
					total[cards[j].cardNum][0]++;
					printf("  c: %d, m: %d, t: %d\n", cards[j].cardNum, cards[j].matches, total[cards[j].cardNum][0]);
					count += total[cards[j].cardNum][0];
				}
			}
		}
	}

	printf("%d\n", count - 1);
}


int* parseWinners(char* line)
{
	char* card = strdup(line);
	// printf("%s\n", card);

	int* winners = calloc(1024, sizeof(int));
	char* strWinners;
	char* token;
	int count = 0;

	while((token = strtok_r(card, ":|\n", &card)) != NULL) {
		if (count == 1) {
			strWinners = token;
		}

		count++;
	}

	count = 0;

	while((token = strtok_r(strWinners, " \n", &strWinners)) != NULL) {
		// printf("%d %s\n", count, token);
		winners[count] = (int)strtol(token, NULL, 10);
		count++;
	}

	winners[count] = '\0';

	int* ptr = winners;
	return ptr;
}


int* parsePlays(char* line)
{
	char* card = strdup(line);
	// printf("%s\n", card);

	int* plays = calloc(1024, sizeof(int));
	char* strPlays;
	char* token;
	int count = 0;

	while((token = strtok_r(card, ":|\n", &card)) != NULL) {
		if (count == 2) {
			strPlays = token;
		}

		count++;
	}

	count = 0;

	while((token = strtok_r(strPlays, " \n", &strPlays)) != NULL) {
		// printf("%d %s\n", count, token);
		plays[count] = (int)strtol(token, NULL, 10);
		count++;
	}

	plays[count] = '\0';

	int* ptr = plays;
	return ptr;
}


FILE* getFile()
{
	char filename[100];
	strcpy (filename, getenv("HOME"));
	strcat (filename, "/code/aoc/2023/day4/input.txt");

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
