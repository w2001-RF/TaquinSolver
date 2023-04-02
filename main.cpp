#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "solution.h"

int main() {
	
	Probleme* probleme = (Probleme*) malloc(sizeof(probleme));
    Etat e = (Etat) malloc (9 * sizeof (int));
    int m[9] = {8,1,3,EMPTY_CASE,4,5,2,7,6};
    for (int i = 0; i < LIGNES; i++) for (int j = 0; j < COLONNES; j++) *(e + i * LIGNES + j) = m[i * LIGNES + j];
    
    probleme->etat_initial = e;
     
    Etat e1 = (Etat) malloc (9 * sizeof (int));
    int m1[9] = {1, 2, 3, 8, EMPTY_CASE, 4, 7, 6, 5};
    for (int i = 0; i < LIGNES; i++) for (int j = 0; j < COLONNES; j++) *(e1 + i * LIGNES + j) = m1[i * LIGNES + j];
    
    probleme->etat_but = e1;
    
    //Parcour A Etoile
    AEtoile(probleme);
    
    //Parcour IDE
    //IDAEtoile(probleme);
    
    return 0;
}
