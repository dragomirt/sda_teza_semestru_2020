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
    if (scanf("%d", &index)) {
        return readFileFromRegister(last, index);
    };
    return "";
}
void adaugareInFisier(const char path[]) {
    marfa_t marfa_test;
    struct Node* last = NULL;

    printf("----------------------------------");
    printf("\nInstanta noua de marfa textila:");
    printf("\nDenumire: ");
    if (!scanf("%s", marfa_test.denumire)) {
        printf("Avortarea crearii instantei!");
    }
    printf("Articol: ");
    if (!scanf("%s", marfa_test.articol)) {
        printf("Avortarea crearii instantei!");
    }
    printf("Model: ");
    if (!scanf("%s", marfa_test.model)) {
        printf("Avortarea crearii instantei!");
    }
    printf("Marime: ");
    if (!scanf("%s", marfa_test.marime)) {
        printf("Avortarea crearii instantei!");
    }
    printf("Calitate: ");
    if (!scanf("%s", marfa_test.calitate)) {
        printf("Avortarea crearii instantei!");
    }
    printf("Pret: ");
    if (!scanf("%f", &marfa_test.pret)) {
        printf("Avortarea crearii instantei!");
    }

    // Incrementarea ultimului index gasit in fisier:
    marfa_test.cod = getLastIndex(path) + 1;

    citireFisier(path, &last);
    last = adaugaLaInceput(last, marfa_test);
    sort(&last, 0);
    creareFisier(path, last);

    printf("\nInstanta cu codul %d si numele \"%s\" a fost inserat cu succes in fisierul \"%s\"!\n", marfa_test.cod, marfa_test.denumire, path);
    printf("----------------------------------");
}
int checkIfFileIsActive(const char path[]) {
    if (!strcmp(path, "")) {
        return 0;
    }

    return 1;
}
void cautareInFisier(const char path[]) {
    int index = 0;
    int code = 0;
    char denumire[MAX_STRING_SIZE];
    struct Node *last= NULL;
    struct Node *element= NULL;

    citireFisier(path, &last);

    printf("\nSelectati tipul de cautare:"
           "\n1) Dupa cod"
           "\n2) Dupa denumire"
           "\n0) Inapoi"
           "\nSelectati: ");
    if (scanf("%d", &index)) {
        switch (index) {
            case 1:
                printf("\nCodul de cautare: ");
                if (scanf("%d", &code)) {
                    element = searchByCode(last, code);
                    if (element) {
                        afisareaDatelor((*element).data);
                    }
                };
                break;

            case 2:
                printf("\nDenmirea de cautare: ");
                if (scanf("%s", &denumire)) {
                    element = searchByDenumire(last, denumire);
                    if (element) {
                        afisareaDatelor((*element).data);
                    }
                };
                break;

            default:
                return;
                break;
        }
    };
}
char* creareFisierNou() {
    char nume_fisier[MAX_STRING_SIZE] = "";
    printf("\nDenumire fisier (calea absoluta): ");
    if (scanf("%s", nume_fisier)) {
        if (strcmp(nume_fisier, "") > 0) {
            createRegisterFile();
            addToRegister(nume_fisier);
            return nume_fisier;
        }
    };

    printf("Introduceti denumirea fisierului!");
    return "";
}
void modifyFile(const char path[]) {
    int index = 0;
    struct Node *last= NULL;
    marfa_t data;
    citireFisier(path, &last);

    if (last == NULL) {
        printf("Nu exista elemente in lista!");
        return;
    }

    traversarea(last);
    printf("\n-1) Iesire");

    printf("\nSelectati instanta ce trebuie modificata: ");
    if (scanf("%d", &index)) {
        if (index == -1) {
            return;
        }
        data = selecteazaDupaIndex(last, index);
        //
        //    if (!data.cod) {
        //        return;
        //    }

        printf("\nSelectati actiunea:"
               "\n1) Rescriere"
               "\n2) Stergere"
               "\n0) Inapoi"
               "\nSelectati: ");
        if (scanf("%d", &index)) {
            switch (index) {
                case 1:
                    sterge(&last, data);
                    creareFisier(path, last);
                    adaugareInFisier(path);
                    break;

                case 2:
                    sterge(&last, data);
                    creareFisier(path, last);
                    break;

                default:
                    return;
                    break;
            }
        };
    };
}

void exporteazaInJSON(const char path[]) {
    struct Node *last = NULL;
    citireFisier(path, &last);
    if (last == NULL){ return; }
    exportToJSON(last);
}

int main() {
    // Datele initiale
    struct Node *last = NULL;
    char fisier_activ[MAX_STRING_SIZE] = "";

    // Meniu
    int input_value;
    int loop_is_running = 1;

    while(loop_is_running) {

        printf("\n\nFisier Activ: %s\n", fisier_activ);

        printf(""
               "\n1) Selectare fisier activ"
               "\n2) Crearea fisier"
               "\n3) Adaugarea in fisierul activ"
               "\n4) Cautarea instantei in fisierul activ"
               "\n5) Modificati fisierul activ"
               "\n-2) BONUS: Exportarea in JSON"
               "\n0) Iesire din program"
               "\nNavigati: ");

        // Citeste primul caracter si sterge cel de-al doilea, pentru a preveni repetarea introducerii
        if (scanf("%d", &input_value)) {
            switch (input_value) {
                case 1:
                    if (printRegisteredFiles() > 0) {
                        strcpy(fisier_activ, citireInformatieDinFisier(&last));
                    }
                    else {
                        printf("Inca nu exista fisiere cu date!\n");
                    }
                    break;

                case 2:
                    strcpy(fisier_activ, creareFisierNou());
                    break;

                case 3:
                    if (checkIfFileIsActive(fisier_activ)) {
                        adaugareInFisier(fisier_activ);
                    }
                    else {
                        printf("\nSelectati un fisier!");
                    }
                    break;

                case 4:
                    if (checkIfFileIsActive(fisier_activ)) {
                        cautareInFisier(fisier_activ);
                    }
                    else {
                        printf("\nSelectati un fisier!");
                    }
                    break;

                case 5:
                    if (checkIfFileIsActive(fisier_activ)) {
                        modifyFile(fisier_activ);
                    }
                    else {
                        printf("\nSelectati un fisier!");
                    }
                    break;

                case 0:
                    loop_is_running = 0;
                    break;

                case -2:
                    if (printRegisteredFiles() > 0) {
                        printf("\n");
                        exporteazaInJSON(fisier_activ);
                    }
                    else {
                        printf("Inca nu exista fisiere cu date!\n");
                    }
                    break;

                default:
                    printf("\n Selectie invalida!");
                    break;
            }
        }
    }

    return 0;
}