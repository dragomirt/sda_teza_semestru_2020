//
// Created by Dragomir Țurcanu on 5/4/20.
//
#include <stdio.h>
#include "lib/marfuri.h"


int main() {
    // Meniu
    char input_value;
    int loop_is_running = 1;

    while(loop_is_running) {

        printf(""
               "\n1) Afiseaza Fisiere"
               "\nq) Iesire din program"
               "\nNavigati: ");

        scanf("%c%*c", &input_value);

        switch (input_value) {
            case '1':
                printRegisteredFiles();
                break;

            case '2':
//                hello();
                break;

            case 'q':
                loop_is_running = 0;
                break;

            default:
                printf("huh");
                break;
        }
    }

    return 0;
}