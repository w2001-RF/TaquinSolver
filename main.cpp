#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "solution.h"
//#include "lireProbleme.h"

int Menu(){
	printf("\n**************************** Taquin solver ****************************\n");
	printf("0 - Fin de programme.\n");
	printf("1 - Creer probleme du Taquin a partir d'un fichier.\n");
	printf("2 - Creer probleme du Taquin.\n");
	printf("3 - Resoudre  du probleme par AEtoile.\n");
	printf("4 - Resoudre du probleme par IDAEtoile.\n");
	printf("5 - Detruire probleme.\n");
	
	printf("\n\nSaisir votre choix? ");
	int choix; scanf("%d", &choix); getchar(); printf("\n");
	return choix;
}
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
    
    free(e);free(e1);
    free(probleme);
  	
  	/*Probleme* probleme = NULL;
  	FILE* file;
    while(vrai) {
    	switch(Menu()){
    		case 0:
    			printf("\n\nFin du programme!!!!\n\n");
    			return 0;
    		case 1:
    			if(probleme == NULL) probleme = (Probleme*) malloc(sizeof(probleme));
				
				fflush(stdin);
				char[10] nomfile;
				printf("\nEntrer le nom du fichier : "); scanf("%s", nomfile);
				file = fopen(nomfile, "r");
				if(file == NULL) {
					printf("\nErreur: Impossible d'ouvrir le fichier\n");
					break;
				}
				probleme = lireProbleme (file);
				printf("\nProbleme taquin bien lisé\n");
				fclose(file);
				break;
    		case 2:
    			if(probleme == NULL) probleme = (Probleme*) malloc(sizeof(probleme));
				
				fflush(stdin);
				printf("\nEntrer l'etat initial du taquin : \n");
				printf("(les valeurs en un seul ligne separe par espace)\n");
				probleme->etat_initial = creer_etat();
				
				fflush(stdin);
				printf("\n---------------------------------------------------\n");
				printf("Entrer l'etat but du taquin : \n");
				printf("(les valeurs en un seul ligne separe par espace)\n");
				probleme->etat_but = creer_etat();
				break;
			case 3:
				printf("\nAEtoile: \n");
				AEtoile(probleme);
				break;
			case 4:
				printf("\nIDAEtoile: \n");
				IDAEtoile(probleme);
				break;
			case 5:
				free(probleme);
				printf("\nProbleme bien detruit : \n");
				break;
			default:
				printf("\nChoix invalide !!!!\n");
				break;
		}
		
		if (!faux) {
			fflush(stdin);
	      	printf ("\n\nTaper Return pour continuer  ");
	      	getchar();
	      	system("cls");
    	}
	}
    */
	return 0;
}
