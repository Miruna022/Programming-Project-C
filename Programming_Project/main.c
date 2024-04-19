#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "Headers/menu functions.h"
#include "Headers/donate.h"
#include "Headers/borrow.h"
#include "Headers/return.h"

void runLibrarySystem();

int main() {
    runLibrarySystem();
    return 0;
}

void runLibrarySystem() {
    char first_name[100], last_name[100];
    char choice = '0', option;
    char search[500];
    char nav = 'a';

    while (choice != '3') {
        printf("======================================\n");
        printf("||                                  ||\n");
        printf("||            WELCOME TO            ||\n");
        printf("||               THE                ||\n");
        printf("||             LIBRARY              ||\n");
        printf("||                                  ||\n");
        printf("||----------------------------------||\n");
        printf("||                                  ||\n");
        printf("||   Choose an option:              ||\n");
        printf("||   1) LOGIN                       ||\n");
        printf("||   2) SIGN UP                     ||\n");
        printf("||                                  ||\n");
        printf("======================================\n");

        choice = validate_choice();
        if (choice == '2') {
            printf("=============   SIGN UP   ============\n"
                   "Sign up using the command:\n"
                   "create [name] [surname] \n");
            if (validate_name_create(first_name, last_name)) {
                if (!existing_name("..\\CSV Files\\users.csv", first_name, last_name)) {
                    add_to_csv("..\\CSV Files\\users.csv", first_name, last_name);
                } else {
                    printf("An account with this name exists already.\n");
                }
            }
        }

        if (choice == '1') {
            printf("==============   LOGIN   =============\n"
                   "Login using the command:\n"
                   "login [name] [surname]\n");
            if (validate_name_login(first_name, last_name)) {
                if (!existing_name("..\\CSV Files\\users.csv", first_name, last_name)) {
                    printf("This account does not exist.\n");
                } else {
                    printf("Logged in successfully!\n");
                    while (option != 6) {
                        menu();
                        option = validate_option();
                        switch (option) {
                            case '1': {
                                printf("=============   BORROW   =============\n");
                                do{
                                    borrow_books("..\\CSV Files\\loans.csv", first_name, last_name);
                                    printf("Do you wish to borrow more books?\n");
                                    printf("    Yes(Y)           No(N)    \n");
                                    scanf("%c",&nav);
                                    getchar();
                                } while(nav =='y' || nav == 'Y');
                                break;
                            }
                            case '2': {
                                printf("=============   RETURN   =============\n");
                                printf("Are you sure you want to return the books?\n");
                                printf("      Yes(Y)                 No(N)        \n");
                                scanf("%c",&nav);
                                getchar();
                                if (nav =='y' || nav == 'Y') {
                                    return_books_to_library("..\\CSV Files\\loans.csv", "..\\CSV Files\\library.csv","..\\CSV Files\\extra2.csv", first_name, last_name);
                                }
                                break;
                            }
                            case '3': {
                                printf("=============   DONATE   =============\n");
                                do{
                                    donate_books("..\\CSV Files\\library.csv");
                                    printf("Do you wish to donate more books?\n");
                                    printf("    Yes(Y)           No(N)    \n");
                                    scanf("%c",&nav);
                                    getchar();
                                } while(nav =='y' || nav == 'Y');
                                break;
                            }
                            case '4': {
                                printf("=============   LOANS   ==============\n");
                                show_user_books("..\\CSV Files\\loans.csv", first_name, last_name);
                                break;
                            }
                            case '5': {
                                printf("=============   SEARCH   =============\n");
                                do{
                                    printf("What are you looking for?\n");
                                    fgets(search, 100, stdin);
                                    strtok(search, "\n");
                                    search_book("..\\CSV Files\\library.csv", search);
                                    printf("Do you wish to search anything else?\n");
                                    printf("    Yes(Y)           No(N)    \n");
                                    scanf("%c",&nav);
                                    getchar();
                                } while(nav =='y' || nav == 'Y');
                                break;
                            }
                            case '6': {
                                printf("Logging out . . .\n");
                                runLibrarySystem();
                                break;
                            }
                            default:
                                printf("Invalid choice. Please enter a number between 1 and 6.\n");
                        }
                    }
                }
            }
        }
    }
}
