//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <malloc.h>
//#include <string.h>
//#include <stdlib.h>
//
//struct Vrajitori {
//	int id;
//	int nivelPutere;
//	float mana;
//	char* denumirePutere;
//	char* denumireVrajitor;
//	unsigned char casa;
//};
//
//typedef struct Vrajitori Vrajitori;
//typedef struct Nod Nod;
//typedef struct ListaDubla LD;
//
//struct Nod {
//	Vrajitori info;
//	Nod* next;
//	Nod* prev;
//};
//
//struct ListaDubla {
//	Nod* prim;
//	Nod* ultim;
//};
//
//Vrajitori citireVrajitoriDinFisier(FILE* numeFisier) {
//	char buffer[300];
//	char sep[3] = ",\n";
//	fgets(buffer, 300, numeFisier);
//	char* aux;
//	Vrajitori v1;
//
//	aux = strtok(buffer, sep);
//
//	v1.id = atoi(aux);
//
//	v1.nivelPutere = atoi(strtok(NULL, sep));
//
//	v1.mana = atof(strtok(NULL, sep));
//
//	aux = strtok(NULL, sep);
//	v1.denumirePutere = malloc(strlen(aux) + 1);
//	strcpy(v1.denumirePutere, aux);
//
//	aux = strtok(NULL, sep);
//	v1.denumireVrajitor = malloc(strlen(aux) + 1);
//	strcpy(v1.denumireVrajitor, aux);
//
//	v1.casa = *strtok(NULL, sep);
//
//	return v1;
//}
//
//void afisareVrajitori(Vrajitori vrajitor) {
//	printf("Id: %d\n", vrajitor.id);
//	printf("Nivel putere : %d\n", vrajitor.nivelPutere);
//	printf("Mana: %.2f\n", vrajitor.mana);
//	printf("Denumire putere: %s\n", vrajitor.denumirePutere);
//	printf("Denumire vrajitor: %s\n", vrajitor.denumireVrajitor);
//	printf("Casa: %c\n\n", vrajitor.casa);
//}
//
//void afisareListaVrajitori(LD lista) {
//	Nod* temp = lista.prim;
//	while (temp) {
//		afisareVrajitori(temp->info);
//		temp = temp->next;
//	}
//}
//
//void afisareInversaListaVrajitori(LD lista) {
//	Nod* temp = lista.ultim;
//	while (temp) {
//		afisareVrajitori(temp->info);
//		temp = temp->prev;
//	}
//}
//
//void adaugareVrajitorInLista(LD* lista, Vrajitori vrajitorNou) {
//	Nod* temp = malloc(sizeof(Nod));
//	temp->info = vrajitorNou;
//	temp->next = NULL;
//	temp->prev = lista->ultim;
//	if (lista->ultim != NULL) {
//		lista->ultim->next = temp;
//	}
//	else {
//		lista->prim = temp;
//	}
//	lista->ultim = temp;
//}
//
//void adaugareVrajitorLaInceputInLista(LD* lista, Vrajitori vrajitorNou) {
//	Nod* temp = malloc(sizeof(Nod));
//	temp->info = vrajitorNou;
//	temp->next = lista->prim;
//	temp->prev = NULL;
//	if (lista->prim != NULL) {
//		lista->prim->prev = temp;
//	}
//	else {
//		lista->ultim = temp;
//	}
//	lista->prim = temp;
//}
//
//LD citireListaVrajitoriDinFisier(const char* numeFisier) {
//	FILE* file = fopen(numeFisier, "r");
//	LD lista;
//	lista.prim = lista.ultim = NULL;
//	while (!feof(file)) {
//		adaugareVrajitorInLista(&lista, citireVrajitoriDinFisier(file));
//	}
//	fclose(file);
//	return lista;
//}
//
//void dezalocareListaDublaVrajitori(LD* lista) {
//	while (lista->prim && lista->prim->next) {
//		free(lista->prim->info.denumirePutere);
//		free(lista->prim->info.denumireVrajitor);
//		lista->prim - lista->prim->next;
//		free(lista->prim->prev);
//	}
//	if (lista->prim) {
//		free(lista->prim->info.denumirePutere);
//		free(lista->prim->info.denumireVrajitor);
//		free(lista->prim);
//	}
//	lista->prim = NULL;
//	lista->ultim = NULL;
//}
//
//int main() {
//	LD lista = citireListaVrajitoriDinFisier("Vrajitori.txt");
//
//	afisareListaVrajitori(lista);
//
//	return 0;
//}