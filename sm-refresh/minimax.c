#include "../utils/super_morpion.h"
#include "minimax.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

// Définir les fonctions max et min
#define max(a, b) ((a) > (b) ? (a) : (b))
#define min(a, b) ((a) < (b) ? (a) : (b))

#define INFINITY 10000  // Valeur arbitraire représentant l'infini
#define NEG_INFINITY -10000  // Valeur arbitraire représentant moins l'infini


childNode obtenirMeilleurCoup(super_morpion *node, int depth, int traitOrdi, int dernierePosition) {
    int meilleurScore = (traitOrdi == node->trait) ? NEG_INFINITY : INFINITY;
    childNode meilleurCoup; // Déclarer une variable pour stocker le meilleur coup
    memset(&meilleurCoup, 0, sizeof(meilleurCoup)); // Initialiser meilleurCoup

    int childrenCount;
    childNode *children = nodeChildren(node, dernierePosition, &childrenCount); // Générer les enfants du noeud actuel

    if (children == NULL) {
        fprintf(stderr, "Erreur pour 'children' dans obtenirMeilleurCoup.\n");
        meilleurCoup.sm = *node;  // Retourner l'état actuel en cas d'erreur
        return meilleurCoup;
    }

    for (int i = 0; i < childrenCount; i++) {
        int currentScore = minimax(children[i], depth - 1, traitOrdi);
        if ((traitOrdi == node->trait && currentScore > meilleurScore) ||
            (traitOrdi != node->trait && currentScore < meilleurScore)) {
            meilleurScore = currentScore;
            meilleurCoup = children[i];
        }
    }

    // Après avoir sélectionné le meilleur coup, affichez le cadran où le prochain coup doit être joué
    int prochainCadran = meilleurCoup.dernierePosition % 9; // Calculer le cadran pour le prochain coup
    printf("Le prochain coup devra être joué dans le cadran %d.\n", prochainCadran); // Les cadrans sont généralement numérotés de 1 à 9

    free(children);
    return meilleurCoup;
}




int minimax(childNode node, int depth, int traitOrdi) {
    if (depth == 0 || isTerminal(&node.sm)) {
        return evaluation_partie(node.sm, node.dernierePosition);  // Utilisez la dernière position stockée dans node
    }

    int value;
    int childrenCount;
    childNode *children = nodeChildren(&node.sm, node.dernierePosition, &childrenCount); // Passez la dernière position à nodeChildren

    if (children == NULL) {
        fprintf(stderr, "Erreur pour 'children' dans minimax.\n");
        return -1;
    }

    if (traitOrdi == node.sm.trait) { // Maximiseur
        value = NEG_INFINITY;
        for (int i = 0; i < childrenCount; i++) {
            // Passez la dernière position jouée de l'enfant aux appels récursifs
            int childScore = minimax(children[i], depth - 1, traitOrdi);
            value = max(value, childScore);
        }
    } else { // Minimiseur
        value = INFINITY;
        for (int i = 0; i < childrenCount; i++) {
            // Passez la dernière position jouée de l'enfant aux appels récursifs
            int childScore = minimax(children[i], depth - 1, traitOrdi);
            value = min(value, childScore);
        }
    }

    free(children); // Libérer la mémoire allouée pour les enfants
    return value; // Retourner la valeur calculée
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


/*int evaluate(super_morpion *node, int traitOrdi) {
    // Vérifier si le jeu est gagné par l'ordinateur
    if (isWinSuperMorpion(node) && node->trait != traitOrdi) { //le trait passe automatiquement au joueur adverse
        return 1; // Retourner +1 pour une victoire de l'ordinateur
    }
    // Vérifier si le jeu est gagné par l'adversaire
    else if (isWinSuperMorpion(node) && node->trait == traitOrdi) {
        return -1; // Retourner -1 pour une défaite de l'ordinateur
    }
    // Vérifier si le jeu est terminé mais sans alignement (vérifier le nombre de marqueurs)
    else if (isOverSuperMorpion(node)) {
        int count = 0; // Compter le nombre de marqueurs de l'ordinateur
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                if (node->g[i][j] == traitOrdi) {
                    count++;
                }
            }
        }

        if (count >= 5) {
            return 1; // Retourner +1 si l'ordinateur a 5 marqueurs ou plus
        } else {
            return -1; // Retourner -1 si l'ordinateur a moins de 5 marqueurs
        }
    }

    return 0; // Retourner 0 en cas d'égalité
}*/
