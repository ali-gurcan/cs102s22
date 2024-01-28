#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORD_SIZE 12
#define MAX_LINE_LENGTH 7000
int read_dict(const char *file_name, char dict[][MAX_WORD_SIZE])
{
   
}
int read_text(const char *text_file, const char *ignore_file, char words[][MAX_WORD_SIZE]) 
{

}
double dissimilarity(char *w1, char *w2, char dict[][MAX_WORD_SIZE], float threshold, int *) 
{

}
int histogram(const char words[][MAX_WORD_SIZE], const int occurrences[], const char hist[][MAX_WORD_SIZE + 5 + 20]) 
{

}

int main(int argc, char *argv[])
{
    // Open the text file for reading
    FILE *file = fopen("input.txt", "r");
    if (file == NULL)
    {
        printf("Error opening file.");
        return 1;
    }

    // Prompt the user for input
    printf("Enter word(s): ");
    char word[MAX_WORD_SIZE];
    fgets(word, MAX_WORD_SIZE, stdin);
    strtok(word, "\n"); // Remove the newline character from the input

    // Loop through the text file and count the number of times the word appears
    char line[MAX_LINE_LENGTH];
    int count = 0;
    while (fgets(line, MAX_LINE_LENGTH, file))
    {
        char *token = strtok(line, " ");
        while (token != NULL)
        {
            if (strcmp(token, word) == 0)
            {
                count++;
            }
            token = strtok(NULL, " ");
        }
    }

    // Output the count to the console
    printf("\"%s\" appears  in \"input.txt\" %d times.\n", word, count);
    // Close the file
    fclose(file);

    return 0;
}