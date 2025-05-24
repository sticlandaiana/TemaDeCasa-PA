#ifndef BOOKS_H //verifica daca BOOKS_H nu a fost inclus anterior in fisierul sursa
#define BOOKS_H //defineste BOOK_H

#include <stdio.h>
#include <stdint.h>
struct Book { //se defineste structura Book
    int pages; //fiecarei carti i se va atribui un numar de pagini
};

//se genereaza numarul de carti
int generate_num_books(void);

//se genereaza pagini pentru fiecare carte
void generate_pages(struct Book* books, int num_books);

//se afiseaza numarul fiecarei carti si cate pagini are
void print_books(struct Book* books, int num_books, FILE* file);

//se afla numarul total de pagini
int no_of_pages(struct Book* books, int num_books, FILE* file);


///se realizeaza impartirea raftului in sectiuni echitabile in ceea ce priveste numarul de pagini ale cartilor
void sections (struct Book* books, int num_books, FILE* file);

void sections2 (struct Book* books, int num_books, FILE* file);
#endif // se incheie blocul de cod conditionat de directiva #ifndef
