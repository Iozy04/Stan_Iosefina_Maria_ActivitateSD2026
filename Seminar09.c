//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//
////trebuie sa folositi fisierul masini.txt
////sau va creati un alt fisier cu alte date
//
////Arbore = este o structura de date formata din noduri
////care poate fi folosita pentru a stoca date intr-un mod ierarhic
////Arborele binar de cautare = este un tip de arbore in care fiecare nod are cel mult doi copii
//	//si in care valoarea din nodul parinte este mai mare decat valorile din subarborele stang
//	//si mai mica decat valorile din subarborele drept
//
//typedef struct StructuraMasina Masina;
//
//struct StructuraMasina {
//	int id;
//	int nrUsi;
//	float pret;
//	char* model;
//	char* numeSofer;
//	unsigned char serie;
//};
//
////creare structura pentru un nod dintr-un arbore binar de cautare
//typedef struct NodArbore Nod;
//struct NodArbore {
//	Masina info;
//    Nod* stanga;
//	Nod* dreapta;
//};
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
//
//void adaugaMasinaInArboreDupaID(Nod** radacina, Masina masinaNoua) {
//	//adauga o noua masina pe care o primim ca parametru in arbore,
//	//astfel incat sa respecte princiippile de arbore binar de cautare
//	//dupa o anumita cheie pe care o decideti - poate fi ID
//	if (*radacina)
//	{
//		if ((*radacina)->info.id > masinaNoua.id) {
//			 adaugaMasinaInArboreDupaID(&(*radacina)->stanga, masinaNoua);
//		}
//		else {
//			adaugaMasinaInArboreDupaID(&(*radacina)->dreapta, masinaNoua);
//		}
//	}
//	else {
//		Nod*nou=malloc(sizeof(Nod));
//		nou->info = masinaNoua;
//		nou->stanga = NULL;
//		nou->dreapta = NULL;
//		*radacina = nou;
//	}
//}
//
//Nod* citireArboreDeMasiniDinFisier(const char* numeFisier) {
//	//functia primeste numele fisierului, il deschide si citeste toate masinile din fisier
//	//prin apelul repetat al functiei citireMasinaDinFisier()
//	//ATENTIE - la final inchidem fisierul/stream-ul
//	FILE* f = fopen(numeFisier, "r");
//	Nod* radacina = NULL;
//	if(f)
//	{
//		while (!feof(f)) {
//			Masina m = citireMasinaDinFisier(f);
//			adaugaMasinaInArboreDupaID(&radacina, m);
//		}
//	}
//	fclose(f);
//	return radacina;
//}
//
////Parcurgerea unui arbore = este procesul de vizitare a tuturor nodurilor din arbore intr-o anumita ordine
////Exista trei moduri de parcurgere a unui arbore binar de cautare: 
//	//1. Parcurgerea in ordine = viziteaza nodurile in ordinea stanga, radacina, dreapta
//	//2. Parcurgerea preordine = viziteaza nodurile in ordinea radacina, stanga, dreapta
//	//3. Parcurgerea postordine = viziteaza nodurile in ordinea stanga, dreapta, radacina
//
//void afisareInordine(Nod* radacina) {
//	if (radacina != NULL) {
//		afisareInordine(radacina->stanga);
//		afisareMasina(radacina->info);
//		afisareInordine(radacina->dreapta);
//	}
//}
//void afisarePreordine(Nod* radacina) {
//	if (radacina != NULL) {
//		afisareMasina(radacina->info);
//		afisarePreordine(radacina->stanga);
//		afisarePreordine(radacina->dreapta);
//	}
//}
//void afisarePostordine(Nod* radacina) {
//	if (radacina != NULL) {
//		afisarePostordine(radacina->stanga);
//		afisarePostordine(radacina->dreapta);
//		afisareMasina(radacina->info);
//	}
//}
//
//void afisareMasiniDinArbore(Nod* radacina) {
//	printf("\nPREORDINE:\n");
//	afisarePreordine(radacina);
//
//	printf("\nINORDINE:\n");
//	afisareInordine(radacina);
//
//	printf("\nPOSTORDINE:\n");
//	afisarePostordine(radacina);
//}
//
////void dezalocareMasina(Masina m) {
////	free(m.model);
////	free(m.numeSofer);
////}
//
////Dezalocarea se face in postordine pentru a fi siguri ca nu pierdem 
//// referinta la nodurile copil inainte de a le dezaloca
//
//void dezalocareArboreDeMasini(Nod** radacina) {
//	//sunt dezalocate toate masinile si arborele de elemente
//	if (*radacina != NULL) {
//		dezalocareArboreDeMasini(&(*radacina)->stanga);
//		dezalocareArboreDeMasini(&(*radacina)->dreapta);
//
//		free((*radacina)->info.model);
//		free((*radacina)->info.numeSofer);
//		free(*radacina);
//		*radacina = NULL;
//	}
//}
//
//Masina getMasinaByID(Nod* radacina, int id) {
//	Masina m;
//	// initializare
//	m.id = -1;
//
//	if (radacina == NULL) {
//		return m;
//	}
//
//	if (id == radacina->info.id) {
//		return radacina->info;
//	}
//	else if (id < radacina->info.id) {
//		return getMasinaByID(radacina->stanga, id);
//	}
//	else {
//		return getMasinaByID(radacina->dreapta, id);
//	}
//}
//int determinaNumarNoduri(Nod* radacina) {
//	if (radacina == NULL) {
//		return 0;
//	}
//
//	return 1 + determinaNumarNoduri(radacina->stanga)
//		+ determinaNumarNoduri(radacina->dreapta);
//}
//
//int calculeazaInaltimeArbore(Nod* radacina) {
//	//calculeaza inaltimea arborelui care este data de 
//	//lungimea maxima de la radacina pana la cel mai indepartat nod frunza
//	if (radacina) {
//		return 1 + max(calculeazaInaltimeArbore(radacina->stanga), calculeazaInaltimeArbore(radacina->dreapta));
//	}
//	return 0;
//}
//
//float calculeazaPretTotal(Nod* radacina) {
//	//calculeaza pretul tuturor masinilor din arbore.
//	if (radacina) {
//		return radacina->info.pret + calculeazaPretTotal(radacina->stanga) + calculeazaPretTotal(radacina->dreapta);
//	}
//	return 0;
//
//}
//
//float calculeazaPretulMasinilorUnuiSofer(Nod*radacina, const char* numeSofer) {
//	//calculeaza pretul tuturor masinilor unui sofer.
//	if (radacina) {
//		if (strcmp(radacina->info.numeSofer, numeSofer) == 0) {
//			return radacina->info.pret + calculeazaPretulMasinilorUnuiSofer(radacina->stanga, numeSofer)+ calculeazaPretulMasinilorUnuiSofer(radacina->dreapta, numeSofer);
//		}
//		else {
//			return calculeazaPretulMasinilorUnuiSofer(radacina->stanga, numeSofer) + calculeazaPretulMasinilorUnuiSofer(radacina->dreapta, numeSofer);
//		}
//	}
//	return 0;
//}
//
//int main() {
//	Nod* arbore = citireArboreDeMasiniDinFisier("Masini_Arbore.txt");
//
//	if (arbore == NULL) {
//		printf("Arborele nu a fost creat.\n");
//		return 0;
//	}
//
//	printf("\n========== AFISARE ARBORE ==========\n");
//	afisareMasiniDinArbore(arbore);
//
//	printf("\n========== CAUTARE DUPA ID EXISTENT ==========\n");
//	afisareMasina(getMasinaByID(arbore, 3));
//
//	printf("\n========== NUMAR NODURI ==========\n");
//	printf("Numar total de noduri: %d\n", determinaNumarNoduri(arbore));
//
//	printf("\n========== INALTIME ARBORE ==========\n");
//	printf("Inaltime arbore: %d\n", calculeazaInaltimeArbore(arbore));
//
//	printf("\n========== PRET TOTAL ==========\n");
//	printf("Pret total masini: %.2f\n", calculeazaPretTotal(arbore));
//
//	printf("\n========== PRET MASINI SOFER ==========\n");
//	printf("Pret total masini pentru soferul Ion: %.2f\n", calculeazaPretulMasinilorUnuiSofer(arbore, "Ionescu"));
//
//	dezalocareArboreDeMasini(&arbore);
//
//
//	return 0;
//}