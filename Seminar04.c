//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
// 
//
//struct StructuraMasina {
//	int id;
//	int nrUsi;
//	float pret;
//	char* model;
//	char* numeSofer;
//	unsigned char serie;
//};
//typedef struct StructuraMasina Masina;
//
////creare structura pentru un nod dintr-o lista simplu inlantuita
//struct Nod{
//	Masina info;
//	struct Nod* next;
//};
//typedef struct Nod Nod;
//
//Masina citireMasinaDinFisier(FILE* file) {
//	char buffer[100];
//	char sep[3] = ",\n";
//	fgets(buffer, 100, file);
//	char* aux;
//	Masina m1;
//	aux = strtok(buffer, sep);
//	m1.id = atoi(aux);
//	m1.nrUsi = atoi(strtok(NULL, sep));
//	m1.pret= atof(strtok(NULL, sep));
//	aux = strtok(NULL, sep);
//	m1.model = malloc(strlen(aux) + 1);
//	strcpy_s(m1.model, strlen(aux) + 1, aux);
//
//	aux = strtok(NULL, sep);
//	m1.numeSofer = malloc(strlen(aux) + 1);
//	strcpy_s(m1.numeSofer, strlen(aux) + 1, aux);
//
//	m1.serie = *strtok(NULL, sep);
//	return m1;
//}
//
//void afisareMasina(Masina masina) {
//	printf("Id: %d\n", masina.id);
//	printf("Nr. usi : %d\n", masina.nrUsi);
//	printf("Pret: %.2f\n", masina.pret);
//	printf("Model: %s\n", masina.model);
//	printf("Nume sofer: %s\n", masina.numeSofer);
//	printf("Serie: %c\n\n", masina.serie);
//}
//
//void afisareListaMasini(Nod* cap) {
//	//afiseaza toate elemente de tip masina din lista simplu inlantuita
//	//prin apelarea functiei afisareMasina()
//	while (cap)
//	{
//		afisareMasina(cap->info);
//		cap = cap->next;
//
//	}
//}
//
//void adaugaMasinaInLista(Nod** cap, Masina masinaNoua) {
//	//adauga la final in lista primita o noua masina pe care o primim ca parametru
//	Nod* temp = malloc(sizeof(Nod));
//	temp->info = masinaNoua;
//	temp->next = NULL;
//	if (!(*cap)) *cap = temp;
//	else
//	{
//		Nod* p = *cap;
//		while (p->next)
//		{
//			p = p->next;
//		}
//		p->next = temp;
//
//	}
//}
//
//void adaugaLaInceputInLista(Nod** cap, Masina masinaNoua) {
//	//adauga la inceputul listei o noua masina pe care o primim ca parametru
//	Nod* temp = malloc(sizeof(Nod));
//	temp->info = masinaNoua;
//	temp->next = *cap;
//	*cap = temp;
//}
//
//void* citireListaMasiniDinFisier(const char* numeFisier) {
//	//functia primeste numele fisierului, il deschide si citeste toate masinile din fisier
//	//prin apelul repetat al functiei citireMasinaDinFisier()
//	//ATENTIE - la final inchidem fisierul/stream-ul
//	FILE* file = fopen(numeFisier, "r");
//	Nod* cap = NULL;
//	while (!feof(file))
//	{
//		adaugaMasinaInLista(&cap, citireMasinaDinFisier(file));
//	}
//	fclose(file);
//	return cap;
//}
//
//void dezalocareListaMasini(Nod** cap) {
//	//sunt dezalocate toate masinile si lista de elemente
//	Nod* temp;
//	while (*cap)
//	{
//		free((*cap)->info.numeSofer);
//		free((*cap)->info.model);
//		temp = *cap;
//		temp = (*cap)->next;
//		free(*cap);
//		*cap = temp;
//	}
//
//}
//
//float calculeazaPretMediu(Nod* cap) {
//	//calculeaza pretul mediu al masinilor din lista.
//	if (cap == NULL) return 0;
//	float suma = 0;
//	int nrMasini = 0;
//	while (cap)
//	{
//		suma += cap->info.pret;
//		nrMasini++;
//		cap = cap->next;
//
//	}
//	return suma / nrMasini;
//}
//
//void stergeMasiniDinSeria(Nod** cap,char serieCautata) {
//	//sterge toate masinile din lista care au seria primita ca parametru.
//	//tratati situatia ca masina se afla si pe prima pozitie, si pe ultima pozitie
//	while (*cap && (*cap)->info.serie == serieCautata) {
//		Nod* temp = *cap;
//		*cap = (*cap)->next;
//		free(temp->info.model);
//		free(temp->info.numeSofer);
//		free(temp);
//	}
//
//	if (*cap == NULL) return;
//
//	Nod* p = *cap;
//	while (p->next) {
//		if (p->next->info.serie == serieCautata) {
//			Nod* temp = p->next;
//			p->next = temp->next;
//			free(temp->info.model);
//			free(temp->info.numeSofer);
//			free(temp);
//		}
//		else {
//			p = p->next;
//		}
//	}
//}
//
//
//float calculeazaPretulMasinilorUnuiSofer(Nod* cap, const char* numeSofer) {
//	//calculeaza pretul tuturor masinilor unui sofer.
//	float suma = 0;
//	while (cap)
//	{
//		if (strcmp(cap->info.numeSofer, numeSofer) == 0)
//			suma += cap->info.pret;
//		cap = cap->next;
//
//	}
//	return suma;
//}
//
//int main() {
//
//	//definim o lista
//	Nod* cap = citireListaMasiniDinFisier("masini.txt");
//		printf("=== Lista initiala ===\n");
//		afisareListaMasini(cap);
//
//		printf("\nPret mediu: %.2f\n", calculeazaPretMediu(cap));
//
//		printf("\nStergem seria 'A'...\n");
//		stergeMasiniDinSeria(&cap, 'A');
//
//		printf("\n=== Lista dupa stergere ===\n");
//		afisareListaMasini(cap);
//
//		dezalocareListaMasini(&cap);
//		printf("\nMemorie eliberata. Program terminat.\n");
//
//		return 0;
//}