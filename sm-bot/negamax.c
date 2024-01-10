
#include "negamax.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

// Définir les fonctions max et min
#define max(a, b) ((a) > (b) ? (a) : (b))
#define min(a, b) ((a) < (b) ? (a) : (b))

#define INFINITY 10000  // Valeur arbitraire représentant l'infini
#define NEG_INFINITY -10000  // Valeur arbitraire représentant moins l'infini

childNode getBestMove(super_morpion *node, int depth, int traitOrdi, int dernierePosition) {
   if(getenv("DEBUG") != NULL) printf("Recherche du meilleur coup pour la position %d\n", dernierePosition);
    
    int meilleurScore = (traitOrdi == node->trait) ? NEG_INFINITY : INFINITY;
    childNode meilleurCoup; // Déclarer une variable pour stocker le meilleur coup
    memset(&meilleurCoup, 0, sizeof(meilleurCoup)); // Initialiser meilleurCoup

    int childrenCount;
    childNode *children = nodeChildren(node, dernierePosition, &childrenCount); // Générer les enfants du noeud actuel

    if (children == NULL) {
        fprintf(stderr, "Erreur pour 'children' dans getBestMove.\n");
        meilleurCoup.sm = *node;  // Retourner l'état actuel en cas d'erreur
        return meilleurCoup;
    }

    for (int i = 0; i < childrenCount; i++) {
        int currentScore = negamax(children[i], depth - 1, NEG_INFINITY, INFINITY, traitOrdi);
        if ((traitOrdi == node->trait && currentScore > meilleurScore) ||
            (traitOrdi != node->trait && currentScore < meilleurScore)) {
            meilleurScore = currentScore;
            meilleurCoup = children[i];
        }
    }

    free(children);
    if(getenv("DEBUG") != NULL) printf("Meilleur coup trouvé: position=%d\n", meilleurCoup.dernierePosition);
    return meilleurCoup;
}



int negamax(childNode node, int depth, int alpha, int beta, int traitOrdi) {
    if (getenv("DEBUG") != NULL) {
        printf("Entrée dans negamax: depth=%d, traitOrdi=%d\n", depth, traitOrdi);
    }

    if (depth == 0 || isTerminal(&node.sm)) {
        return (traitOrdi == node.sm.trait) ? 
               evaluation_partie(node.sm, node.dernierePosition) : 
               -evaluation_partie(node.sm, node.dernierePosition);
    }

    int value = NEG_INFINITY;
    int childrenCount;
    childNode *children = nodeChildren(&node.sm, node.dernierePosition, &childrenCount);

    if (children == NULL) {
        fprintf(stderr, "Erreur pour 'children' dans negamax.\n");
        return -1;
    }

    for (int i = 0; i < childrenCount; i++) {
        int childScore = -negamax(children[i], depth - 1,-alpha,-beta, traitOrdi);
        value = max(value, childScore);
        if (value >= beta) return value;
        alpha = max(alpha,value);
      
    }

    free(children); // Libérer la mémoire allouée pour les enfants

    if (getenv("DEBUG") != NULL) {
        printf("Sortie de negamax: valeur=%d\n", value);
    }

    return value;
}





// Vérifie si une grille spécifique dans un super_morpion est gagnée ou complète
int isGridWonOrComplete(super_morpion *node, int grid) {
    int res = 0;
    morpion m = newMorpion(); // Créez une instance de morpion
    memcpy(m.g, node->g[grid], sizeof(m.g)); // Copiez la grille spécifique dans le morpion
    m.trait = node->trait; // On teste la victoire pour les deux joueurs
    res += isWin(m);
    m.trait = 1 - node->trait;
    res += isWin(m);
    //printf("Grille %d est gagnée: %d, est complète: %d\n", grid, res, isOver(m));

    return res || isOver(m); // Vérifiez si la grille est gagnée ou complète
}


childNode * nodeChildren(super_morpion *node, int dernierePosition, int *childrenCount){
    int tempCount = 0;  // Variable temporaire pour compter le nombre d'enfants valides
    int grid = -1;  // Initialiser la grille à -1

    // Si dernierePosition n'est pas -1, calculer la grille correspondante
    if (dernierePosition != -1) {
        grid = dernierePosition % 9;
    }

    // Le joueur peut jouer n'importe où si aucun coup n'a été joué ou si la grille ciblée est déjà gagnée ou complète
    int canPlayAnywhere = (dernierePosition == -1 || isGridWonOrComplete(node, grid));

    // Compter les coups valides
    for (int i = 0; i < 81; i++) {
        int currentGrid = i / 9;
        // Vérifiez si la case est vide, que la grille n'est ni gagnée ni complète, et si la grille est correcte ou si le joueur peut jouer n'importe où
        if (node->g[currentGrid][i % 9] == -1 &&
            (!isGridWonOrComplete(node, currentGrid)) &&
            (canPlayAnywhere || currentGrid == grid)) {
            tempCount++;
        }
    }

    childNode *list = malloc(tempCount * sizeof(childNode));
    if (list == NULL) {
        fprintf(stderr, "Erreur d'allocation mémoire pour 'list' dans nodeChildren.\n");
        *childrenCount = 0;
        return NULL;
    }

    if(getenv("DEBUG") != NULL) printf("Génération des enfants pour nodeChildren. Nombre d'enfants attendus: %d\n", tempCount);
    
    
    // Générez et stockez les enfants valides
    int index = 0;
    for (int i = 0; i < 81; i++) {
        int currentGrid = i / 9;
        int posInGrid = i % 9;
        // Vérifiez si la case est vide, que la grille n'est ni gagnée ni complète, et si la grille est correcte ou si le joueur peut jouer n'importe où
        if (node->g[currentGrid][posInGrid] == -1 &&
            (!isGridWonOrComplete(node, currentGrid)) &&
            (canPlayAnywhere || currentGrid == grid)) {
            childNode newChild;
            newChild.sm = *node;
            newChild.sm.g[currentGrid][posInGrid] = node->trait;
            newChild.sm.trait = 1 - node->trait;
            newChild.dernierePosition = i;  // Stockez la position actuelle
            list[index++] = newChild;
        }
    }

    if(getenv("DEBUG") != NULL) printf("Nombre d'enfants générés: %d\n", index);

    *childrenCount = index;
    return list;
}



// Fonction pour vérifier si un état de jeu est terminal pour l'un ou l'autre des joueurs.
int isTerminal(super_morpion *node) {
    int currentPlayerWin = isWinSuperMorpion(node);

    // Temporairement changer le trait pour vérifier si l'adversaire a gagné.
    node->trait = 1 - node->trait;  // Change le trait pour l'autre joueur.
    int otherPlayerWin = isWinSuperMorpion(node);
    node->trait = 1 - node->trait;  // Restaure le trait original.

    if (currentPlayerWin || otherPlayerWin) {
        // Si l'un des joueurs a gagné, le jeu est terminé.
        return 1;  // Retourne 1 si le jeu est gagné par l'un ou l'autre joueur.
    } else if (isOverSuperMorpion(node)) {
        // Vérifier s'il n'y a plus de coups valides et que le jeu est donc terminé.
        return 1;  // Retourne 1 si le jeu est terminé sans gagnant, donc terminal.
    } else {
        // Dans tous les autres cas, le jeu n'est pas encore terminé.
        return 0;  // Retourne 0 si le jeu n'est pas terminal.
    }
}

int convCoup(int coup){
  int grille = coup/9+1;
  int pos = coup%9+1;
  
  return grille*10+pos;
  
}

int invConvCoup(const int coup){
	int grille = (coup/10)-1;
	int pos = (coup%10)-1;
	return grille*9+pos;
}
