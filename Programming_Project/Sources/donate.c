#include "../Headers/donate.h"
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>
#define MAX_INPUT_LEN 550
#define MAX_LINE_LEN 100

struct Book{
    char title[100];
    char author[100];
    int copies;
};


bool book_exists(const char *file_name, const char *title, const char *author){
    FILE *file = fopen(file_name, "r");
    if (file == NULL){
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    char line[MAX_INPUT_LEN];
    while (fgets(line, sizeof(line), file) != NULL) {
        char *token = strtok(line, ",");
        if (strcmp(token, title) == 0) {
            token = strtok(NULL, ",");
            if (strcmp(token, author) == 0) {
                fclose(file);
                return true;
            }
        }
    }
    fclose(file);
    return false;
}

void donate_books(const char *file_name) {
    char input[MAX_INPUT_LEN];
    char title[100], author[100];
    int copies;

    printf("Enter book details (title, author, copies): \n");
    fgets(input, 256, stdin);

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
    if (book_exists(file_name, title, author)) {
        update_copies_in_csv(file_name, "..\\CSV Files\\extra.csv", title, author, copies);
    } else {
        add_book_to_library(file_name, title, author, copies);
    }

    printf("Book donation successfully recorded!\n");
}

void update_copies_in_csv(const char *file_name, const char *temp_file_name, const char *title, const char *author, int copies) {
    FILE *input_file, *temp_file, *output_file;
    char line[MAX_LINE_LEN];
    int found = 0;

    input_file = fopen(file_name, "r");
    if (input_file == NULL) {
        perror("Error opening input file");
        return;
    }

    temp_file = fopen(temp_file_name, "w");
    if (temp_file == NULL) {
        perror("Error opening temporary file");
        fclose(input_file);
        return;
    }

    while (fgets(line, sizeof(line), input_file)) {
        char entry_title[MAX_LINE_LEN], entry_author[MAX_LINE_LEN];
        int entry_copies;

        sscanf(line, "%[^,],%[^,],%d", entry_title, entry_author, &entry_copies);

        if (strcmp(entry_title, title) == 0 && strcmp(entry_author, author) == 0) {
            entry_copies += copies;
            found = 1;
        }

        fprintf(temp_file, "%s,%s,%d\n", entry_title, entry_author, entry_copies);
    }

    fclose(input_file);
    fclose(temp_file);

    if (!found) {
        printf("Book not found in the library. Unable to update copies.\n");
        remove(temp_file_name);
        return;
    }

    output_file = fopen(file_name, "w");
    if (output_file == NULL) {
        perror("Error opening output file");
        return;
    }

    temp_file = fopen(temp_file_name, "r");
    if (temp_file == NULL) {
        perror("Error opening temporary file");
        fclose(output_file);
        return;
    }

    while (fgets(line, sizeof(line), temp_file)) {
        fprintf(output_file, "%s", line);
    }

    fclose(output_file);
    fclose(temp_file);

    remove(temp_file_name);
}

void add_book_to_library(const char *file_name, const char *title, const char *author, int copies) {
    FILE *library_file;

    library_file = fopen(file_name, "a");
    if (library_file == NULL) {
        perror("Error opening library file");
        return;
    }

    fprintf(library_file, "%s,%s,%d\n", title, author, copies);
    fclose(library_file);
}
