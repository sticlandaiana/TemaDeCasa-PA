#include <stdlib.h>
#include <stdio.h> //se deschide biblioteca standard pentru functiile de citire si afisare
#include <time.h> //se include biblioteca standard pentru functii legate de timp, in cazul nostru functia de generare random
#include "books.h" //se include fisierul header care contine prototipurile functiilor folosite si
//definitia structurii Book
#include <stdint.h>
//se definesc doua constante care pot fi accesate usor in vederea modificarii dimensiunii cartilor
#define MIN_PAGES 50 //se defineste numarul minim de pagini pentru o carte
#define MAX_PAGES 1500 //se defineste numarul maxim de pagini pentru o carte

//generarea numarului de carti, numar cuprins intre 10^3 si 10^8
int generate_num_books()
{
    int lower_bound = 1000; //limita inferioaranin ceea ce priveste numarul de carti
    int upper_bound = 100000000; //limita superioara in ceea ce priveste maximuol de carti
    int num; //variabila pentru stocarea numarului generat


    srand(time(NULL)); //initializarea generatorului de numere aleatorii

    num = (rand() % (upper_bound - lower_bound + 1)) + lower_bound; //generarea unui numar aleatoriu intre limita superioara si cea inferioara



    return num; //se returneaza numarul generat
}


//generarea numarului de pagini pentru fiecare carte in parte
void generate_pages(struct Book* books, int num_books)
{

    for(int i = 0; i < num_books; i++) //se parcurge fiecare carte
    {
        // Generează un număr aleatoriu de pagini pentru fiecare carte între limitele tastate
        books[i].pages = MIN_PAGES + rand() / (RAND_MAX / (MAX_PAGES - MIN_PAGES + 1) + 1);
    }
}

//afisarea fiecarei carti impreuna cu dimensiunea
void print_books(struct Book* books, int num_books, FILE* file)
{
    for(int i = 0; i < num_books; i++)//parcurgerea cartilor
    {
        fprintf(file,"| %6d | %6d |\n", i+1, books[i].pages); //afisarea cartilor pe 6 spatii, pentru a mima aspectul unui tabel
    }
}

//aflarea numarului TOTAL de pagini
int no_of_pages(struct Book* books, int num_books, FILE* file)
{
    long long total_pages = 0; //variabila careia i se va atribui numarul de pagini prin insumare treptata, initializata cu 0
    for(int i = 0; i < num_books; i++)//parcurgerea cartilor
        total_pages += books[i].pages; //aflarea numarului total de pagini prin insumare
    return total_pages; //returnarea numarului total de pagini
}

//aflarea unei treimi din numarul total de pagini


///realizarea echitabila a celor trei sectiuni, printr-o functie de tipul greedy
void sections (struct Book* books, int num_books, FILE* file)
{
    long long total_pages = no_of_pages(books, num_books, file); //salveaza numarul total de pagini
    long long third = total_pages / 3; //calculeaza o treime din pagini, pentru a sti orientativ cate pagini i-ar reveni unui angajat
    long long pages[3] = {0, 0, 0}; //un vector cu trei el;emente care va reprezenta numarul de pagini pentru fievare angajat
    int section = 0; //sectiunea curenta, care poate sa fie 0, 1 sau 2

    for(int i = 0; i < num_books; i++) //parcurgerea cartilor
    {
        //daca suma dintre numarul curent de pagini si paginile cartii curente e mai mica decat o treime din totalul de pagini
        // sau am completat primele doua sectiuni si suntem la sectiunea 2, nr de pagini din sectiune se actualizeaza
        if(pages[section] + books[i].pages <= third || section == 2)
        {
            pages[section] += books[i].pages;
        }
        else //se trece la urmatoarea sectiune si se actualizeaza nr curent de pagini
        {
            section++;
            pages[section] += books[i].pages;
        }
    }
    fprintf(file, "===Rezultatele in cazul unei metode greedy===\n");
    fprintf(file, "Angajatul 1 este responsabil de %lld pagini.\n", pages[0]);
    fprintf(file, "Angajatul 2 este responsabil de %lld pagini.\n", pages[1]);
    fprintf(file, "Angajatul 3 este responsabil de %lld pagini.\n", pages[2]);
}

///realizarea celor trei sectiuni, printr-o metoda exhaustiva
void sections2 (struct Book* books, int num_books, FILE* file)
{
    long long total_pages = no_of_pages(books, num_books, file); //se afla numarul total de pagini
    long long pages[3] = {0, 0, 0}; //se realizeaza vectorul reprezentand sectiunile
    long long min_pages, max_pages, diff, min_diff = total_pages; //se declara variabile pentru a calcula diferenta minima globala, aceasta fiind initializata cu nr maxim de magini
    int first_break = 0, second_break = 0; //pozitiile despartitoare dintre sectoiuni

    for(int i = 0; i < num_books - 2; i++) //parcurge toate cartile incercand fiecare ppunct de impartire
    {
        pages[0] += books[i].pages; //paginile cartii curente sunt adaugate in prima sectiune
        pages[1] = 0; //nr de pagini pentru a doua sectiune este resetat la 0 pentru fiecare i
        for(int j = i + 1; j < num_books - 1; j++)
        {
            pages[1] += books[j].pages;//paginile cartii curente sunt adaugate in a doua sectiune
            pages[2] = total_pages - pages[0] - pages[1]; //restul de pagini ramase sunt adaugate in sectiunea a treia
            // Determinarea numărului minim de pagini
            if(pages[0] < pages[1])
            {
                if(pages[0] < pages[2])
                {
                    min_pages = pages[0];
                }
                else
                {
                    min_pages = pages[2];
                }
            }
            else
            {
                if(pages[1] < pages[2])
                {
                    min_pages = pages[1];
                }
                else
                {
                    min_pages = pages[2];
                }
            }

            // Determinarea numărului maxim de pagini
            if(pages[0] > pages[1])
            {
                if(pages[0] > pages[2])
                {
                    max_pages = pages[0];
                }
                else
                {
                    max_pages = pages[2];
                }
            }
            else
            {
                if(pages[1] > pages[2])
                {
                    max_pages = pages[1];
                }
                else
                {
                    max_pages = pages[2];
                }
            }


            diff = max_pages - min_pages; //aflarea diferentei dintre numarul maxim de pagini si cel minim
            if(diff < min_diff) //aflarea diferentei minime globale
            {
                min_diff = diff; //actualizarea diferentei minime globale
                first_break = i; //primul marcator de pozitie, dintre sectiunea 0 si sectiunea 1
                second_break = j; //al doilea marcator de pozitie, dintre sectiunea 2 si sectiunea 3
            }
        }
    }

    //resetarea sectiunilor, in vederea recalcularii lor in functie de marcatorii de pozitie
    pages[0] = pages[1] = pages[2] = 0;

    for(int i = 0; i < num_books; i++) //parcurgerea cartilor
    {
        if(i <= first_break)
            pages[0] += books[i].pages; //aflarea primei sectiuni
        else if(i <= second_break)
            pages[1] += books[i].pages;
        //aflarea celei de-a doua sectiuni
        else
            pages[2] += books[i].pages; //aflarea celei de-a treia sectiuni
    }
    fprintf(file, "===Rezultatele in cazul unei metode de cautare exhaustive===\n");
    fprintf(file, "Angajatul 1 este responsabil de %lld pagini.\n", pages[0]);
    fprintf(file, "Angajatul 2 este responsabil de %lld pagini.\n", pages[1]);
    fprintf(file, "Angajatul 3 este responsabil de %lld pagini.\n", pages[2]);
}

