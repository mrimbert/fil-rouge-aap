#include <stdio.h>
#include <stdlib.h>
#include "../utils/super_morpion.h"
#include "minimax.h"

int main(int argc, char *argv[]) {
    // Récupérer la variable d'environnement SMPATH, si elle est définie
    char *smPath = getenv("SMPATH");

    int horizon;
    int dernierePositionAdversaire = -1;  // Au début, le joueur peut jouer n'importe où
    int traitOrdi = CROIX;  // L'ordinateur joue avec les croix

    // Vérification de la validité des arguments d'entrée
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <horizon>\n", argv[0]);
        return 1;
    }

    // Convertir le deuxième argument en entier pour définir l'horizon de recherche
    horizon = atoi(argv[1]);
    if (horizon <= 0) {
        fprintf(stderr, "L'horizon doit être un nombre positif\n");
        return 1;
    }

    // Initialisation du super morpion
    super_morpion sm = newSuperMorpion();

    // Boucle principale du jeu, continue tant que le jeu n'est pas terminé
    while(!isWinSuperMorpion(&sm) && !isOverSuperMorpion(&sm)) {
        if(sm.trait == ROND){
            // Si c'est au joueur humain de jouer
            int pos = convertMove();  // Demander et obtenir la position du coup du joueur humain
            playSuperMorpion(&sm, pos);  // Jouer le coup dans le super morpion
            dernierePositionAdversaire = pos;  // Mise à jour de la dernière position jouée
            generateSuperMorpionImage(sm);  // Générer l'image du super morpion (si implémenté)
            showSuperMorpion(&sm);  // Afficher l'état actuel du super morpion
        } else {
            // Si c'est au tour de l'ordinateur de jouer
            childNode meilleurCoup = getBestMove(&sm, horizon, traitOrdi, dernierePositionAdversaire);  // Calculer le meilleur coup
            playSuperMorpion(&sm, meilleurCoup.dernierePosition);  // Jouer le meilleur coup trouvé
            dernierePositionAdversaire = meilleurCoup.dernierePosition;  // Mise à jour de la dernière position jouée
            generateSuperMorpionImage(sm);  // Générer l'image du super morpion
            showSuperMorpion(&sm);  // Afficher l'état actuel du super morpion
        }
    }

    // Annoncer le résultat du jeu
    if (isWinSuperMorpion(&sm)) {
        // Annoncer le vainqueur
        if (sm.trait == ROND) {
            printf("Le joueur ROND a gagné!\n");
        } else {
            printf("L'ordinateur a gagné!\n");
        }
    } else {
        // Annoncer une égalité si le jeu se termine sans gagnant
        printf("La partie se termine par une égalité.\n");
    }

    return 0;
}
