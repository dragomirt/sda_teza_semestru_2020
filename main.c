//
// Created by Dragomir Țurcanu on 5/4/20.
//
#include <stdio.h>
#include "lib/marfuri.h"
#include <string.h>

#define MAX_STRING_SIZE 200

char* citireInformatieDinFisier(struct Node** last) {
    int index = 0;
    printf("Selectati fisierul activ: ");
    scanf("%d", &index);
    return readFileFromRegister(last, index);
}

void adaugareInFisier(char path[]) {

}

int main() {
    // Datele initiale
    struct Node *last = NULL;
    char fisier_activ[MAX_STRING_SIZE];

    // Meniu
    char input_value;
    int loop_is_running = 1;

    while(loop_is_running) {

        printf("\n\nFisier Activ: %s\n", fisier_activ);

        printf(""
               "\n1) Afiseaza Fisiere"
               "\n2) Adaugarea in Fisier"
               "\nq) Iesire din program"
               "\nNavigati: ");

        // Citeste primul caracter si sterge cel de-al doilea, pentru a preveni repetarea introducerii
        scanf("%c%*c", &input_value);

        switch (input_value) {
            case '1':
                if (printRegisteredFiles() > 0) {
                    strcpy(fisier_activ, citireInformatieDinFisier(&last));
                } else {
                    printf("Inca exista fisiere cu date!\n");
                }
                break;

            case '2':

                break;

            case '0':
                loop_is_running = 0;
                break;

            default:
                printf("huh");
                break;
        }
    }

    return 0;
}