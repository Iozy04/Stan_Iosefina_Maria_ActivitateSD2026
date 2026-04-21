#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Vrajitori {
    int id;
    int nivelPutere;
    float mana;
    char* denumirePutere;
    char* denumireVrajitor;
    unsigned char casa;
};
typedef struct Vrajitori Vrajitori;

Vrajitori citireVrajitoriDinFisier(FILE* file) {
    char buffer[300];
    char sep[3] = ",\n";
    Vrajitori v;
    v.id = -1;
    v.denumirePutere = NULL;
    v.denumireVrajitor = NULL;
    if (!fgets(buffer, 300, file)) return v;
    char* aux = strtok(buffer, sep);
    if (!aux) return v;
    v.id = atoi(aux);
    v.nivelPutere = atoi(strtok(NULL, sep));
    v.mana = atof(strtok(NULL, sep));
    aux = strtok(NULL, sep);
    v.denumirePutere = malloc(strlen(aux) + 1);
    strcpy(v.denumirePutere, aux);
    aux = strtok(NULL, sep);
    v.denumireVrajitor = malloc(strlen(aux) + 1);
    strcpy(v.denumireVrajitor, aux);
    v.casa = *strtok(NULL, sep);
    return v;
}

void afisareVrajitori(Vrajitori v) {
    printf("Id: %d | Nivel: %d | Mana: %.2f | Putere: %s | Vrajitor: %s | Casa: %c\n",
        v.id, v.nivelPutere, v.mana,
        v.denumirePutere, v.denumireVrajitor, v.casa);
}
//STIVA (STACK)

// STIVA CU LSI (Lista Simplu Inlantuita)
typedef struct NodLSI NodLSI;
struct NodLSI {
    Vrajitori info;
    NodLSI* next;
};

void pushLSI(NodLSI** cap, Vrajitori v) {
    NodLSI* nou = malloc(sizeof(NodLSI));
    nou->info = v;
    nou->next = *cap;   // noul nod pointeaza spre fostul cap
    *cap = nou;         // noul nod devine capul
}

Vrajitori popLSI(NodLSI** cap) {
    Vrajitori rezultat;
    rezultat.id = -1;
    if (!(*cap)) return rezultat;
    rezultat = (*cap)->info;
    NodLSI* temp = *cap;
    *cap = (*cap)->next; // capul avanseaza
    free(temp);
    return rezultat;
}

int isEmptyLSI(NodLSI* cap) {
    return cap == NULL;
}

void dezalocareStiva_LSI(NodLSI** cap) {
    while (*cap) {
        NodLSI* temp = *cap;
        free((*cap)->info.denumirePutere);
        free((*cap)->info.denumireVrajitor);
        *cap = (*cap)->next;
        free(temp);
    }
}

NodLSI* citireStivaLSIDinFisier(const char* numeFisier) {
    FILE* f = fopen(numeFisier, "r");
    NodLSI* cap = NULL;
    while (!feof(f)) {
        Vrajitori v = citireVrajitoriDinFisier(f);

        pushLSI(&cap, v);
    }
    fclose(f);
    return cap;
}

// STIVA CU LDI (Lista Dublu Inlantuita)
typedef struct NodLDI NodLDI;
struct NodLDI {
    Vrajitori info;
    NodLDI* next;
    NodLDI* prev;
};

typedef struct StivaLDI StivaLDI;

struct StivaLDI{
    NodLDI* first;
    NodLDI* last;
};

void pushLDI(StivaLDI* stiva, Vrajitori v) {
    NodLDI* nou = malloc(sizeof(NodLDI));
    nou->info = v;
    nou->prev = NULL;
    nou->next = stiva->first;   // noul nod pointeaza spre fostul first
    if (stiva->first) {
        stiva->first->prev = nou; // fostul first il vede inapoi pe nou
    }
    else {
        stiva->last = nou;        // lista era goala, nou e si ultimul
    }
    stiva->first = nou;
}

Vrajitori popLDI(StivaLDI* stiva) {
    Vrajitori rezultat;
    rezultat.id = -1;
    if (!stiva->first) return rezultat;
    rezultat = stiva->first->info;
    NodLDI* temp = stiva->first;
    stiva->first = stiva->first->next;
    if (stiva->first) {
        stiva->first->prev = NULL; // noul first nu mai are prev
    }
    else {
        stiva->last = NULL;        // lista a ramas goala
    }
    free(temp);
    return rezultat;
}

int isEmptyLDI(StivaLDI* stiva) {
    return stiva->first == NULL;
}

void dezalocareStiva_LDI(StivaLDI* stiva) {
    while (stiva->first) {
        NodLDI* temp = stiva->first;
        free(stiva->first->info.denumirePutere);
        free(stiva->first->info.denumireVrajitor);
        stiva->first = stiva->first->next;
        free(temp);
    }
    stiva->last = NULL;
}

StivaLDI citireStivaLDIDinFisier(const char* numeFisier) {
    FILE* f = fopen(numeFisier, "r");
    StivaLDI stiva;
    stiva.first = stiva.last = NULL;
    while (!feof(f)) {
        Vrajitori v = citireVrajitoriDinFisier(f);

        pushLDI(&stiva, v);
    }
    fclose(f);
    return stiva;
}

// STIVA CU VECTOR (array dinamic)
// top = indexul varfului (-1 daca e goala)
typedef struct {
    Vrajitori* elemente;
    int top;        // indexul varfului stivei
    int capacitate;
} StivaVector;

StivaVector creazaStivaVector(int capacitate) {
    StivaVector sv;
    sv.elemente = malloc(sizeof(Vrajitori) * capacitate);
    sv.top = -1;
    sv.capacitate = capacitate;
    return sv;
}

void pushVector(StivaVector* sv, Vrajitori v) {
    if (sv->top < sv->capacitate - 1) {
        sv->elemente[++sv->top] = v; // top creste, apoi punem elementul
    }
}

Vrajitori popVector(StivaVector* sv) {
    Vrajitori rezultat;
    rezultat.id = -1;
    if (sv->top >= 0) {
        rezultat = sv->elemente[sv->top--]; // luam elementul, apoi top scade
    }
    return rezultat;
}

int isEmptyVector(StivaVector* sv) {
    return sv->top == -1;
}

void dezalocareStiva_Vector(StivaVector* sv) {
    for (int i = 0; i <= sv->top; i++) {
        free(sv->elemente[i].denumirePutere);
        free(sv->elemente[i].denumireVrajitor);
    }
    free(sv->elemente);
    sv->top = -1;
}

StivaVector citireStivaVectorDinFisier(const char* numeFisier, int capacitate) {
    FILE* f = fopen(numeFisier, "r");
    StivaVector sv = creazaStivaVector(capacitate);
    while (!feof(f)) {
        Vrajitori v = citireVrajitoriDinFisier(f);

        pushVector(&sv, v);
    }
    fclose(f);
    return sv;
}

//COADA (QUEUE)

// COADA CU LSI (Lista Simplu Inlantuita)
typedef struct NodCoadaLSI NodCoadaLSI;
struct NodCoadaLSI {
    Vrajitori info;
    NodCoadaLSI* next;
};

typedef struct {
    NodCoadaLSI* front; // de unde scoatem
    NodCoadaLSI* rear;  // unde adaugam
} CoadaLSI;

void enqueueLSI(CoadaLSI* coada, Vrajitori v) {
    NodCoadaLSI* nou = malloc(sizeof(NodCoadaLSI));
    nou->info = v;
    nou->next = NULL;
    if (coada->rear) {
        coada->rear->next = nou; // fostul rear il vede pe nou
    }
    else {
        coada->front = nou;      // coada era goala, nou e si primul
    }
    coada->rear = nou;
}

Vrajitori dequeueLSI(CoadaLSI* coada) {
    Vrajitori rezultat;
    rezultat.id = -1;
    if (!coada->front) return rezultat;
    rezultat = coada->front->info;
    NodCoadaLSI* temp = coada->front;
    coada->front = coada->front->next;
    if (!coada->front) coada->rear = NULL; // coada a ramas goala
    free(temp);
    return rezultat;
}

int isEmptyCoadaLSI(CoadaLSI* coada) {
    return coada->front == NULL;
}

void dezalocareCoadaLSI(CoadaLSI* coada) {
    while (coada->front) {
        NodCoadaLSI* temp = coada->front;
        free(coada->front->info.denumirePutere);
        free(coada->front->info.denumireVrajitor);
        coada->front = coada->front->next;
        free(temp);
    }
    coada->rear = NULL;
}

CoadaLSI citireCoadaLSIDinFisier(const char* numeFisier) {
    FILE* f = fopen(numeFisier, "r");
    CoadaLSI coada;
    coada.front = coada.rear = NULL;
    while (!feof(f)) {
        Vrajitori v = citireVrajitoriDinFisier(f);

        enqueueLSI(&coada, v);
    }
    fclose(f);
    return coada;
}

// COADA CU LDI (Lista Dublu Inlantuita)
typedef struct NodCoadaLDI NodCoadaLDI;
struct NodCoadaLDI {
    Vrajitori info;
    NodCoadaLDI* next;
    NodCoadaLDI* prev;
};

typedef struct {
    NodCoadaLDI* first;
    NodCoadaLDI* last;
} CoadaLDI;

void enqueueLDI(CoadaLDI* coada, Vrajitori v) {
    NodCoadaLDI* nou = malloc(sizeof(NodCoadaLDI));
    nou->info = v;
    nou->next = NULL;
    nou->prev = coada->last;
    if (coada->last) {
        coada->last->next = nou;
    }
    else {
        coada->first = nou;
    }
    coada->last = nou;
}

Vrajitori dequeueLDI(CoadaLDI* coada) {
    Vrajitori rezultat;
    rezultat.id = -1;
    if (!coada->first) return rezultat;
    rezultat = coada->first->info;
    NodCoadaLDI* temp = coada->first;
    coada->first = coada->first->next;
    if (coada->first) {
        coada->first->prev = NULL;
    }
    else {
        coada->last = NULL;
    }
    free(temp);
    return rezultat;
}

int isEmptyCoadaLDI(CoadaLDI* coada) {
    return coada->first == NULL;
}

void dezalocareCoadaLDI(CoadaLDI* coada) {
    while (coada->first) {
        NodCoadaLDI* temp = coada->first;
        free(coada->first->info.denumirePutere);
        free(coada->first->info.denumireVrajitor);
        coada->first = coada->first->next;
        free(temp);
    }
    coada->last = NULL;
}

CoadaLDI citireCoadaLDIDinFisier(const char* numeFisier) {
    FILE* f = fopen(numeFisier, "r");
    CoadaLDI coada;
    coada.first = coada.last = NULL;
    while (!feof(f)) {
        Vrajitori v = citireVrajitoriDinFisier(f);

        enqueueLDI(&coada, v);
    }
    fclose(f);
    return coada;
}

// COADA CU VECTOR
// front = indexul primului element (de unde scoatem)
// rear  = indexul ultimului element (unde adaugam)
// size  = cate elemente sunt in coada

typedef struct {
    Vrajitori* elemente;
    int front;      // de unde scoatem
    int rear;       // unde adaugam
    int size;       // cate elemente sunt
    int capacitate;
} CoadaVector;

CoadaVector creazaCoadaVector(int capacitate) {
    CoadaVector cv;
    cv.elemente = malloc(sizeof(Vrajitori) * capacitate);
    cv.front = 0;
    cv.rear = -1;
    cv.size = 0;
    cv.capacitate = capacitate;
    return cv;
}

void enqueueVector(CoadaVector* cv, Vrajitori v) {
    if (cv->size < cv->capacitate) {
        cv->rear = (cv->rear + 1) % cv->capacitate; // circular
        cv->elemente[cv->rear] = v;
        cv->size++;
    }
}

Vrajitori dequeueVector(CoadaVector* cv) {
    Vrajitori rezultat;
    rezultat.id = -1;
    if (cv->size > 0) {
        rezultat = cv->elemente[cv->front];
        cv->front = (cv->front + 1) % cv->capacitate; // circular
        cv->size--;
    }
    return rezultat;
}

int isEmptyCoadaVector(CoadaVector* cv) {
    return cv->size == 0;
}

void dezalocareCoadaVector(CoadaVector* cv) {
    for (int i = 0; i < cv->size; i++) {
        int idx = (cv->front + i) % cv->capacitate;
        free(cv->elemente[idx].denumirePutere);
        free(cv->elemente[idx].denumireVrajitor);
    }
    free(cv->elemente);
    cv->size = 0;
}

CoadaVector citireCoadaVectorDinFisier(const char* numeFisier, int capacitate) {
    FILE* f = fopen(numeFisier, "r");
    CoadaVector cv = creazaCoadaVector(capacitate);
    while (!feof(f)) {
        Vrajitori v = citireVrajitoriDinFisier(f);

        enqueueVector(&cv, v);
    }
    fclose(f);
    return cv;
}

int main() {

    printf("========== STIVA LSI ==========\n");
    NodLSI* stivaLSI = citireStivaLSIDinFisier("Vrajitori.txt");
    while(!isEmptyLSI(stivaLSI))
    {
        afisareVrajitori(popLSI(&stivaLSI)); 
    }
    dezalocareStiva_LSI(&stivaLSI);

    printf("\n========== STIVA LDI ==========\n");
    StivaLDI stivaLDI = citireStivaLDIDinFisier("Vrajitori.txt");
    while(!isEmptyLDI(&stivaLDI))
    {
        afisareVrajitori(popLDI(&stivaLDI));
    }
    dezalocareStiva_LDI(&stivaLDI);

    printf("\n========== STIVA VECTOR ==========\n");
    StivaVector stivaVec = citireStivaVectorDinFisier("Vrajitori.txt", 20);
    while(!isEmptyVector(&stivaVec))
    {
        afisareVrajitori(popVector(&stivaVec));
    }
    dezalocareStiva_Vector(&stivaVec);

    printf("\n========== COADA LSI ==========\n");
    CoadaLSI coadaLSI = citireCoadaLSIDinFisier("Vrajitori.txt");
    afisareVrajitori(dequeueLSI(&coadaLSI)); // scoate primul citit (FIFO)
    afisareVrajitori(dequeueLSI(&coadaLSI));
    dezalocareCoadaLSI(&coadaLSI);

    printf("\n========== COADA LDI ==========\n");
    CoadaLDI coadaLDI = citireCoadaLDIDinFisier("Vrajitori.txt");
    afisareVrajitori(dequeueLDI(&coadaLDI));
    afisareVrajitori(dequeueLDI(&coadaLDI));
    dezalocareCoadaLDI(&coadaLDI);

    printf("\n========== COADA VECTOR ==========\n");
    CoadaVector coadaVec = citireCoadaVectorDinFisier("Vrajitori.txt", 20);
    afisareVrajitori(dequeueVector(&coadaVec));
    afisareVrajitori(dequeueVector(&coadaVec));
    dezalocareCoadaVector(&coadaVec);

    return 0;
}
