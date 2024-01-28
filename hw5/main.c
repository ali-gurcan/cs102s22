#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

typedef enum
{
    RED,
    GREEN,
    BLUE,
    YELLOW,
    ORANGE
} Color;


void count_letters(FILE *fp, int *counts)
{
    int c;
    while ((c = fgetc(fp)) != EOF)
    {
        if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
        {
            if (c >= 'A' && c <= 'Z')
            {
                c = c - 'A' + 'a'; // converting to lowercase
            }
            counts[c - 'a']++; // counting operation
        }
    }
    //print counts
    printf("Letter Frequency:\n");
    for (int i = 0; i < 26; i++)
    {
        printf("%c: %d\n", 'a' + i, counts[i]);
    }
}

int part1(){
    char filename[100];
    FILE *fp ;
    printf("Enter the file name: ");
    scanf("%s", filename);
    //Comparing user input and filename
    if (strcmp(filename, "example.txt") != 0)
    {
        printf("there is no such file\n");
        return part1();
    }
    fp= fopen(filename, "r");
    if (fp == NULL)
    {
        printf("Error: could not open file\n");
        return 1;
    }

    int counts[26] = {0};//each letter initialized to 0
    count_letters(fp, counts);

    fclose(fp);

    printf("\n\n");
}

const char *colorToString(Color c)
{
    switch (c)
    {
    case RED:
        return "RED";
    case GREEN:
        return "GREEN";
    case BLUE:
        return "BLUE";
    case YELLOW:
        return "YELLOW";
    case ORANGE:
        return "ORANGE";
    }
}

Color colorMixer(Color c1, Color c2, Color (*mixFunction)(Color, Color))
{
    return mixFunction(c1, c2);
}

void colorToVector(Color c, double v[3])
{
    switch (c)
    {
    case RED:
        v[0] = 1.0;
        v[1] = 0.0;
        v[2] = 0.0;
        break;
    case GREEN:
        v[0] = 0.0;
        v[1] = 1.0;
        v[2] = 0.0;
        break;
    case BLUE:
        v[0] = 0.0;
        v[1] = 0.0;
        v[2] = 1.0;
        break;
    case YELLOW:
        v[0] = 0.5;
        v[1] = 0.5;
        v[2] = 0.0;
        break;
    case ORANGE:
        v[0] = 0.5;
        v[1] = 0.4;
        v[2] = 0.2;
        break;
    }
}

Color charToColor(char c)
{
    switch (c)
    {
    case 'r':
    case 'R':
        return RED;
    case 'g':
    case 'G':
        return GREEN;
    case 'b':
    case 'B':
        return BLUE;
    case 'y':
    case 'Y':
        return YELLOW;
    case 'o':
    case 'O':
        return ORANGE;
    default:
        return RED; //To avoid a possible bug,returning red for invalid input
    }
}

Color mixFunction(Color c1, Color c2)
{
    // Converting the input colors to vectors
    double v1[3], v2[3];
    colorToVector(c1, v1);
    colorToVector(c2, v2);

    double vm[3];
    // Mixing 
    vm[0] = (v1[0] + v2[0]) / 2;
    vm[1] = (v1[1] + v2[1]) / 2;
    vm[2] = (v1[2] + v2[2]) / 2;

    //Euclidean distance part

    Color colors[] = {RED, GREEN, BLUE, YELLOW, ORANGE};
    //Array of color vectors
    double vectors[][3] = {{1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {0.0, 0.0, 1.0}, {0.5, 0.5, 0.0}, {0.5, 0.4, 0.2}};
    //Initialize the minimum distance and the closest color
    double minDist = 100;
    Color closestColor = RED;

    // Finding array that the minimum euclidean distance of the mixed vector
    for (int i = 0; i < 5; i++)
    {
        //Euclidean distance between mixed vector and color vectors
        double dist = sqrt(pow(vm[0] - vectors[i][0], 2) + pow(vm[1] - vectors[i][1], 2) + pow(vm[2] - vectors[i][2], 2));
        //If distance is smaller than minimum distance,update minimum distance and closest color
        if (dist < minDist)
        {
            minDist = dist;
            closestColor = colors[i];
        }
    }
    // Return closest color
    return closestColor;
}

void part2(){
    char c1, c2,ch;
    printf("Enter color 1 (r,g,b,y,o): ");
    scanf(" %c", &ch);
    c1 = charToColor(ch);

    printf("Enter color 2 (r,g,b,y,o): ");
    scanf(" %c", &ch);
    c2 = charToColor(ch);
    Color mixedColor = colorMixer(c1, c2, mixFunction);
    
    // Print the result
    printf("Mixed Color: %s", colorToString(mixedColor));

    // Converting mixed color to a vector
    double mixedVector[3];
    colorToVector(mixedColor, mixedVector);
    printf(" [%0.1f,%0.1f,%0.1f]\n\n", mixedVector[0], mixedVector[1], mixedVector[2]);

}


int game_status(char board[3][3]){
    int status=0,turn=0;
    //movement counter
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++)
        {
            if(board[i][j]!='_')
            turn++;
        }
    }
   
    //Horizontal status
    for (int i = 0; i < 3; i++){
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2])
        {
            if (board[i][0] != '_')
            {
            if (board[i][0] == 'X')
            {
                status = 1;
            }
            else
                status = 2;
            }
        }
    }
    
    //Vertical status
    for (int i = 0; i < 3; i++){
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i])
        {
            if (board[0][i] != '_')
            {
            if (board[0][i] == 'X')
            {
                status = 1;
            }
            else
                status = 2;
            }
        }
   }

    //Diagonal status
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2])
   {
        if (board[0][0] != '_')
        {
            if (board[0][0] == 'X')
            {
                status = 1;
            }
            else
                status = 2;
            }
    }
    if (board[2][0] == board[1][1] && board[1][1] == board[0][2])
    {
            if (board[2][0] != '_')
            {
            if (board[2][0] == 'X')
            {
                status = 1;
            }
            else
                status = 2;
            }
    }
    if (turn==9 && status==0)
    {
        status=9;//Draw
    }
    return status;
}
void display_table(char board[3][3]){
    int i,j;
    for ( i = 0; i < 3; i++){
        for ( j = 0; j < 3; j++){
            printf("%c", board[i][j]);
        }
        printf("\n");
    }
}
void movements(char board[3][3]){
    int row1,col1,row2,col2;
    do{
        printf("Player 1(X),enter your move(row,col): ");
        scanf("%d %d", &row1, &col1);
        //Overlap check 
        if (board[row1][col1] == '_' && board[row1][col1] != 'O')
        {
            board[row1][col1] = 'X';
        }
        else{
            board[row1][col1] = 'O';
            printf("Player 1(X),enter your move(row,col): ");
            scanf("%d %d", &row1, &col1);
            board[row1][col1] = 'X';
        }
        display_table(board);
        game_status(board);//winner check for player 1
        if (game_status(board) == 0)
        {
            printf("Player 2(O),enter your move(row,col): ");
            scanf("%d %d", &row2,&col2);
            if (board[row2][col2] == '_' && board[row2][col2] !='X'){
                board[row2][col2] = 'O';
            }
            else{
                board[row2][col2] = 'X';
                printf("Player 2(O),enter your move(row,col): ");
                scanf("%d %d", &row2, &col2);
                board[row2][col2] = 'O';
        }
        display_table(board);
        }
    } while (game_status(board) == 0);

   int endgame = game_status(board) ;

    // Checking who is winner
   if (endgame != 0){
        if (endgame == 1)
        {
        printf("Player 1 (X) Wins!\n");
        }
        if (endgame == 2)
        {
            printf("Player 2 (O) Wins!\n");
        }
        if (endgame == 9)
        {
            printf("Draw!\n");
        }
    }
}
void part3(){
    char board[3][3] = {{'_','_','_'},{'_', '_','_'},{'_','_','_'}};
    char prefer;
    movements(board);
    printf("Do you want to play again(Y/N)?: ");
    scanf(" %c",&prefer);
    switch (prefer)
    {
    case 'y':    
    case 'Y':
        return part3();
        break;
    case 'n':
    case 'N':
        printf("Goodbye...\n");
        break;  
    default:
        printf("Invalid value,Goodbye...\n");
        break;
    }
}

int main(){
part1();
part2();
part3();
return 0;
}