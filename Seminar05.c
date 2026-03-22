//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//
//// trebuie sa folositi fisierul masini.txt
//// sau va creati un alt fisier cu alte date
// 
//
//struct StructuraMasina {
//    int id;
//    int nrUsi;
//    float pret;
//    char* model;
//    char* numeSofer;
//    unsigned char serie;
//};
//typedef struct StructuraMasina Masina;
//typedef struct Nod Nod;
//typedef struct ListaDubla ListaDubla;
//
//// creare structura pentru un nod dintr-o lista dublu inlantuita
//struct Nod {
//    Masina info;
//    Nod* next;
//    Nod* prev;
//};
//
//// creare structura pentru Lista Dubla
//struct ListaDubla {
//    Nod* prim;
//    Nod* ultim;
//};
//
//char* copiazaText(const char* text) {
//    if (text == NULL) return NULL;
//    char* copie = (char*)malloc(strlen(text) + 1);
//    if (copie) {
//        strcpy(copie, text);
//    }
//    return copie;
//}
//
//void dezalocareMasina(Masina* m) {
//    if (m) {
//        free(m->model);
//        free(m->numeSofer);
//        m->model = NULL;
//        m->numeSofer = NULL;
//    }
//}
//
//Masina citireMasinaDinFisier(FILE* file) {
//    char buffer[100];
//    char sep[3] = ",\n";
//    Masina m1;
//    m1.id = -1;
//    m1.nrUsi = 0;
//    m1.pret = 0;
//    m1.model = NULL;
//    m1.numeSofer = NULL;
//    m1.serie = 0;
//
//    if (!fgets(buffer, 100, file)) {
//        return m1;
//    }
//
//    char* aux;
//    aux = strtok(buffer, sep);
//    if (!aux) return m1;
//    m1.id = atoi(aux);
//
//    aux = strtok(NULL, sep);
//    if (!aux) {
//        m1.id = -1;
//        return m1;
//    }
//    m1.nrUsi = atoi(aux);
//
//    aux = strtok(NULL, sep);
//    if (!aux) {
//        m1.id = -1;
//        return m1;
//    }
//    m1.pret = (float)atof(aux);
//
//    aux = strtok(NULL, sep);
//    if (!aux) {
//        m1.id = -1;
//        return m1;
//    }
//    m1.model = copiazaText(aux);
//
//    aux = strtok(NULL, sep);
//    if (!aux) {
//        dezalocareMasina(&m1);
//        m1.id = -1;
//        return m1;
//    }
//    m1.numeSofer = copiazaText(aux);
//
//    aux = strtok(NULL, sep);
//    if (!aux) {
//        dezalocareMasina(&m1);
//        m1.id = -1;
//        return m1;
//    }
//    m1.serie = aux[0];
//
//    return m1;
//}
//
//void afisareMasina(Masina masina) {
//    printf("Id: %d\n", masina.id);
//    printf("Nr. usi : %d\n", masina.nrUsi);
//    printf("Pret: %.2f\n", masina.pret);
//    printf("Model: %s\n", masina.model);
//    printf("Nume sofer: %s\n", masina.numeSofer);
//    printf("Serie: %c\n\n", masina.serie);
//}
//
//void afisareListaMasini(ListaDubla lista) {
//    // afiseaza toate elemente de tip masina din lista dublu inlantuita
//    // prin apelarea functiei afisareMasina()
//    Nod* p = lista.prim;
//    while (p) {
//        afisareMasina(p->info);
//        p = p->next;
//    }
//}
//
//void afisareInversaListaMasini(ListaDubla lista) {
//    // afiseaza toate elemente de tip masina din lista dublu inlantuita
//    // prin apelarea functiei afisareMasina()
//    Nod* p = lista.ultim;
//    while (p) {
//        afisareMasina(p->info);
//        p = p->prev;
//    }
//}
//
//void adaugaMasinaInLista(ListaDubla* ld, Masina masinaNoua) {
//            // adauga la final in lista primita o noua masina pe care o primim ca parametru
//            Nod* nou = malloc(sizeof(Nod));
//            nou->info = masinaNoua;
//            nou->next = NULL;
//            nou->prev = ld->ultim;
//
//            if (ld->ultim != NULL) {
//                ld->ultim->next = nou;
//            }
//            else {
//		        ld->prim = nou;
//            }
//            ld->ultim = nou;
//
//        }
//
//void adaugaLaInceputInLista(ListaDubla* lista, Masina masinaNoua) {
//    // adauga la inceputul listei dublu inlantuite o noua masina pe care o primim ca parametru
//    Nod* nou = (Nod*)malloc(sizeof(Nod));
//    nou->info = masinaNoua;
//    nou->prev = NULL;
//    nou->next = lista->prim;
//
//    if (lista->prim != NULL) {
//        lista->prim->prev = nou;
//    }
//    else {
//        lista->ultim = nou;
//    }
//
//    lista->prim = nou;
//}
//
//ListaDubla citireLDMasiniDinFisier(const char* numeFisier) {
//    // functia primeste numele fisierului, il deschide si citeste toate masinile din fisier
//    // prin apelul repetat al functiei citireMasinaDinFisier()
//    // ATENTIE - la final inchidem fisierul/stream-ul
//
//    FILE* f = fopen(numeFisier, "r");
//    if (f) {
//        ListaDubla ld;
//		ld.prim = ld.ultim = NULL;
//        while (!feof(f)) {
//			adaugaMasinaInLista(&ld, citireMasinaDinFisier(f));
//        }
//		fclose(f);
//        return ld;
//    }
//
//}
//
//void dezalocareLDMasini(ListaDubla* lista) {
//    // sunt dezalocate toate masinile si lista dublu inlantuita de elemente
//
//    while (lista->prim && lista->prim->next) {
//		free(lista->prim->info.numeSofer);
//		free(lista->prim->info.model);
//		lista->prim = lista->prim->next;
//		free(lista->prim->prev);
//    }
//    if (lista->prim) {
//        free(lista->prim->info.numeSofer);
//        free(lista->prim->info.model);
//		free(lista->prim);
//    }
//
//	lista->prim = NULL;
//	lista->ultim = NULL;
//}
//
//float calculeazaPretMediu(ListaDubla lista) {
//    // calculeaza pretul mediu al masinilor din lista.
//    float suma = 0;
//    int nr = 0;
//    Nod* p = lista.prim;
//
//    while (p) {
//        suma += p->info.pret;
//        nr++;
//        p = p->next;
//    }
//    return suma / nr;
//}
//
//void stergeMasinaDupaID(ListaDubla* ld, int id) {
//    // sterge masina cu id-ul primit.
//    // tratati situatia ca masina se afla si pe prima pozitie, si pe ultima pozitie
//    if(ld->prim && ld->prim->info.id== id) {
//		free(ld->prim->info.numeSofer);
//		free(ld->prim->info.model);
//		ld->prim = ld->prim->next;
//        if(ld->prim) {
//            free(ld->prim->prev);
//        }
//        else {
//			free(ld->ultim);
//			ld->ultim = NULL;
//        }
//        return;
//	}
//
//    Nod* p = ld->prim;
//    while (p && p->info.id != id) {
//		p = p->next;
//    }
//    if (p) {
//        if(p->prev) {
//            p->prev->next = p->next;
//		}
//        if (p->next) {
//            p->next->prev = p->prev;
//        }
//        else {
//			p->prev->next = NULL;
//			ld->ultim = p->prev;
//        }
//        free(p->info.numeSofer);
//        free(p->info.model);
//		free(p);
//    }
//}
//
//char* getNumeSoferMasinaScumpa(ListaDubla lista) {
//    // cauta masina cea mai scumpa si
//    // returneaza numele soferului acestei masini.
//    // returnez o copie, deci trebuie free() in main
//    Nod* p = lista.prim;
//    Nod* max = lista.prim;
//    while (p) {
//        if (p->info.pret > max->info.pret) {
//            max = p;
//        }
//        p = p->next;
//    }
//
//    return max->info.numeSofer;
//}
//
//int main() {
//
//	ListaDubla lista=citireLDMasiniDinFisier("masini.txt");
//	afisareListaMasini(lista);
//	/*lista.prim = NULL;
//	lista.ultim = NULL;*/
//
//
//    printf("Pret mediu: %.2f\n\n", calculeazaPretMediu(lista));
//
// 
//   /* ListaDubla lista = citireLDMasiniDinFisier("masini.txt");
//
//    printf("=== Lista initiala ===\n");
//    afisareListaMasini(lista);*/
//     char* numeSofer = getNumeSoferMasinaScumpa(lista);
//     printf("Soferul masinii celei mai scumpe este: %s\n\n", numeSofer);
//
//
//	 stergeMasinaDupaID(&lista, 10);
//	 printf("=== Lista dupa stergerea masinii cu id = 1 ===\n");
//	 afisareListaMasini(lista);
//
//   /* stergeMasinaDupaID(&lista, 2);
//    printf("=== Lista dupa stergerea masinii cu id = 2 ===\n");
//    afisareListaMasini(lista);
//
//    Masina mNoua;
//    mNoua.id = 100;
//    mNoua.nrUsi = 4;
//    mNoua.pret = 55000;
//    mNoua.model = copiazaText("BMW");
//    mNoua.numeSofer = copiazaText("Popescu");
//    mNoua.serie = 'Z';
//
//    adaugaLaInceputInLista(&lista, mNoua);
//    printf("=== Lista dupa adaugare la inceput ===\n");
//    afisareListaMasini(lista);
//
//    dezalocareLDMasini(&lista);*/
//    return 0;
//}