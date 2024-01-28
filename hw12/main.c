#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct Node
{
    void *data;
    struct Node *next;
} Node;

typedef struct
{
    char type[20];
    int ivals[1];
    double svals[1];
} Asset1;

typedef struct
{
    char type[20];
    double svals[2];
    int ivals[2];
} Asset2;

typedef struct
{
    char type[20];
    char string1[50];
    char string2[50];
} Asset3;

typedef struct
{
    char type[20];
    double value1;
    float value2;
    double value3;
} Asset4;

void fillLinkedList(struct Node **head);
void serializeLinkedList(struct Node *head);
void deserializeLinkedList(struct Node **head);
void printLinkedList(struct Node *head);



void fillLinkedList(struct Node **head)
{
    srand(time(NULL));

    //Random numbers between 10 and 20
    int numAssets = rand() % 11 + 10; 


    for (int i = 0; i < numAssets; i++)
    {
        //Random numbers between 1 and 4
        int assetType = rand() % 4+1;

        Node* newNode = (Node *)malloc(sizeof(Node));
        
        
        switch (assetType)
        {
        case 1:
        {
            Asset1 *asset = malloc(sizeof(Asset1));
            strcpy(asset->type, "Asset1");
            asset->ivals[0] = rand() % 100;
            asset->svals[0] = (double)(rand() % 100) ;
            newNode->data = asset;
            break;
        }
        case 2:
        {
            Asset2 *asset = malloc(sizeof(Asset2));
            strcpy(asset->type, "Asset2");
            asset->svals[0] = (double)(rand() % 100) ;
            asset->svals[1] = (double)(rand() % 100) ;
            asset->ivals[0] = rand() % 100;
            asset->ivals[1] = rand() % 100;
            newNode->data = asset;
            break;
        }
        case 3:
        {
            Asset3 *asset = malloc(sizeof(Asset3));
            strcpy(asset->type, "Asset3");
            sprintf(asset->string1, "ali");
            sprintf(asset->string2, "gurcan");
            newNode->data = asset;
            break;
        }
        case 4:
        {
            Asset4 *asset = malloc(sizeof(Asset4));
            strcpy(asset->type, "Asset4");
            asset->value1 = (double)(rand() % 100) ;
            asset->value2 = (float)(rand() % 100) ;
            asset->value3 = (double)(rand() % 100) ;
            newNode->data = asset;
            break;
        }
        }

        if (*head == NULL){
            *head = newNode;
        }
        else{
            Node *curr = *head;
            while (curr->next != NULL)
            {
                curr = curr->next;
            }
            curr->next = newNode;
        }
    }
}

void serializeLinkedList(Node *head)
{
    FILE *file = fopen("linkedlist.bin", "wb");
    if (file == NULL)
    {
        printf("Error opening file for writing.\n");
        return;
    }

    Node* curr = head;
    while (curr != NULL)
    {
        if (strcmp(((Asset1 *)curr->data)->type, "Asset1") == 0)
        {
            fwrite(((Asset1 *)curr->data), sizeof(Asset1), 1, file);
        }
        else if (strcmp(((Asset2 *)curr->data)->type, "Asset2") == 0)
        {
            fwrite(((Asset2 *)curr->data), sizeof(Asset2), 1, file);
        }
        else if (strcmp(((Asset3 *)curr->data)->type, "Asset3") == 0)
        {
            fwrite(((Asset3 *)curr->data), sizeof(Asset3), 1, file);
        }
        else if (strcmp(((Asset4 *)curr->data)->type, "Asset4") == 0)
        {
            fwrite(((Asset4 *)curr->data), sizeof(Asset4), 1, file);
        }

        curr = curr->next;
    }

    fclose(file);
}

void printLinkedList( Node *head)
{
    Node *curr = head;
    while (curr != NULL)
    {
        if (strcmp(((Asset1 *)curr->data)->type, "Asset1") == 0)
        {
            Asset1 *asset = (Asset1 *)curr->data;
            printf("Type: %s, ", asset->type);
            printf("ival: %d, ", asset->ivals[0]);
            printf("sval: %lf\n", asset->svals[0]);
        }
        else if (strcmp(((Asset2 *)curr->data)->type, "Asset2") == 0)
        {
            Asset2 *asset = (Asset2 *)curr->data;
            printf("Type: %s, ", asset->type);
            printf("sval1: %lf, ", asset->svals[0]);
            printf("sval2: %lf,", asset->svals[1]);
            printf("ival1: %d,", asset->ivals[0]);
            printf("ival2: %d\n", asset->ivals[1]);
        }
        else if (strcmp(((Asset3 *)curr->data)->type, "Asset3") == 0)
        {
            Asset3 *asset = (Asset3 *)curr->data;
            printf("Type: %s, ", asset->type);
            printf("string1: %s, ", asset->string1);
            printf("string2: %s\n", asset->string2);
        }
        else if (strcmp(((Asset4 *)curr->data)->type, "Asset4") == 0)
        {
            Asset4 *asset = (Asset4 *)curr->data;
            printf("Type: %s, ", asset->type);
            printf("value1: %lf,", asset->value1);
            printf("value2: %f, ", asset->value2);
            printf("value3: %lf\n", asset->value3);
        }

        curr = curr->next;
    }
}
void deserializeLinkedList( Node **head)
{
    FILE *file = fopen("linkedlist.bin", "rb");
    if (file == NULL)
    {
        printf("Failed to open file.\n");
        return;
    }

    struct Node *current = NULL;
    while (!feof(file))
    {
        long position = ftell(file);

        //Reading the type field
        char type[20];
        fread(type, sizeof(char), 20, file);

        //Determine the size of the data structure by type
        size_t dataSize;
        if (strcmp(type, "Asset1") == 0)
        {
            dataSize = sizeof(Asset1);
        }
        else if (strcmp(type, "Asset2") == 0)
        {
            dataSize = sizeof(Asset2);
        }
        else if (strcmp(type, "Asset3") == 0)
        {
            dataSize = sizeof(Asset3);
        }
        else if (strcmp(type, "Asset4") == 0)
        {
            dataSize = sizeof(Asset4);
        }
        else
        {
            printf("Unknown type: %s\n", type);
        }

        //Allocating memory for the new node
        struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
        newNode->data = malloc(dataSize);
        newNode->next = NULL;

        //Positioning the file pointer to the beginning of the data

        fseek(file, position, SEEK_SET);

        //Reading serialized data to new node
        fread(newNode->data, dataSize, 1, file);

        //Connecting nodes to the linked list
        if (*head == NULL)
        {
            *head = newNode;
        }
        else
        {
            current->next = newNode;
        }
        current = newNode;
    }

    fclose(file);
}
int main()
{
    Node *head = NULL;

    fillLinkedList(&head);
    printf("Generated Linked List:\n");
    printf("--------------------\n");

    serializeLinkedList(head);

    printLinkedList(head);

    Node*  reconstructedHead = NULL;
    deserializeLinkedList(&reconstructedHead);
    printf("Reconstructed Linked List:\n");
    printf("--------------------\n");

    printLinkedList(reconstructedHead);

    free(head);
    free(reconstructedHead);

    return 0;
}
