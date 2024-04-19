#ifndef UNTITLED_MENU_FUNCTIONS_H
#define UNTITLED_MENU_FUNCTIONS_H

void menu();
void add_to_csv(const char *file_name, const char *first_name, const char *last_name);
char validate_choice ();
char validate_option ();
int validate_name_create(char *first_name_buffer, char *last_name_buffer);
int validate_name_login(char *first_name_buffer, char *last_name_buffer);
int existing_name(const char*file_name, const char *first_name, const char *last_name);

#endif //UNTITLED_MENU_FUNCTIONS_H
