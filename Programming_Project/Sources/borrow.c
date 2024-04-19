#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include "../Headers/borrow.h"
#define MAX_LINE_LEN 550
#define MAX_INPUT_LEN 100

bool book_in_library(const char *file_name, const char *title, const char *author){
    FILE *file = fopen(file_name, "r");
    if (file == NULL){
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    char line[MAX_INPUT_LEN];
    while (fgets(line, sizeof(line), file) != NULL) {
        // Tokenize the line to extract title, author, and copies
        char *token = strtok(line, ",");
        if (strcmp(token, title) == 0) {
            token = strtok(NULL, ",");
            if (strcmp(token, author) == 0) {
                fclose(file);
                return true; // Book already exists
            }
        }
    }
    fclose(file);
    return false; // Book does not exist
}

void borrow_books(const char *file_name, const char *name_borrower, const char *surname_borrower) {
    char input[MAX_INPUT_LEN]; // Input buffer
    char title[100], author[100];
    int copies;

    // Get book details from the user
    printf("What book would you like to borrow and how many copies of it? (title, author, copies): \n");
    fgets(input, 256, stdin);

    // Tokenize the input to extract title, author, and copies
    char *token = strtok(input, ",");
    if (token != NULL) {
        strcpy(title, token);
    } else {
        printf("Invalid input format.\n");
        return;
    }

    token = strtok(NULL, ",");
    if (token != NULL) {
        strcpy(author, token);
    } else {
        printf("Invalid input format.\n");
        return;
    }

    token = strtok(NULL, ",");
    if (token != NULL) {
        copies = atoi(token);
    } else {
        printf("Invalid input format.\n");
        return;
    }
    // Check if the book already exists in the library
    if (book_in_library("..\\CSV Files\\library.csv", title, author)) {
        // Check if the requested number of copies exceeds the available copies in the library
        int available_copies = get_available_copies("..\\CSV Files\\library.csv", title, author);
        if (copies <= get_available_copies("..\\CSV Files\\library.csv", title, author)) {
            add_book_to_loans(file_name, name_borrower, surname_borrower, title, author, copies);
            reduce_copies_in_csv("..\\CSV Files\\library.csv", "..\\CSV Files\\reduce.csv", title, author, copies);
            printf("Books were successfully borrowed!\n");
        } else {
            printf("Error: Requested number of copies exceeds the available copies in the library. There are %d copies left.\n", available_copies);
        }
    } else {
        printf("Book is not part of the library.\n");
    }
}

void reduce_copies_in_csv(const char *file_name, const char *temp_file_name, const char *title, const char *author, int copies) {
    FILE *input_file, *temp_file, *output_file;
    char line[MAX_LINE_LEN];
    int found = 0;

    // Open the input file in read mode
    input_file = fopen(file_name, "r");
    if (input_file == NULL) {
        perror("Error opening input file");
        return;
    }

    // Open the specified temporary file in write mode
    temp_file = fopen(temp_file_name, "w");
    if (temp_file == NULL) {
        perror("Error opening temporary file");
        fclose(input_file);
        return;
    }

    // Read input file line by line
    while (fgets(line, sizeof(line), input_file)) {
        char entry_title[MAX_LINE_LEN], entry_author[MAX_LINE_LEN];
        int entry_copies;

        // Tokenize the line based on commas
        sscanf(line, "%[^,],%[^,],%d", entry_title, entry_author, &entry_copies);

        // Check if the current line matches the provided title and author
        if (strcmp(entry_title, title) == 0 && strcmp(entry_author, author) == 0) {
            // Update the number of copies
            entry_copies -= copies;
            found = 1;
        }

        // Write the line (with possibly updated copies) to the temporary file
        fprintf(temp_file, "%s,%s,%d\n", entry_title, entry_author, entry_copies);
    }

    // Close files
    fclose(input_file);
    fclose(temp_file);

    // If book not found, remove temporary file and return
    if (!found) {
        printf("Book not found in the library. Unable to retrieve book.\n");
        remove(temp_file_name);
        return;
    }

    // Open the original file in append mode
    output_file = fopen(file_name, "w");
    if (output_file == NULL) {
        perror("Error opening output file");
        return;
    }

    // Open the temporary file in read mode
    temp_file = fopen(temp_file_name, "r");
    if (temp_file == NULL) {
        perror("Error opening temporary file");
        fclose(output_file);
        return;
    }

    // Append the content of the temporary file to the original file
    while (fgets(line, sizeof(line), temp_file)) {
        fprintf(output_file, "%s", line);
    }

    // Close files
    fclose(output_file);
    fclose(temp_file);

    // Remove the temporary file
    remove(temp_file_name);
}

void add_book_to_loans(const char *file_name, const char *name_borrower, const char *surname_borrower, const char *title, const char *author, int copies) {
    FILE *library_file;

    // Open the original library file for appending
    library_file = fopen(file_name, "a");
    if (library_file == NULL) {
        perror("Error opening library file");
        return;
    }


    // Write the new book details to the temporary file
    fprintf(library_file, "%s,%s,%s,%s,%d\n", name_borrower, surname_borrower, title, author, copies);
    fclose(library_file);
}

int get_available_copies(const char *file_name, const char *title, const char *author) {
    FILE *file = fopen(file_name, "r");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    char line[MAX_INPUT_LEN];
    while (fgets(line, sizeof(line), file) != NULL) {
        char entry_title[100], entry_author[100];
        int entry_copies;
        // Tokenize the line based on commas
        char *token = strtok(line, ",");
        // Extract title from the first token
        if (strcmp(token, title) == 0) {
            // Extract author from the next token
            token = strtok(NULL, ",");
            if (token != NULL && strcmp(token, author) == 0) {
                // Extract copies from the next token
                token = strtok(NULL, ",");
                entry_copies = atoi(token);
                fclose(file);
                return entry_copies; // Return the number of copies available
            }
        }
    }
    fclose(file);
    return 0; // Book not found or no copies available
}