//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <malloc.h>
//#include <string.h>
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
//
//struct Nod {
//	Vrajitori info;
//	struct Nod* next;
//};
//typedef struct Nod Nod;
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
//void afisareListaVrajitori(Nod* nod) {
//	while (nod) {
//		afisareVrajitori(nod->info);
//		nod = nod->next;
//	}
//}
//
//void adaugareVrajitorInLista(Nod** cap, Vrajitori vrajitorNou) {
//	Nod* temp = malloc(sizeof(Nod));
//	temp->info = vrajitorNou;
//	temp->next = NULL;
//	if (!(*cap)) *cap = temp;
//	else {
//		Nod* p = *cap;
//		while (p->next) {
//			p = p->next;
//		}
//		p->next = temp;
//	}
//}
//
//void adaugareVrajitorLaInceputInLista(Nod** cap, Vrajitori vrajitorNou) {
//	Nod* temp = malloc(sizeof(Nod));
//	temp->info = vrajitorNou;
//	temp->next = *cap;
//	*cap = temp;
//}
//
//Nod* citireListaVrajitoriDinFisier(const char* numeFisier) {
//	FILE* file = fopen(numeFisier, "r");
//	Nod* cap = NULL;
//	while (!feof(file)) {
//		adaugareVrajitorInLista(&cap, citireVrajitoriDinFisier(file));
//	}
//	fclose(file);
//	return cap;
//}
//
//void dezalocareListaVrajitori(Nod** cap) {
//	Nod* temp;
//	while (*cap) {
//		temp = *cap;
//		free((*cap)->info.denumirePutere);
//		free((*cap)->info.denumireVrajitor);
//		temp = (*cap)->next;
//		free(*cap);
//		*cap = temp;
//	}
//}
//
//int main() {
//	Nod* cap = citireListaVrajitoriDinFisier("Vrajitori.txt");
//	afisareListaVrajitori(cap);
//	return 0;
//}