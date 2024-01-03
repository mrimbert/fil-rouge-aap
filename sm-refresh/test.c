#include "../utils/super_morpion.h"
#include "minimax.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void test_playInCompletedOrWonMorpion();
void setupWinningNode(super_morpion *node);

// Prototypes de vos fonctions de test
void test_minimax();
void test_nodeChildren();
void test_isTerminal();
void test_evaluate();
void test_obtenirMeilleurCoup();
void test_playInCompletedOrWonMorpion();

int main() {
    printf("Début des tests...\n");
    //test_minimax();
    //test_nodeChildren();
    //test_isTerminal();
    //test_evaluate();
    test_obtenirMeilleurCoup();
    //test_playInCompletedOrWonMorpion();
    printf("Tous les tests sont terminés !\n");
    return 0;
}

void test_minimax() {
    // Créer un état de jeu spécifique pour le test
    super_morpion node = newSuperMorpion();
    printf("Le super morpion a été créé\n");

    // Configurez un scénario de jeu où l'ordinateur peut prendre une décision avantageuse
    node.g[0][0] = ROND;  // Supposons que ROND est l'ordinateur
    node.g[0][1] = ROND;
    node.g[0][2] = -1;    // Case vide où l'ordinateur peut gagner
    node.trait = ROND;    // C'est au tour de l'ordinateur de jouer
    int dernierePosition = 2;  // Supposons que la dernière position jouée est 2

    // Définir une profondeur de recherche
    int depth = 3;  // Profondeur suffisante pour que Minimax trouve le coup gagnant

    // Définir le trait de l'ordinateur
    int traitOrdi = ROND;  // Supposons que ROND est l'ordinateur

    // Convertir super_morpion en childNode
    childNode testNode;
    testNode.sm = node;  // Copiez l'état du jeu
    testNode.dernierePosition = dernierePosition;  // Définissez la dernière position

    // Appeler Minimax avec la structure childNode, la profondeur, et le trait de l'ordinateur
    int bestValue = minimax(testNode, depth, traitOrdi);


    // Définir le résultat attendu pour ce scénario de test
    int expectedValue = 3;  // Vous devrez déterminer cette valeur en fonction de votre fonction d'évaluation et de l'état du jeu

    // Vérifier si le résultat de Minimax est celui attendu
    if (bestValue == expectedValue) {
        printf("Test minimax: PASSED\n");
    } else {
        printf("Test minimax: FAILED\n");
        printf("Expected %d, but got %d\n", expectedValue, bestValue);
    }
}


/*
void setupWinningNode(super_morpion *node) {
    // Réinitialiser le jeu
    *node = newSuperMorpion();

    // Configurer manuellement trois grilles gagnantes pour ROND
    // Première grille (en haut à gauche)
    node->g[0][0] = ROND;
    node->g[0][1] = ROND;
    node->g[0][2] = ROND;

    // Deuxième grille (en haut au milieu)
    node->g[1][0] = ROND;
    node->g[1][1] = ROND;
    node->g[1][2] = ROND;

    // Troisième grille (en haut à droite)
    node->g[2][0] = ROND;
    node->g[2][1] = ROND;
    node->g[2][2] = ROND;

    // Définissez le trait au joueur opposé pour simuler un jeu après un coup gagnant
    node->trait = CROIX;
}


void setupFilledNode(super_morpion *node) {
    *node = newSuperMorpion();

    // Remplir toutes les cases de manière à ce qu'aucun joueur n'ait gagné
    // et alterner les symboles pour éviter un alignement gagnant
    for (int grid = 0; grid < 9; grid++) {
        for (int position = 0; position < 9; position++) {
            node->g[grid][position] = (position % 2 == 0) ? ROND : CROIX;
        }
    }

    // Assurez-vous que ROND a 5 marqueurs ou plus en les plaçant manuellement
    node->g[1][0] = ROND;
    node->g[1][2] = ROND;
    node->g[2][0] = ROND;
    node->g[2][2] = ROND;
    node->g[2][4] = ROND;  // Ajout d'un cinquième marqueur ROND
}

void setupOngoingNode(super_morpion *node) {
    *node = newSuperMorpion();

    // Configurer un jeu en cours avec quelques cases remplies
    node->g[0][0] = ROND;
    node->g[0][1] = CROIX;
    // Laisser des cases vides pour simuler un jeu en cours
}


/*void test_isTerminal() {
    int tests_passed = 0;
    int total_tests = 3;
    super_morpion node;

    // Test 1: Scénario gagnant
    setupWinningNode(&node);
    if (isTerminal(&node) == 1) {
        printf("Test isTerminal (winning scenario): PASSED\n");
        tests_passed++;
    } else {
        printf("Test isTerminal (winning scenario): FAILED\n");
    }

    // Test 2: Scénario rempli mais non gagnant
    setupFilledNode(&node);
    if (isTerminal(&node) == 1) {
        printf("Test isTerminal (filled scenario): PASSED\n");
        tests_passed++;
    } else {
        printf("Test isTerminal (filled scenario): FAILED\n");
    }

    // Test 3: Scénario où le jeu est terminé sans gagnant mais avec assez de marqueurs pour l'ordinateur
    setupFilledNode(&node); // Configurez un état rempli sans alignement gagnant
    int result = evaluate(&node, ROND);
    if (result == 1) {
        printf("Test evaluate (tie with enough markers for ROND): PASSED\n");
        tests_passed++;
    } else {
        printf("Test evaluate (tie with enough markers for ROND): FAILED\n");
    }

    // Résumé des tests
    if (tests_passed == total_tests) {
        printf("All tests for isTerminal passed!\n");
    } else {
        printf("Some tests for isTerminal failed: %d out of %d passed.\n", tests_passed, total_tests);
    }
}*/


/*void test_evaluate() {
    int tests_passed = 0;
    int total_tests = 5;
    super_morpion node;
    int result;

    // Test 1: Scénario où le jeu est gagné par le joueur (ROND)
    setupWinningNode(&node); // Configurez un état gagnant pour ROND
    result = evaluate(&node, ROND);
    if (result == 1) {
        printf("Test evaluate (player wins as ROND): PASSED\n");
        tests_passed++;
    } else {
        printf("Test evaluate (player wins as ROND): FAILED\n");
    }

    // Test 2: Scénario où le jeu est gagné par l'adversaire (CROIX)
    setupWinningNode(&node); // Configurez un état gagnant pour CROIX
    result = evaluate(&node, CROIX);
    if (result == -1) {
        printf("Test evaluate (opponent wins as CROIX): PASSED\n");
        tests_passed++;
    } else {
        printf("Test evaluate (opponent wins as CROIX): FAILED\n");
    }

    // Test 3: Scénario où le jeu est terminé sans gagnant mais avec assez de marqueurs pour l'ordinateur
    setupFilledNode(&node); // Configurez un état rempli sans alignement gagnant
    // Assurez-vous que ROND a 5 marqueurs ou plus
    node.g[1][0] = ROND;
    node.g[1][2] = ROND;
    node.g[2][0] = ROND;
    node.g[2][2] = ROND;
    result = evaluate(&node, ROND);
    if (result == 1) {
        printf("Test evaluate (tie with enough markers for ROND): PASSED\n");
        tests_passed++;
    } else {
        printf("Test evaluate (tie with enough markers for ROND): FAILED\n");
    }

    // Test 4: Scénario où le jeu est terminé sans gagnant et avec moins de marqueurs pour l'ordinateur
    setupFilledNode(&node); // Configurez un état rempli sans alignement gagnant
    // Assurez-vous que ROND a moins de 5 marqueurs
    node.g[1][0] = CROIX;
    node.g[1][2] = CROIX;
    node.g[2][0] = CROIX;
    node.g[2][2] = CROIX;
    result = evaluate(&node, ROND);
    if (result == -1) {
        printf("Test evaluate (tie with not enough markers for ROND): PASSED\n");
        tests_passed++;
    } else {
        printf("Test evaluate (tie with not enough markers for ROND): FAILED\n");
    }

    // Test 5: Scénario neutre où le jeu n'est pas encore terminé
    setupOngoingNode(&node); // Configurez un état de jeu en cours
    result = evaluate(&node, ROND);
    if (result == 0) {
        printf("Test evaluate (neutral ongoing game): PASSED\n");
        tests_passed++;
    } else {
        printf("Test evaluate (neutral ongoing game): FAILED\n");
    }

    // Résumé des tests
    if (tests_passed == total_tests) {
        printf("All tests for evaluate passed!\n");
    } else {
        printf("Some tests for evaluate failed: %d out of %d passed.\n", tests_passed, total_tests);
    }
}*/

/*void test_nodeChildren() {
    // Créer un état de jeu spécifique pour le test
    super_morpion node = newSuperMorpion();
    
    node.g[4][0] = ROND;
    node.g[4][1] = ROND;
    node.g[4][2] = ROND;
    node.g[0][0] = ROND;  // Premier coup joué par ROND
    node.g[0][4] = CROIX;  // Premier coup joué par CROIX
    node.trait = ROND;     // C'est au tour de ROND de jouer
    dernierePositionAdversaire = 4;  // Le dernier coup joué par CROIX était dans la grille 

    int childrenCount;
    super_morpion *children = nodeChildren(&node, &childrenCount);

    // Définir le nombre attendu d'enfants pour ce scénario spécifique
    // Par exemple, si vous savez qu'il y a 8 coups valides possibles
    int expectedChildrenCount = 9;

    for(int i = 0; i != childrenCount; i++){
        generateSuperMorpionImage(children[i]);
    }

    // Vérifier si le nombre d'enfants générés est égal au nombre attendu
    if (childrenCount == expectedChildrenCount) {
        printf("Test nodeChildren: PASSED\n");
    } else {
        printf("Test nodeChildren: FAILED\n");
        printf("Expected %d children, but got %d children\n", expectedChildrenCount, childrenCount);
    }

    // Libérer la mémoire allouée pour les enfants
    free(children);
}

*/
void test_obtenirMeilleurCoup() {
    // Créer un état de jeu spécifique pour le test
    super_morpion node = newSuperMorpion();

    // Configurer un scénario de jeu où l'ordinateur peut prendre une décision avantageuse
    node.g[0][0] = ROND;  // Première case du premier morpion
    node.g[0][1] = ROND;  // Deuxième case du premier morpion
    node.g[0][2] = -1;    // Case vide où l'ordinateur peut gagner
    node.trait = ROND;    // C'est au tour de l'ordinateur de jouer
    int dernierePositionAdversaire = 4;  // Supposons que la dernière position jouée est 4

    int depth = 3;  // Profondeur suffisante pour que Minimax trouve le meilleur coup
    int traitOrdi = ROND;  // Supposons que ROND est l'ordinateur

    // Appeler obtenirMeilleurCoup avec l'état de jeu spécifique, la profondeur et la dernière position
    childNode meilleurCoup = obtenirMeilleurCoup(&node, depth, traitOrdi, dernierePositionAdversaire);

    // Définir l'index de la position attendue pour le meilleur coup
    int expectedBestMoveIndex = 2;  // Supposons que la position gagnante soit à l'index 2 pour cet état

    // Vérifier si le meilleur coup renvoyé correspond au meilleur coup attendu
    if (meilleurCoup.sm.g[0][expectedBestMoveIndex] == traitOrdi) {
        printf("Test obtenirMeilleurCoup: PASSED\n");
    } else {
        printf("Test obtenirMeilleurCoup: FAILED\n");
        printf("Expected best move at position %d, but got different position\n", expectedBestMoveIndex);
    }
}




/*
void test_playInCompletedOrWonMorpion() {
    super_morpion node = newSuperMorpion();
    // Configurez un scénario où un morpion spécifique est complet ou gagné
    // Par exemple, remplissez complètement le morpion 4
    for (int i = 0; i < 9; i++) {
        node.g[4][i] = i % 2 == 0 ? ROND : CROIX;
    }

    dernierePositionAdversaire = 4; // Le joueur est envoyé au morpion 4

    // Simulez un coup joué dans un autre morpion valide
    playSuperMorpion(&node, 11);  // Essayez de jouer dans le morpion 1, position 1

    // Vérifiez que le coup a été joué avec succès
    if (node.g[1][1] == ROND) {
        printf("Test playInCompletedOrWonMorpion: PASSED\n");
    } else {
        printf("Test playInCompletedOrWonMorpion: FAILED\n");
    }
}*/