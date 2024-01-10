#include "../utils/super_morpion.h"
#include "minimax.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

// Définition des fonctions max et min
#define max(a, b) ((a) > (b) ? (a) : (b))
#define min(a, b) ((a) < (b) ? (a) : (b))

#define INFINITY 10000  // Valeur arbitraire représentant l'infini
#define NEG_INFINITY -10000  // Valeur arbitraire représentant moins l'infini

childNode getBestMove(super_morpion *node, int depth, int traitOrdi, int dernierePosition) {
   if(getenv("DEBUG") != NULL) printf("Recherche du meilleur coup pour la position %d\n", dernierePosition);
    
    int meilleurScore = (traitOrdi == node->trait) ? NEG_INFINITY : INFINITY;
    childNode meilleurCoup;
    memset(&meilleurCoup, 0, sizeof(meilleurCoup)); // Initialisation du meilleurCoup

    int childrenCount;
    childNode *children = nodeChildren(node, dernierePosition, &childrenCount); // Générer les enfants du noeud actuel

    if (children == NULL) {
        fprintf(stderr, "Erreur pour 'children' dans getBestMove.\n");
        meilleurCoup.sm = *node;  // Retourner l'état actuel en cas d'erreur
        return meilleurCoup;
    }

    for (int i = 0; i < childrenCount; i++) {
    // Calculer le score actuel en utilisant la fonction minimax
        int currentScore = minimax(children[i], depth - 1, traitOrdi);
    
        // Vérifier si le score actuel est meilleur que le meilleur score actuel
        if ((traitOrdi == node->trait && currentScore > meilleurScore) ||
            (traitOrdi != node->trait && currentScore < meilleurScore)) {
            // Mettre à jour le meilleur score et le meilleur coup si nécessaire
            meilleurScore = currentScore;
            meilleurCoup = children[i];
        }
    }

    // Libérer la mémoire allouée pour les enfants
    free(children);

    if(getenv("DEBUG") != NULL) printf("Meilleur coup trouvé: position=%d\n", meilleurCoup.dernierePosition);
    showSuperMorpion(&meilleurCoup.sm);
    return meilleurCoup;
}



int minimax(childNode node, int depth, int traitOrdi) {

    if(getenv("DEBUG") != NULL) printf("Entrée dans minimax: depth=%d, traitOrdi=%d\n", depth, traitOrdi);
    
    // Vérifier si la profondeur maximale est atteinte ou si la position est terminale
    if (depth == 0 || isTerminal(&node.sm)) {
        return evaluation_partie(node.sm, node.dernierePosition);
    }

    int value;
    int childrenCount;
    childNode *children = nodeChildren(&node.sm, node.dernierePosition, &childrenCount); // Générer les enfants du nœud actuel
    
    // Vérifier si la génération des enfants a échoué
    if (children == NULL) {
        fprintf(stderr, "Erreur pour 'children' dans minimax.\n");
        return -1;
    }

    if (traitOrdi == node.sm.trait) { // Maximiseur
        value = NEG_INFINITY;
        for (int i = 0; i < childrenCount; i++) {
            // Appel récursif de minimax pour chaque enfant en passant la dernière position jouée
            int childScore = minimax(children[i], depth - 1, traitOrdi);
            value = max(value, childScore);
        }
    } else { // Minimiseur
        value = INFINITY;
        for (int i = 0; i < childrenCount; i++) {
            // Appel récursif de minimax pour chaque enfant en passant la dernière position jouée
            int childScore = minimax(children[i], depth - 1, traitOrdi);
            value = min(value, childScore);
        }
    }

    free(children); // Libérer la mémoire allouée pour les enfants
    
    if(getenv("DEBUG") != NULL) printf("Sortie de minimax: valeur=%d\n", value);
    return value; 
}



// Vérifie si une grille spécifique dans un super_morpion est gagnée ou complète
int isGridWonOrComplete(super_morpion *node, int grid) {
    int res = 0;
    morpion m = newMorpion();
    memcpy(m.g, node->g[grid], sizeof(m.g)); // Copier la grille spécifique dans le morpion
    m.trait = node->trait; // On teste la victoire pour les deux joueurs
    res += isWin(m);
    m.trait = 1 - node->trait;
    res += isWin(m);

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


