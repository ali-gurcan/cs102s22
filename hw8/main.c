#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define STATE_FILE "game_state.txt"
#define SCORE_FILE "high_score.txt"

typedef struct {
	char board[9];
	int nMoves;
} gameContext;

int checkWin(gameContext *context) {
	return !strncmp("12345678_", context->board, 9);
}

/* return 1 or 0 if the board is solvable or not */
int solvable(gameContext *context) {
	int inv = 0;
	/* increase the number of inversions for every out of order number */
	for(int i = 0; i < 9; i++) {
		for(int j = i + 1; context->board[i] != '_' && j < 9; j++) {
			if(context->board[j] != '_' && context->board[i] > context->board[j]) {
				inv++;
			}
		}
	}
	/* the board is solvable if the number of inversions is even */
	return inv % 2 == 0;
}

void generateBoard(gameContext *context) {
	int i, c, n;
	/* make every slot blank */
	for(i = 0; i < 9; i++) {
		context->board[i] = '_';
	}
	/* pick a spot for every number */
	for(i = 1; i < 9; i++) {
		/* place number i to nth blank spot from beginning */
		n = rand() % (10 - i);
		/* increment n if there are non-blank spots */
		for(c = 0; c <= n; c++) {
			if(context->board[c] != '_'){
				n++;
			}
		}
		context->board[n] = '0' + i;
	}
	context->nMoves = 0;
	/* generate a new board if the board is already solved or it is impossible to solve */
	if(checkWin(context) || !solvable(context)) {
		generateBoard(context);
	}
}

void printBoard(gameContext *context) {
	int y;
	printf("\n");
	for(y = 0; y < 3; y++) {
		printf("%c %c %c\n", context->board[y * 3], context->board[y * 3 + 1], context->board[y * 3 + 2]);
	}
}

/* save the state of the board to a file */
void saveState(gameContext *context) {
	int y;
	FILE *fp = fopen(STATE_FILE, "w");
	if(fp) {
		for(y = 0; y < 3; y++) {
			fprintf(fp, "%c %c %c\n", context->board[y * 3], context->board[y * 3 + 1], context->board[y * 3 + 2]);
		}
		fclose(fp);
	}
	else {
		printf("\nError: Could not write to file \"%s\".\n", STATE_FILE);
	}
}

/* tries to make the given move */
/* if move is legal changes the board and increments nMoves and returns 1 */
/* if move is illegal returns 0 */
int doMove(gameContext *context, const char move[]) {
	int legal, idx1, idx2;
	legal = move[1] == '-' && move[0] >= '1' && move[0] <= '8';
	if(legal) {
		/* find the index of left side number of the input */
		for(idx1 = 0; context->board[idx1] != move[0]; idx1++);
		/* find the index of the other number using direction on the right side of input */
		switch(move[2]) {
			case 'U':
			case 'u':
				legal = idx1 >= 3;
				if(legal) {
					idx2 = idx1 - 3;
				}
				break;
			case 'D':
			case 'd':
				legal = idx1 <= 5;
				if(legal) {
					idx2 = idx1 + 3;
				}
				break;
			case 'L':
			case 'l':
				legal = idx1 % 3;
				if(legal) {
					idx2 = idx1 - 1;
				}
				break;
			case 'R':
			case 'r':
				legal = (idx1 - 2) % 3;
				if(legal) {
					idx2 = idx1 + 1;
				}
				break;
			default:
				legal = 0;
				break;
		}
		/* check if the space trying to swap is blank */
		legal = legal && context->board[idx2] == '_';
	}
	if(legal) {
		context->board[idx2] = context->board[idx1];
		context->board[idx1] = '_';
		context->nMoves++;
	}
	return legal;
}

void playAsUser(gameContext *context) {
	char move[4];
	int score, highScore;
	FILE *fp;
	generateBoard(context);
	printBoard(context);
	saveState(context);
	/* take inputs until the game is won */
	while(!checkWin(context)) {
		printf("\nEnter your move (number-direction, e.g, 2-R): ");
		scanf("%*[^\n]");
		scanf(" %3s", move);
		if(!doMove(context, move)) {
			printf("\n%s is an illegal move.\n", move);
		}
		printBoard(context);
		saveState(context);
	}
	score = 1000 - context->nMoves * 10;
	printf("\nCongratulations! You finished the game.\n");
	printf("\nTotal number of moves: %d\nYour Score: %d\n", context->nMoves, score);
	/* try to open and read the score file */
	fp = fopen(SCORE_FILE, "r");
	if(fp) {
		fscanf(fp, "%d", &highScore);
		fclose(fp);
	}
	else {
		/* if score file is not found try to make current score new high score */
		highScore = -99999999;
	}
	/* try to write to score file if current score is high score */
	if(score > highScore) {
		fp = fopen(SCORE_FILE, "w");
		if(fp) {
			fprintf(fp, "%d", score);
			fclose(fp);
		}
		else {
			printf("\nError: Could not write to file \"%s\".\n", SCORE_FILE);
		}
	}
}

void auto_finish(gameContext *context) {
	/* static is to use less stack */
	static char move[4];
	move[1] = '-';
	move[3] = '\0';
	/* try to make a move until it is legit */
	do {
		/* left side of the move input */
		move[0] = rand() % 8 + '1';
		/* pick the letter of direction from the predefined array */
		move[2] = "URDL"[rand() % 4];
	}
	while(!doMove(context, move));
	saveState(context);
	printf("\nComputer Move: %s\n", move);
	printBoard(context);
	if(checkWin(context)) {
		printf("\nComputer finished the game.\n");
		printf("\nTotal number of moves: %d\n", context->nMoves);
	}
	else {
		auto_finish(context);
	}
	return;
}

/* prints the number inside score file */
void bestScore() {
	int score;
	FILE *fp = fopen(SCORE_FILE, "r");
	if(fp) {
		fscanf(fp, "%d", &score);
		printf("\nBest Score: %d\n", score);
		fclose(fp);
	}
	else {
		printf("\nNo score file found.\n");
	}
}

int selectionGet(int min, int max, const char options[], const char prompt[]) {
	int input;
	printf("%s", options);
	while(1) {
		printf("%s", prompt);
		if(!scanf("%*[^-0-9]%d", &input)) {
			scanf("%d", &input);
		}
		if(input >= min && input <= max) {
			break;
		}
		else {
			printf("\nInvalid input.\n");
		}
	}
	return input;
}

int main() {
	gameContext context;
	int input;
	srand(time(NULL));
	while((input = selectionGet(1, 4, "\nWelcome to the 8-Puzzle Game!\nPlease select an option:\n1. Play game as a user\n2. Finish the game with PC\n3. Show the best score\n4. Exit\n", "\n> ")) != 4) {
		switch(input) {
			case 1:
				playAsUser(&context);
				break;
			case 2:
				generateBoard(&context);
				printBoard(&context);
				auto_finish(&context);
				break;
			case 3:
				bestScore();
				break;
		}
	}
}
