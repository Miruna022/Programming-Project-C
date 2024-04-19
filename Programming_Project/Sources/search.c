#include "../Headers/return.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_INPUT_LEN 550

void search_book(const char *file_name, const char *search){
    FILE *file = fopen(file_name, "r");
    if (file == NULL){
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    char line[MAX_INPUT_LEN];
    int found = 0;
    printf("Matching results:\n");
    while (fgets(line, 256, file) != NULL) {
        char temp_title[100], temp_author[100];
        int copies;
        sscanf(line, "%[^,],%[^,],%d", temp_title, temp_author, &copies);
        if (strstr(temp_title, search) != NULL || strstr(temp_author, search) != NULL) {
            printf("%s by %s (%d copies)\n", temp_title, temp_author, copies);
            found = 1;
        }
    }

    if (!found) {
        printf("No matching results found.\n");
    }

    fclose(file);
}