#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_LINE_LEN 550
#include "../Headers/return.h"

void return_books_to_library(const char *loans_file, const char *library_file, const char *temporary_file, const char *name_borrower, const char *surname_borrower) {
    FILE *loans = fopen(loans_file, "r");
    if (loans == NULL) {
        perror("Error opening loans file");
        exit(EXIT_FAILURE);
    }

    FILE *library = fopen(library_file, "r");
    if (library == NULL) {
        perror("Error opening library file");
        fclose(loans);
        exit(EXIT_FAILURE);
    }

    FILE *temp_file = fopen(temporary_file, "w"); // Temporary file to hold non-matching borrowed books
    if (temp_file == NULL) {
        perror("Error opening temporary file");
        fclose(loans);
        fclose(library);
        exit(EXIT_FAILURE);
    }

    char line[MAX_LINE_LEN];
    int books_returned = 0;

    while (fgets(line, 550, loans) != NULL) {
        char borrower_name[100], borrower_surname[100], title[100], author[100];
        int copies;

        // Parse the line to extract book details
        if (sscanf(line, "%[^,],%[^,],%[^,],%[^,],%d", borrower_name, borrower_surname, title, author, &copies) != 5) {
            // Invalid format, skip this line
            continue;
        }

        if (strcmp(borrower_name, name_borrower) == 0 && strcmp(borrower_surname, surname_borrower) == 0) {
            char lib_line[MAX_LINE_LEN];
            int found = 0;
            rewind(library);
            while (fgets(lib_line, sizeof(lib_line), library) != NULL) {
                char lib_title[100], lib_author[100];
                int lib_copies;
                if (sscanf(lib_line, "%[^,],%[^,],%d", lib_title, lib_author, &lib_copies) == 3) {
                    if (strcmp(lib_title, title) == 0 && strcmp(lib_author, author) == 0) {
                        lib_copies += copies;
                        found = 1;
                    }
                    fprintf(temp_file, "%s,%s,%d\n", lib_title, lib_author, lib_copies);
                }
            }
            if (!found) {
                printf("Error: Book not found in library: %s by %s\n", title, author);
            } else {
                books_returned++;
            }
        } else {
            fprintf(temp_file, "%s", line);
        }
    }

    fclose(loans);
    fclose(library);
    fclose(temp_file);

    remove(library_file);
    rename(temporary_file, library_file);

    // Empty the loans file
    FILE *empty_loans = fopen(loans_file, "w");
    if (empty_loans == NULL) {
        perror("Error opening loans file for emptying");
        exit(EXIT_FAILURE);
    }
    fclose(empty_loans);

    if (books_returned > 0) {
        printf("Returned %d book(s) to the library from loans for %s %s.\n", books_returned, name_borrower, surname_borrower);
    } else {
        printf("No books borrowed by %s %s.\n", name_borrower, surname_borrower);
    }
}

void show_user_books(const char *loans_file, const char *name_borrower, const char *surname_borrower) {
    FILE *loans = fopen(loans_file, "r");
    if (loans == NULL) {
        perror("Error opening loans file");
        exit(EXIT_FAILURE);
    }

    char line[MAX_LINE_LEN];
    int books_found = 0;

    printf("Books borrowed by %s %s:\n", name_borrower, surname_borrower);
    while (fgets(line, sizeof(line), loans) != NULL) {
        char borrower_name[100], borrower_surname[100], title[100], author[100];
        int copies;

        // Parse the line to extract book details
        if (sscanf(line, "%[^,],%[^,],%[^,],%[^,],%d", borrower_name, borrower_surname, title, author, &copies) != 5) {
            // Invalid format, skip this line
            continue;
        }

        // Check if the borrower matches the specified user
        if (strcmp(borrower_name, name_borrower) == 0 && strcmp(borrower_surname, surname_borrower) == 0) {
            printf("-%d copies of %s by %s\n", copies, title, author);
            books_found++;
        }
    }

    fclose(loans);

    if (books_found == 0) {
        printf("No books borrowed by %s %s.\n", name_borrower, surname_borrower);
    }
}
