#include <unistd.h>
#include <stdlib.h>
#include <ncurses.h>
#include <cstring>
#include <time.h>
#include <thread>
#include <chrono>

// variabili
char a;
char caratteri_menu[] = {'1','2','3','0'};
int i;
int out_err;

// funzioni
void cls();
void menu(int i);
void in();
void villain();
void display_invalid_input();
void controllo_last_string_input(char controllo);


int main() {

    // Inizializza ncurses
    initscr();
    scrollok(stdscr, TRUE);

    menu(0);
    do {
        in();
        switch (a) {
            case '1': villain(); break;
            case '2': printw("work in progress\n"); break;
            case '3': printw("work in progress\n"); break;
            case '0': endwin(); break;
            default: display_invalid_input(); break;
        }
    } while(a != '0');

    return 0;
}

void cls() {
    clear();
}

void menu(int i) {
    switch(i) {
        case 0: printw("Menu inizio\n1] villain\n2] work in progress\n3] work in progress\n0] Exit\n"); break;
        case 1: printw("Menu villain\n"); break;
        case 2: printw("Menu 2\n"); break;
        case 3: printw("Menu 3\n"); break;
    }
}

void in() {
    // Disabilita il buffering di linea e l'eco dei caratteri
    cbreak();
    noecho();

    // Ottieni un carattere dalla tastiera
    a = getch();
}

void villain() {
    clear();
    menu(1);
    getch();
}

void display_invalid_input() {
    for(i = 0; i < sizeof(caratteri_menu); i++) {
        if(a != caratteri_menu[i]) {
            out_err++;
        } else {
            out_err = 0;
        }
    }
    if(out_err == 4) {
        printw("Input non valido\n");
        // Avvia un thread che stampa un carattere ogni 5 secondi
        std::thread contr_input(controllo_last_string_input, a);
        contr_input.detach(); // Rilascia il thread, permettendogli di continuare in background
    }
}

void controllo_last_string_input(char controllo) {
    //while(true) {
        std::this_thread::sleep_for(std::chrono::seconds(2)); // Attendi 5 secondi
        //printw("%c\n", controllo); // Stampa il carattere
        clear();
        menu(0);
        refresh(); // Aggiorna lo schermo
        
    //}
}
