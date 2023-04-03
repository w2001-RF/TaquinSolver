#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "solution.h"
#include "liste.h"

//Pour liste des actions
static int equal (Objet * objet1, Objet * objet2){
  if(objet1 == NULL || objet2 == NULL){ return faux;}
  Action obj1 = (Action) objet1;
  Action obj2 = (Action) objet2;
  return ((*obj1 == *obj2) && (*(obj1 + 1) == *(obj2 + 1))) ? vrai : faux;
}

static char * toString (Objet * objet){
  char *s = (char *) malloc (20 * sizeof (char));
  if(objet == NULL) { strcpy(s,""); return s;}
  Action obj = (Action) objet;
  sprintf (s, "[%d, %d]", *obj, *(obj + 1));
  return s;
}

static char * matrice_toString (Etat e){
  //27 caractères car pour un taquin de 3x3 on a 9 caractères + [ + ] + (, + espace) * 8  
  char *str_etat = (char *) malloc (27*sizeof (char)); strcpy(str_etat, "");
  if(e == NULL) { strcpy(str_etat,""); return str_etat;}
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

//Pour la liste des états
static char * etat_toString (Objet* objet){
  Etat e = (Etat) e;
  //27 caractères car pour un taquin de 3x3 on a 9 caractères + [ + ] + (, + espace) * 8  
  char *str_etat = (char *) malloc (27*sizeof (char)); strcpy(str_etat, "");
  if(e == NULL) { strcpy(str_etat,""); return str_etat;}
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

static int comparer_etat(Objet* objet1, Objet* objet2){
  if(objet1 == NULL || objet2 == NULL) { return 0;}
  
  Etat e1 = (Etat) objet1;
  Etat e2 = (Etat) objet2;
  
  for (int i = 0; i < LIGNES; i++){
    for (int j = 0; j < COLONNES; j++){
	  if (e1[i*LIGNES + j] != e2[i*LIGNES + j]) return 0;
	}
  }
  return 1;
}

//Pour la frontière
static char* afficher(Objet* objet){
    char* s = (char*) malloc(50*sizeof(char));
    if(objet == NULL) { strcpy(s,""); return s;}
    Noeud* noeud = (Noeud*) objet;
	char* str_etat = matrice_toString(noeud->etat);
	
    sprintf(s, "(%s , %d)", str_etat, noeud->cout_de_chemin);
    return s;
}

static int comparer(Objet* objet1, Objet* objet2){
    if(objet1 == NULL || objet2 == NULL) { return -1;}
    Noeud* noeud1 = (Noeud*) objet1;
    Noeud* noeud2 = (Noeud*) objet2;
    int result = noeud1->cout_de_chemin - noeud2->cout_de_chemin;
	return (result == 0) ? result : (int) (result / abs(result));
}

static void matriceEtat(Etat e){
  printf("\n--------------\n");
  if(e == NULL) { printf("NULL Taquin\n"); return ;}
  for (int i = 0; i < LIGNES; i++){
    for (int j = 0; j < COLONNES; j++){
	  printf ("%4d ", e[i * LIGNES + j]);
	}
	printf("\n");
  }
}


/*static char* afficher_solution(Noeud* solution) {
    char* path = (char*) malloc(1000*sizeof(char)); strcpy(path, "");
    char* tmp  = (char*) malloc(1000*sizeof(char));
    Noeud* noeud = (Noeud*) malloc(sizeof(Noeud));
    
    noeud = solution;
    if (noeud == NULL) strcat(path,"Aucun solution trouvee!");
    else{
        while (noeud != NULL) {
        	matriceEtat(noeud->etat);
        	 
            strcpy(tmp,path);
            strcpy(path, matrice_toString(noeud->etat));
            
            strcat(path, " -> ");
            strcat(path, tmp);
            
            noeud = noeud->parent;
        }
    }
    free(tmp);
    free(noeud);
    return path;
}*/

static char* afficher_solution(Noeud* solution) {
    char* path = (char*) malloc(10*sizeof(char)); strcpy(path, "");
    char* tmp  = (char*) malloc(10*sizeof(char));
    Noeud* noeud = solution;
    
    if (noeud == NULL) strcat(path,"Aucune solution trouvée!");
    else{
        while (noeud != NULL) {
            //matriceEtat(noeud->etat);
            
            strcpy(tmp,path);
            strcpy(path, matrice_toString(noeud->etat));
            
            strcat(path, " -> ");
            strcat(path, tmp);
            
            //printf("\npath = %s\n",path);
            //printf("\ncurrent = 0x%0x , parent = 0x%0x",noeud, noeud->parent);
            noeud = noeud->parent;
            
        }
    }
    free(noeud);
    free(tmp);
    return path;
}

Liste* ACTIONS(Probleme* probleme, Etat s) {
    if (probleme == NULL || s == NULL) return NULL;

    Liste* li = creerListe(0, toString, equal);
    int i_empty, j_empty;

    // Find empty case
    for (int i = 0; i < LIGNES; i++) {
        for (int j = 0; j < COLONNES; j++) {
            if (s[i * LIGNES + j] == EMPTY_CASE) {
                i_empty = i;
                j_empty = j;
                goto found;
            }
        }
    }

found:
    // Define possible moves as row and column offsets
    int moves[][2] = {
        {-1, 0}, {1, 0}, {0, -1}, {0, 1},
    };

    // Check each possible move
    for (int i = 0; i < 4; i++) {
        int new_i = i_empty + moves[i][0];
        int new_j = j_empty + moves[i][1];

        // If the move is within the bounds of the grid, create an action and add it to the list
        if (new_i >= 0 && new_i < LIGNES && new_j >= 0 && new_j < COLONNES) {
            Action a = (Action)malloc(2 * sizeof(int));
            *(a) = new_i;
            *(a + 1) = new_j;
            insererEnFinDeListe(li, (Objet*)a);
        }
    }

    return li;
}

Etat RESULTAT(Probleme* probleme, Etat s, Action a){
	if((probleme == NULL || s == NULL) || a == NULL) return NULL;
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
    if(probleme == NULL || s == NULL) return faux;
	for(int i=0; i < LIGNES; i++){
		for(int j=0; j < COLONNES; j++){
			if(s[i*LIGNES + j] != probleme->etat_but[i*LIGNES + j]){
				return faux;
			}
		}
	}
	return vrai;
}

int COUT_DE_CHEMIN(Probleme* probleme, Etat s0, Action a, Etat s1){
    if(((probleme == NULL || s0 == NULL) || a == NULL) || s1 == NULL) return INFINI;
	return 1;
}

int heuristique(Probleme* probleme, Etat e){
    if(probleme == NULL || e == NULL) return INFINI;
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

Noeud* creer_noeud(Etat e, Noeud* parent, Action a, int cout_de_chemin){
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

void AEtoile(Probleme* probleme) {
    Liste* actions = NULL;
    Noeud* fils = NULL;
    
    Noeud* noeud_initial = creer_noeud(probleme->etat_initial, NULL, NULL, heuristique(probleme, probleme->etat_initial));
    Liste* frontiere = creerListe(1, afficher, comparer);
    insererEnOrdre(frontiere, noeud_initial);
    
	Liste* explore = creerListe(0, etat_toString, comparer_etat);
	
    Noeud* noeud = NULL;
    int i = 0, j = 0;
    bool goal_found = false;
    while (!goal_found && frontiere->nbElt > 0) {
    	//Choisit le noeud de la frontière avec le cout le plus faible
        noeud = (Noeud*) extraireEnTeteDeListe(frontiere);
        
        //Tester si l'état du noeud choisit correspond à l'état de but
        goal_found = TEST_DE_BUT(probleme, noeud->etat);
        
        if (goal_found) {
            printf("\n Solution trouvé\n");
            printf("\nLe chemin du solution est : \n");
            printf("%s\n", afficher_solution(noeud));
        } else {
        	//Ajouter l'etat de la noeud actual à l'ensemble des états explorés
            insererEnFinDeListe(explore, (Objet*) noeud->etat);
            
            actions = ACTIONS(probleme, noeud->etat);
            j=0;
            while (actions->nbElt > 0) {
            	printf("\n---------------------------\n");
                fils = NOEUD_FILS(probleme, noeud, (Action) extraireEnTeteDeListe(actions));
                
                //Ajouter le fils de la noeud actual à la frontière
                insererEnOrdre(frontiere, fils);
                printf("fils(%d,%d) => %s", i+1, j+1, afficher(fils));
                printf("\n---------------------------\n");
                j++;
            }
        }
        i++;
    }
    
    //Tester si la frontière est vide et aucun noeud exploré correspond à la solution
    if (!goal_found) {
        printf("\nPas de solution !!!!!\n");
    }
    detruireListe(explore);
    detruireListe(frontiere);
    free(noeud_initial);
    free(fils);
    detruireListe(actions);
}

Contour* creer_Contour(Noeud* noeud, int next_f){
	Contour* res = (Contour*) malloc(sizeof(Contour));
	
	res->noeud = noeud; res->next_f = next_f;
	
	return res;
}


static Contour* EPL_CONTOUR(Probleme* probleme, Noeud* noeud, int f_limite){
	int next_f = INFINI;
	
	if(noeud->cout_de_chemin > f_limite) return creer_Contour(NULL, noeud->cout_de_chemin);
	else if (TEST_DE_BUT(probleme, noeud->etat)) return creer_Contour(noeud, f_limite);
	
	Liste*   actions = ACTIONS(probleme, noeud->etat);
	Noeud*   fils    = creer_noeud(NULL, NULL, NULL, 0);
	Contour* res     = creer_Contour(NULL, 0);
	
	while(actions->nbElt > 0){
		fils = NOEUD_FILS(probleme, noeud, (Action) extraireEnTeteDeListe(actions));
		res = EPL_CONTOUR(probleme, fils, f_limite);
		
		if (res->noeud != NULL) {
			detruireListe(actions);
			return creer_Contour(res->noeud, f_limite);
		}
		
		next_f = (next_f > res->next_f) ? res->next_f : next_f;
		free(fils); free(res);
	}
	detruireListe(actions);
	return creer_Contour(NULL, next_f);	
}

void IDAEtoile (Probleme* probleme){ 
	Noeud* racine = creer_noeud(probleme->etat_initial, NULL, NULL, heuristique (probleme,probleme->etat_initial));
	int f_limite = racine->cout_de_chemin;
	
	Contour* res = creer_Contour(NULL, 0);
	while(vrai){
		res = EPL_CONTOUR(probleme, racine, f_limite);
		f_limite = res->next_f;
		printf("\nres => ");
	    printf ("(noeud = %s, next_f = %d)\n", afficher(res->noeud), res->next_f);
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
	free(racine); free(res);
}


Etat creer_etat() {
	Etat a = (Etat) malloc(9 * sizeof(int));
	
    // reading input from user
    char input[18]; // 9 numbers + 8 spaces + 1 \n
    fgets(input, sizeof(input), stdin);
    
    // parsing input and storing values in array
    char *token = strtok(input, " ");
    int i = 0;
    while (token != NULL && i < 9){
        a[i]= atoi(token);
        i++;
        token = strtok(NULL, " ");
    }
    
    // handling invalid input
    if (i != 9) {
        printf("Erreur: Entrez exactement 9 nombres entiers separes par des espaces.\n");
        exit(1);
    }
    
	return a;
}


