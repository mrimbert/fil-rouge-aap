#include "../utils/super_morpion.h"
#include "minimax.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Prototypes de vos fonctions de test
void test_minimax();
void test_nodeChildren();
void test_isTerminal();
void test_obtenirMeilleurCoup();

int main() {
    printf("Début des tests...\n");
    test_minimax();
    test_nodeChildren();
    test_isTerminal();
    test_obtenirMeilleurCoup();
    printf("Tous les tests sont terminés !\n");
    return 0;
}

void test_minimax() {
    printf("Début du test minimax\n");
    // Créer un état de jeu spécifique pour le test
    super_morpion node = newSuperMorpion();

    // Configurer un scénario de jeu où l'ordinateur peut prendre une décision avantageuse
    node.g[0][0] = ROND;  // Supposons que ROND est l'ordinateur
    node.g[0][1] = ROND;
    node.g[0][2] = -1;    // Case vide où l'ordinateur peut gagner
    node.trait = ROND;    // C'est au tour de l'ordinateur de jouer
    int dernierePosition = 0;  // Supposons que la dernière position jouée est 2

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

    printf("La meilleure valeur est : %d\n",bestValue);
}



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


void test_isTerminal() {
    printf("Début du test de isTerminal");
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

    // Test 3: Scénario de jeu en cours
    setupOngoingNode(&node);
    if (isTerminal(&node) == 0) {  // Dans un jeu en cours, isTerminal doit retourner 0
        printf("Test isTerminal (ongoing scenario): PASSED\n");
        tests_passed++;
    } else {
        printf("Test isTerminal (ongoing scenario): FAILED\n");
    }    

    // Résumé des tests
    if (tests_passed == total_tests) {
        printf("Tous les tests de isTerminal ont fonctionné\n");
    } else {
        printf("Certains des tests de isTerminal n'ont pas fonctionné : %d sur %d ont réussi.\n", tests_passed, total_tests);
    }
}


void test_nodeChildren() {
    printf("Début du test de nodeChildren\n");
    int tests_passed = 0;
    int total_tests = 3;

    // Test 1: Jeu n'a pas commencé (dernierePosition = -1)
    {
        super_morpion node = newSuperMorpion();
        node.trait = CROIX; // C'est au tour de CROIX de jouer
        int dernierePositionAdversaire = -1; // Aucun coup joué précédemment

        int childrenCount;
        childNode *children = nodeChildren(&node, dernierePositionAdversaire, &childrenCount);

        // Dans ce scénario, tous les coups sont possibles
        int expectedChildrenCount = 81 - 0; // Ajuster en fonction de la configuration du jeu

        if (childrenCount == expectedChildrenCount) {
            printf("Test nodeChildren (jeu n'a pas commencé): PASSED\n");
            tests_passed++;
        } else {
            printf("Test nodeChildren (jeu n'a pas commencé): FAILED\n");
            printf("On attendait %d children, mais on a eu %d children\n", expectedChildrenCount, childrenCount);
        }

        free(children);
    }

    // Test 2: Jouer dans une grille spécifique
    {
        super_morpion node = newSuperMorpion();
        node.g[4][0] = ROND;  // Supposons que la grille 5 a déjà quelques coups joués
        node.trait = CROIX;   // C'est au tour de CROIX de jouer
        int dernierePositionAdversaire = 40;  // Le dernier coup joué par ROND était dans la grille 5

        int childrenCount;
        childNode *children = nodeChildren(&node, dernierePositionAdversaire, &childrenCount);

        // Ici, nous nous attendons à ce que tous les coups valides dans la grille 5 soient comptés
        int expectedChildrenCount = 9 - 1; // Ajuster en fonction de la configuration du jeu

        if (childrenCount == expectedChildrenCount) {
            printf("Test nodeChildren (jouer dans une grille spécifique): PASSED\n");
            tests_passed++;
        } else {
            printf("Test nodeChildren (jouer dans une grille spécifique): FAILED\n");
            printf("On attendait %d children, mais on a eu %d children\n", expectedChildrenCount, childrenCount);
        }

        free(children);
    }

    // Test 3: Grille déjà gagnée
    {
        super_morpion node = newSuperMorpion();
        
        // Configurer une grille comme déjà gagnée
        node.g[3][0] = node.g[3][1] = node.g[3][2] = CROIX;
        node.trait = ROND;   // C'est au tour de ROND de jouer
        int dernierePositionAdversaire = 30;  // Le dernier coup joué par CROIX était dans la grille 4

        int childrenCount;
        childNode *children = nodeChildren(&node, dernierePositionAdversaire, &childrenCount);

        // Dans ce cas, le joueur ne peut pas jouer dans la grille 4
        int expectedChildrenCount = 81 - 9; // Ajuster en fonction de la configuration du jeu

        if (childrenCount == expectedChildrenCount) {
            printf("Test nodeChildren (grille déjà gagnée): PASSED\n");
            tests_passed++;
        } else {
            printf("Test nodeChildren (grille déjà gagnée): FAILED\n");
            printf("On attendait %d children, mais on a eu %d children\n", expectedChildrenCount, childrenCount);
        }

        free(children);
    }

    // Résumé des tests
    if (tests_passed == total_tests) {
        printf("Tous les tests ont fonctionné\n");
    } else {
        printf("Certains tests n'ont pas fonctionné : %d sur %d ont réussi.\n", tests_passed, total_tests);
    }
}


void test_obtenirMeilleurCoup() {
    printf("Début du test de obtenirMeilleurCoup");
    // Créer un état de jeu spécifique pour le test
    super_morpion node = newSuperMorpion();

    // Configurer un scénario de jeu où l'ordinateur peut prendre une décision avantageuse
    node.g[0][0] = ROND;  // Supposons que ROND est l'ordinateur
    node.g[0][1] = ROND;    // Case vide où l'ordinateur peut gagner
    node.trait = ROND;    // C'est au tour de l'ordinateur de jouer
    int dernierePositionAdversaire = 0;  // Supposons que la dernière position jouée est 4

    // Définir une profondeur de recherche
    int depth = 3;  // Profondeur suffisante pour que Minimax trouve le meilleur coup

    // Définir le trait de l'ordinateur
    int traitOrdi = ROND;  // Supposons que ROND est l'ordinateur

    // Appeler obtenirMeilleurCoup avec l'état de jeu spécifique, la profondeur et la dernière position
    childNode meilleurCoup = obtenirMeilleurCoup(&node, depth, traitOrdi, dernierePositionAdversaire);

    // Afficher le super morpion après le meilleur coup trouvé
    printf("Meilleur coup trouvé :\n");
    showSuperMorpion(&meilleurCoup.sm);

    // Définir l'index de la position attendue pour le meilleur coup
    int expectedBestMoveIndex = 2;  // Ajustez en fonction de la logique de votre jeu

    // Vérifier si le meilleur coup renvoyé correspond au meilleur coup attendu
    if (meilleurCoup.sm.g[0][expectedBestMoveIndex] == traitOrdi) {
        printf("Test obtenirMeilleurCoup: PASSED\n");
    } else {
        printf("Test obtenirMeilleurCoup: FAILED\n");
        printf("Expected best move at position %d, but got different position\n", expectedBestMoveIndex);
    }
}


