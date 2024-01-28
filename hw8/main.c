/*#include<stdio.h>
#include<stdlib.h>

typedef struct{
    character[9],
    move[4];
    
}board;


void game(){

}
void board(){

}
void score(){

}

int exitt(){
    return 0;
}
void menu(){
    printf("Welcome to the 8-Puzzle Game!\n");
    printf("Please select an option\n");
    printf("1. Play game as a user\n");
    printf("2. Finish the game with PC\n");
    printf("3. Show the best score\n");
    printf("4. Exit\n> ");
    int select;
    scanf("%d",&select);
    switch (select)
    {
    case 1:
        
        break;
    case 2:

        break;
    case 3:

        break;
    case 4:
        exitt();
        break;

    default:
        exitt();

        break;
    }
}
int main(){
    menu();    
}*/



/*
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define BOARD_SIZE 3
#define EMPTY_TILE 0

// Struct to represent the puzzle board
typedef struct
{
    int tiles[BOARD_SIZE][BOARD_SIZE];
} PuzzleBoard;

// Function to initialize a new puzzle board
void initializeBoard(PuzzleBoard *board)
{
    int num = 1;
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            board->tiles[i][j] = num++;
        }
    }
    board->tiles[BOARD_SIZE - 1][BOARD_SIZE - 1] = EMPTY_TILE;
}

// Function to print the puzzle board
void printBoard(PuzzleBoard *board)
{
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            if (board->tiles[i][j] == EMPTY_TILE)
            {
                printf("_ ");
            }
            else
            {
                printf("%d ", board->tiles[i][j]);
            }
        }
        printf("\n");
    }
}

// Function to swap two tiles on the board
void swapTiles(PuzzleBoard *board, int row1, int col1, int row2, int col2)
{
    int temp = board->tiles[row1][col1];
    board->tiles[row1][col1] = board->tiles[row2][col2];
    board->tiles[row2][col2] = temp;
}

// Function to check if the puzzle is solved
bool isPuzzleSolved(PuzzleBoard *board)
{
    int num = 1;
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            if (board->tiles[i][j] != num++)
            {
                return false;
            }
        }
    }
    return true;
}

// Function to generate a random number within a range
int getRandomNumber(int min, int max)
{
    return min + rand() % (max - min + 1);
}

// Function to randomly shuffle the puzzle board
void shuffleBoard(PuzzleBoard *board)
{
    srand(time(NULL));
    int numShuffles = getRandomNumber(50, 100);
    for (int i = 0; i < numShuffles; i++)
    {
        int direction = getRandomNumber(1, 4);
        int emptyRow, emptyCol;

        // Find the position of the empty tile
        for (int row = 0; row < BOARD_SIZE; row++)
        {
            for (int col = 0; col < BOARD_SIZE; col++)
            {
                if (board->tiles[row][col] == EMPTY_TILE)
                {
                    emptyRow = row;
                    emptyCol = col;
                    break;
                }
            }
        }

        // Move the empty tile in a random direction
        switch (direction)
        {
        case 1: // Up
            if (emptyRow > 0)
            {
                swapTiles(board, emptyRow, emptyCol, emptyRow - 1, emptyCol);
            }
            break;
        case 2: // Down
            if (emptyRow < BOARD_SIZE - 1)
            {
                swapTiles(board, emptyRow, emptyCol, emptyRow + 1, emptyCol);
            }
            break;
        case 3: // Left
            if (emptyCol > 0)
            {
                swapTiles(board, emptyRow, emptyCol, emptyRow, emptyCol - 1);
            }
            break;
        case 4: // Right
            if (emptyCol < BOARD_SIZE - 1)
            {
                swapTiles(board, emptyRow, emptyCol, emptyRow, emptyCol + 1);
            }
            break;
        }
    }
}

// Function to save the board state to a text file
void saveBoardState(PuzzleBoard *board)
{
    FILE *file = fopen("board_state.txt", "w");
    if (file == NULL)
    {
        printf("Error opening file.\n");
        return;
    }

    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            fprintf(file, "%d ", board->tiles[i][j]);
        }
        fprintf(file, "\n");
    }

    fclose(file);
}

// Function to play the game as a user
void playGame()
{
    PuzzleBoard board;
    initializeBoard(&board);
    shuffleBoard(&board);
    saveBoardState(&board);
    printf("The puzzle board has been initialized and shuffled.\n");

    while (!isPuzzleSolved(&board))
    {
        printBoard(&board);
        printf("Enter your move (number-direction, e.g., 2-R): ");
        int number;
        char direction;
        scanf("%d-%c", &number, &direction);

        int row, col;
        bool found = false;

        // Find the position of the tile
        for (row = 0; row < BOARD_SIZE; row++)
        {
            for (col = 0; col < BOARD_SIZE; col++)
            {
                if (board.tiles[row][col] == number)
                {
                    found = true;
                    break;
                }
            }
            if (found)
            {
                break;
            }
        }

        // Move the tile in the specified direction
        switch (direction)
        {
        case 'u':    
        case 'U':
            if (row > 0)
            {
                swapTiles(&board, row, col, row - 1, col);
            }
            break;
        case 'd':   
        case 'D':
            if (row < BOARD_SIZE - 1)
            {
                swapTiles(&board, row, col, row + 1, col);
            }
            break;
        case 'l':
        case 'L':
            if (col > 0)
            {
                swapTiles(&board, row, col, row, col - 1);
            }
            break;
        case 'r':    
        case 'R':
            if (col < BOARD_SIZE - 1)
            {
                swapTiles(&board, row, col, row, col + 1);
            }
            break;
        default:
            printf("Invalid direction. Try again.\n");
            continue;
        }

        saveBoardState(&board);
    }

    printf("Congratulations! You solved the puzzle!\n");
}

// Function to finish the game with PC
void finishGameWithPC()
{
    // Add your code here to implement the PC solving the puzzle
    printf("This feature is coming soon!\n");
}

// Function to show the best score
void showBestScore()
{
    // Add your code here to retrieve and display the best score
    printf("This feature is coming soon!\n");
}

int main()
{
    int choice;

    do
    {
        printf("\nWelcome to the 8-Puzzle Game!\n");
        printf("Please select an option\n");
        printf("1. Play game as a user\n");
        printf("2. Finish the game with PC\n");
        printf("3. Show the best score\n");
        printf("4. Exit\n");
        printf("> ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            playGame();
            break;
        case 2:
            finishGameWithPC();
            break;
        case 3:
            showBestScore();
            break;
        case 4:
            printf("Exiting...\n");
            break;
        default:
            printf("Invalid choice. Try again.\n");
            break;
        }
    } while (choice != 4);

    return 0;
}
*/
/*#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define BOARD_SIZE 3
#define EMPTY_TILE 0

// Struct to represent the puzzle board
typedef struct
{
    int tiles[BOARD_SIZE][BOARD_SIZE];
} PuzzleBoard;

// Function to initialize a new puzzle board
void initializeBoard(PuzzleBoard *board)
{
    int num = 1;
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            board->tiles[i][j] = num++;
        }
    }
    board->tiles[BOARD_SIZE - 1][BOARD_SIZE - 1] = EMPTY_TILE;
}

// Function to print the puzzle board
void printBoard(PuzzleBoard *board)
{
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            if (board->tiles[i][j] == EMPTY_TILE)
            {
                printf("  ");
            }
            else
            {
                printf("%d ", board->tiles[i][j]);
            }
        }
        printf("\n");
    }
}

// Function to swap two tiles on the board
void swapTiles(PuzzleBoard *board, int row1, int col1, int row2, int col2)
{
    int temp = board->tiles[row1][col1];
    board->tiles[row1][col1] = board->tiles[row2][col2];
    board->tiles[row2][col2] = temp;
}

// Function to check if the puzzle is solved
bool isPuzzleSolved(const PuzzleBoard *board)
{
    int count = 1;
    for (int row = 0; row < BOARD_SIZE; row++)
    {
        for (int col = 0; col < BOARD_SIZE; col++)
        {
            if (board->tiles[row][col] != count % (BOARD_SIZE * BOARD_SIZE))
            {
                return false;
            }
            count++;
        }
    }
    return true;
}

// Function to generate a random number within a range
int getRandomNumber(int min, int max)
{
    return min + rand() % (max - min + 1);
}

// Function to randomly shuffle the puzzle board
void shuffleBoard(PuzzleBoard *board)
{
    srand(time(NULL));
    int numShuffles = getRandomNumber(50, 100);
    for (int i = 0; i < numShuffles; i++)
    {
        int direction = getRandomNumber(1, 4);
        int emptyRow, emptyCol;

        // Find the position of the empty tile
        for (int row = 0; row < BOARD_SIZE; row++)
        {
            for (int col = 0; col < BOARD_SIZE; col++)
            {
                if (board->tiles[row][col] == EMPTY_TILE)
                {
                    emptyRow = row;
                    emptyCol = col;
                    break;
                }
            }
        }

        // Move the empty tile in a random direction
        switch (direction)
        {
        case 1: // Up
            if (emptyRow > 0)
            {
                swapTiles(board, emptyRow, emptyCol, emptyRow - 1, emptyCol);
            }
            break;
        case 2: // Down
            if (emptyRow < BOARD_SIZE - 1)
            {
                swapTiles(board, emptyRow, emptyCol, emptyRow + 1, emptyCol);
            }
            break;
        case 3: // Left
            if (emptyCol > 0)
            {
                swapTiles(board, emptyRow, emptyCol, emptyRow, emptyCol - 1);
            }
            break;
        case 4: // Right
            if (emptyCol < BOARD_SIZE - 1)
            {
                swapTiles(board, emptyRow, emptyCol, emptyRow, emptyCol + 1);
            }
            break;
        }
    }
}

// Function to save the board state to a text file
void saveBoardState(PuzzleBoard *board)
{
    FILE *file = fopen("board_state.txt", "w");
    if (file == NULL)
    {
        printf("Error opening file.\n");
        return;
    }

    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            fprintf(file, "%d ", board->tiles[i][j]);
        }
        fprintf(file, "\n");
    }

    fclose(file);
}

// Function to load the board state from a text file
void loadBoardState(PuzzleBoard *board)
{
    FILE *file = fopen("board_state.txt", "r");
    if (file == NULL)
    {
        printf("Error opening file.\n");
        return;
    }

    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            fscanf(file, "%d", &board->tiles[i][j]);
        }
    }

    fclose(file);
}

// Function to play the game as a user
// Function to play the game as a user
void playGame()
{
    PuzzleBoard board;
    loadBoardState(&board);
    printf("The puzzle board has been loaded.\n");

    int moves = 0;

    while (!isPuzzleSolved(&board))
    {
        printBoard(&board);
        printf("Enter the number and direction (U - Up, D - Down, L - Left, R - Right): ");
        int number;
        char direction;
        scanf("%d-%c", &number, &direction);

        int row, col;
        bool found = false;

        // Find the position of the tile
        for (row = 0; row < BOARD_SIZE; row++)
        {
            for (col = 0; col < BOARD_SIZE; col++)
            {
                if (board.tiles[row][col] == number)
                {
                    found = true;
                    break;
                }
            }
            if (found)
            {
                break;
            }
        }

        // Check if the move is valid
        switch (direction)
        {
        case 'U':
            if (row > 0)
            {
                swapTiles(&board, row, col, row - 1, col);
                moves++;
            }
            else
            {
                printf("Invalid move. Try again.\n");
                continue;
            }
            break;
        case 'D':
            if (row < BOARD_SIZE - 1)
            {
                swapTiles(&board, row, col, row + 1, col);
                moves++;
            }
            else
            {
                printf("Invalid move. Try again.\n");
                continue;
            }
            break;
        case 'L':
            if (col > 0)
            {
                swapTiles(&board, row, col, row, col - 1);
                moves++;
            }
            else
            {
                printf("Invalid move. Try again.\n");
                continue;
            }
            break;
        case 'R':
            if (col < BOARD_SIZE - 1)
            {
                swapTiles(&board, row, col, row, col + 1);
                moves++;
            }
            else
            {
                printf("Invalid move. Try again.\n");
                continue;
            }
            break;
        default:
            printf("Invalid direction. Try again.\n");
            continue;
        }

        saveBoardState(&board);
    }

    int score = 1000 - 10 * moves;

    printf("Congratulations! You solved the puzzle!\n");
    printf("Total number of moves: %d\n", moves);
    printf("Score: %d\n", score);

    // Check if the current score is the best score
    int bestScore;
    FILE *bestScoreFile = fopen("best_score.txt", "r");
    if (bestScoreFile != NULL)
    {
        fscanf(bestScoreFile, "%d", &bestScore);
        fclose(bestScoreFile);
    }
    else
    {
        bestScore = score;
    }

    if (score > bestScore)
    {
        printf("You achieved the best score!\n");
        FILE *newBestScoreFile = fopen("best_score.txt", "w");
        if (newBestScoreFile != NULL)
        {
            fprintf(newBestScoreFile, "%d", score);
            fclose(newBestScoreFile);
        }
    }

    // Return to the main menu
    printf("Returning to the main menu...\n");
}

// Function to finish the game with PC
void finishGameWithPC()
{
    // Add your code here to implement the PC solving the puzzle
    printf("This feature is coming soon!\n");
}

// Function to show the best score
void showBestScore()
{
    int bestScore;
    FILE *bestScoreFile = fopen("best_score.txt", "r");
    if (bestScoreFile != NULL)
    {
        fscanf(bestScoreFile, "%d", &bestScore);
        fclose(bestScoreFile);
        printf("Best Score: %d\n", bestScore);
    }
    else
    {
        printf("No best score found.\n");
    }
}

int main()
{
    int choice;

    do
    {
        printf("\n--- 8-Puzzle Game ---\n");
        printf("1. Play game as a user\n");
        printf("2. Finish the game with PC\n");
        printf("3. Show the best score\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            playGame();
            break;
        case 2:
            finishGameWithPC();
            break;
        case 3:
            showBestScore();
            break;
        case 4:
            printf("Exiting...\n");
            break;
        default:
            printf("Invalid choice. Try again.\n");
            break;
        }
    } while (choice != 4);

    return 0;
}
*/#include <stdio.h>
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