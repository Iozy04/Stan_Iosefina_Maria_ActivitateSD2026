//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//
////trebuie sa folositi fisierul masini.txt
////sau va creati un alt fisier cu alte date
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
//void afisareMasina(Masina masina) {
//	//afiseaza toate atributele unei masini
//	printf("ID: %d\n Numar usi: %d\n Pret: %5.2f\n Model: %-10s\n Nume sofer: %-10s\n Seria: %c\n",
//		   masina.id,masina.nrUsi,masina.pret,masina.model,masina.numeSofer,masina.serie);
//}
//
//void afisareVectorMasini(Masina* masini, int nrMasini) {
//	//afiseaza toate elemente de tip masina din vector
//	//prin apelarea functiei afisareMasina()
//	if(masini==NULL || nrMasini<=0) {
//		printf("Nu exista masini de afisat\n");
//		return;
//	}
//	for(int i=0;i<nrMasini; i++) {
//		afisareMasina(masini[i]);
//	}
//}
//
//void adaugaMasinaInVector(Masina** masini, int * nrMasini, Masina masinaNoua) {
//	//adauga in vectorul primit o noua masina pe care o primim ca parametru
//	//ATENTIE - se modifica numarul de masini din vector;
//	Masina* temp = (Masina*)malloc(sizeof(Masina) * ((*nrMasini) + 1));
//	for (int i = 0; i < *nrMasini; i++) {
//		temp[i] = (*masini)[i];
//	}
//	temp[*nrMasini] = masinaNoua;
//	free(*masini);
//	*masini = temp;
//	(*nrMasini)++;
//}
//
//Masina citireMasinaFisier(FILE* file) {
//	//functia citeste o masina dintr-un stream deja deschis
//	//masina citita este returnata;
//	char linie[256];
//	char delimitator[3]=",\n";
//	Masina masina;
//	fgets(linie, 255, file);
//	masina.id = atoi(strtok(linie, delimitator));
//	masina.nrUsi = atoi(strtok(NULL, delimitator));
//	masina.pret = atof(strtok(NULL, delimitator));
//	char* temp = strtok(NULL,delimitator);
//	masina.model=(char*)malloc(sizeof(char)*(strlen(temp)+1));
//	strcpy(masina.model,temp);
//	temp = strtok(NULL, delimitator);
//	masina.numeSofer = (char*)malloc(sizeof(char) * (strlen(temp) + 1));
//	strcpy(masina.numeSofer, temp);
//	masina.serie = strtok(NULL, delimitator)[0];
//	return masina;
//}
//
//Masina* citireVectorMasiniFisier(const char* numeFisier, int* nrMasiniCitite) {
//	//functia primeste numele fisierului, il deschide si citeste toate masinile din fisier
//	//prin apelul repetat al functiei citireMasinaFisier()
//	//numarul de masini este determinat prin numarul de citiri din fisier
//	//ATENTIE - la final inchidem fisierul/stream-ul
//	FILE* file = fopen(numeFisier, "r");
//	if(!file) {
//		printf("Nu s-a putut deschide fisierul %s\n");
//		return;
//	}
//	else {
//		Masina* vectmasina=NULL;
//		*nrMasiniCitite = 0;
//		while(!feof(file)) {
//			Masina masina = citireMasinaFisier(file);
//			adaugaMasinaInVector(&vectmasina, nrMasiniCitite, masina );
//		}
//		return vectmasina;
//	}
//}
//
//void dezalocareVectorMasini(Masina** vector, int* nrMasini) {
//	//este dezalocat intreg vectorul de masini
//}
//
//int main() {
//
//	int nrMasini = 0;
//	Masina* masini = citireVectorMasiniFisier("masini.txt", &nrMasini);
//	for(int i=0;i<nrMasini;i++) {
//		afisareVectorMasini(masini,nrMasini);
//	}
//
//	return 0;
//}