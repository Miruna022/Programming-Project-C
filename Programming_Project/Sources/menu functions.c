#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include "../Headers/menu functions.h"


int nav;
void menu(){
    printf("======================================\n");
    printf("||   What would you like to do?     ||\n");
    printf("||   1) Borrow a book               ||\n");
    printf("||   2) Return a book               ||\n");
    printf("||   3) Donate a book               ||\n");
    printf("||   4) View your loans             ||\n");
    printf("||   5) Search for a book           ||\n");
    printf("||   6) Log out                     ||\n");
    printf("======================================\n");
}

void add_to_csv(const char *file_name, const char *first_name, const char *last_name){
    FILE *file = fopen(file_name, "a");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }
    fprintf(file, "%s,%s\n", first_name, last_name);
    fclose(file);
    printf("Your account has been created successfully!\n");
}

char validate_choice (){
    char buffer[100];
    do{
        fgets(buffer,100,stdin);
        if (strlen(buffer) != 2 || buffer[0] < '1' || buffer[0] > '2'){
            printf("The value you entered is invalid. Please try again.\n");
        }
    } while (strlen(buffer) != 2 || buffer[0] < '1' || buffer[0] > '2');
    return buffer[0];
}

char validate_option (){
    char buffer[100];
    int option;
    do{
        fgets(buffer,100,stdin);
        if (sscanf(buffer, "%d", &option) != 1 || option < 1 || option > 6){
            printf("The value you entered is invalid. Please try again.\n");
        }
    } while (sscanf(buffer, "%d", &option) != 1 || option < 1 || option > 6);
    return option + '0';
}

int validate_name_create(char *first_name_buffer, char *last_name_buffer){
    char input[100];

    fgets(input, 100, stdin);
    input[strcspn(input, "\n")] = '\0';

    int count = sscanf(input, "create %s %s", first_name_buffer, last_name_buffer);
    if (count != 2 || strlen(first_name_buffer) == 0 || strlen(last_name_buffer) == 0){
        printf("Invalid input format. Please enter 'create [name] [surname]'.\n");
        return 0;
    }
    return 1;
}

int validate_name_login(char *first_name_buffer, char *last_name_buffer){
    char input[100];

    fgets(input, 100, stdin);
    input[strcspn(input, "\n")] = '\0';

    if (first_name_buffer[strlen(first_name_buffer) - 1] == '\n') {
        first_name_buffer[strlen(first_name_buffer) - 1] = '\0';
    }
    if (last_name_buffer[strlen(last_name_buffer) - 1] == '\n') {
        last_name_buffer[strlen(last_name_buffer) - 1] = '\0';
    }

    int count = sscanf(input, "login %s %s", first_name_buffer, last_name_buffer);
    if (count != 2 || strlen(first_name_buffer) == 0 || strlen(last_name_buffer) == 0){
        printf("Invalid input format. Please enter 'login [name] [surname]'.\n");
        return 0;
    }
    return 1;
}

int existing_name(const char *file_name, const char *first_name, const char *last_name){
    char buffer[100];
    char stored_first_name[100];
    char stored_last_name[100];
    int found = 0;

    FILE *file = fopen(file_name, "r");
    if (file == NULL){
        printf("Error opening file.\n");
        return 0;
    }
    while (fgets(buffer, 100, file) != NULL){
        sscanf(buffer, "%[^,],%s", stored_first_name, stored_last_name);
        if (strcmp(first_name, stored_first_name) == 0 && strcmp(last_name, stored_last_name) == 0){
            found = 1;
            break;
        }
    }
    fclose(file);
    return found;
}
