#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 100

// Book structure
typedef struct Book {
    char isbn[MAX_LENGTH];
    char title[MAX_LENGTH];
    char author[MAX_LENGTH];
    int publicationYear;
    int reserved;
    struct Book* next;
} Book;

// Student structure
typedef struct Student {
    char name[MAX_LENGTH];
    int id;
    struct Book* borrowedBooks;
    struct Student* next;
} Student;

// Function prototypes
void displayMenu();
void loadLibrary();
void saveLibrary();
void addBook(char* isbn, char* title, char* author, int publicationYear, int method);
void deleteBook(char* isbn);
void updateBook(char* isbn, char* feature, char* value);
void filterAndSortBooks(int filterChoice, char* filter, int sortChoice);
void reverseBookList();
void searchBooks(int searchChoice, char* searchValue);
void displayBorrowedBooks(int studentId);

// Global variables
Book* bookList = NULL;
Student* studentList = NULL;

int main() {
    int choice;
    char isbn[MAX_LENGTH];
    char title[MAX_LENGTH];
    char author[MAX_LENGTH];
    int publicationYear;
    int method;
    char feature[MAX_LENGTH];
    char value[MAX_LENGTH];
    int filterChoice;
    char filter[MAX_LENGTH];
    int sortChoice;
    int searchChoice;
    char searchValue[MAX_LENGTH];
    int studentId;

    loadLibrary();

    do {
        displayMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // Clear the newline character from the input buffer

        switch (choice) {
            case 1:
                printf("Enter ISBN number: ");
                fgets(isbn, MAX_LENGTH, stdin);
                isbn[strcspn(isbn, "\n")] = '\0'; // Remove the newline character from the input
                printf("Enter title: ");
                fgets(title, MAX_LENGTH, stdin);
                title[strcspn(title, "\n")] = '\0';
                printf("Enter author: ");
                fgets(author, MAX_LENGTH, stdin);
                author[strcspn(author, "\n")] = '\0';
                printf("Enter publication year: ");
                scanf("%d", &publicationYear);
                getchar();
                printf("Enter book management method (0 for FIFO, 1 for LIFO): ");
                scanf("%d", &method);
                getchar();
                addBook(isbn, title, author, publicationYear, method);
                break;
            case 2:
                printf("Enter the ISBN number of the book to delete: ");
                fgets(isbn, MAX_LENGTH, stdin);
                isbn[strcspn(isbn, "\n")] = '\0';
                deleteBook(isbn);
                break;
            case 3:
                printf("Enter the ISBN number of the book to update: ");
                fgets(isbn, MAX_LENGTH, stdin);
                isbn[strcspn(isbn, "\n")] = '\0';
                printf("Enter the name of the feature to update (title, author, or publication year): ");
                fgets(feature, MAX_LENGTH, stdin);
                feature[strcspn(feature, "\n")] = '\0';
                printf("Enter the new value: ");
                fgets(value, MAX_LENGTH, stdin);
                value[strcspn(value, "\n")] = '\0';
                updateBook(isbn, feature, value);
                break;
            case 4:
                printf("Filter books by (0 for author, 1 for publication year): ");
                scanf("%d", &filterChoice);
                getchar();
                printf("Enter the filter value: ");
                fgets(filter, MAX_LENGTH, stdin);
                filter[strcspn(filter, "\n")] = '\0';
                printf("Sort books by (0 for title, 1 for author, 2 for publication year): ");
                scanf("%d", &sortChoice);
                getchar();
                filterAndSortBooks(filterChoice, filter, sortChoice);
                break;
            case 5:
                reverseBookList();
                break;
            case 6:
                printf("Search books by (0 for ISBN number, 1 for author, 2 for title): ");
                scanf("%d", &searchChoice);
                getchar();
                printf("Enter the search value: ");
                fgets(searchValue, MAX_LENGTH, stdin);
                searchValue[strcspn(searchValue, "\n")] = '\0';
                searchBooks(searchChoice, searchValue);
                break;
            case 7:
                printf("Enter the student ID: ");
                scanf("%d", &studentId);
                getchar();
                displayBorrowedBooks(studentId);
                break;
            case 8:
                saveLibrary();
                printf("Exiting the program.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }

        printf("\n");

    } while (choice != 8);

    return 0;
}

void displayMenu() {
    printf("Library Book Management System\n");
    printf("1. Add Book\n");
    printf("2. Delete Book\n");
    printf("3. Update Book\n");
    printf("4. Filter and Sort Books\n");
    printf("5. Reverse Book List\n");
    printf("6. Search Books\n");
    printf("7. Display Borrowed Books of a Student\n");
    printf("8. Exit\n");
}

void loadLibrary() {
    FILE* file = fopen("library.txt", "r");

    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    char line[MAX_LENGTH];

    while (fgets(line, sizeof(line), file)) {
        char isbn[MAX_LENGTH];
        char title[MAX_LENGTH];
        char author[MAX_LENGTH];
        int publicationYear;
        int reserved;

        sscanf(line, "%s %s %s %d %d", isbn, title, author, &publicationYear, &reserved);
        addBook(isbn, title, author, publicationYear, 0);
    }

    fclose(file);
}

void saveLibrary() {
    FILE* file = fopen("library.txt", "w");

    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    Book* current = bookList;

    while (current != NULL) {
        fprintf(file, "%s %s %s %d %d\n", current->isbn, current->title, current->author, current->publicationYear, current->reserved);
        current = current->next;
    }

    fclose(file);
}

void addBook(char* isbn, char* title, char* author, int publicationYear, int method) {
    Book* newBook = (Book*)malloc(sizeof(Book));
    strcpy(newBook->isbn, isbn);
    strcpy(newBook->title, title);
    strcpy(newBook->author, author);
    newBook->publicationYear = publicationYear;
    newBook->reserved = 0;

    if (method == 0) { // FIFO
        newBook->next = NULL;

        if (bookList == NULL) {
            bookList = newBook;
        } else {
            Book* current = bookList;

            while (current->next != NULL) {
                current = current->next;
            }

            current->next = newBook;
        }
    } else if (method == 1) { // LIFO
        newBook->next = bookList;
        bookList = newBook;
    }
}

void deleteBook(char* isbn) {
    Book* current = bookList;
    Book* previous = NULL;

    while (current != NULL) {
        if (strcmp(current->isbn, isbn) == 0) {
            if (previous == NULL) {
                bookList = current->next;
            } else {
                previous->next = current->next;
            }

            free(current);
            printf("Book deleted successfully.\n");
            return;
        }

        previous = current;
        current = current->next;
    }

    printf("Book not found.\n");
}

void updateBook(char* isbn, char* feature, char* value) {
    Book* current = bookList;

    while (current != NULL) {
        if (strcmp(current->isbn, isbn) == 0) {
            if (strcmp(feature, "title") == 0) {
                strcpy(current->title, value);
                printf("Book updated successfully.\n");
                return;
            } else if (strcmp(feature, "author") == 0) {
                strcpy(current->author, value);
                printf("Book updated successfully.\n");
                return;
            } else if (strcmp(feature, "publication year") == 0) {
                current->publicationYear = atoi(value);
                printf("Book updated successfully.\n");
                return;
            } else {
                printf("Invalid feature name.\n");
                return;
            }
        }

        current = current->next;
    }

    printf("Book not found.\n");
}

void filterAndSortBooks(int filterChoice, char* filter, int sortChoice) {
    Book* filteredBooks = NULL;

    // Filter the books
    Book* current = bookList;

    while (current != NULL) {
        if (filterChoice == 0) { // Filter by author
            if (strcmp(current->author, filter) == 0) {
                Book* newBook = (Book*)malloc(sizeof(Book));
                strcpy(newBook->isbn, current->isbn);
                strcpy(newBook->title, current->title);
                strcpy(newBook->author, current->author);
                newBook->publicationYear = current->publicationYear;
                newBook->reserved = current->reserved;
                newBook->next = NULL;

                if (filteredBooks == NULL) {
                    filteredBooks = newBook;
                } else {
                    Book* temp = filteredBooks;

                    while (temp->next != NULL) {
                        temp = temp->next;
                    }

                    temp->next = newBook;
                }
            }
        } else if (filterChoice == 1) { // Filter by publication year
            if (current->publicationYear == atoi(filter)) {
                Book* newBook = (Book*)malloc(sizeof(Book));
                strcpy(newBook->isbn, current->isbn);
                strcpy(newBook->title, current->title);
                strcpy(newBook->author, current->author);
                newBook->publicationYear = current->publicationYear;
                newBook->reserved = current->reserved;
                newBook->next = NULL;

                if (filteredBooks == NULL) {
                    filteredBooks = newBook;
                } else {
                    Book* temp = filteredBooks;

                    while (temp->next != NULL) {
                        temp = temp->next;
                    }

                    temp->next = newBook;
                }
            }
        }

        current = current->next;
    }

    // Sort the books
    if (sortChoice == 0) { // Sort by title
        // 
    } else if (sortChoice == 1) { // Sort by author
        // 
    } else if (sortChoice == 2) { // Sort by publication year
        // 
    }

    // Display the filtered and sorted books
    current = filteredBooks;

    while (current != NULL) {
        printf("ISBN: %s\n", current->isbn);
        printf("Title: %s\n", current->title);
        printf("Author: %s\n", current->author);
        printf("Publication Year: %d\n", current->publicationYear);
        printf("Reserved: %d\n", current->reserved);
        printf("\n");

        current = current->next;
    }

    // Free for filtered books
    current = filteredBooks;

    while (current != NULL) {
        Book* temp = current;
        current = current->next;
        free(temp);
    }
}

void reverseBookList() {
    Book* previous = NULL;
    Book* current = bookList;
    Book* next = NULL;

    while (current != NULL) {
        next = current->next;
        current->next = previous;
        previous = current;
        current = next;
    }

    bookList = previous;
}

void searchBooks(int searchChoice, char* searchValue) {
    Book* current = bookList;
    int found = 0;

    while (current != NULL) {
        if (searchChoice == 0) { // Search by ISBN number
            if (strcmp(current->isbn, searchValue) == 0) {
                printf("ISBN: %s\n", current->isbn);
                printf("Title: %s\n", current->title);
                printf("Author: %s\n", current->author);
                printf("Publication Year: %d\n", current->publicationYear);
                printf("Reserved: %d\n", current->reserved);
                printf("\n");

                found = 1;
                break;
            }
        } else if (searchChoice == 1) { // Search by author
            if (strcmp(current->author, searchValue) == 0) {
                printf("ISBN: %s\n", current->isbn);
                printf("Title: %s\n", current->title);
                printf("Author: %s\n", current->author);
                printf("Publication Year: %d\n", current->publicationYear);
                printf("Reserved: %d\n", current->reserved);
                printf("\n");

                found = 1;
                break;
            }
        } else if (searchChoice == 2) { // Search by title
            if (strcmp(current->title, searchValue) == 0) {
                printf("ISBN: %s\n", current->isbn);
                printf("Title: %s\n", current->title);
                printf("Author: %s\n", current->author);
                printf("Publication Year: %d\n", current->publicationYear);
                printf("Reserved: %d\n", current->reserved);
                printf("\n");

                found = 1;
                break;
            }
        }

        current = current->next;
    }

    if (!found) {
        printf("Book not found.\n");
    }
}

void displayBorrowedBooks(int studentId) {
    Student* current = studentList;
    int found = 0;

    while (current != NULL) {
        if (current->id == studentId) {
            Book* borrowedBooks = current->borrowedBooks;

            if (borrowedBooks == NULL) {
                printf("No borrowed books for this student.\n");
            } else {
                while (borrowedBooks != NULL) {
                    printf("ISBN: %s\n", borrowedBooks->isbn);
                    printf("Title: %s\n", borrowedBooks->title);
                    printf("Author: %s\n", borrowedBooks->author);
                    printf("Publication Year: %d\n", borrowedBooks->publicationYear);
                    printf("Reserved: %d\n", borrowedBooks->reserved);
                    printf("\n");

                    borrowedBooks = borrowedBooks->next;
                }
            }

            found = 1;
            break;
        }

        current = current->next;
    }

    if (!found) {
        printf("Student not found.\n");
    }
}
