import random #importarea modulului random pentru generarea de numere aleatorii
import time #importarea modulului random pentru a obtine timpul curent

class Book: #definim o clasa numita Book
    def __init__(self, pages): #constructorul clasei Book, care primeste numarul de pagini ca argument
        self.pages = pages #atribuirea numarului de pagini

def generate_num_books(): #functia care genereaza numarul de carti
    lower_bound = 1000 #limita inferioara
    upper_bound = 100000000#limita superioara
    random.seed(time.time()) #initializarea generatorului de numere cu timpul curent
    return random.randint(lower_bound, upper_bound) #generarea unui numar aleatoriu

def generate_pages(num_books): #functia care genereaza numarul de pagini pentru fiecare carte
    MIN_PAGES = 50 #numarul minim de pagini pe care o carte poate sa le aiba
    MAX_PAGES = 1500 #numarul maxim de pagini pe care o carte poate sa le aiba
    books = [Book(random.randint(MIN_PAGES, MAX_PAGES)) for _ in range(num_books)] #generarea numarului de pagini pentru fiecare carte
    return books #returnarea listei de carti

def print_books(books, file): #functia care afiseaza cartile si numarul de pagini ale acestora
    file.write("\n| Cartea | Pagini |\n") #se vor afisa datele intr-un format prietenos cu utilizatorul
    file.write("|--------|--------|\n")
    for i, book in enumerate(books): #se parcurge lista de carti
        file.write(f"| {i+1:6} | {book.pages:6} |\n") #se afiseaza datele corespunzatoare

def no_of_pages(books): #functia care returneaza numarul total de pagini
    return sum(book.pages for book in books) #se returneaza suma

def sections(books, num_books, file): #functia care imparte cartile intre angajati folosind o metoda greedy
    total_pages = no_of_pages(books) #se calculeaza numarul total de pagini, prin apelarea functiei anterioare
    third = total_pages // 3 #se afla o treime din numarul total de pagini
    pages = [0, 0, 0] #se initializeaza numarul de pagini ce-i revin fiecarui angajat
    section = 0 #initializam sectiunea curenta cu 0

    for book in books: #parcurgem lista de carti
        if pages[section] + book.pages <= third or section == 2: #adaugam paginile urmatoarei carti daca suma nu depaseste o treime din total sau suntem la ultima sectiune
            pages[section] += book.pages
        else: #altfel
            section += 1 #trecem la noua sectiune
            pages[section] += book.pages #adaugam paginile la noua sectoiune

    file.write("===Rezultatele in cazul unei metode greedy===\n") #se afiseaza rezultatele
    file.write(f"Angajatul 1 este responsabil de {pages[0]} pagini.\n")
    file.write(f"Angajatul 2 este responsabil de {pages[1]} pagini.\n")
    file.write(f"Angajatul 3 este responsabil de {pages[2]} pagini.\n")

def sections2(books, num_books, file): #functie care imparte cartile prin o metoda exhaustiva
    total_pages = no_of_pages(books) #se afla numarul total de pagini
    pages = [0, 0, 0] #initializam nr de pagini pentru fiecare angajat cu 0
    min_diff = total_pages #initializam diferenta minima cu numarul total de pagini
    first_break = 0 #initializam prima pauza din lista cu 0
    second_break = 0 #initializam a doua pauza din lista cu 0

    for i in range(num_books - 2): #parcurgerea listei de carti pana la penultima carte
        pages[0] += books[i].pages #adaugam paginile cartii curente in sectiunea primului angajat
        pages[1] = 0 #resetam numarul de pagini pentru al doilea angajat
        for j in range(i + 1, num_books - 1): #parcurgem lista de carti de la cartea curenta pana la ultima carte
            pages[1] += books[j].pages #adaugam paginile cartii curente la al doilea angajat
            pages[2] = total_pages - pages[0] - pages[1] #calculam numarul de pagini pentru al treilea angajat ca fiind restul de pagini ramase
            min_pages = min(pages) #calulam numarul minim de pagini
            max_pages = max(pages) #calculam numarul maxim de pagini
            diff = max_pages - min_pages #diferenta dintre numarul minim si numarul maxim de pagini

            if diff < min_diff: #daca diferenta obtinuta e mai mica decat diferenta minima
                min_diff = diff #actualizam diferenta minima
                first_break = i #actualizam prima pauza
                second_break = j #actualizam a doua pagina

    pages[0] = pages[1] = pages[2] = 0 #resetam numarul de pagini pentru fiecare angajat

    for i in range(num_books): #parcurgem lista de carti
        if i <= first_break: #daca suntem inainte de prima pagina, adaugam paginile la primul angajat
            pages[0] += books[i].pages
        elif i <= second_break: #daca suntem inainte de a doua pauza, adaugam paginile la al doilea angajat
            pages[1] += books[i].pages
        else: #altfel, adaugam paginile la al treilea angajat
            pages[2] += books[i].pages

    file.write("===Rezultatele in cazul unei metode de cautare exhaustive===\n") #se afiseaza rezultatele
    file.write(f"Angajatul 1 este responsabil de {pages[0]} pagini.\n")
    file.write(f"Angajatul 2 este responsabil de {pages[1]} pagini.\n")
    file.write(f"Angajatul 3 este responsabil de {pages[2]} pagini.\n")

def main(): #functia principala
    num_books = generate_num_books() #se genereaza numarul de carti
    
    books = generate_pages(num_books) #se genereaza numarul de pagini pentru fiecare carte
    
    with open('rezultate11.txt', 'w', encoding='utf-8') as file:
        file.write(f"Numărul de cărți este {num_books}\n")
        
        print_books(books, file) #se afiseaza tabelul cu cartile si paginile lor
        
        total_pages = no_of_pages(books) #se calculeaza numarul total de pagini si se afiseaza
        file.write(f"Numerul TOTAL de pagini este {total_pages}\n")
        
        third_pages = total_pages // 3 #se calculeaza o treime si se afiseaza
        file.write(f"O TREIME de pagini este reprezentata de {third_pages}\n")
        
        sections(books, num_books, file) #se realizeaza sectiunile conform primei metode
        sections2(books, num_books, file) #se realizeaza sectiunile conform celei de-a doua metode

if __name__ == "__main__":
    main()
