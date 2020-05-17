#include "marfuri.h"
#include <stdio.h>
#include <stdlib.h>
#include <db.h>

#define MAX_STRING_SIZE 200

struct MARFURI_TEXTILE {
    char denumire[MAX_STRING_SIZE];
    char articol[MAX_STRING_SIZE];
    char model[MAX_STRING_SIZE];
    char marime[MAX_STRING_SIZE];
    char calitate[MAX_STRING_SIZE];
    float pret;
    int cod;
};

typedef struct MARFURI_TEXTILE marfa_t;

struct Node {
    marfa_t data;
    struct Node *next;
};

// Metode de manipulare a listei
struct Node *adaugaListaPustie(struct Node *last, marfa_t data)
{
    // Functia e doar pentru lista pustie
    if (last != NULL)
        return last;

    // Crearea nodului dinamic
    struct Node *temp =
            (struct Node*)malloc(sizeof(struct Node));

    // Atribuirea marfei
    temp -> data = data;
    last = temp;

    // Crearea legaturii
    last -> next = last;

    return last;
}
struct Node *adaugaLaInceput(struct Node *last, marfa_t data)
{
    if (last == NULL)
        return adaugaListaPustie(last, data);

    struct Node *temp =
            (struct Node *)malloc(sizeof(struct Node));

    temp -> data = data;
    temp -> next = last -> next;
    last -> next = temp;

    return last;
}
struct Node *adaugaLaSfarsit(struct Node *last, marfa_t data)
{
    if (last == NULL)
        return adaugaListaPustie(last, data);

    struct Node *temp =
            (struct Node *)malloc(sizeof(struct Node));

    temp -> data = data;
    temp -> next = last -> next;
    last -> next = temp;
    last = temp;

    return last;
}
struct Node *adaugaDupa(struct Node *last, marfa_t data, marfa_t item)
{
    if (last == NULL)
        return NULL;

    struct Node *temp, *p;
    p = last -> next;
    do
    {
        if ((p ->data).cod == item.cod)
        {
            temp = (struct Node *)malloc(sizeof(struct Node));
            temp -> data = data;
            temp -> next = p -> next;
            p -> next = temp;

            if (p == last)
                last = temp;
            return last;
        }
        p = p -> next;
    }  while(p != last -> next);

    printf("Intrarea nu a fost gasita!");
    return last;
}
void sterge(struct Node** head, marfa_t data)
{

    if (*head == NULL)
        return;

    if((*head)->data.cod == data.cod && (*head)->next==*head)
    {
        free(*head);
        *head=NULL;
    }

    struct Node *last=*head,*d;

    if((*head)->data.cod==data.cod) {

        while(last->next!=*head)
            last=last->next;

        last->next=(*head)->next;
        free(*head);
        *head=last->next;
    }

    while(last->next!=*head && last->next->data.cod!=data.cod) {
        last=last->next;
    }

    if(last->next->data.cod == data.cod) {
        d=last->next;
        last->next=d->next;
        free(d);
    }
    else
        printf("Intrarea nu a fost gasita!");
}
void curataLista(struct Node** head_ref) {
    struct Node* current = *head_ref;
    struct Node* next;

    while (current != *head_ref)
    {
        next = current->next;
        free(current);
        current = next;
    }

    *head_ref = NULL;
}
void traversarea(struct Node *last)
{
    struct Node *p;

    // Daca lista este pustie, intoarce
    if (last == NULL)
    {
        printf("List is empty.\n");
        return;
    }

    // Selectia primului nod
    p = last -> next;

    // Traversarea listei
    do
    {
        printf("%s ", p->data.denumire);
        p = p -> next;

    }
    while(p != last->next);
}

// Exportul / importul datelor
void exportToJSON(struct Node *last) {
    struct Node *p;

    // Daca lista este pustie, intoarce
    if (last == NULL)
    {
        printf("List is empty.\n");
        return;
    }

    // Selectia primului nod
    p = last -> next;

    printf("[");
    // Traversarea listei
    do
    {
        printf("{");
        printf("\"cod\": %d,", p->data.cod);
        printf("\"denumire\": \"%s\",", p->data.denumire);
        printf("\"articol\": \"%s\",", p->data.articol);
        printf("\"model\": \"%s\",", p->data.model);
        printf("\"marime\": \"%s\",", p->data.marime);
        printf("\"calitate\": \"%s\",", p->data.calitate);
        printf("\"pret\": %f", p->data.pret);
        printf("}");

        if (p->next != last->next) {
            printf(",");
        }
        p = p -> next;
    }
    while(p != last->next);

    printf("]");
}
void exportToFile(FILE *fp, struct Node *last) {
    struct Node *p;

    // Daca lista este pustie, intoarce
    if (last == NULL)
    {
        printf("List is empty.\n");
        return;
    }

    // Selectia primului nod
    p = last -> next;

    // Traversarea listei
    do
    {
        fprintf(fp, "%d %s %s %s %s %s %f\n", p->data.cod, p->data.denumire, p->data.articol, p->data.model, p->data.marime, p->data.calitate, p->data.pret);
        p = p -> next;
    }
    while(p != last->next);
}

struct Node *readFile(FILE *fp) {
    marfa_t mo; // Marfa Object
    struct Node *p = NULL;

    // Citirea fisierului
    do
    {
        fscanf(fp, "%d %s %s %s %s %s %f\n", &mo.cod, mo.denumire, mo.articol, mo.model, mo.marime, mo.calitate, &mo.pret);
        p = adaugaLaInceput(p, mo);
    }
    while(!feof(fp));

    return p;
}

// Metode de manipulare a fisierelor
void creareFisier(char path[], struct Node *last) {
    FILE *fp;
    fp = fopen(path, "w+");
    exportToFile(fp, last);
    fclose(fp);
}

void citireFisier(char path[], struct Node **last) {
    FILE *fp;
    fp = fopen(path, "r");
    *last = readFile(fp);
    fclose(fp);
}

void hello(void) {
    struct Node *last = NULL;
//    marfa_t marfa_test = {"test", "articol_1", "model_1", "L", "buna", 10.2, 1};
//    marfa_t marfa_test_1 = {"test1", "articol_2", "model_2", "L", "asdf", 6.23, 2};
//    marfa_t marfa_test_2 = {"test2", "articol_3", "model_3", "L", "asdf", 8.23, 3};
//
//    last = adaugaListaPustie(last, marfa_test);
//    last = adaugaLaInceput(last, marfa_test_1);
//    last = adaugaLaSfarsit(last, marfa_test_2);
//
//    creareFisier("testdata.txt", last);
//    sterge(&last, marfa_test_1);
//    traversarea(last);

    printf("\n______\n");
    curataLista(&last);
    citireFisier("testdata.txt", &last);
    traversarea(last);
}