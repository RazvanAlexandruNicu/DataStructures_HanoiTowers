#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
typedef struct celulalista
{
	void *info;
	struct celulalista *urm;
} TCelula, *TLista, **ALista;

typedef struct celula
{
	void *info;
	struct celula *urm;
} TDisc, *TStiva, **AStiva;
// Nicu Razvan-Alexandru 313 CB
typedef struct celulaC
{
	void *info;
	struct celulaC *urm;
} TCDisc, *TCoada, **ACoada;

typedef struct
{
	int diametru;
	char *culoare;
} Disc;

typedef struct
{
	char *mutare;
} infoCoada;

typedef struct
{
	TStiva tijaA, tijaB, tijaC;
	TCoada start, end;
	char *culoare;
	int nrMutariRamase;
	int sw;
} sistemHanoi;

typedef int (*TFCmp)(void*, void*);

// antete de functii
int comparareCuloare(void* x, void* y);

TStiva AlocareCelulaa(void *x);
void creeareCoada(TLista lista, void *y, TFCmp functie);

int dimS ( void *x);
int VidaS( TStiva x);

TStiva Push( TStiva x, void *elem);
void* Pop( AStiva x);
void intrQ( ACoada start, ACoada end, void *y);
void* extrQ( ACoada start, ACoada end);

TStiva introduceInTija( TStiva tija, void *y);
TLista introduceDisc( TLista listasisteme, void *y, TFCmp functie);
void play( TLista listasisteme, void* y, int nrMutari, TFCmp functie);
void functieShow( TLista listasisteme, void *y, FILE* out, TFCmp functie);
int hanoi (int n, char* a, char* b, char* c, ACoada start, ACoada end);
int show_moves(TLista listasisteme, void *y, int nrMutari, FILE* fisier, TFCmp functie);

void EliberareStiva(AStiva stiva);
void EliberareLista( ALista listasisteme);
void EliberareCoada( ACoada start, ACoada end);

int EventimenteHanoi ( FILE *f1, FILE *f2);
