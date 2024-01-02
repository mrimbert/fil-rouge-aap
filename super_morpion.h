#include "morpion.h"
typedef struct{
	grille g[9];
	int trait;
} super_morpion;

typedef struct {
    int meilleureEval; // Meilleure évaluation
    int meilleureGrille; // Meilleure grille à jouer
} EvalResult;

super_morpion newSuperMorpion(); //Fonction qui initialise un super morpion
//super_morpion toSuperMorpion(char * play); //Fonction qui prend en argument une chaîne FEN représentant un super morpion et renvoie l'état du super morpion correspondant
//void printSuperMorpion(super_morpion sm); //Fonction qui affiche dans la console un super morpion
void generateSuperMorpionImage(super_morpion sm); //Fonction qui affiche graphiquement une position de super morpion
void playSuperMorpion(super_morpion * sm, int pos); //Fonction qui permet de jouer un coup de super morpion à la position pos
int isWinSuperMorpion(super_morpion * sm); //Fonction qui permet de détecter si une grille de super-morpion est gagnée
int evaluation_grille(morpion m);
int evaluation_partie(super_morpion sm, int position);
EvalResult negaMax(super_morpion position, int grilleAJouer, int profondeur, int alpha, int beta, int joueur);
int includesZero(morpion M);
