#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define BOARD_SIZE 10
#define MAX_OBSTACLES 3

typedef struct
{
    int row;
    int col;
} Point;

typedef struct
{
    char type;
    int value;
} Block;

typedef struct
{
    Point *body;
    int length;
} Snake;

Block **init_board();
void draw_board(Block** board, Snake snake);
void play();
void move(Snake* snake);
int check_status(Block** board, Snake snake);
void update(Block** board, Snake* snake);

Block **init_board()
{
    Block **board = (Block **)malloc(BOARD_SIZE * sizeof(Block *));
    // Initializing each block on the board
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        board[i] = (Block *)malloc(BOARD_SIZE * sizeof(Block));
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            board[i][j].type = 'e';
            board[i][j].value = 0;
        }
    }
    // Initializing the snake and the bait
    int snake_row = 0;
    int snake_col = 0;
    int bait_row, bait_col;
    do
    {
        bait_row = rand() % BOARD_SIZE;
        bait_col = rand() % BOARD_SIZE;
    } while (bait_row == snake_row && bait_col == snake_col);

    board[snake_row][snake_col].type = 'e';
    board[snake_row][snake_col].value = 0;
    
    // The bait's position
    board[bait_row][bait_col].type = 'b';
    board[bait_row][bait_col].value = 0;

    return board;
}

void draw_board(Block **board, Snake snake)
{
    printf("┌──────────┐\n");
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        printf("|");
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            int is_snake_body = 0;
            for (int k = 1; k < snake.length; k++)
            {
                if (i == snake.body[k].row && j == snake.body[k].col)
                {
                    is_snake_body = 1;
                    break;
                }
            }

            if (i == snake.body[0].row && j == snake.body[0].col)
            {
                printf("O");
            }
            else if (is_snake_body)
            {
                printf("X");
            }
            else if (board[i][j].type == 'o')
            {
                if (board[i][j].value <= 9)
                {
                    printf("%d", board[i][j].value);
                }
                else
                {
                    board[i][j].value = 9;
                    printf("%d", board[i][j].value);
                }
            }
            else if (board[i][j].type == 'b')
            {
                printf(".");
            }
            else
            {
                printf(" ");
            }
        }
        printf("|\n");
    }
    printf("└──────────┘\n");
}

void play()
{
    Block **board = init_board();
    Snake snake;
    snake.body = (Point *)malloc(sizeof(Point));
    snake.body[0].row = 0;
    snake.body[0].col = 0;
    snake.length = 1;

    int game_over = 0;
    while (!game_over)
    {
        draw_board(board, snake);
        move(&snake);
        game_over = check_status(board, snake);
        update(board, &snake);
    }

    printf("Game Over!\n");
    free(snake.body);
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        free(board[i]);
    }
    free(board);
}

void move(Snake *snake)
{
    char direction;
    printf("Enter direction (w/a/s/d): ");
    scanf(" %c", &direction);

    Point head = snake->body[0];
    Point new_head = head;
    switch (direction)
    {
    case 'w':
        new_head.row--;
        break;
    case 'a':
        new_head.col--;
        break;
    case 's':
        new_head.row++;
        break;
    case 'd':
        new_head.col++;
        break;
    }
    if (head.row == 'b' && head.col == 'b')
    {
        // If the snake eats the bait, increase length by 1
        snake->length++;
        snake->body = (Point *)realloc(snake->body, (snake->length + 1) * sizeof(Point));
    }
    else
    {
        // Shift the body positions
        for (int i = snake->length - 1; i > 0; i--)
        {
            snake->body[i] = snake->body[i - 1];
        }
    }

    // Updating the new head position
    snake->body[0] = new_head;
}

int check_status(Block **board, Snake snake)
{
    Point head = snake.body[0];
    for (int i = 1; i < snake.length; i++)
    {
        if (snake.body[i].row == head.row && snake.body[i].col == head.col)
        {
            return 1; // If Snake's head touches its body
        }
    }

    if (head.row < 0 || head.row >= BOARD_SIZE || head.col < 0 || head.col >= BOARD_SIZE)
    {
        return 1; // If snake collides with a wall
    }

    if (board[head.row][head.col].type == 'o' && board[head.row][head.col].value > snake.length)
    {
        return 1; // If the snake encounters an obstacle taller than itself
    }

    return 0;
}

void update(Block **board, Snake *snake)
{
    Point head = snake->body[0];

    if (board[head.row][head.col].type == 'b')
    {
        // Snake eats the bait
        int empty_found = 0;
        while (!empty_found)
        {
            // Finding a random empty cell for the bait
            int row = rand() % BOARD_SIZE;
            int col = rand() % BOARD_SIZE;
            if (board[row][col].type == 'e')
            {
                board[row][col].type = 'b';
                empty_found = 1;
            }
        }
        snake->length++;
        snake->body = (Point *)realloc(snake->body, (snake->length) * sizeof(Point));
    }
    else
    {
        // Shifting snake's body
        for (int i = snake->length - 1; i > 0; i--)
        {
            snake->body[i] = snake->body[i - 1];
        }
    }

    // Updating obstacles
    static int move_counter = 0;
    if (move_counter % 5 == 0)
    {
        int obstacle_count = 0;
        for (int i = 0; i < BOARD_SIZE; i++)
        {
            for (int j = 0; j < BOARD_SIZE; j++)
            {
                if (board[i][j].type == 'o')
                {
                    obstacle_count++;
                }
            }
        }

        if (obstacle_count < MAX_OBSTACLES)
        {
            int obstacle_row, obstacle_col;
            do
            {   // Finding a random empty cell for the new obstacle
                obstacle_row = rand() % (BOARD_SIZE - 1) + 1;
                obstacle_col = rand() % (BOARD_SIZE - 1) + 1;
            } while (board[obstacle_row][obstacle_col].type != 'e');

            board[obstacle_row][obstacle_col].type = 'o';
            board[obstacle_row][obstacle_col].value = 1;
        }
        else // Increment the value of each existing obstacle
        {
            for (int i = 0; i < BOARD_SIZE; i++)
            {
                for (int j = 0; j < BOARD_SIZE; j++)
                {
                    if (board[i][j].type == 'o')
                    {
                        board[i][j].value++;
                    }
                }
            }
        }
    }

    move_counter++;
}

int main()
{
    srand(time(NULL));
    play();
    return 0;
}
