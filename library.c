#include <stdio.h>
#include <string.h>

#define MAX_BOOKS 100 

typedef struct {
    char title[50];
    int isBorrowed;
} Book;
void addBook(Book *books, int *bookCount);
void checkBookStatus(Book *books, int bookCount);
void borrowBook(Book *books, int bookCount);
void returnBook(Book *books, int bookCount);
void saveToFile(Book *books, int bookCount);
void loadFromFile(Book *books, int *bookCount);
int menu();

int main() {
    Book books[MAX_BOOKS];
    int bookCount = 0;
    loadFromFile(books, &bookCount);

    printf("Welcome to the Iqra Library Management System!\n");

    while (1) {
        int choice = menu();

        switch (choice) {
            case 1:
                addBook(books, &bookCount);
                break;
            case 2:
                checkBookStatus(books, bookCount);
                break;
            case 3:
                borrowBook(books, bookCount);
                break;
            case 4:
                returnBook(books, bookCount);
                break;
            case 5:
                saveToFile(books, bookCount);
                printf("Thank you for using the Iqra Library Management System. Goodbye!\n");
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
int menu() {
    int choice;
    printf("\nChoose an option:\n");
    printf("1. Add a Book\n");
    printf("2. Check Book Status\n");
    printf("3. Borrow a Book\n");
    printf("4. Return a Book\n");
    printf("5. Exit\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    fflush(stdin); 
    return choice;
}

void addBook(Book *books, int *bookCount) {
    if (*bookCount >= MAX_BOOKS) {
        printf("Library is full. Cannot add more books.\n");
        return;
    }

    printf("Enter the title of the book: ");
    fflush(stdin); 
    fgets(books[*bookCount].title, 50, stdin);
    books[*bookCount].title[strcspn(books[*bookCount].title, "\n")] = '\0'; 
    books[*bookCount].isBorrowed = 0; 
    (*bookCount)++;
    printf("Book added successfully!\n");
}

void checkBookStatus(Book *books, int bookCount) {
    char title[50];
    printf("Enter the title of the book to check: ");
    fflush(stdin); 
    fgets(title, 50, stdin);
    title[strcspn(title, "\n")] = '\0'; 
int i;
    for ( i = 0; i < bookCount; i++) {
        if (strcmp(books[i].title, title) == 0) {
            if (books[i].isBorrowed == 0) {
                printf("The book '%s' is available.\n", books[i].title);
            } else {
                printf("The book '%s' is currently borrowed.\n", books[i].title);
            }
            return;
        }
    }
    printf("The book '%s' is not found in the library.\n", title);
}
void borrowBook(Book *books, int bookCount) {
    char title[50];
    printf("Enter the title of the book to borrow: ");
    fflush(stdin); 
    fgets(title, 50, stdin);
    title[strcspn(title, "\n")] = '\0'; 
int i;
    for ( i = 0; i < bookCount; i++) {
        if (strcmp(books[i].title, title) == 0) {
            if (books[i].isBorrowed == 0) {
                books[i].isBorrowed = 1;
                printf("You borrowed the book '%s'.\n", books[i].title);
            } else {
                printf("Sorry, the book '%s' is already borrowed.\n", books[i].title);
            }
            return;
        }
    }
    printf("The book '%s' is not found in the library.\n", title);
}

// Return a book
void returnBook(Book *books, int bookCount) {
    char title[50];
    printf("Enter the title of the book to return: ");
    fflush(stdin); // Clear input buffer
    fgets(title, 50, stdin);
    title[strcspn(title, "\n")] = '\0'; // Remove newline
int i;
    for ( i = 0; i < bookCount; i++) {
        if (strcmp(books[i].title, title) == 0) {
            if (books[i].isBorrowed == 1) {
                books[i].isBorrowed = 0;
                printf("You returned the book '%s'.\n", books[i].title);
            } else {
                printf("The book '%s' was not borrowed.\n", books[i].title);
            }
            return;
        }
    }
    printf("The book '%s' is not found in the library.\n", title);
}

// Save books to a file
void saveToFile(Book *books, int bookCount) {
    FILE *file = fopen("library.txt", "w");
    if (file == NULL) {
        printf("Error saving to file.\n");
        return;
    }
int i;
    fprintf(file, "%d\n", bookCount);
    for ( i = 0; i < bookCount; i++) {
        fprintf(file, "%s\n%d\n", books[i].title, books[i].isBorrowed);
    }

    fclose(file);
    printf("Library saved successfully!\n");
}

// Load books from a file
void loadFromFile(Book *books, int *bookCount) {
    FILE *file = fopen("library.txt", "r");
    if (file == NULL) {
        printf("No saved library data found. Starting fresh.\n");
        return;
    }
int i;
    fscanf(file, "%d\n", bookCount);
    for ( i = 0; i < *bookCount; i++) {
        fgets(books[i].title, 50, file);
        books[i].title[strcspn(books[i].title, "\n")] = '\0'; // Remove newline
        fscanf(file, "%d\n", &books[i].isBorrowed);
    }

    fclose(file);
    printf("Library loaded successfully!\n");
}
