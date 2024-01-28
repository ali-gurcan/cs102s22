#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 500
#define MAX_TREE_NAME_LENGTH 500
#define MAX_FILENAME_LENGTH 500
#define MAX_CHILDREN 5

typedef struct Node{
    char name[MAX_NAME_LENGTH];
    int age;
    struct Node* mother;
    struct Node* father;
    struct Node** child;
}Node;

void saveFamilyTree(Node* root, char* treeName,int flag);
Node* loadFamilyTree(char *treeName);
Node* addNodeToTree(Node* root,int flag);
void removeNodeFromTree(Node* root, Node* node);
void printFamilyDetails(Node* root);
Node* findNode(Node *root, const char *name);


//At first I updated root and made root->fater->father,
//But the struct structure in the assignment is not suitable for this, 
//Because father and mother are like brothers
//Therefore,I assigned root as grandfather as shown in pdf

int main(){
    int flag=0;
    //int i=0;
    char treeName[MAX_TREE_NAME_LENGTH];

    Node* root = NULL;

    while (1) {
        int choice, choice2,choice3,choice4;

        printf("Family Tree System Menu:\n");
        printf("1-Add family tree\n");
        printf("2-Remove family tree\n");
        printf("3-Load Family Tree\n");
        printf("4-Exit\n");
        printf("> ");

        scanf("%d", &choice);
        getchar();  // Consume the newline character

        switch (choice) {
            case 1:
                do 
                {
                    printf("1-Add node \n");
                    printf("2-Save family Tree \n");
                    printf("3-Exit\n");
                    printf("> ");
                    scanf("%d", &choice2);
                    getchar();

                    switch (choice2)
                    {
                    case 1:
                        root = addNodeToTree(root, flag);

                        if (root!=NULL)
                        {
                           if (root->child!=NULL){
                            //flag keeps child number
                            flag++;
                           } 
                        }

                        break;
                    case 2:
                        if(root==NULL){
                           printf("Please create a family tree first\n");
                        }
                        else{
                           printf("Enter the name for the new family tree(without using.txt): ");
                           fgets(treeName, MAX_TREE_NAME_LENGTH, stdin);
                           treeName[strcspn(treeName, "\n")] = '\0'; // Remove trailing newline
                           saveFamilyTree(root, treeName, flag);
                           printf("Family tree saved successfully!\n");
                           // Adds the family to familyList.txt
                           FILE *fp;
                           fp = fopen("familyList.txt", "a");
                           fprintf(fp, "%s\n", treeName);
                           fclose(fp); 
                        }

                        break;
                    case 3:
                       
                        break;
                    default:
                        break;
                    }
                } while (choice2 < 1 || choice2>3);
                break;
            case 2:

                printf("Enter the surname of the family tree to remove(without using.txt): ");
                fgets(treeName, MAX_TREE_NAME_LENGTH, stdin);
                treeName[strcspn(treeName, "\n")] = '\0';  // Remove trailing newline
                remove(strcat(treeName, ".txt"));
                printf("%s has been removed successfully!\n",treeName);
                break;
            case 3:
                printf("Listing Family Trees\n");
                
                //Reads and prints famliyList.txt 
                char line[MAX_NAME_LENGTH];
                FILE* fp;
                fp=fopen("familyList.txt","r");
                if (fp == NULL){
                    printf("Failed to open the file.\n");
                    return 1;
                }
                while (fgets(line, sizeof(line), fp)){
                    printf("- %s", line);
                }
                printf("\n");
                fclose(fp);


                printf("Select the family(without.txt): ");
                fgets(treeName, MAX_FILENAME_LENGTH, stdin);
                treeName[strcspn(treeName, "\n")] = '\0';

                printf("%s has been selected...\n", treeName);
                
                //Load family from text file 
                Node* root =loadFamilyTree(treeName);
                do
                {
                    printf("Select an operation\n");
                    printf("1- Add new person\n");
                    printf("2- Remove a person\n");
                    printf("3- Print a Person's nuclear family\n");
                    printf("4- Search Relatives of Given Person\n");
                    printf("5- Return to the main menu\n");
                    printf(">");
                    scanf("%d", &choice3);
                    getchar();
                    switch (choice3)
                    {
                    case 1:
                        root = addNodeToTree(root, flag);
                        if (root != NULL)
                        {
                            if (root->child != NULL)
                            {
                                flag++;
                            }
                        }
                        //saveFamilyTree(root, treeName, flag);
                        choice3 = 0;

                        break;
                    case 2:
                        if (root == NULL)
                        {
                        printf("Please create a family tree first!\n");
                        }
                        else
                        {
                        char nodeName[MAX_NAME_LENGTH];
                        printf("Enter the name of the person to remove: ");
                        fgets(nodeName, MAX_NAME_LENGTH, stdin);
                        nodeName[strcspn(nodeName, "\n")] = '\0'; // Remove trailing newline
                      
                        Node *nodeToRemove = findNode(root, nodeName);
                        if (nodeToRemove != NULL)
                        {
                        
                        if (nodeToRemove->age<30)
                        {
                            //a child is assumed to be a maximum of 30 years old
                            flag--;
                        }
                        
                        remove(strcat(treeName,".txt"));
                        saveFamilyTree(root, treeName, flag);
                        printf("Person removed successfully!\n");
                        }
                        else{
                        printf("Person not found in the family tree!\n");
                        }
                        }
                        choice3 = 0;

                        break;
                    case 3:
                        if (root == NULL)
                        {
                        printf("Please create a family tree first!\n");
                        }
                        else
                        printFamilyDetails(root);
                        choice3=0;
                        break;
                    case 4:
                        if (root == NULL)
                        {
                        printf("Please create a family tree first!\n");
                        }
                        else{
                        do{                              
                        printf("1- Parents\n");
                        printf("2- Childrens\n");
                        printf("3- Grandparent\n");
                        printf(">");
                        scanf("%d",&choice4);
                        getchar();
                        switch (choice4)
                        {
                        case 1:
                        if (root->father != NULL){
                            printf("Father: %s\n", root->father->name);
                        }
                        else{
                            printf("Father: Unknown\n");
                        }
                        if (root->mother != NULL){
                            printf("Mother: %s\n", root->mother->name);
                        }
                        else{
                            printf("Mother: Unknown\n");
                        }
                            break;
                        case 2:
                            for (int q = 0; q < MAX_CHILDREN; q++)
                            {
                            printf("Siblings: %s \n", root->child[q]->name);
                            if (root->child[q + 1]->age == 0)
                            {
                                break;
                            }
                            }
                            break;
                        case 3:
                            printf("Grandfather: %s\n", root->name);

                            break;
                        default:
                        break;
                        }
                        
                        }while(choice4<1||choice4>3);
                        }
                        choice3 = 0;
                        break;
                    case 5:

                        memset(treeName, '\0', sizeof(treeName));

                        //free(root);
                        break;
                    default:
                        printf("Invalid choice! Please try again.\n");
                    }

                }while (choice3<1||choice3>5);
                break;
            case 4:
                if (root != NULL){
                    free(root);
                }

                printf("Exiting the program...\n");
                exit(0);
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}

void saveFamilyTree(Node* root, char* treeName,int flag) {
    int k;
    FILE* file;
    char fileName[MAX_FILENAME_LENGTH];
    snprintf(fileName, MAX_FILENAME_LENGTH, "%s.txt", treeName);
    file = fopen(fileName, "a+");
    if (file == NULL) {
        printf("Error creating the file!\n");
        return;
    }

    if (root != NULL) {

        fprintf(file, "%s %d\n", root->name, root->age);
        
        fprintf(file, "%s %d\n", root->father->name, root->father->age);
        
        fprintf(file, "%s %d\n", root->mother->name, root->mother->age);

        for ( k=0; k <flag; k++)
        {
            fprintf(file, "%s %d\n", root->child[k]->name, root->child[k]->age);


        }
        
    }

    fclose(file);
}

Node* loadFamilyTree(char* treeName) {
    FILE* file;
    char fileName[MAX_FILENAME_LENGTH];
    snprintf(fileName, MAX_FILENAME_LENGTH, "%s.txt", treeName);
    file = fopen(fileName, "r");
    if (file == NULL) {
        printf("Error loading the file!\n");
        return NULL;
    }
    int flag=0;
    Node *root = (Node *)malloc(sizeof(Node));
    root->father = (Node *)malloc(sizeof(Node));
    root->mother = (Node *)malloc(sizeof(Node));
    root->child = (Node **)malloc(MAX_CHILDREN * sizeof(Node *));

   
        fscanf(file, "%s %d", root->name, &(root->age));

        fscanf(file, "%s %d", root->father->name, &(root->father->age));

        fscanf(file, "%s %d", root->mother->name, &(root->mother->age));
        for (int i = 0; i < MAX_CHILDREN; i++)
        {
            fscanf(file, "%s %d", root->child[i]->name, &(root->child[i]->age));
            
        }
        int i = 0;
        while (!feof(file))
        {
            root->child[i] = (Node *)malloc(sizeof(Node));
            fscanf(file, "%s %d", root->child[i]->name, &(root->child[i]->age));
            i++;
        }
        fclose(file);
        return root;

      
}


Node* addNodeToTree(Node* root,int flag) 
{
    //FOR FIRST ATTEMPT
    if(root==NULL){
        Node* root = (Node *)malloc(sizeof(Node));
        if (root == NULL)
        {
            printf("Memory allocation failed!\n");
            exit(1);
        }

    printf("Enter the grandfather name: ");
    fgets(root->name, MAX_NAME_LENGTH, stdin);
    root->name[strcspn(root->name, "\n")] = '\0'; // Remove trailing newline

    printf("Enter the age: ");
    scanf("%d", &(root->age));
    getchar(); // Consume the newline character

    root->father = NULL;
    root->mother = NULL;
    root->child = NULL;
    return root;
    }
    // FOR REST ATTEMPTS

    if (root->father == NULL){
        root->father = (Node *)malloc(sizeof(Node));
    }

    if (root->mother == NULL){
        root->mother = (Node *)malloc(sizeof(Node));
    }  

    if (root->child == NULL){
        root->child = (Node **)malloc(MAX_CHILDREN * sizeof(Node *));
    }
        
    if (root->child[flag]==NULL)
        {
        root->child[flag] = (Node *)malloc(sizeof(Node));
        }
        
        
        root->child[flag]->father = root->father;
        root->child[flag]->mother = root->mother;
    
    if (root != NULL){
        if (root->mother->age == 0){
            if (root->mother->age == 0){
                printf("Enter the name of the mother: ");
                fgets(root->mother->name, MAX_NAME_LENGTH, stdin);
                root->mother->name[strcspn(root->mother->name, "\n")] = '\0'; 

                printf("Enter the mother's age: ");
                scanf("%d", &(root->mother->age));
                getchar();
        
            }
            if (root->father->age == 0){
                printf("Enter the name of the father: ");
                fgets(root->father->name, MAX_NAME_LENGTH, stdin);
                root->father->name[strcspn(root->father->name, "\n")] = '\0'; 

                printf("Enter the father's age: ");
                scanf("%d", &(root->father->age));
                getchar();
            }
        }     
                
        printf("Enter the name of the child: ");
        fgets(root->child[flag]->name, MAX_NAME_LENGTH, stdin);
        root->child[flag]->name[strcspn(root->child[flag]->name, "\n")] = '\0'; 

        printf("Enter the child's age: ");
        scanf("%d", &(root->child[flag]->age));
        getchar(); // Consume the newline character


    }

    printf("Person(s) added successfully!\n");
   
    return root;
}

void removeNodeFromTree(Node* root, Node* node) {
    if (root == NULL || node == NULL) {
        return;
    }

    if (root->mother == node) {
        root->mother = NULL;
    }

    if (root->father == node) {
        root->father = NULL;
    }

    
    free(node);
}

void printFamilyDetails(Node* root) {
    if (root == NULL) {
        return;
    }
    int i;
    printf("----------------\n");
    printf("Printing nuclear family...\n");
    printf("Father: %s\n", root->father->name);
    printf("Mother: %s\n", root->mother->name);
    for ( i = 0; i < MAX_CHILDREN; i++)
    {
        printf("Siblings: %s \n",root->child[i]->name);
        if (root->child[i+1]->age==0)
        {
            break;
        }
        
    }
    
}

Node* findNode(Node *root, const char *name){
    if (root == NULL)
    {
        return NULL;
    }
    if (strcmp(root->name, name) == 0)
    {
        return root;
    }

    

    if (strcmp(root->father->name, name) == 0)
    {
        return root->father;
    }

    if (strcmp(root->mother->name, name) == 0)
    {
        return root->mother;
    }

    for (int i = 0; i < MAX_CHILDREN; i++)
    {
        if (strcmp(root->child[i]->name, name) == 0)
        {
            return root->child[i];
        }
    }
}

