//#include<stdio.h>
//#include<malloc.h>
//
//struct Telefon {
//	int id;
//	int RAM;
//	char* producator;
//	float pret;
//	char serie;
//};
//struct Telefon initializare(int id, int ram, const char* producator, float pret, char serie) {
//	struct Telefon t;
//	t.id = id;
//	t.RAM = ram;
//	t.producator = (char*)malloc(sizeof(char) * (strlen(producator) + 1));
//	strcpy_s(t.producator, strlen(producator) + 1, producator);
//	//strcpy(t.producator, producator);
//	t.pret = pret;
//	t.serie = serie;
//	return t;
//}
//struct Telefon copiazaTelefon(struct Telefon t) {
//	struct Telefon telefon = initializare(t.id, t.RAM, t.producator, t.pret, t.serie);
//	return telefon;
//}
//
//void afisare(struct Telefon t) {
//	printf(" id %d\n ram %d\n producator %s\n pret %5.2f\n serie %c\n\n", t.id, t.RAM, t.producator, t.pret,t.serie);
//}
//
//void afisareVector(struct Telefon* t, int nrElemente) {
//	for (int i = 0; i < nrElemente; i++)
//		afisare(t[i]);
//
//}
//
//struct Telefon* copiazaPrimeleNElemente(struct Telefon* t, int nrElemente, int nrElementeCopiate) {
//	//copiem intr-un vector nou pe care il vom returna primele nrElementeCopiate
//	if(nrElementeCopiate<=nrElemente)
//	{
//		struct Telefon* vectorNou = (struct Telefon*)malloc(sizeof(struct Telefon) * nrElementeCopiate);
//		for (int i = 0; i < nrElementeCopiate; i++) {
//			vectorNou[i] = copiazaTelefon(t[i]);
//		}
//		return vectorNou;
//	}
//}
//
//void dezalocare(struct Telefon** t, int* nrElemente) {
//	//dezalocam elementele din vector si vectorul
//	for (int i = 0; i < *nrElemente; i++)
//	{
//		free((*t)[i].producator);
//		(*t)[i].producator = NULL;
//	}
//	free(*t);
//	*t = NULL;
//	*nrElemente = 0;
//}
//
//void copiazaTelefoaneScumpe(struct Telefon* t, char nrElemente, float pretMinim, struct Telefon** vectorNou, int* dimensiune) {
//	//parametrul prag poate fi modificat in functie de 
//	// tipul atributului ales pentru a indeplini o conditie
//	//este creat un nou vector cu elementele care indeplinesc acea conditie
//	*dimensiune = 0;
//	for (int i = 0; i < nrElemente; i++) {
//		if (t[i].pret >= pretMinim)
//		{
//			(*dimensiune)++;
//		}
//	}
//	*vectorNou = malloc((*dimensiune) * sizeof(struct Telefon));
//	for (int i = 0, j=0; i < nrElemente; i++)
//	{
//		if (t[i].pret >= pretMinim)
//		{
//			(*vectorNou)[j] = copiazaTelefon(t[i]);
//			j++;
//		}
//	}
//}
//
//struct Telefon getPrimulTelefonConditionat(struct Telefon* vector, int nrElemente, const char* conditie) {
//	//trebuie cautat elementul care indeplineste o conditie
//	//dupa atributul de tip char*. Acesta este returnat.
//	struct Telefon t;
//	t.id = -1;
//	t.producator = NULL;
//	for (int i = 0; i < nrElemente; i++)
//	{
//		if (vector[i].producator != NULL && strcmp(vector[i].producator, conditie) == 0)
//		{
//			return copiazaTelefon(vector[i]);
//		}
//	}
//
//
//	return t;
//}
//
//
//int main() {
//	struct Telefon t;
//	int ntTelefoaneCopiate = 2;
//	t = initializare(1, 256, "Samsung", 2000.5, 'A');
//	printf("Telefonul t este: \n");
//	afisare(t);
//	int nrTelefon = 4;
//	struct Telefon* telefoane = (struct Telefon*)malloc(sizeof(struct Telefon) * nrTelefon);
//	telefoane[0] = initializare(3, 8, "Motorola", 2000.4, 'C'); 
//	telefoane[1] = initializare(2, 8, "Google", 3500, 'B');
//	telefoane[2] = initializare(4, 8, "Apple", 3000.4, 'D');
//	telefoane[3] = t;
//	printf("Vectorul de telefoane este: \n");
//	afisareVector(telefoane, nrTelefon);
//	struct Telefon* telefoaneCopiate = copiazaPrimeleNElemente(telefoane, nrTelefon, ntTelefoaneCopiate);
//	printf("Primele 2 telefoane copiate sunt: \n");
//	afisareVector(telefoaneCopiate,ntTelefoaneCopiate);
//	dezalocare(&telefoaneCopiate,&ntTelefoaneCopiate);
//	int dim = 0;
//	struct Telefon* vectorNou;
//	copiazaTelefoaneScumpe(telefoane, nrTelefon, 2000.4, &vectorNou, &dim);
//	printf("Telefoane scumpe: \n");
//	afisareVector( vectorNou, dim);
//
//	struct Telefon gasit = getPrimulElementConditionat(telefoane, nrTelefon, "Samsung");
//	if (gasit.id != -1) {
//		printf("Primull telefon cu producatorul cerut este: \n");
//		afisare(gasit);
//	}
//	else printf("Nu s-a gasit niciun telefon cu producatorul cerut\n");
//	return 0;
//}