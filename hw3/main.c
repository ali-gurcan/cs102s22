#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define UP 'w'
#define LEFT 'a'
#define DOWN 's'
#define RIGHT 'd'
void menu();
void drawRoom(int size, int characterX, int characterY, int doorX, int doorY);
int controlStatus(int characterX, int characterY, int doorX, int doorY);
void gameplay();
void help();
void menu();
int main(){
    menu();
    return 0;
}
void drawRoom(int size, int characterX, int characterY, int doorX, int doorY){
        int x, y;
        printf("\n");
        //Top wall
        for (int j = 0; j < size; j++){
                        printf("--");
                }
        printf("-");
        printf("\n");
        for (y = 0; y < size; y++){
                printf("|");
                for (x = 0; x < size; x++){
                        if (y == characterY && x == characterX){
                                //checks the character
                                printf("C|");
                        }
                        else if (y == doorY && x == doorX){
                                //checks the door
                                printf("D|");
                        }
                        else{
                                printf(" |");
                        }
                }
                printf("\n");
        }
        //Bottom wall
        for (int i = 0; i < size; i++){
                printf("--");
        }
        printf("-");
        printf("\n");
        }
int controlStatus(int characterX, int characterY, int doorX, int doorY){
        //Ending scenario
        return (characterX == doorX && characterY == doorY);
}
void gameplay(){
        int size, characterX, characterY, doorX, doorY, movecount = 0;
        char move;
        //It makes rand function work properly
        srand(time(0));
        //Initialization the game
        printf("Enter the size of the room (5-10): ");
        scanf("%d", &size);
        if (size < 5 || size > 10){
                printf("Invalid room size!\n");
                return;
        }
        characterX = rand() % size;
        characterY = rand() % size;
        // This prevents the game from ending before it starts
        do
        {
                doorX = rand() % size;
                doorY = rand() % size;
        } while (doorX == characterX && doorY == characterY);
        drawRoom(size, characterX, characterY, doorX, doorY);
        do
        {
                printf("Enter your move (a=left, d=right, w=up, s=down): ");
                scanf(" %c", &move);
                switch (move)
                {
                case UP:
                        if (characterY == 0){
                                printf("You cannot move up!\n");
                        }
                        else{
                                characterY--;
                                movecount++;
                        }
                        break;
                case LEFT:
                        if (characterX == 0){
                                printf("You cannot move left!\n");
                        }
                        else{
                                characterX--;
                                movecount++;
                        }
                        break;
                case DOWN:
                        if (characterY == size - 1){
                                printf("You cannot move down!\n");
                        }
                        else{
                                characterY++;
                                movecount++;
                        }
                        break;
                case RIGHT:
                        if (characterX == size - 1){
                                printf("You cannot move right!\n");
                        }
                        else{
                                characterX++;
                                movecount++;
                        }
                        break;
                default:
                        printf("Invalid move!\n");
                }
                //It prevents the final state of the room from being seen
                if (!controlStatus(characterX, characterY, doorX, doorY)){
                        drawRoom(size, characterX, characterY, doorX, doorY);
                }
        } while (!controlStatus(characterX, characterY, doorX, doorY));
        printf("Congratulations,You have reached the door in %d moves!\n", movecount);
        return menu();
}
void help(){
                printf("\nInstructions:\n");
                printf("Move the character 'C' to the door 'D' to win the game.\n");
                printf("Use the following keys to move the character:\n");
                printf("'w' for up\n");
                printf("'a' for left\n");
                printf("'s' for down\n");
                printf("'d' for right\n");
                printf("You cannot move diagonally.\n");
                printf("The game will prompt you for a new move after each move is made until the game is over.\n");
                printf("If the character attempts to move through a wall, a warning message will be displayed.\n");
                printf("The game ends when the character reaches the door.\n");
                printf("After the game is over, you will return to the main menu.\n");
                printf("-------------------------------\n");
        }                
void menu(){
                //It makes rand function work properly
                srand(time(0)); 

                //menu
                printf("Welcome to the 2D puzzle game!\n");
                printf("1. New Game\n");
                printf("2. Help\n");
                printf("3. Exit\n");

                //It prompts the user to make a selection and validates the input
                int choice;
                do
                {
                        printf("Enter your choice (1-3): ");
                        if (scanf("%d", &choice) != 1)
                        {
                                printf("Invalid input. Please enter an integer.\n");
                                while (getchar() != '\n');
                                continue;
                        }
                        if (choice < 1 || choice > 3)
                        {
                                printf("Invalid choice. Please enter a number between 1 and 3.\n");
                        }
                } while (choice < 1 || choice > 3);

                //user's choice
                switch (choice)
                {
                case 1:
                        gameplay();//the game begins
                        break;
                case 2:
                        help(); //help
                        menu(); // return to the main menu
                        break;
                case 3:
                        printf("Goodbye\n");
                }
}
        