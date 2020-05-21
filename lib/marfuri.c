#include "marfuri.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define REGISTER_NAME "path_register.txt"

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
struct Node *ultimulElement(struct Node *last)
{
    struct Node *p = NULL;

    // Daca lista este pustie, intoarce
    if (last == NULL)
    {
        printf("Lista e pustie.\n");
        return last;
    }

    // Selectia primului nod
    p = last;

    // Traversarea listei
    do {
        p = p -> next;
    } while(p->next != last);

    return p;
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
    struct Node *p = NULL;
    int counter = 0;

    // Daca lista este pustie, intoarce
    if (last == NULL)
    {
        printf("List is empty.\n");
        return;
    }

    // Selectia primului nod
    p = last;

    // Traversarea listei
    do {
        printf("\n%d) Cod: %d | Denumire: \"%s\" | Articol: \"%s\" | Model: \"%s\" | Marime: \"%s\" | Calitate: \"%s\" | Pret: %f",
               counter++, p->data.cod, p->data.denumire, p->data.articol, p->data.model, p->data.marime, p->data.calitate, p->data.pret);
        p = p -> next;
    } while(p != last);
}
void afisareaDatelor(const marfa_t data)
{
    printf("\n———————————\n");
    printf("Cod: %d | Denumire: \"%s\" | Articol: \"%s\" | Model: \"%s\" | Marime: \"%s\" | Calitate: \"%s\" | Pret: %f",
            data.cod, data.denumire, data.articol, data.model, data.marime, data.calitate, data.pret);
    printf("\n———————————\n");
}
marfa_t selecteazaDupaIndex(const struct Node* last, int index)
{
    struct Node *p = NULL;
    marfa_t empty_response = {};
    int counter = 0;

    // Daca lista este pustie, intoarce
    if (last == NULL)
    {
        printf("Lista este pustie!.\n");
        return empty_response;
    }

    // Selectia primului nod
    p = last;

    // Traversarea listei
    do {
        if (index == counter++) {
            return p->data;
        }
        p = p -> next;
    } while(p != last);
    return empty_response;
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
    p = last;

    // Traversarea listei
    do
    {
        fprintf(fp, "%d %s %s %s %s %s %f\n", p->data.cod, p->data.denumire, p->data.articol, p->data.model, p->data.marime, p->data.calitate, p->data.pret);
        p = p -> next;
    } while(p != last);
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

// Metode de stocare a datelor despre fisiere
void createRegisterFile() {
    FILE *fp;
    fp = fopen(REGISTER_NAME, "a");
    fclose(fp);
}
int checkIfInRegister(const char path[]) {
    FILE *fp;
    fp = fopen(REGISTER_NAME, "r");
    char file_name[MAX_STRING_SIZE];

    do
    {
        fscanf(fp, "%s\n", file_name);
        if (!strcmp(file_name, path)) {
            fclose(fp);

            return 1;
        }
    }
    while(!feof(fp));

    fclose(fp);
    return 0;
}
void addToRegister(const char path[]) {
    if (!checkIfInRegister(path)) {
        FILE *fp;
        fp = fopen(REGISTER_NAME, "a+");
        fprintf(fp, "%s\n", path);
        fclose(fp);
    }
}
void removeFromRegister(const char path[]) {
    if (checkIfInRegister(path)) {
        FILE *fp, *temp;
        char data[MAX_STRING_SIZE];
        fp = fopen(REGISTER_NAME, "r");
        temp = fopen("temp.txt", "w+");

        do
        {
            fscanf(fp, "%s\n", data);

            if (strcmp(data, path) != 0) {
                fprintf(temp, "%s\n", data);
            }
        }
        while(!feof(fp));

        fclose(fp);
        fp = fopen(REGISTER_NAME, "w");

        do
        {
            fscanf(temp, "%s\n", data);
            fprintf(fp, "%s\n", data);
        }
        while(!feof(temp));

        fclose(temp);
        fclose(fp);

        remove("temp.txt");
    }
}
int printRegisteredFiles() {
    FILE *fp;
    fp = fopen(REGISTER_NAME, "r");
    char file_name[MAX_STRING_SIZE];
    int index = 0;

    while(!feof(fp))
    {
        fscanf(fp, "%s\n", file_name);
        printf("%d) %s\n", index, file_name);
        index++;
    }

    fclose(fp);
    return index;
}

// Metode de manipulare a fisierelor
void creareFisier(const char path[], struct Node *last) {
    FILE *fp;
    fp = fopen(path, "w+");
    exportToFile(fp, last);
    fclose(fp);

    createRegisterFile();
    addToRegister(path);
}
void citireFisier(const char path[], struct Node **last) {
    FILE *fp;
    fp = fopen(path, "r");
    *last = readFile(fp);
    fclose(fp);
}
char* readFileFromRegister(struct Node** last, int register_index) {
    FILE *fp;
    fp = fopen(REGISTER_NAME, "r");
    char file_name[MAX_STRING_SIZE];
    int counter = 0;

    do
    {
        fscanf(fp, "%s\n", file_name);
        if (counter == register_index) {
            citireFisier(file_name, last);
            break;
        }
        counter++;
    }
    while(!feof(fp));

    fclose(fp);
    return file_name;
}

// Metode ajutatoare
// Schimbarea cu locul a datelor din nodurile listei
void swap(struct Node *a, struct Node *b)
{
    marfa_t temp = a->data;
    a->data = b->data;
    b->data = temp;
}

// Sparge lista circulara in lista liniara
struct Node *breakTheCircle(struct Node *last) {
    struct Node *start = last;

    if (last == NULL) {
        return last;
    }

    while(last->next != start) {
        last = last->next;
    }

    last->next = NULL;
    return start;
}

// Re-strange lista liniara in una circulara
struct Node *reAssembleTheCircle(struct Node *last) {
    struct Node *start = last;

    if (last == NULL) {
        return last;
    }

    while(last->next != NULL) {
        last = last->next;
    }

    last->next = start;

    return start;
}

// Manipularea datelor ( sortare / cautare )
// In dependenta de valoarea variabilei type se iau diferiti parametri de comparatie
// 0 = se compara dupa cod
// 1 = se compara dupa denumire
// 2 = se compara dupa articol
void sort(struct Node **start, int type)
{
    int swapped, i;
    struct Node *ptr1;
    struct Node *lptr = NULL;

    /* Checking for empty list */
    if (start == NULL)
        return;

    struct Node *temp = NULL;
    temp = breakTheCircle(*start);

    do
    {
        swapped = 0;
        ptr1 = *start;

        while (ptr1->next != lptr)
        {
            switch (type) {
                case 1:
                    if (strcmp(ptr1->data.denumire, ptr1->next->data.denumire) > 0)
                    {
                        swap(ptr1, ptr1->next);
                        swapped = 1;
                    }
                    break;

                case 2:
                    if (strcmp(ptr1->data.model, ptr1->next->data.model) > 0)
                    {
                        swap(ptr1, ptr1->next);
                        swapped = 1;
                    }
                    break;

                default:
                    if (ptr1->data.cod > ptr1->next->data.cod)
                    {
                        swap(ptr1, ptr1->next);
                        swapped = 1;
                    }
            }

            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    }
    while (swapped);

    *start = reAssembleTheCircle(temp);
}

// Searching
struct Node *searchByCode(const struct Node *last, const int code) {

    struct Node *p = NULL;

    // Daca lista este pustie, intoarce
    if (last == NULL)
    {
        printf("List is empty.\n");
        return NULL;
    }

    // Selectia primului nod
    p = last;

    // Traversarea listei
    do {
        if (p->data.cod == code) {
            return p;
        }
        p = p -> next;
    } while(p != last);

    return NULL;
}
struct Node *searchByDenumire(const struct Node *last, const char denumire[]) {

    struct Node *p = NULL;

    // Daca lista este pustie, intoarce
    if (last == NULL)
    {
        printf("List is empty.\n");
        return NULL;
    }

    // Selectia primului nod
    p = last;

    // Traversarea listei
    do {
        if (!strcmp(p->data.denumire,denumire)) {
            return p;
        }
        p = p -> next;
    } while(p != last);

    return NULL;
}

// Gaseste ultimul cod din fisier
int getLastIndex(const char path[]) {
    struct Node *last = NULL;

    citireFisier(path, &last);
    sort(&last, 0);
    if (ultimulElement(last) != NULL) {
        return ultimulElement(last)->data.cod;
    }

    return -1;
}

void hello(void) {
    struct Node *last = NULL;

    citireFisier("testdata.txt", &last);
    sort(&last, 2);

    creareFisier("testdata.txt", last);

    struct Node *p = searchByDenumire(last, "dhdf1");
    if (p) {
        printf("%d", p->data.cod);
    }

    traversarea(last);
}