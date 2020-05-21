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

void adaugareInFisier(const char path[]) {
    marfa_t marfa_test;
    struct Node* last = NULL;

    printf("——————————————————");
    printf("\nInstanta noua de marfa textila:");
    printf("\nDenumire: "); scanf("%s", marfa_test.denumire);
    printf("Articol: "); scanf("%s", marfa_test.articol);
    printf("Model: "); scanf("%s", marfa_test.model);
    printf("Marime: "); scanf("%s", marfa_test.marime);
    printf("Calitate: "); scanf("%s", marfa_test.calitate);
    printf("Pret: "); scanf("%f", &marfa_test.pret);

    // Incrementarea ultimului index gasit in fisier:
    marfa_test.cod = getLastIndex(path) + 1;

    citireFisier(path, &last);
    adaugaLaInceput(last, marfa_test);
    sort(&last, 0);
    creareFisier(path, last);

    printf("\nInstanta cu codul %d si numele \"%s\" a fost inserat cu succes in fisierul \"%s\"!\n", marfa_test.cod, marfa_test.denumire, path);
    printf("——————————————————");
}

int checkIfFileIsActive(const char path[]) {
    if (!strcmp(path, "")) {
        return 0;
    }

    return 1;
}

int main() {
    // Datele initiale
    struct Node *last = NULL;
    char fisier_activ[MAX_STRING_SIZE];

    // Meniu
    int input_value;
    int loop_is_running = 1;

    while(loop_is_running) {

        printf("\n\nFisier Activ: %s\n", fisier_activ);

        printf(""
               "\n1) Selectare fisier activ"
               "\n2) Crearea fisier"
               "\n3) Adaugarea in fisierul activ"
               "\n-2) BONUS: Exportarea in JSON"
               "\n0) Iesire din program"
               "\nNavigati: ");

        // Citeste primul caracter si sterge cel de-al doilea, pentru a preveni repetarea introducerii
        scanf("%d", &input_value);

        switch (input_value) {
            case 1:
                if (printRegisteredFiles() > 0) {
                    strcpy(fisier_activ, citireInformatieDinFisier(&last));
                } else {
                    printf("Inca nu exista fisiere cu date!\n");
                }
                break;

            case 3:
                if (checkIfFileIsActive(fisier_activ)) {
                    adaugareInFisier(fisier_activ);
                } else {
                    printf("\nSelectati un fisier!");
                }
                break;

            case 0:
                loop_is_running = 0;
                break;

            case -2:
                printf("JSON!");
                break;

            default:
                printf("\n Selectie invalida!");
                break;
        }
    }

    return 0;
}