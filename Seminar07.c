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

//creare structura pentru un nod dintr-o lista simplu inlantuita
typedef struct Nod Nod;
struct Nod{
	Masina masina;
	Nod* next;
};

//creare structura pentru tabela de dispersie
// aceasta este un vector de liste
typedef struct HashTable HashTable;
struct HashTable {
	int dim;
	Nod** vector;
};

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

void afisareListaMasini(Nod* nod) {
	//afiseaza toate elemente de tip masina din lista dublu inlantuita
	//prin apelarea functiei afisareMasina()
	while (nod) {
		afisareMasina(nod->masina);
		nod = nod->next;
	}
}

void adaugaMasinaInLista(Nod** nod, Masina masinaNoua) {
	//adauga la final in lista primita o noua masina pe care o primim ca parametru
	Nod* temp =(Nod*)malloc(sizeof(Nod));
	temp->masina= masinaNoua;
	temp->next = NULL;
	if (!(*nod)) {
		(*nod) = temp;
	}
	else {
		Nod* p=(*nod);
		while (p->next) {
			p = p->next;
		}
		p->next= temp;
	}
}


HashTable initializareHashTable(int dimensiune) {
	HashTable ht;
	//initializeaza vectorul de liste si seteaza fiecare lista ca fiind NULL;
	ht.dim = dimensiune;
	ht.vector = malloc(sizeof(Nod*) * ht.dim);
	for(int i=0;i<ht.dim; i++) {
		ht.vector[i] = NULL;
	}
	return ht;
}

int calculeazaHash(int id, int dimensiune) {
	// este calculat hash-ul in functie de dimensiunea tabelei si un atribut al masinii
	return (id * 31) % dimensiune;
}

void inserareMasinaInTabela(HashTable ht, Masina masina) {
	//este folosit mecanismul CHAINING
	//este determinata pozitia si se realizeaza inserarea pe pozitia respectiva
	int hash = calculeazaHash(masina.id, ht.dim);
	if(ht.vector[hash]!=NULL) {
		adaugaMasinaInLista(&(ht.vector[hash]), masina);
		return;
	}
	Nod* nod = malloc(sizeof(Nod));
	nod->masina = masina;
	nod->next = NULL;

	ht.vector[hash] = nod;

}

HashTable citireMasiniDinFisier(const char* numeFisier) {
	//functia primeste numele fisierului, il deschide si citeste toate masinile din fisier
	//prin apelul repetat al functiei citireMasinaDinFisier()
	// aceste masini sunt inserate intr-o tabela de dispersie initializata aici
	//ATENTIE - la final inchidem fisierul/stream-ul
	FILE* f = fopen(numeFisier, "r");
	HashTable ht = initializareHashTable(5);
	while (!feof(f)) {
		Masina m=citireMasinaDinFisier(f);
		inserareMasinaInTabela(ht, m);
	}
	fclose(f);
	return ht;
}

void afisareTabelaDeMasini(HashTable ht) {
	//sunt afisate toate masinile cu evidentierea clusterelor realizate
	for (int i = 0; i < ht.dim; i++) {
		while (ht.vector[i] != NULL) {
			printf("Cluster %d", i+1);
			Nod* p = ht.vector[i];
			afisareListaMasini(p);
			printf("=====================\n");
			break;
		}
	}

}

void dezalocareTabelaDeMasini(HashTable* ht) {
	//sunt dezalocate toate masinile din tabela de dispersie
	for (int i = 0; i < ht->dim; i++) {
		if (ht->vector[i] != NULL) {
			Nod* p = ht->vector[i];
			Nod* next = NULL;
			while (p != NULL) {
				free(p->masina.model);
				free(p->masina.numeSofer);
				next = p->next;
				free(p);
				p = next;
			}
		}
	}
	free(ht->vector);
	ht->dim = 0;
	ht->vector = NULL;
}

float* calculeazaPreturiMediiPerClustere(HashTable ht, int* nrClustere) {
	//calculeaza pretul mediu al masinilor din fiecare cluster.
	//trebuie sa returnam un vector cu valorile medii per cluster.
	//lungimea vectorului este data de numarul de clustere care contin masini
	int nr = 0;
	for (int i = 0; i < ht.dim; i++) {
		if(ht.vector[i]!=NULL) {
			nr++;
		}
	}

	float* preturiMediiPerClustere = malloc(sizeof(float) * nr);
	int j = 0;
	for (int i = 0; i < ht.dim; i++) {
		if (ht.vector[i] != NULL) {
			float suma = 0;
			int nrMasini = 0;
			Nod* aux = ht.vector[i];
			while (aux != NULL) {
				nrMasini++;
				suma += aux->masina.pret;
				aux = aux->next;
			}
			preturiMediiPerClustere[j++] = suma / nrMasini;
		}
	}
	*nrClustere = nr;
	return preturiMediiPerClustere;
}

Masina getMasinaById(HashTable ht,int id) {
	Masina m;
	m.id = -1;
	//cauta masina dupa valoarea atributului cheie folosit in calcularea hash-ului
	//trebuie sa modificam numele functiei 
	int hash = calculeazaHash(id, ht.dim);
	Nod* aux = ht.vector[hash];
	while (aux) {
		if (aux->masina.id == id) {
			m = aux->masina;

			m.model = malloc(strlen(aux->masina.model) + 1);
			strcpy(m.model, aux->masina.model);

			m.numeSofer = malloc(strlen(aux->masina.numeSofer) + 1);
			strcpy(m.numeSofer, aux->masina.numeSofer);

			return m;
		}
		aux = aux->next;
	}
	return m;
}

int main() {
	HashTable ht = citireMasiniDinFisier("masini.txt");
	afisareTabelaDeMasini(ht);

	printf("=== Masina cu id = 9 ===\n");
	afisareMasina(getMasinaById(ht, 9));

	printf("=== Preturi medii per cluster ===\n");
	int nrClustere ;
	float* preturiMedii = calculeazaPreturiMediiPerClustere(ht, &nrClustere);
	for (int i = 0; i < nrClustere; i++) {
		printf("%.2f\n",preturiMedii[i]);
	}
	dezalocareTabelaDeMasini(&ht);
	return 0;
}