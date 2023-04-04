#include "liste.h"
#include <limits.h>

#ifndef SOLUTION
#define SOLUTION

typedef int* Etat;
typedef int* Action;
typedef int  booleen;

#define faux 0
#define vrai 1
#define INFINI INT_MAX

#define EMPTY_CASE 0
#define LIGNES 3
#define COLONNES 3

typedef struct probleme {
	Etat etat_initial;
	Etat etat_but;
} Probleme;

typedef struct noeud {
	Etat etat;
	struct noeud* parent;
	Action a;
	int cout_de_chemin;
} Noeud;

typedef struct contour {
	struct noeud* noeud;
	int next_f;
} Contour;

Liste*  ACTIONS(Probleme* probleme, Etat s);
Etat    RESULTAT(Probleme* probleme, Etat s, Action a);
booleen TEST_DE_BUT(probleme* probleme, Etat s);
int     COUT_DE_CHEMIN(Probleme* probleme, Etat s0,Action a, Etat s1);


Noeud*  creer_noeud(Etat e, Noeud* parent, Action a, int cout_de_chemin);
Noeud*  NOEUD_FILS(Probleme* probleme, Noeud* parent, Action a);
int     heuristique(Probleme* probleme, Etat e);

void     AEtoile   (Probleme* probleme);

Contour* creer_Contour(Noeud* noeud, int next_f); 
void     IDAEtoile (Probleme* probleme);


Etat     creer_etat();
Etat     creer_etat(char* str);
#endif
