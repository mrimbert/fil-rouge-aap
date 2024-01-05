#include <stdio.h>
#include <stdlib.h>
#include "../utils/super_morpion.h"
#include "minimax.h"

int main(int argc, char *argv[]) {
    int horizon;
    int dernierePositionAdversaire = -1;  // Supposons qu'au début le joueur peut jouer n'importe où
    int traitOrdi = CROIX;  // Supposons que l'ordinateur joue avec les croix

    // Vérification des arguments d'entrée
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <horizon>\n", argv[0]);
        return 1;
    }

    // Vérification et affectation de l'horizon
    horizon = atoi(argv[1]);
    if (horizon <= 0) {
        fprintf(stderr, "L'horizon doit être un nombre positif\n");
        return 1;
    }

    // Initialisation du jeu
    super_morpion sm = newSuperMorpion();

    while(!isWinSuperMorpion(&sm) && !isOverSuperMorpion(&sm)) {  // Continuez tant que le jeu n'est pas gagné et pas terminé
        if(sm.trait == ROND){
            int pos = convertMove();  // Obtenez la position du coup du joueur humain
            printf("la position est : %d\n", pos);
            playSuperMorpion(&sm, pos);  // Jouez le coup
            dernierePositionAdversaire = pos;  // Mettre à jour la dernière position pour l'adversaire
            generateSuperMorpionImage(sm);  // Générer l'image
            showSuperMorpion(&sm);
        } else {
            childNode meilleurCoup = obtenirMeilleurCoup(&sm, horizon, traitOrdi, dernierePositionAdversaire);  // Calculer le meilleur coup pour l'ordinateur
            playSuperMorpion(&sm, meilleurCoup.dernierePosition);
           // sm = meilleurCoup.sm;  // Mettre à jour l'état du jeu avec le meilleur coup
            dernierePositionAdversaire = meilleurCoup.dernierePosition;  // Mettre à jour la dernière position en fonction du coup de l'ordinateur
            generateSuperMorpionImage(sm);  // Générer l'image
            showSuperMorpion(&sm);
        }
    }

    // Annoncer le résultat du jeu
    if (isWinSuperMorpion(&sm)) {
        if (sm.trait == ROND) {
            printf("Le joueur ROND a gagné!\n");
        } else {
            printf("L'ordinateur a gagné!\n");
        }
    } else {
        printf("La partie se termine par une égalité.\n");
    }

    return 0;
}

