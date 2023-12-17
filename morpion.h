#define CROIX 1
#define ROND 0

typedef int grille[9];

typedef struct {
	grille g;
	int trait;
} morpion;

typedef struct{
	grille g[9];
	int trait;
} super_morpion;

morpion newMorpion(); //Fonction qui initialise une grille de morpion
void printMorpion(morpion M); //Fonction qui affiche dans la console l'état du morpion
void playMorpion(morpion * M, int pos); //Fonction qui permet de jouer un coup de morpion à la position pos
int isWin(morpion M); //Fonction qui permet de déterminer si l'un des joueurs à gagner, renvoie 1 si le joueur CROIX gagne, 0 si personne ne gagne, -1 si le joueur ROND gagne
void generateMorpionImage(const morpion M); //Fonction qui permet de générer une image représentant une position de morpion

//void printSuperMorpion(super_morpion S);
