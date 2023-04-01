#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "solution.h"
#include "liste.h"

//Pour liste des actions
static int equal (Objet * objet1, Objet * objet2){
  Action obj1 = (Action) objet1;
  Action obj2 = (Action) objet2;
  return ((*obj1 == *obj2) && (*(obj1 + 1) == *(obj2 + 1))) ? vrai : faux;
}

static char * toString (Objet * objet){
  char *s = (char *) malloc (20 * sizeof (char));
  Action obj = (Action) objet;
  sprintf (s, "[%d, %d]", *obj, *(obj + 1));
  return s;
}

static char * matrice_toString (Etat e){
    //27 caractères car pour un taquin de 3x3 on a 9 caractères + [ + ] + (, + espace) * 8  
  char *str_etat = (char *) malloc (27*sizeof (char)); strcpy(str_etat, "");
  char int_str[2];

  strcat (str_etat, "[");
  for (int i = 0; i < LIGNES; i++)
    {
      for (int j = 0; j < COLONNES; j++)
	{
	  sprintf (int_str, "%d", e[i * LIGNES + j]);
	  strcat (str_etat, int_str);
	  if (i != LIGNES - 1 || j != COLONNES - 1) strcat (str_etat, ", ");
	}
    }
  strcat (str_etat, "]");
  return str_etat;
}

//Pour la frontière
static char* afficher(Objet* objet){
    Noeud* noeud = (Noeud*) objet;
	char* str_etat = matrice_toString(noeud->etat);
	char* s = (char*) malloc(50*sizeof(char));
	
    sprintf(s, "(%s , %d)", str_etat, noeud->cout_de_chemin);
    return s;
}

static int comparer(Objet* objet1, Objet* objet2){
    Noeud* noeud1 = (Noeud*) objet1;
    Noeud* noeud2 = (Noeud*) objet2;
    int result = noeud1->cout_de_chemin - noeud2->cout_de_chemin;
	return (result == 0) ? result : (int) (result / abs(result));
}

static void matriceEtat(Etat e){
  printf("\n--------------\n");
  for (int i = 0; i < LIGNES; i++){
    for (int j = 0; j < COLONNES; j++){
	  printf ("%4d ", e[i * LIGNES + j]);
	}
	printf("\n");
  }
}

static char* afficher_solution(Noeud* solution) {
    char* path = (char*) malloc(1000*sizeof(char)); strcpy(path, "");
    char* tmp  = (char*) malloc(1000*sizeof(char));
    
    Noeud* noeud = solution;
    if (noeud == NULL) strcat(path,"Aucun solution trouvee!");
    else{
        while (noeud != NULL) {
            strcpy(tmp,path);
            strcpy(path, matrice_toString(noeud->etat));
            
            matriceEtat(noeud->etat);
            
            strcat(path, " -> ");
            strcat(path, tmp);
            
            noeud = noeud->parent;
        }
    }
    free(tmp);
    free(noeud);
    return path;
}



Liste* ACTIONS(Probleme* probleme, Etat s) {
	
	Liste* li = creerListe(0, toString, equal);
	Action a = (Action) malloc(2 * sizeof(int));
	int i_empty, j_empty;
	
	for(int i=0; i < LIGNES; i++){
		for(int j=0; j < COLONNES; j++){
			if (s[i*LIGNES + j] == EMPTY_CASE){
				i_empty = i; j_empty = j;
				break;
			}
		}
	}
	
	if(i_empty == 0){
		if(j_empty == 0){
			// (0,1)
			*(a) = i_empty; *(a+1) = j_empty + 1;
			insererEnFinDeListe(li, (Objet*) a);
			
			//(1,0)
			a = (Action) malloc(sizeof(Action));
			*(a) = i_empty + 1; *(a+1) = j_empty;
			insererEnFinDeListe(li, (Objet*) a);
			
			return li;
		}
		else if (0 < j_empty && j_empty < COLONNES - 1) {
			// (0,0)
			*(a) = i_empty; *(a+1) = j_empty - 1;
			insererEnFinDeListe(li, (Objet*) a);
			
			//(1,1)
			a = (Action) malloc(sizeof(Action));
			*(a) = i_empty + 1; *(a+1) = j_empty;
			insererEnFinDeListe(li, (Objet*) a);
			
			//(0,2)
			a = (Action) malloc(sizeof(Action));
			*(a) = i_empty; *(a+1) = j_empty + 1;
			insererEnFinDeListe(li, (Objet*) a);
			
			return li;
		}
		else if (j_empty == COLONNES - 1) {
			// (0,1)
			*(a) = i_empty; *(a+1) = j_empty - 1;
			insererEnFinDeListe(li, (Objet*) a);
			
			//(1,2)
			a = (Action) malloc(sizeof(Action));
			*(a) = i_empty + 1; *(a+1) = j_empty;
			insererEnFinDeListe(li, (Objet*) a);
			
			return li;
		}
	}
	else if(0 < i_empty && i_empty < LIGNES - 1) {
		if(j_empty == 0){
			// (0,0)
			*(a) = i_empty - 1; *(a+1) = j_empty;
			insererEnFinDeListe(li, (Objet*) a);
			
			//(1,1)
			a = (Action) malloc(sizeof(Action));
			*(a) = i_empty; *(a+1) = j_empty + 1;
			insererEnFinDeListe(li, (Objet*) a);
			
			//(2,1)
			a = (Action) malloc(sizeof(Action));
			*(a) = i_empty + 1; *(a+1) = j_empty;
			insererEnFinDeListe(li, (Objet*) a);
			
			return li;
		}
		else if (0 < j_empty && j_empty < COLONNES - 1) {
			// (1,0)
			*(a) = i_empty; *(a+1) = j_empty - 1;
			insererEnFinDeListe(li, (Objet*) a);
			
			//(0,1)
			a = (Action) malloc(sizeof(Action));
			*(a) = i_empty - 1; *(a+1) = j_empty;
			insererEnFinDeListe(li, (Objet*) a);
			
			//(1,2)
			a = (Action) malloc(sizeof(Action));
			*(a) = i_empty; *(a+1) = j_empty + 1;
			insererEnFinDeListe(li, (Objet*) a);
			
			//(2,1)
			a = (Action) malloc(sizeof(Action));
			*(a) = i_empty + 1; *(a+1) = j_empty;
			insererEnFinDeListe(li, (Objet*) a);
			
			return li;
		}
		else if (j_empty == COLONNES - 1) {
			// (1,1)
			*(a) = i_empty; *(a+1) = j_empty - 1;
			insererEnFinDeListe(li, a);
			
			//(0,2)
			a = (Action) malloc(sizeof(Action));
			*(a) = i_empty - 1; *(a+1) = j_empty;
			insererEnFinDeListe(li, (Objet*) a);
			
			//(2,2)
			a = (Action) malloc(sizeof(Action));
			*(a) = i_empty + 1; *(a+1) = j_empty;
			insererEnFinDeListe(li, (Objet*) a);
			
			return li;
		}
	}
	else if(i_empty == LIGNES - 1){
		if(j_empty == 0){
			// (1,0)
			*(a) = i_empty - 1; *(a+1) = j_empty;
			insererEnFinDeListe(li, (Objet*) a);
			
			//(2,1)
			a = (Action) malloc(sizeof(Action));
			*(a) = i_empty; *(a+1) = j_empty + 1;
			insererEnFinDeListe(li, (Objet*) a);
			
			return li;
		}
		else if (0 < j_empty && j_empty < COLONNES - 1) {
			// (2,0)
			*(a) = i_empty; *(a+1) = j_empty - 1;
			insererEnFinDeListe(li, (Objet*) a);
			
			//(1,1)
			a = (Action) malloc(sizeof(Action));
			*(a) = i_empty - 1; *(a+1) = j_empty;
			insererEnFinDeListe(li, (Objet*) a);
			
			//(2,2)
			a = (Action) malloc(sizeof(Action));
			*(a) = i_empty; *(a+1) = j_empty + 1;
			insererEnFinDeListe(li, (Objet*) a);
			
			return li;
		}
		else if (j_empty == COLONNES - 1) {
			// (2,1)
			*(a) = i_empty; *(a+1) = j_empty - 1;
			insererEnFinDeListe(li, (Objet*) a);
			
			//(1,2)
			a = (Action) malloc(sizeof(Action));
			*(a) = i_empty - 1; *(a+1) = j_empty;
			insererEnFinDeListe(li, (Objet*) a);
			
			return li;
		}
	}
	
	return li;
}

Etat RESULTAT(Probleme* probleme, Etat s, Action a){
	Etat new_etat = (Etat) malloc(9*sizeof(Etat));
	int i_empty, j_empty;
	
	for(int i=0; i < LIGNES; i++){
		for(int j=0; j < COLONNES; j++){
			if(s[i*LIGNES + j] == EMPTY_CASE){
				i_empty = i;
				j_empty = j;
			}
			new_etat[i*LIGNES + j] = s[i*LIGNES + j];
		}
	}
	
	
	new_etat[i_empty*LIGNES + j_empty] = s[a[0]*LIGNES + a[1]];
	new_etat[a[0]*LIGNES + a[1]] = EMPTY_CASE;
	
	return new_etat;
}

booleen TEST_DE_BUT(Probleme* probleme, Etat s) {
	booleen v = vrai;
	
	for(int i=0; i < LIGNES; i++){
		for(int j=0; j < COLONNES; j++){
			if(s[i*LIGNES + j] != probleme->etat_but[i*LIGNES + j]){
				v = faux;
			}
		}
	}
	
	return v;
	
}

int COUT_DE_CHEMIN(Probleme* probleme, Etat s0, Action a, Etat s1){
	return 1;
}

int heuristique(Probleme* probleme, Etat e){
	int count = 0;
	
	for(int i=0; i < LIGNES; i++){
		for(int j=0; j < COLONNES; j++){
			if((probleme->etat_but[i*LIGNES + j] != e[i*LIGNES + j]) && e[i*LIGNES + j] != EMPTY_CASE) {
				count++;
			}
		}
	}
	
	return count;
}

Noeud*  creer_noeud(Etat e, Noeud* parent, Action a, int cout_de_chemin){
	Noeud* n = (Noeud*) malloc(sizeof(Noeud));
	
	n->etat           = e;
	n->parent         = parent;
	n->a              = a;
	n->cout_de_chemin = cout_de_chemin;
	
	return n;
}

Noeud* NOEUD_FILS(Probleme* probleme, Noeud* parent, Action a) {
	
	Etat new_etat = RESULTAT(probleme, parent->etat, a);
	return creer_noeud(RESULTAT(probleme, parent->etat, a), 
	                   parent, 
					   a, 
					  (parent->cout_de_chemin - heuristique(probleme, parent->etat) + COUT_DE_CHEMIN(probleme, parent->etat, a, new_etat)) + heuristique(probleme, new_etat));
}

void AEtoile   (Probleme* probleme){
  Liste* actions = creerListe(0, toString, equal);
  Noeud* fils = (Noeud*) malloc(sizeof(Noeud));
  
  Noeud* noeud_initial = creer_noeud(probleme->etat_initial, NULL, NULL, 0);
  
  Liste* frontiere = creerListe(1, afficher, comparer); 
  insererEnOrdre (frontiere, noeud_initial);
  
  Noeud* noeud = (Noeud*) malloc(sizeof(Noeud));
  
  int i=0, j;
  while(vrai){
        j=0;
		//Tester si la frontière est vide
		if(frontiere->nbElt == 0){
			printf("\nPas de solution !!!!!\n");
			free(actions);
			free(fils);
			free(noeud_initial);
			free(frontiere);
			free(noeud);
			break;
		}
		
		//Choisit le noeud de la frontière avec le cout le plus faible
		noeud = (Noeud*) extraireEnTeteDeListe(frontiere);
		
		//Tester si l'état du noeud choisit correspond à l'état de but
		if (TEST_DE_BUT(probleme,noeud->etat)){
			printf("\n Solution trouvé\n");
			printf("\nLe chemin du solution est : \n");
			printf("%s\n", afficher_solution(noeud));
			free(actions);
			free(fils);
			free(noeud_initial);
			free(frontiere);
			free(noeud);
			break;
		}
		
		actions = ACTIONS(probleme, noeud->etat);
		while(actions->nbElt > 0){
		    printf("\n---------------------------\n");
			fils = NOEUD_FILS(probleme, noeud, (Action) extraireEnTeteDeListe(actions));
			insererEnOrdre(frontiere, fils);
			printf("fils(%d,%d) => %s",i+1,j+1,afficher(fils));
			printf("\n---------------------------\n");
			j++;
		}
		i++;
  }
	
}

Contour* creer_Contour(Noeud* noeud, int next_f){
	Contour* res = (Contour*) malloc(sizeof(Contour));
	
	res->noeud = noeud; res->next_f = next_f;
	
	return res;
}


static Contour* EPL_CONTOUR(Probleme* probleme, Noeud* noeud, int f_limite){
	Liste* actions = creerListe(0, NULL, NULL);
    Noeud* fils = (Noeud*) malloc(sizeof(Noeud));
    
    
	int next_f = INFINI;
	if(noeud->cout_de_chemin > f_limite) return creer_Contour(NULL, noeud->cout_de_chemin);
	else if (TEST_DE_BUT(probleme, noeud->etat)) return creer_Contour(noeud, f_limite);
	
	actions = ACTIONS(probleme, noeud->etat);
	
	Contour* res = creer_Contour(NULL, NULL);
	
	while(actions->nbElt > 0){
		fils = NOEUD_FILS(probleme, noeud, (Action) extraireEnTeteDeListe(actions));
		res = EPL_CONTOUR(probleme, fils, f_limite);
		
		if (res->noeud != NULL) return creer_Contour(res->noeud, f_limite);
		
		next_f = (next_f > res->next_f) ? res->next_f : next_f;
	}
	
	return creer_Contour(NULL, next_f);
}


void   IDAEtoile (Probleme* probleme){
	Noeud* racine = creer_noeud(probleme->etat_initial, NULL, NULL, 0);
	int f_limite = racine->cout_de_chemin;
	
	Contour* res = creer_Contour(NULL, NULL);
	while(vrai){
		res = EPL_CONTOUR(probleme, racine, f_limite);
		if (res->noeud != NULL){
			printf("\n Solution trouvé\n");
			printf("\nLe chemin du solution est : \n");
			printf("%s\n", afficher_solution(res->noeud));
			break;
		}
		else if (f_limite == INFINI) {
			printf("\nPas de solution !!!!!\n");
			break;
		}
	}
}


