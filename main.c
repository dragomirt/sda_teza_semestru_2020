//
// Created by Dragomir Țurcanu on 5/4/20.
//
#include <stdio.h>
#include "lib/marfuri.h"

#include <ncurses.h>
#include <unistd.h>

void another_menu(void) {
    char input_value;
    int loop_is_running = 1;

    clear();
    while(loop_is_running) {

        printw(""
               "\n1) blabla"
               "\nq) Inapoi"
               "\nNavigati: ");
        refresh();

        scanf("%c", &input_value);
        clear();

        switch (input_value) {
            case '1':
                printw("helloooo");
                break;

            case 'q':
                loop_is_running = 0;
                break;

            default:
                printw("huh");
                break;
        }
    }
}

int main() {
    hello();
    // Meniu
//    char input_value;
//    int loop_is_running = 1;
//
//    initscr();
//    noecho();
//    curs_set(FALSE);
//
//    while(loop_is_running) {
//
//        printw(""
//               "\n1) Afiseaza Fisiere"
//               "\nq) Iesire din program"
//               "\nNavigati: ");
//        refresh();
//
//        scanf("%c\n", &input_value);
//        clear();
//
//        switch (input_value) {
//            case '1':
//                another_menu();
//                break;
//
//            case '2':
//                hello();
//                break;
//
//            case 'q':
//                loop_is_running = 0;
//                break;
//
//            default:
//                printw("huh");
//                break;
//        }
//    }
//    endwin();

    return 0;
}