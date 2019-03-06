// Nicu Razvan-Alexandru 313CB
#include "functii.h"

/*
 * Functie de comparare pentru a compara doua stringuri
 * returneaza 0 in cazul 'egalitatii'
*/

int comparareCuloare(void* x, void* y)
{
	
	return strcmp(((sistemHanoi*)(((TLista)x) -> info)) -> culoare, (char*)y);
}

 
/*
 * Functie care verifica daca stiva 
 * este vida. Output 0/1 nu/da
*/

int VidaS(TStiva x)
{
 	if( x == NULL)
 	{
 		return 1;
 	}
 	else
 	{ 
 		return 0;
	}
}

/*
 * Functie ce aloca o celula 
 * pentru umplerea stivei/cozii
*/

TStiva AlocareCelulaa(void *x)
{
	TStiva aux = NULL;
	aux = (TStiva)calloc(1, sizeof(TDisc));
	if (!aux)
	{
		return NULL;
	}
	// adaugare informatie
	aux -> info = x;
	aux -> urm = NULL;
	return aux;
}

/*
 * Functie ce realizeaza extragerea unui element
 * dintr-o stiva. 
*/

void* Pop(AStiva x)
{
	TStiva head = (TStiva)(*x);
	TStiva element = head;
	(*x) = (*x) -> urm;
	return element;
}

/*
 * Functie ce realizeaza introducerea unui element
 * intr-o stiva. 
*/

TStiva Push(TStiva x, void *elem)
{
	TStiva head =  x;
	TStiva nou = (TStiva)elem;
	nou -> urm = head;
	head = nou;
	return head;
}

/*
 * Functie ce realizeaza extragerea unui element
 * dintr-o coada. 
*/

void* extrQ(ACoada start, ACoada end)
{
	TCoada eliminat = *start;
	*start = (*start) -> urm;
	return eliminat;
}

/*
 * Functie ce realizeaza introducerea unui element
 * intr-o coada. 
*/

void intrQ(ACoada start, ACoada end, void *y)
{
	if (*start == NULL && *end == NULL)// daca avem o coada goala
	{
		*start = (TCoada)y;
		*end = (TCoada)y;
	}
	else
	{
		(*end) -> urm = (TCoada)y;
		*end = (*end) -> urm;
	}
}

/*
 * Functie ce calculeaza lungimea unei stive.
 * Fara iteratii prin stiva. Folosind push/pop
 * + contorizari la mutarea intr-o stiva auxiliara
*/

int dimS(void *x)
{
	int nr = 0;
	TStiva aux = NULL;
	TStiva disc = NULL;
	TStiva head = (TStiva)x;
	while (VidaS(head) == 0)
	{	
		nr++;
		disc = Pop(&head);
		aux = Push(aux, disc);
	}
	// am mutat tot in aux
	while(VidaS(aux) == 0)
	{	
		disc = Pop(&aux);
		head = Push(head, disc);
	}
	return nr;
}

/*
 * Functie ce primeste ca parametri tija/stiva
 * si un bloc 'TStiva' alocat. Aceasta introduce
 * discul pe pozitia corespunzatoare in stiva data
 * (conform ordinii diametrelor) prin mutarea discurilor
 * intr-o stiva auxiliara si analog cu ajutorul Pop/Push
 */ 

TStiva introduceInTija(TStiva tija, void *y)
{
	TStiva disc = (TStiva)y;
	TStiva aux = NULL;
	TStiva disc1 = NULL;
	if (tija == NULL) // daca tija e goala
	{
		disc -> urm = tija;
		tija = disc;
		return tija; 
	} // am pus discul in tija initial goala si returnez tija
	
	while (VidaS(tija) == 0 && ((Disc*)(tija -> info)) -> diametru < ((Disc*)(disc -> info)) -> diametru)
	{
		TStiva disc1 = Pop(&tija);
		aux = Push(aux, disc1);
	//	scot discurile de dimensiune mai mica si le bag in stiva auxiliara
	}
	// am loc sa pun.
	tija = Push(tija, disc);
	// pun discul pe pozitia buna
	while (VidaS(aux) == 0)
	{
		disc1 = Pop(&aux);
		tija = Push(tija, disc1);
	}
	return tija;
}

 /*
 * Functie ce primeste ca parametri listadesisteme
 * si un bloc 'TStiva' alocat anterior. Functia cauta
 * sistemul de culoare corespunzatoare discului, si insereaza
 * discul cu ajutorul functiei de mai sus 'introduceInTija'
 * , iar daca sistemul nu exista, il creeaza si apoi introduce
 * discul in tijaA a sistemului nou creat.
 */ 

TLista IntroduceDisc(TLista listasisteme, void *y, TFCmp functie)
{
	TLista sistemnou = NULL;
	TLista p = NULL; // iterez pprin listadesisteme
	TStiva discAlocat = AlocareCelulaa(y);
	// pun in discAlocat discul dat ca al doilea parametru
	char culoare[50];
	strcpy(culoare, ((Disc*)(discAlocat -> info)) -> culoare);
	if (listasisteme == NULL) // daca nu avem niciun sistem trebuie sa cream primul sistem
	{	
		listasisteme = (TLista)calloc(1, sizeof(TCelula));
		if (!listasisteme)
		{
			return NULL;
		}
		listasisteme -> info = calloc (1, sizeof(sistemHanoi)); // aloc zona pentru sistem
		if (!(listasisteme -> info))
		{
			free(listasisteme);
			return NULL;
		}
		((sistemHanoi*)(listasisteme -> info)) -> culoare = strdup(culoare);
		if (!(((sistemHanoi*)(listasisteme -> info)) -> culoare))
		{
			free(listasisteme -> info);
			free(listasisteme);
			return NULL;
		}
		((sistemHanoi*)(listasisteme -> info)) -> tijaA = NULL;
		((sistemHanoi*)(listasisteme -> info)) -> tijaB = NULL;
		((sistemHanoi*)(listasisteme -> info)) -> tijaC = NULL;
		listasisteme -> urm = NULL;
		((sistemHanoi*)(listasisteme -> info)) -> tijaA = introduceInTija( ((sistemHanoi*)(listasisteme -> info)) -> tijaA, discAlocat);

	}
	else
	{
		for (p = listasisteme; p != NULL; p = p -> urm) // caut sistem cu culoarea discului
		{
			if (functie(p, culoare) == 0) // daca sistemul are culoare pe care o caut
			{
				((sistemHanoi*)(p -> info)) -> tijaA = introduceInTija( ((sistemHanoi*)(p -> info)) -> tijaA, discAlocat); // introduc discul in tijaA din sistemul gasit
				return listasisteme;
			}

		}
		if (p == NULL) // daca nu gasim sistem de culoarea necesara
		{
			sistemnou = (TLista)calloc(1, sizeof(TCelula));
			if(!sistemnou)
			{
				return NULL;
			}
			sistemnou -> info = calloc (1, sizeof(sistemHanoi)); // aloc sistemul
			if (!(sistemnou -> info))
			{
				free(sistemnou);
				return NULL;
			}
			((sistemHanoi*)(sistemnou -> info)) -> culoare = strdup(culoare);
			if (!(((sistemHanoi*)(sistemnou -> info)) -> culoare))
			{
				free(sistemnou -> info);
				free(sistemnou);
				return NULL;
			}
			((sistemHanoi*)(sistemnou -> info)) -> tijaA = NULL;
			((sistemHanoi*)(sistemnou -> info)) -> tijaB = NULL;
			((sistemHanoi*)(sistemnou -> info)) -> tijaC = NULL;
			sistemnou -> urm = listasisteme;
			listasisteme = sistemnou;
			// leg noul sistem la inceputul listei de sisteme.
			((sistemHanoi*)(sistemnou -> info)) -> tijaA = introduceInTija(((sistemHanoi*)(sistemnou -> info)) -> tijaA, discAlocat);
		}

	}
	return listasisteme;
}

 /*
 * Functie ce cauta sistemul cerut si ii afiseaza
 * configuratia din momentul apelarii. (foloseste mutarea
 * in stiva auxiliara cu ajutorul POp/Push.
 */
void functieShow(TLista listasisteme, void *y, FILE* out, TFCmp functie)
{
 	char* culoare = (char*)y; // culoarea.
	//printf("%s \n", culoare);
	TStiva aux = NULL; // stiva auxiliara
	TStiva disc1 = NULL;
	TLista p = NULL; // iterez prin lista de sisteme
	for (p = listasisteme; p != NULL; p = p -> urm)
	{
		if (functie(p, culoare ) == 0 )
		{
			break;
		}
		// daca gasesc sistemul pe care il caut ma opresc 
	}
	if (p == NULL)
	{
		fprintf(out, "A_%s:\n", culoare);
		fprintf(out, "B_%s:\n", culoare);
		fprintf(out, "C_%s:\n", culoare);
	}
	else
	{	
		// tija A
		fprintf(out, "A_%s:", culoare);
		while (VidaS( ((sistemHanoi*)(p -> info)) -> tijaA) == 0 ) // cat timp nu e vida
		{
			disc1 = Pop(&(((sistemHanoi*)(p -> info)) -> tijaA)); // EXTRAG discul din tija
			aux = Push(aux, disc1); // pun discul in aux
		}
		// am pus toate discurile in aux , iar acum incep operatia inversa
		while (VidaS(aux) == 0 ) // cat timp nu e vida
		{
			disc1 = Pop(&aux); // EXTRAG discul din tija
			fprintf(out, " %d", ((Disc*)(disc1 -> info)) -> diametru);
			(((sistemHanoi*)(p -> info)) -> tijaA) = Push((((sistemHanoi*)(p -> info)) -> tijaA), disc1); // pun discul in aux
		}
		fprintf(out, "\n");
		aux = NULL;

		// tija B
		fprintf(out, "B_%s:", culoare);
		while (VidaS(((sistemHanoi*)(p -> info)) -> tijaB) == 0 ) // cat timp nu e vida
		{
			disc1 = Pop(&(((sistemHanoi*)(p -> info)) -> tijaB)); // EXTRAG discul din tija
			aux = Push(aux, disc1); // pun discul in aux
		}
		// am pus toate discurile in aux , iar acum incep operatia inversa
		while (VidaS(aux) == 0 ) // cat timp nu e vida
		{
			disc1 = Pop(&aux); // EXTRAG discul din tija
			fprintf(out, " %d", ((Disc*)(disc1 -> info)) -> diametru);
			(((sistemHanoi*)(p -> info)) -> tijaB) = Push((((sistemHanoi*)(p -> info)) -> tijaB), disc1); // pun discul in aux
		}
		fprintf(out, "\n");
		aux = NULL;

		// tija C
		fprintf(out, "C_%s:", culoare);
		while (VidaS(((sistemHanoi*)(p -> info)) -> tijaC) == 0 ) // cat timp nu e vida
		{
			disc1 = Pop(&(((sistemHanoi*)(p -> info)) -> tijaC)); // EXTRAG discul din tija
			aux = Push(aux, disc1); // pun discul in aux
		}
		// am pus toate discurile in aux , iar acum incep operatia inversa
		while (VidaS(aux) == 0 ) // cat timp nu e vida
		{
			disc1 = Pop(&aux); // EXTRAG discul din tija
			fprintf(out, " %d", ((Disc*)(disc1 -> info)) -> diametru);
			(((sistemHanoi*)(p -> info)) -> tijaC) = Push((((sistemHanoi*)(p -> info)) -> tijaC), disc1); // pun discul in aux
		}
		fprintf(out, "\n");
		aux = NULL;

	}
}

 /*
 * Functie ce realizeaza eliberarea stivei prin eliberarea
 * fiecarui disc din stiva.
 */

void EliberareStiva(AStiva stiva)
{
	TStiva stiva1 = *stiva;
	TStiva p = NULL;
	TStiva temp = NULL;
	for (p = stiva1; p !=NULL; )
	{
		temp = p;
		p = p -> urm;
		free(((Disc*)(temp -> info)) -> culoare);
		free(temp -> info);
		free(temp);
	}
	stiva1 = NULL;
}

 /*
 * Functie ce realizeaza eliberarea unei cozi
 * prin eliminarea fiecarui element din coada
 */

void EliberareCoada(ACoada start, ACoada end)
{
	TCoada disc;
	while (*start != *end)
	{
		disc = (TCoada)extrQ(start, end);
		free(((infoCoada*)(disc -> info)) -> mutare);
		free(disc -> info);
		free(disc);
	}
	// am eliberat tot fara ultimul element
	free(((infoCoada*)((*start) -> info)) -> mutare);
	free((*start) -> info);
	free((*start));
	// am eliberat si ultimul
}

 /*
 * Functie ce realizeaza eliberarea listei de sisteme
 * prin eliberarea stivelor/cozilor si celorlalte elemente alocate
 * cu ajutorul functiilor de mai sus.
 */

void EliberareLista( ALista listasisteme)
{
	TLista lista = *listasisteme;
	TLista temp = NULL;
	TLista p = NULL;
	for (p = lista; p != NULL; )
	{
		temp = p;
		p = p -> urm;
		free(((sistemHanoi*)(temp -> info)) -> culoare);
		EliberareStiva(&(((sistemHanoi*)(temp -> info)) -> tijaA));
		EliberareStiva(&(((sistemHanoi*)(temp -> info)) -> tijaB));
		EliberareStiva(&(((sistemHanoi*)(temp -> info)) -> tijaC));
		if (((sistemHanoi*)(temp -> info)) -> start != NULL || ((sistemHanoi*)(temp -> info)) -> end != NULL)
		{
			EliberareCoada(&(((sistemHanoi*)(temp -> info)) -> start), &(((sistemHanoi*)(temp -> info)) -> end));
		}
		free(temp -> info);
		free(temp);
	}
}

 /*
 * Functie ce realizeaza generarea mutarilor intr-un mod recursiv
 * din sistemul hanoi plecand de la numarul de discuri de pe tijaA
 * Creeaza o coada cu mutarile obtinute
 */

int hanoi (int n, char* a, char* b, char* c, ACoada start, ACoada end)
{
	char string[20];
	TCoada indicestart = *start;
	TCoada indiceend = *end;
	TCoada celulanoua;
	if(n == 1)
	{
		sprintf(string, "%s->%s", a, b);
		// pun mutarea in string.
		infoCoada* mutarenoua = (infoCoada*)malloc(sizeof(infoCoada));
		mutarenoua -> mutare = strdup(string);
		if (!(mutarenoua -> mutare))
		{
			return -1;
		}
		celulanoua = (TCoada)AlocareCelulaa(mutarenoua);
		if (!celulanoua)
		{
			free(mutarenoua -> mutare);
			return -1;
		}
		intrQ(start, end, celulanoua);
	}
	else
	{
		hanoi(n-1, a, c, b, start, end);

		sprintf(string, "%s->%s", a, b);
		// pun mutarea in string.
		infoCoada* mutarenoua = (infoCoada*)malloc(sizeof(infoCoada));
		mutarenoua -> mutare = strdup(string);
		if (!(mutarenoua -> mutare))
		{
			return -1;
		}
		celulanoua = (TCoada)AlocareCelulaa(mutarenoua);
		if (!celulanoua)
		{
			free(mutarenoua -> mutare);
			return -1;
		}
		intrQ(start, end, celulanoua);
		
		hanoi(n-1, c, b, a, start, end);
	}
}

 /*
 * Functie ce initializeaza coada din sistemul la care s-a apelat
 * fie functia play , fie functia show_moves din moment ce dupa aceasta
 * apelare nu se vor mai face adaugari in sistem.
 */

void creeareCoada(TLista lista, void *y, TFCmp functie)
{
	char* culoare = (char*)y;
	TLista p = NULL; // iterez sistemele pentru a cauta culoarea potrivita.
	TCoada t = NULL;
	for (p = lista; p != NULL; p = p -> urm)
	{
		if (functie(p, culoare ) == 0 )
		{
			break;
		}
	}
	if (p == NULL)
	{
		printf("NU AM GASIT CULOARE CERUTA\n");	
	}
	((sistemHanoi*)(p -> info)) -> start = NULL;
	((sistemHanoi*)(p -> info)) -> end = NULL;
	int n = dimS(((sistemHanoi*)(p -> info)) -> tijaA);
	char a[10], b[10], c[10];
	strcpy(a, "A");
	strcpy(b, "B");
	strcpy(c, "C");
	hanoi(n, a, c, b, &(((sistemHanoi*)(p -> info)) -> start),&(((sistemHanoi*)(p -> info)) -> end));
	((sistemHanoi*)(p -> info)) -> nrMutariRamase = pow(2, dimS( ((sistemHanoi*)(p -> info)) -> tijaA)) -1;
	// numarul maxim de mutari = 2^n -1
	((sistemHanoi*)(p -> info)) -> sw = 1;
	// am initializat cozile
}

 /*
 * Functie ce elimina din coada n miscari si modifica sistemul
 * conform celor n miscari eliminate.
 */

void play( TLista listasisteme, void* y, int nrMutari, TFCmp functie)
{
	char* culoare = (char*)y;
	TCoada mutare = NULL;
	TStiva disc = NULL;
	TLista p = NULL;
	for (p = listasisteme; p != NULL; p = p -> urm)
	{
		if (functie(p, culoare ) == 0 )
		{
			break;
		}
	}
	if (p == NULL)
	{
		printf("NU AM GASIT CULOARE CERUTA\n");	
	}
	// am in p sistemul bun
	int i, sw = 0;
	for (i = 0; i < nrMutari; i++)
	{
		((sistemHanoi*)(p -> info)) -> nrMutariRamase--;
		if (((sistemHanoi*)(p -> info)) -> nrMutariRamase == 0)
		{
			sw = 1;
			break;
		}
		mutare = (TCoada)extrQ( &(((sistemHanoi*)(p -> info)) -> start) , &(((sistemHanoi*)(p -> info)) -> end));
		if (strcmp(((infoCoada*)(mutare -> info)) -> mutare, "A->B") == 0)
		{
			disc = Pop(&(((sistemHanoi*)(p -> info)) -> tijaA));
			((sistemHanoi*)(p -> info)) -> tijaB = Push( ((sistemHanoi*)(p -> info)) -> tijaB, disc);
		}
		if (strcmp(((infoCoada*)(mutare -> info)) -> mutare, "A->C") == 0)
		{
			disc = Pop(&(((sistemHanoi*)(p -> info)) -> tijaA));
			((sistemHanoi*)(p -> info)) -> tijaC = Push( ((sistemHanoi*)(p -> info)) -> tijaC, disc);
		}
		if (strcmp(((infoCoada*)(mutare -> info)) -> mutare, "B->A") == 0)
		{
			disc = Pop(&(((sistemHanoi*)(p -> info)) -> tijaB));
			((sistemHanoi*)(p -> info)) -> tijaA = Push( ((sistemHanoi*)(p -> info)) -> tijaA, disc);
		}
		if (strcmp(((infoCoada*)(mutare -> info)) -> mutare, "B->C") == 0)
		{
			disc = Pop(&(((sistemHanoi*)(p -> info)) -> tijaB));
			((sistemHanoi*)(p -> info)) -> tijaC = Push( ((sistemHanoi*)(p -> info)) -> tijaC, disc);
		}
		if (strcmp(((infoCoada*)(mutare -> info)) -> mutare, "C->A") == 0)
		{
			disc = Pop(&(((sistemHanoi*)(p -> info)) -> tijaC));
			((sistemHanoi*)(p -> info)) -> tijaA = Push( ((sistemHanoi*)(p -> info)) -> tijaA, disc);
		}
		if (strcmp(((infoCoada*)(mutare -> info)) -> mutare, "C->B") == 0)
		{
			disc = Pop(&(((sistemHanoi*)(p -> info)) -> tijaC));
			((sistemHanoi*)(p -> info)) -> tijaB = Push( ((sistemHanoi*)(p -> info)) -> tijaB, disc);
		}
		free(((infoCoada*)(mutare -> info)) -> mutare);
		free(mutare -> info);
		free(mutare);
	}
	if (sw == 1)
	{
		// AM RAMAS CU ULTIMUL DE ELIMINAT
		mutare = ((sistemHanoi*)(p -> info)) -> start;
		if (strcmp(((infoCoada*)(mutare -> info)) -> mutare, "A->B") == 0)
		{
			disc = Pop(&(((sistemHanoi*)(p -> info)) -> tijaA));
			((sistemHanoi*)(p -> info)) -> tijaB = Push( ((sistemHanoi*)(p -> info)) -> tijaB, disc);
		}
		if (strcmp(((infoCoada*)(mutare -> info)) -> mutare, "A->C") == 0)
		{
			disc = Pop(&(((sistemHanoi*)(p -> info)) -> tijaA));
			((sistemHanoi*)(p -> info)) -> tijaC = Push( ((sistemHanoi*)(p -> info)) -> tijaC, disc);
		}
		if (strcmp(((infoCoada*)(mutare -> info)) -> mutare, "B->A") == 0)
		{
			disc = Pop(&(((sistemHanoi*)(p -> info)) -> tijaB));
			((sistemHanoi*)(p -> info)) -> tijaA = Push( ((sistemHanoi*)(p -> info)) -> tijaA, disc);
		}
		if (strcmp(((infoCoada*)(mutare -> info)) -> mutare, "B->C") == 0)
		{
			disc = Pop(&(((sistemHanoi*)(p -> info)) -> tijaB));
			((sistemHanoi*)(p -> info)) -> tijaC = Push( ((sistemHanoi*)(p -> info)) -> tijaC, disc);
		}
		if (strcmp(((infoCoada*)(mutare -> info)) -> mutare, "C->A") == 0)
		{
			disc = Pop(&(((sistemHanoi*)(p -> info)) -> tijaC));
			((sistemHanoi*)(p -> info)) -> tijaA = Push( ((sistemHanoi*)(p -> info)) -> tijaA, disc);
		}
		if (strcmp(((infoCoada*)(mutare -> info)) -> mutare, "C->B") == 0)
		{
			disc = Pop(&(((sistemHanoi*)(p -> info)) -> tijaC));
			((sistemHanoi*)(p -> info)) -> tijaB = Push( ((sistemHanoi*)(p -> info)) -> tijaB, disc);
		}
		// fac mutarea
		free(((infoCoada*)(mutare -> info)) -> mutare);
		free(mutare -> info);
		free(mutare);
		((sistemHanoi*)(p -> info)) -> start = NULL;
		((sistemHanoi*)(p -> info)) -> end = NULL;
	}
	// 
}

 /*
 * Functie ce scoate din coada de miscari n miscari , le afiseaza in fisierul
 * de output, le pune intr-o coada auxiliara, dupa care reface coada initiala
 * cu ajutorul functiilor intrQ si extrQ definite mai sus
 */

int show_moves(TLista listasisteme, void *y, int nrMutari, FILE* fisier, TFCmp functie)
{
	char* culoare = (char*)y;
	TCoada startnou = NULL, endnou = NULL; // coada noua auxiliara
	TCoada mutare = NULL;
	TLista p = NULL;
	TCoada t = NULL;
	for(p = listasisteme; p != NULL; p = p -> urm)
	{
		if( functie(p, culoare ) == 0 )
		{
			break;
		}
	}
	if ( p == NULL)
	{
		printf("NU AM GASIT CULOARE CERUTA\n");	
	}
	fprintf(fisier, "M_%s:", culoare);
	int i;
	if( ((sistemHanoi*)(p -> info)) -> nrMutariRamase == 0)
	{
		fprintf(fisier,"\n");
		return 1;

	}
	if(((sistemHanoi*)(p -> info)) -> nrMutariRamase > nrMutari)
	{
		for(i = 0; i < nrMutari; i++)
		{
			mutare = (TCoada)extrQ( &(((sistemHanoi*)(p -> info)) -> start) , &(((sistemHanoi*)(p -> info)) -> end)); // extrag o mutare.
			fprintf(fisier, " %s", ((infoCoada*)(mutare -> info)) -> mutare); // scriu mutarea in fisier.
			intrQ(&startnou, &endnou, mutare); // pun mutarea in coada noua.
		}
		while(((sistemHanoi*)(p -> info)) -> start != ((sistemHanoi*)(p -> info)) -> end)
		{
			mutare = (TCoada)extrQ( &(((sistemHanoi*)(p -> info)) -> start) , &(((sistemHanoi*)(p -> info)) -> end)); // extrag o mutare.
			intrQ(&startnou, &endnou, mutare); // pun mutarea in coada noua.
		}
		fprintf(fisier, "\n");
		mutare = ((sistemHanoi*)(p -> info)) -> start; // extrag o mutare.
		intrQ(&startnou, &endnou, mutare); // pun mutarea in coada noua.
		((sistemHanoi*)(p -> info)) -> start = NULL;
		((sistemHanoi*)(p -> info)) -> end = NULL;

		while( startnou != endnou)
		{
			mutare = (TCoada)extrQ( &startnou , &endnou); // extrag o mutare.
			intrQ(&(((sistemHanoi*)(p -> info)) -> start) , &(((sistemHanoi*)(p -> info)) -> end), mutare); // pun mutarea in coada noua.
		}
		mutare = startnou; // extrag o mutare.
		intrQ(&(((sistemHanoi*)(p -> info)) -> start), &(((sistemHanoi*)(p -> info)) -> end), mutare); // pun mutarea in coada noua.
		startnou = NULL;
		endnou = NULL;
	}
	else
	{
		// arat toate mutarile din prima coada
		while( ((sistemHanoi*)(p -> info)) -> start != ((sistemHanoi*)(p -> info)) -> end)
		{
			mutare = (TCoada)extrQ( &(((sistemHanoi*)(p -> info)) -> start) , &(((sistemHanoi*)(p -> info)) -> end)); // extrag o mutare.
			fprintf(fisier, " %s", ((infoCoada*)(mutare -> info)) -> mutare); // scriu mutarea in fisier.
			intrQ(&startnou, &endnou, mutare); // pun mutarea in coada noua.
		}
		mutare = ((sistemHanoi*)(p -> info)) -> start; // extrag o mutare.
		fprintf(fisier, " %s", ((infoCoada*)(mutare -> info)) -> mutare); // scriu mutarea in fisier.
		intrQ(&startnou, &endnou, mutare); // pun mutarea in coada noua.
		fprintf(fisier, "\n");
		((sistemHanoi*)(p -> info)) -> start = NULL;
		((sistemHanoi*)(p -> info)) -> end = NULL;
		// scot mutarile din coada noua si le pun in coada initiala
		while( startnou != endnou)
		{
			mutare = (TCoada)extrQ( &startnou , &endnou); // extrag o mutare.
			intrQ(&(((sistemHanoi*)(p -> info)) -> start) , &(((sistemHanoi*)(p -> info)) -> end), mutare); // pun mutarea in coada noua.
		}
		mutare = startnou; // extrag o mutare.
		intrQ(&(((sistemHanoi*)(p -> info)) -> start), &(((sistemHanoi*)(p -> info)) -> end), mutare); // pun mutarea in coada noua.
		startnou = NULL;
		endnou = NULL;
		// am refacut coada initiala
	}
}

 /*
 * Functie ce citeste n linii din fisierul de intrare
 * si executa comenzile corespunzatoare
 * Functia parseaza comenzile.
 */

int EventimenteHanoi ( FILE *f1, FILE *f2)
{
	char *p, *buffer = NULL, *culoare = NULL, *diametru = NULL, *mutari = NULL;
	int nrDiametru = 0, nrMutari = 0;
	// alocare buffer pentru citire evenimente
	buffer  = (char *)calloc(100, sizeof(char));
	TLista listasisteme = NULL; // lista sitemelor hanoi
	TLista t = NULL;
	if(!buffer)
	{
		printf("Alocare esuata!\n");
		return -1;
	}
	int numarevenimente = 0, i;
	fscanf(f1, "%d\n", &numarevenimente);
	for (i = 0; i < numarevenimente; i++)
	{
		fgets(buffer, 100, f1);
		buffer[strlen(buffer) - 1] = '\0';
		p = strtok(buffer, " ");
		if (strcmp(p,"add")==0)
		{
			p = strtok(NULL, " ");
			culoare = strdup(p);
			p = strtok(NULL, " ");
			diametru = strdup(p);
			nrDiametru = strtol(diametru, NULL, 10);
			Disc* discnou = (Disc*)malloc(sizeof(Disc));
			discnou -> culoare = strdup(culoare);
			discnou -> diametru = nrDiametru;
			// am creat discul pe care trebuie sa-l introduc
			listasisteme = IntroduceDisc(listasisteme, discnou, comparareCuloare);
			free(culoare);
			free(diametru);
		}
		if (strcmp(p,"show")==0)
		{
			p = strtok(NULL, " ");
			culoare = strdup(p);
		//	printf("%s %s\n", "show", culoare);
			for( t = listasisteme ; t != NULL; t = t -> urm)
			{
				if (comparareCuloare(t, culoare ) == 0 )
				{
					break;
				}
			}
			functieShow(listasisteme, culoare, f2, comparareCuloare);
			free(culoare);
		}	
		if (strcmp(p,"play")==0)
		{
			p = strtok(NULL, " ");
			culoare = strdup(p);
			p = strtok(NULL, " ");
			mutari = strdup(p);
			nrMutari = strtol(mutari, NULL, 10);
			for (t = listasisteme ; t != NULL; t = t -> urm)
			{
				if (comparareCuloare(t, culoare ) == 0 )
				{
					break;
				}
			}
			if (((sistemHanoi*)(t -> info)) -> sw == 0 )
			{
				creeareCoada(listasisteme, culoare, comparareCuloare);
			}
			// execut miscarile
			play(listasisteme, culoare, nrMutari, comparareCuloare);
			free(culoare);
			free(mutari);
		}
		if (strcmp(p,"show_moves")==0)
		{
			p = strtok(NULL, " ");
			culoare = strdup(p);
			p = strtok(NULL, " ");
			mutari = strdup(p);
			nrMutari = strtol(mutari, NULL, 10);
			for (t = listasisteme ; t != NULL; t = t -> urm)
			{
				if (comparareCuloare(t, culoare ) == 0 )
				{
					break;
				}
			}
			if (((sistemHanoi*)(t -> info)) -> sw == 0 )
			{
				creeareCoada(listasisteme, culoare, comparareCuloare);
			}
			// arat mutarile
			show_moves(listasisteme, culoare, nrMutari, f2, comparareCuloare);
			free(culoare);
			free(mutari);
		}
		
	}
	EliberareLista(&listasisteme);
	free(buffer);
}
