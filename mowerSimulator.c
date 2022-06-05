#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#define NUMBER_LINES 10
#define NUMBER_COLLUMNS 10
#define MOWER_SPEED 100000


typedef struct {
	int line;
	int collumn;
} position;

typedef struct {
	int x;
	int y;
} change;


void printBoard(char board[][NUMBER_COLLUMNS]) {
	for (int i = 0; i < NUMBER_LINES; i++){
		for (int j = 0; j < NUMBER_COLLUMNS; j++){
			printf("%c", board[i][j]);
			if (j != NUMBER_COLLUMNS-1)
				printf(" ");
		}
		printf("\n");
	}
	printf("\n");
}


void classicMower(char board[][NUMBER_COLLUMNS]) {
	int iter = 1;
	position position;

	position.line = 0;
	position.collumn = 0;

	do {
		board[position.line][position.collumn] = 'T';
		printf("Iteration nº%d\n", iter);
		iter++;
		printBoard(board);
		usleep(MOWER_SPEED);
		board[position.line][position.collumn] = '_';

		if (position.collumn < NUMBER_COLLUMNS-1 && position.line % 2 == 0) {
			position.collumn++;
		}
		else if (position.collumn > 0 && position.line % 2 != 0) {
			position.collumn--;
		}
		else {
			if (position.line % 2 == 0)
				position.collumn = NUMBER_COLLUMNS-1;
			else
				position.collumn = 0;
			position.line++;
		}

	} while (position.line < NUMBER_LINES || position.collumn > 0);

	printf("All done! It finished in %d iterations.\n", iter-1);
}


int allDone(char board[][NUMBER_COLLUMNS]) {
	for (int i = 0; i < NUMBER_LINES; i++)
		for (int j = 0; j < NUMBER_COLLUMNS; j++)
			if (board[i][j] == '~')
				return 0;
	return 1;
}


void robotMower(char board[][NUMBER_COLLUMNS]) {
	int num, lower = 0, upper = 3, tempX, tempY, done = 0, iter = 0;
	position position;
	change c1, c2, c3, c4;

	c1.x = 1;
	c1.y = 0;
	c2.x = -1;
	c2.y = 0;
	c3.x = 0;
	c3.y = 1;
	c4.x = 0;
	c4.y = -1;

	change options[] = {c1, c2, c3, c4};

	position.line = NUMBER_LINES / 2 - 1;
	position.collumn = NUMBER_COLLUMNS / 2 - 1;

	srand(time(NULL));

	do {
		board[position.line][position.collumn] = 'T';
		printf("Iteration nº%d\n", iter);
		iter++;
		printBoard(board);
		usleep(MOWER_SPEED);
		board[position.line][position.collumn] = '_';

		do {
			tempX = position.line;
			tempY = position.collumn;

	    	num = (rand() % (upper - lower + 1)) + lower;

	        tempX += options[num].x;
	        tempY += options[num].y;

    	} while (tempX > NUMBER_LINES-1 || tempX < 0 || tempY > NUMBER_COLLUMNS-1 || tempY < 0);

		position.line += options[num].x;
		position.collumn += options[num].y;
		
		done = allDone(board);

	} while (done == 0);

	printf("All done! It finished in %d iterations.\n", iter-1);
}


int main() {
	int answer;
	char board[NUMBER_LINES][NUMBER_COLLUMNS];

	for (int i = 0; i < NUMBER_LINES; i++)
		for (int j = 0; j < NUMBER_COLLUMNS; j++)
			board[i][j] = '~';

	printf("Do you want to use the Classic Mower(1) or the Robot Lawn Mower(2)?\n");
	scanf("%d", &answer);

	switch (answer) {
		case 1:
			classicMower(board);
			break;
		case 2:
			robotMower(board);
			break;
		default:
			printf("Invalid. Insert 1 or 2.\n");
			break;
	}

	return 0;
}
