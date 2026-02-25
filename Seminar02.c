#include<stdio.h>
#include<malloc.h>

struct Telefon {
	int id;
	int RAM;
	char* producator;
	float pret;
	char serie;
};
struct Telefon initializare(int id, int ram, const char* producator, float pret, char serie) {
	struct Telefon t;
	t.id = id;
	t.RAM = ram;
	t.producator = (char*)malloc(sizeof(char) * (strlen(producator) + 1));
	strcpy_s(t.producator, strlen(producator) + 1, producator);
	//strcpy(t.producator, producator);
	t.pret = pret;
	t.serie = serie;
	return t;
}
struct Telefon copiazaTelefon(struct Telefon t) {
	struct Telefon telefon = initializare(t.id, t.RAM, t.producator, t.pret, t.serie);
	return telefon;
}

void afisare(struct Telefon t) {
	printf(" id %d\n ram %d\n producator %s\n pret %5.2f\n serie %c\n\n", t.id, t.RAM, t.producator, t.pret,t.serie);
}

void afisareVector(struct Telefon* t, int nrElemente) {
	for (int i = 0; i < nrElemente; i++)
		afisare(t[i]);

}

struct Telefon* copiazaPrimeleNElemente(struct Telefon* t, int nrElemente, int nrElementeCopiate) {
	//copiem intr-un vector nou pe care il vom returna primele nrElementeCopiate
	if(nrElementeCopiate<=nrElemente)
	{
		struct Telefon* vectorNou = (struct Telefon*)malloc(sizeof(struct Telefon) * nrElementeCopiate);
		for (int i = 0; i < nrElementeCopiate; i++) {
			vectorNou[i] = copiazaTelefon(t[i]);
		}
		return vectorNou;
	}
}

void dezalocare(struct Telefon** t, int* nrElemente) {
	//dezalocam elementele din vector si vectorul
	for (int i = 0; i < *nrElemente; i++)
	{
		free((*t)[i].producator);
		(*t)[i].producator = NULL;
	}
	free(*t);
	*t = NULL;
	*nrElemente = 0;
}

void copiazaTelefoaneScumpe(struct Telefon* t, char nrElemente, float pretMinim, struct Telefon** vectorNou, int* dimensiune) {
	//parametrul prag poate fi modificat in functie de 
	// tipul atributului ales pentru a indeplini o conditie
	//este creat un nou vector cu elementele care indeplinesc acea conditie
	*dimensiune = 0;
	for (int i = 0; i < nrElemente; i++) {
		if (t[i].pret >= pretMinim)
		{
			(*dimensiune)++;
		}
	}
	*vectorNou = malloc((*dimensiune) * sizeof(struct Telefon));
	for (int i = 0, j=0; i < nrElemente; i++)
	{
		if (t[i].pret >= pretMinim)
		{
			(*vectorNou)[j] = copiazaTelefon(t[i]);
			j++;
		}
	}
}

struct Telefon getPrimulElementConditionat(struct Telefon* vector, int nrElemente, const char* conditie) {
	//trebuie cautat elementul care indeplineste o conditie
	//dupa atributul de tip char*. Acesta este returnat.
	struct Telefon t;
	t.id = 1;

	return t;
}


int main() {
	struct Telefon t;
	int ntTelefoaneCopiate = 2;
	t = initializare(1, 256, "Samsung", 2000.5, 'A');
	//afisare(t);
	int nrTelefon = 3;
	struct Telefon* telefoane = (struct Telefon*)malloc(sizeof(struct Telefon) * nrTelefon);
	telefoane[0] = initializare(1,8,"Samsung",3500,'B');
	telefoane[1] = initializare(1, 8, "Motorola", 2000.4, 'C');
	telefoane[2] = initializare(1, 8, "Apple", 3000.4, 'D');
	//afisareVector(telefoane, nrTelefon);
	struct Telefon* telefoaneCopiate = copiazaPrimeleNElemente(telefoane, nrTelefon, ntTelefoaneCopiate);
	//afisareVector(telefoaneCopiate,ntTelefoaneCopiate);
	//dezalocare(&telefoaneCopiate,&nrTelefonCopiate);
	int dim = 0;
	struct Telefon* vectorNou;
	copiazaTelefoaneScumpe(&telefoane, 3, 2000.4, &vectorNou, &dim);
	afisareVector( vectorNou, dim);
	return 0;
}