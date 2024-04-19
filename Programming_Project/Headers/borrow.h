#ifndef UNTITLED_BORROW_H
#define UNTITLED_BORROW_H

void borrow_books(const char *file_name, const char *name_borrower, const char *surname_borrower);
void reduce_copies_in_csv(const char *file_name, const char *temp_file_name, const char *title, const char *author, int copies);
void add_book_to_loans(const char *file_name, const char *name_borrower, const char *surname_borrower, const char *title, const char *author, int copies);
bool book_in_library(const char *file_name, const char *title, const char *author);
int get_available_copies(const char *file_name, const char *title, const char *author);
#endif //UNTITLED_BORROW_H
