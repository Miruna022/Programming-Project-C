#ifndef UNTITLED_DONATE_H
#define UNTITLED_DONATE_H
#include<stdbool.h>
void donate_books(const char *file_name);
void update_copies_in_csv(const char *file_name, const char *temp_file_name, const char *title, const char *author, int copies);
bool book_exists(const char *file_name, const char *title, const char *author);
void add_book_to_library(const char *file_name, const char *title, const char *author, int copies);

#endif //UNTITLED_DONATE_H
