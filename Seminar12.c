#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//trebuie sa folositi fisierul masini.txt
//sau va creati un alt fisier cu alte date

struct StructuraMasina {
	int id;
	int nrUsi;
	float pret;
	char* model;
	char* numeSofer;
	unsigned char serie;
};
typedef struct StructuraMasina Masina;

Masina citireMasinaDinFisier(FILE* file) {
	char buffer[100];
	char sep[3] = ",\n";
	fgets(buffer, 100, file);
	char* aux;
	Masina m1;
	aux = strtok(buffer, sep);
	m1.id = atoi(aux);
	m1.nrUsi = atoi(strtok(NULL, sep));
	m1.pret = atof(strtok(NULL, sep));
	aux = strtok(NULL, sep);
	m1.model = malloc(strlen(aux) + 1);
	strcpy_s(m1.model, strlen(aux) + 1, aux);

	aux = strtok(NULL, sep);
	m1.numeSofer = malloc(strlen(aux) + 1);
	strcpy_s(m1.numeSofer, strlen(aux) + 1, aux);

	m1.serie = *strtok(NULL, sep);
	return m1;
}

void afisareMasina(Masina masina) {
	printf("Id: %d\n", masina.id);
	printf("Nr. usi : %d\n", masina.nrUsi);
	printf("Pret: %.2f\n", masina.pret);
	printf("Model: %s\n", masina.model);
	printf("Nume sofer: %s\n", masina.numeSofer);
	printf("Serie: %c\n\n", masina.serie);
}

//1. 
// structuri necesare
//dorim stocarea unui graf intr-o lista de liste
//astfel avem nod ListaPrincipala si NodListaSecundara

struct NodListaSecundara {
	NodListaPrincipala* info;
	NodListaSecundara* next;
};
typedef struct NodListaSecundara NodListaSecundara;

struct NodListaPrincipala {
	Masina info;
	NodListaSecundara* vecini;//lista de adiacenta pentru fiecare nod din lista principala
	NodListaPrincipala* next;
};
typedef struct NodListaPrincipala NodListaPrincipala;

//2.
//functii de inserare in liste
//si in principala si in secundara

void inserareInListaPrincipala(NodListaPrincipala** lista, Masina m) {
	NodListaPrincipala* nou = malloc(sizeof(NodListaPrincipala));
	nou->next = NULL;
	nou->vecini = NULL;
	nou->info = m;

	if ((*lista) == NULL)
	{
		(*lista) = nou;
	}
	else
	{
		NodListaPrincipala* temp = (*lista);
		while (temp->next)
		{
			temp = temp->next;
		}
		temp->next = nou;
	}

}

void inserareInListaSecundara(NodListaSecundara** lista, NodListaPrincipala* nod) {
	NodListaSecundara* nou = malloc(sizeof(NodListaSecundara));
	nou->info = nod;
	nou->next = NULL;
	if ((*lista) == NULL)
	{
		(*lista) = nou;
	}
	else {
		NodListaSecundara* temp = (*lista);
		while (temp->next) {
			temp = temp->next;
		}
		temp->next = nou;
	}
}

//3.
//functie de cautarea in lista principala dupa ID
NodListaPrincipala* cautaNodDupaID(NodListaPrincipala* graf, int id) {
	while (graf && graf->info.id != id) {
		graf = graf->next;
	}
		return graf;
}

//4.
//inserare muchie
void inserareMuchie(NodListaPrincipala* graf, int idStart, int idStop) {
	NodListaPrincipala* start=cautaNodDupaID(graf, idStart);
	NodListaPrincipala* stop = cautaNodDupaID(graf, idStop);
	if (start && stop) {
		inserareInListaSecundara(&start->vecini, stop);
		inserareInListaSecundara(&stop->vecini, start);
	}

}


void* citireNoduriMasiniDinFisier(const char* numeFisier) {
	//functia primeste numele fisierului, il deschide si citeste toate masinile din fisier
	//prin apelul repetat al functiei citireMasinaDinFisier()
	//ATENTIE - la final inchidem fisierul/stream-ul
	FILE* file = fopen(numeFisier, "r");
	NodListaPrincipala* graf = NULL;
	while(!feof(file))
	{
		inserareInListaPrincipala(&graf, citireMasinaDinFisier(file));
	}
	fclose(file);
	return graf;
}

void citireMuchiiDinFisier(NodListaPrincipala* graf,const char* numeFisier) {
	//functia primeste numele fisierului, il deschide si citeste 
	//toate id-urile de start si stop pentru fiecare muchie
	//ATENTIE - la final inchidem fisierul/stream-ul

	FILE* file = fopen(numeFisier, "r");
	int idStart, idStop;

	while(!feof(file))
	{
		fscanf(file, "%d %d", &idStart, &idStop);
		inserareMuchie(graf, idStart, idStop);
	}
	fclose(file);
}

void dezalocareNoduriGraf(void* listaPrincipala) {
	//sunt dezalocate toate masinile din graf 
	//si toate nodurile celor doua liste
}

void afiseazaListaSecundara(NodListaPrincipala* graf, int id) {
	//se cauta nodul cu id-ul dat ca parametru
	//daca acesta exista se afiseaza toate masinile care sunt vecine cu acesta
	NodListaPrincipala* nou = cautaNodDupaID(graf, id);
	NodListaSecundara* aux = nou->vecini;
	while (aux) {
		afisareMasina(aux->info->info);
		aux = aux->next;
	}
}

int main() {

	NodListaPrincipala* garf = citireNoduriMasiniDinFisier("masini.txt");
	citireMuchiiDinFisier(garf, "muchii.txt");
	afiseazaListaSecundara(garf,8);
	return 0;
} 