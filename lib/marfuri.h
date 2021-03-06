#ifndef TEZA_SEMESTRU_SDA_MARFURI_H
#define TEZA_SEMESTRU_SDA_MARFURI_H

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

struct Node *adaugaLaInceput(struct Node *last, marfa_t data);
struct Node *adaugaLaSfarsit(struct Node *last, marfa_t data);
struct Node *adaugaDupa(struct Node *last, marfa_t data, marfa_t item);
void sterge(struct Node** head, marfa_t data);
void curataLista(struct Node** head_ref);
void traversarea(struct Node *last);
void afisareaDatelor(const marfa_t data);
marfa_t selecteazaDupaIndex(const struct Node* last, int index);

void exportToJSON(struct Node *last);
void createRegisterFile();
void addToRegister(const char path[]);
void removeFromRegister(const char path[]);

int printRegisteredFiles();
void creareFisier(const char path[], struct Node *last);
void citireFisier(const char path[], struct Node **last);
char* readFileFromRegister(struct Node** last, int register_index);

void sort(struct Node **start, int type);
struct Node *searchByCode(const struct Node *last, const int code);
struct Node *searchByDenumire(const struct Node *last, const char denumire[]);
int getLastIndex(const char path[]);

#endif //TEZA_SEMESTRU_SDA_MARFURI_H
