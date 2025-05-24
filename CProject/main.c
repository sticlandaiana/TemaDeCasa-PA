#include <stdio.h> //se introduce biblioteca standard pentru functiile de afisare, citire si deschiderea unui fisier
#include <stdlib.h> //se include biblioteca standard pentru functiile malloc si free
                    //folosite pentru alocarea memoriei si eliberarea memoriei

#include "books.h" //se include fisierul header care contine prototipurile functiilor folosite si
                   //definitia structurii Book

#include <stdint.h>
int main() {
    int num_books = generate_num_books(); //variabile num_books i se atribuie o valoare random prin apelarea functiei generate_num_books
    long long pages; //se declara o variabila care va stoca numarul total de pagini, iar apoi va fi folosita pentru a retine o treime din pagini
                     //din moment ce pot fi generate pana la 10^8 carti, acest numar poate fi foarte mare

    struct Book* books = malloc(num_books * sizeof(struct Book)); //se aloca memorie pentru un tablou ce va reprezenta totalitatea cartilor de pe raft

    generate_pages(books, num_books); //se apeleaza functia care va genera random pagini pentru toate cele "num_books" carti

    FILE* file = fopen("books11.txt", "w"); //se deschide un fisier in care vor fi inregistrate rezultatele
    //se verifica daca fisierul a fost deschis cu succes
    if (file == NULL) {
        printf("Nu s-a putut deschide fișierul books1.txt\n"); //se afideaza un mesaj corespunzator
        free(books); //se elibereaza memoria
        return 1; //se incheie programul returnandu-se 1
    }

    fprintf(file, "Numărul de cărți este %d\n", num_books); //se va afisa in fisier numarul de carti impreuna cu mesajul sugestiv

    //se va simula aspectul unui tabel si se va afisa in tabel numarul cartii si cate pagini are aceasta
    fprintf(file, "\n| Cartea | Pagini |\n");
    fprintf(file, "|--------|--------|\n");
    print_books(books, num_books, file);

    //se calculeaza numarul de pagini, i se atribuie variabilei pages si se afiseaza in fisier
    pages=no_of_pages(books, num_books, file);
    fprintf(file, "Numerul TOTAL de pagini este %lld\n", pages);

    //se calculeaza cat reprezinta o treime din pagini, se refoloseste variabile pages pentru a inregistra acest numar si se afiseaza
    pages=pages/3;
    fprintf(file, "O TREIME de pagini este reprezentata %lld\n", pages);

    //se apeleaza functia care asigura impartirea echitabila a raftului de carti in trei sectiuni
    sections(books, num_books, file);
    sections2(books, num_books, file);

    fclose(file); //se inchide fisierul
    free(books); // se eleibereaza memoria alocata

    return 0; //programul se incheie fara erori
}
