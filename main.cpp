#include <unistd.h>
#include <stdlib.h>
#include <ncurses.h>
#include <cstring>
#include <time.h>
#include <thread>
#include <chrono>

using namespace std;

// variabili
char a;
char caratteri_menu[] = {'1','2','3','0'};
int i;
int out_err;

// funzioni
void menu(int i);
void in();
void villain();
void switch_default_invalid();
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
            default: switch_default_invalid(); break;
        }
    } while(a != '0');

    return 0;
}

void menu(int i) {
    switch(i) {
        case 0: printw("Menu inizio\n\n1] villain\n2] work in progress\n3] work in progress\n0] Exit\n"); break;
        case 1: printw("Menu villain\n\n1] villain\n2] work in progress\n3] work in progress\n0] Exit\n"); break;
        case 2: printw("Menu 2\n\n1] villain\n2] work in progress\n3] work in progress\n0] Exit\n"); break;
        case 3: printw("Menu 3\n\n1] villain\n2] work in progress\n3] work in progress\n0] Exit\n"); break;
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
}

void switch_default_invalid() {

    for(i = 0; i < sizeof(caratteri_menu); i++) {
        if(a != caratteri_menu[i]) {
            out_err++;
        } else {
            out_err = 0;
        }
    }

    if(out_err == 4) {
        printw("Input non valido\n");
        // Avvia thread
        thread contr_input(controllo_last_string_input, a);
        contr_input.detach(); // Rilascia il thread, permettendogli di continuare in background
    }

}

void controllo_last_string_input(char controllo) {

    this_thread::sleep_for(chrono::seconds(2)); // Attendi 5 secondi
    clear();
    menu(0);
    refresh();
    out_err = 0;
}
