#include "super_morpion.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
int cadranprev = -1;

super_morpion newSuperMorpion() {
  super_morpion sm = {{{-1, -1, -1, -1, -1, -1, -1, -1, -1},
                       {-1, -1, -1, -1, -1, -1, -1, -1, -1},
                       {-1, -1, -1, -1, -1, -1, -1, -1, -1},
                       {-1, -1, -1, -1, -1, -1, -1, -1, -1},
                       {-1, -1, -1, -1, -1, -1, -1, -1, -1},
                       {-1, -1, -1, -1, -1, -1, -1, -1, -1},
                       {-1, -1, -1, -1, -1, -1, -1, -1, -1},
                       {-1, -1, -1, -1, -1, -1, -1, -1, -1},
                       {-1, -1, -1, -1, -1, -1, -1, -1, -1}},
                      ROND};
  return sm;
}

int includesZero(morpion M) {
    for (int i = 0; i < 9; i++) {
        if (M.g[i] == -1) {  
            return 1; 
        }
    }
    return 0;
}

void playSuperMorpion(super_morpion *sm, int pos) {
  assert(pos <= 88 && pos >= 0);
  if (cadranprev == -1) {
  	if(pos>=10) cadranprev = (pos / 10); // Numéro du cadran
  	else cadranprev = 0;
  }
  int j = (pos % 10); // Position dans le cadran

  morpion grille = newMorpion();
  grille.trait = sm->trait;
  memcpy(grille.g, sm->g[cadranprev], 9);

  if (abs(isWin(grille)) == 1) {
    printf("La grille est déjà jouée, merci de jouer dans une autre grille !");
  }

  if (sm->g[cadranprev][j] == ROND ||
      sm->g[cadranprev][j] ==
          CROIX) { // On vérifie que la position n'a pas déjà été jouée
    printf("Position déjà jouée, merci de rejouer \n");
    return;
  }

  sm->g[cadranprev][j] = sm->trait;
  if (sm->trait == ROND) {
    sm->trait = CROIX;
  } else {
    sm->trait = ROND;
  }
  
  grille.trait = sm->trait;
  memcpy(grille.g, sm->g[cadranprev], 9);
  if (abs(isWin(grille)) == 1) {
    cadranprev = -1;
  } else {
    cadranprev = j;
  }
  printf("Le prochain coup devra être jouée dans le cadran %d \n", cadranprev);
}

void generateSuperMorpionImage(super_morpion sm) {
  int i;
  int j;
  char fileName[100], pngFileName[100], command[200];

  // Créer un nom de fichier unique pour le fichier DOT et le fichier PNG
  snprintf(fileName, sizeof(fileName),
           "./g.dot");
  snprintf(pngFileName, sizeof(pngFileName),
           "./g.png");

  FILE *file = fopen(fileName, "w");
  if (file == NULL) {
    printf("Erreur : Impossible d'ouvrir le fichier %s.\n", fileName);
    return;
  }

  // Écriture du contenu DOT représentant le morpion dans le fichier
  fprintf(file, "digraph {\n");
  fprintf(file, " a0 [shape=none label=<\n");
  fprintf(file, "<TABLE border=\"0\" cellspacing=\"10\" cellpadding=\"10\" "
                "style=\"rounded\" bgcolor=\"black\"> \n");
  fprintf(file, "<TR> \n");
  fprintf(file, "<TD bgcolor=\"black\"> \n");
  fprintf(file, "<TABLE border=\"0\" cellspacing=\"10\" cellpadding=\"10\" "
                "style=\"rounded\" bgcolor=\"white\"> \n");
  fprintf(file, "<TR> \n");
  for (i = 0; i < 9; i++) {
    for (j = 0; j < 9; j++) {
      if (sm.g[i][j] == ROND) {
        fprintf(file, "<TD bgcolor=\"white\">O</TD> \n");
      }
      if (sm.g[i][j] == CROIX) {
        fprintf(file, "<TD bgcolor=\"white\">X</TD> \n");
      }
      if (sm.g[i][j] == -1) {
        fprintf(file, "<TD bgcolor=\"white\">.</TD> \n");
      }
      if (j % 3 == 2) {
        fprintf(file, "</TR> \n");
        if (j != 8) {
          fprintf(file, "<TR> \n");
        }
      }
    }
    fprintf(file, "</TABLE> \n");
    fprintf(file, "</TD> \n");
    if (i % 3 == 2 && i != 8) {
      fprintf(file, "</TR> \n");
      fprintf(file, "<TR> \n");
    }
    if (i != 8) {
      fprintf(file, "<TD bgcolor=\"white\"> \n");
      fprintf(file, "<TABLE border=\"0\" cellspacing=\"10\" cellpadding=\"10\" "
                    "style=\"rounded\" bgcolor=\"white\"> \n");
      fprintf(file, "<TR> \n");
    }
  }
  fprintf(file, "</TR>");
  fprintf(file, "</TABLE>");
  fprintf(file, ">];");
  fprintf(file, "}\n");
  fclose(file);
  snprintf(command, sizeof(command),
           "dot %s -Tpng -o g.png",
           fileName);
  system(command);
}

int isWinSuperMorpion(super_morpion *sm) {
    morpion tempGrille;
  
    for (int i = 0; i < 3; i++) {
        memcpy(tempGrille.g, sm->g[i * 3], sizeof(tempGrille.g));
        tempGrille.trait = sm->trait;
        int win1 = isWin(tempGrille);

        memcpy(tempGrille.g, sm->g[i * 3 + 1], sizeof(tempGrille.g));
        int win2 = isWin(tempGrille);

        memcpy(tempGrille.g, sm->g[i * 3 + 2], sizeof(tempGrille.g));
        int win3 = isWin(tempGrille);

        if (abs(win1) == 1 && abs(win2) == 1 && abs(win3) == 1) {
            return sm->trait + 1;
        }
    }

    for (int i = 0; i < 3; i++) {
        memcpy(tempGrille.g, sm->g[i], sizeof(tempGrille.g));
        tempGrille.trait = sm->trait;
        int win1 = isWin(tempGrille);

        memcpy(tempGrille.g, sm->g[i + 3], sizeof(tempGrille.g));
        int win2 = isWin(tempGrille);

        memcpy(tempGrille.g, sm->g[i + 6], sizeof(tempGrille.g));
        int win3 = isWin(tempGrille);

        if (abs(win1) == 1 && abs(win2) == 1 && abs(win3) == 1) {
            return sm->trait + 1;
        }
    }

    memcpy(tempGrille.g, sm->g[0], sizeof(tempGrille.g));
    tempGrille.trait = sm->trait;
    int diagWin1 = isWin(tempGrille);

    memcpy(tempGrille.g, sm->g[4], sizeof(tempGrille.g));
    int diagWin2 = isWin(tempGrille);

    memcpy(tempGrille.g, sm->g[8], sizeof(tempGrille.g));
    int diagWin3 = isWin(tempGrille);

    if (abs(diagWin1) == 1 && abs(diagWin2) == 1 && abs(diagWin3) == 1) {
        return sm->trait + 1;
    }

    memcpy(tempGrille.g, sm->g[2], sizeof(tempGrille.g));
    int diagWin4 = isWin(tempGrille);

    memcpy(tempGrille.g, sm->g[4], sizeof(tempGrille.g));  // Déjà copié, mais pour la clarté
    int diagWin5 = isWin(tempGrille);

    memcpy(tempGrille.g, sm->g[6], sizeof(tempGrille.g));
    int diagWin6 = isWin(tempGrille);

    if (abs(diagWin4) == 1 && abs(diagWin5) == 1 && abs(diagWin6) == 1) {
        return sm->trait + 1;
    }
    return 0;
}

int evaluation_grille(morpion m) {
 int evaluation = 0;
    float points[] = {0.3, 0.2, 0.3, 0.2, 0.4, 0.2, 0.3, 0.2, 0.3};
    for(int i = 0; i < 9; i++) {
        if(m.g[i] == -1) {
        evaluation = evaluation + 0;
        if(m.g[i] == ROND) {
        evaluation = evaluation -  points[i];
        }
        if(m.g[i] == CROIX) { 
        evaluation = evaluation + points[i];
        }
    }
    }
    int a = -1;
    if((m.g[0] + m.g[1] + m.g[2] == a) || (m.g[3] + m.g[4] + m.g[5] == a) || (m.g[6] + m.g[7] + m.g[8] == a) ||
       (m.g[0] + m.g[3] + m.g[6] == a) || (m.g[1] + m.g[4] + m.g[7] == a) || (m.g[2] + m.g[5] + m.g[8] == a) ||
       (m.g[0] + m.g[4] + m.g[8] == a) || (m.g[2] + m.g[4] + m.g[6] == a)) {
        evaluation -= 6;
    }

  
    if(((m.g[1] + m.g[4] == ROND) && (m.g[7] == CROIX)) || ((m.g[2] + m.g[5] == ROND) && (m.g[8] == CROIX)) || 
      ((m.g[0] + m.g[4] == ROND) && (m.g[8] == CROIX)) || ((m.g[3] + m.g[4] == ROND) && (m.g[5] == CROIX)) || 
      ((m.g[6] + m.g[7] == ROND) && (m.g[8] == CROIX)) || ((m.g[0] + m.g[6] == ROND) && (m.g[3] == CROIX)) || 
      ((m.g[4] + m.g[5] == ROND) && (m.g[3] == CROIX)) || ((m.g[0] + m.g[8] == ROND) && (m.g[4] == CROIX)) || 
      ((m.g[3] + m.g[6] == ROND) && (m.g[0] == CROIX)) || ((m.g[0] + m.g[3] == ROND) && (m.g[6] == CROIX)) || 
      ((m.g[2] + m.g[4] == ROND) && (m.g[6] == CROIX)) || ((m.g[7] + m.g[8] == ROND) && (m.g[6] == CROIX)) || 
      ((m.g[1] + m.g[7] == ROND) && (m.g[4] == CROIX)) || ((m.g[0] + m.g[2] == ROND) && (m.g[1] == CROIX)) || 
      ((m.g[4] + m.g[7] == ROND) && (m.g[1] == CROIX)) || ((m.g[4] + m.g[8] == ROND) && (m.g[0] == CROIX)) || 
      ((m.g[2] + m.g[8] == ROND) && (m.g[5] == CROIX)) || ((m.g[5] + m.g[8] == ROND) && (m.g[2] == CROIX)) || 
      ((m.g[1] + m.g[2] == ROND) && (m.g[0] == CROIX)) || ((m.g[3] + m.g[5] == ROND) && (m.g[4] == CROIX)) || 
      ((m.g[0] + m.g[1] == ROND) && (m.g[2] == CROIX)) || ((m.g[2] + m.g[6] == ROND) && (m.g[4] == CROIX))) {
        evaluation -= 9;
    }
    a = 1;
    if((m.g[0] + m.g[1] + m.g[2] == a) || (m.g[3] + m.g[4] + m.g[5] == a) || (m.g[6] + m.g[7] + m.g[8] == a) ||
       (m.g[0] + m.g[3] + m.g[6] == a) || (m.g[1] + m.g[4] + m.g[7] == a) || (m.g[2] + m.g[5] + m.g[8] == a) ||
       (m.g[0] + m.g[4] + m.g[8] == a) || (m.g[2] + m.g[4] + m.g[6] == a)) {
        evaluation += 6;
    }
    if(((m.g[1] + m.g[4] == 2) && (m.g[7] == ROND)) || ((m.g[2] + m.g[5] == 2) && (m.g[8] == ROND)) || 
      ((m.g[0] + m.g[4] == 2) && (m.g[8] == ROND)) || ((m.g[3] + m.g[4] == 2) && (m.g[5] == ROND)) || 
      ((m.g[6] + m.g[7] == 2) && (m.g[8] == ROND)) || ((m.g[0] + m.g[6] == 2) && (m.g[3] == ROND)) || 
      ((m.g[4] + m.g[5] == 2) && (m.g[3] == ROND)) || ((m.g[0] + m.g[8] == 2) && (m.g[4] == ROND)) || 
      ((m.g[3] + m.g[6] == 2) && (m.g[0] == ROND)) || ((m.g[0] + m.g[3] == 2) && (m.g[6] == ROND)) || 
      ((m.g[2] + m.g[4] == 2) && (m.g[6] == ROND)) || ((m.g[7] + m.g[8] == 2) && (m.g[6] == ROND)) || 
      ((m.g[1] + m.g[7] == 2) && (m.g[4] == ROND)) || ((m.g[0] + m.g[2] == 2) && (m.g[1] == ROND)) || 
      ((m.g[4] + m.g[7] == 2) && (m.g[1] == ROND)) || ((m.g[4] + m.g[8] == 2) && (m.g[0] == ROND)) || 
      ((m.g[2] + m.g[8] == 2) && (m.g[5] == ROND)) || ((m.g[5] + m.g[8] == 2) && (m.g[2] == ROND)) || 
      ((m.g[1] + m.g[2] == 2) && (m.g[0] == ROND)) || ((m.g[3] + m.g[5] == 2) && (m.g[4] == ROND)) || 
      ((m.g[0] + m.g[1] == 2) && (m.g[2] == ROND)) || ((m.g[2] + m.g[6] == 2) && (m.g[4] == ROND))) {
        evaluation += 9; }
 
    evaluation += isWin(m) * 12;
    return evaluation;
}

int evaluation_partie(super_morpion sm, int position) {
    int evaluation = 0;
    float poids[] = {1.4, 1, 1.4, 1, 1.75, 1, 1.4, 1, 1.4};
    int grand_morpion[9];
    for (int i = 0; i < 9; i++) {
        morpion tempMorpion;
        memcpy(tempMorpion.g, sm.g[i], sizeof(tempMorpion.g));
        tempMorpion.trait = sm.trait;
        evaluation += evaluation_grille(tempMorpion) * 1.5 * poids[i];
        if (i == position) {
            evaluation += evaluation_grille(tempMorpion) * poids[i];
        }
        int Ev = isWin(tempMorpion);
        evaluation -= Ev * poids[i];
        grand_morpion[i] = Ev;
    }
    morpion morpion_principal;
    memcpy(morpion_principal.g, grand_morpion, sizeof(morpion_principal.g));
    morpion_principal.trait = sm.trait;
    evaluation -= isWin(morpion_principal) * 5000;
    evaluation += evaluation_grille(morpion_principal) * 150;
    return evaluation;
}


EvalResult negaMax(super_morpion position, int grilleAJouer, int profondeur, int alpha, int beta, int joueur) {
    EvalResult resultat;
    resultat.meilleureEval = INT_MIN;
    resultat.meilleureGrille = -1;

    int evalCalculee = evaluation_partie(position, grilleAJouer);
    if (profondeur <= 0 || abs(evalCalculee) > 5000) {
        resultat.meilleureEval = joueur * evalCalculee;
        return resultat;
    }

    morpion grilleActuelle;
    memcpy(grilleActuelle.g, position.g[grilleAJouer], sizeof(grilleActuelle.g));
    grilleActuelle.trait = joueur;

    if (grilleAJouer != -1 && isWin(grilleActuelle) != 0) {
        grilleAJouer = -1;
    }

    if (grilleAJouer != -1 && !includesZero(grilleActuelle)) {
        grilleAJouer = -1;
    }

    int evalMax = INT_MIN;

    for (int i = 0; i < 9; i++) {
        int evalCourante = INT_MIN;
        int nouvelleGrilleAJouer;
        if (grilleAJouer == -1) {
            nouvelleGrilleAJouer = i;
        } else {
            nouvelleGrilleAJouer = grilleAJouer;
        }

        for (int j = 0; j < 9; j++) {
            if (isWin(grilleActuelle) == 0 && position.g[nouvelleGrilleAJouer][j] == -1) {
                position.g[nouvelleGrilleAJouer][j] = joueur;
                super_morpion nouvellePosition = position;
                EvalResult resultatTemp = negaMax(nouvellePosition, j, profondeur - 1, -beta, -alpha, -joueur);
                position.g[nouvelleGrilleAJouer][j] = -1;

                evalCourante = -resultatTemp.meilleureEval;
                if (evalCourante > evalMax) {
                    evalMax = evalCourante;
                    resultat.meilleureGrille = nouvelleGrilleAJouer;
                }

                if (alpha < evalCourante) {
                    alpha = evalCourante;
                }
                if (beta <= alpha) {
                    break;
                }
            }
        }

        if (grilleAJouer != -1) {
            break;
        }
    }

    resultat.meilleureEval = evalMax;
    return resultat;
}

int convertMove() {
    char colonne;
    int grille, ligne;
    int pos;

    // Lire l'entrée de l'utilisateur
    printf("Entrez votre coup (par exemple, 3 c3): ");
    scanf("%d %c%d", &grille, &colonne, &ligne);

    // Convertir la colonne de 'a', 'b', 'c' à 0, 1, 2
    colonne -= 'a';

    // Convertir la ligne de 1, 2, 3 à 0, 1, 2 (soustraire 1)
    ligne -= 1;  // Changez ici de '1' à 1
    printf("grille : %d, colonne : %d, ligne : %d\n", grille, colonne, ligne);

    // Vérifier la validité de l'entrée
    if(grille < 1 || grille > 9 || colonne < 0 || colonne > 2 || ligne < 0 || ligne > 2) {
        printf("Coup invalide\n");
        printf("grille : %d, colonne : %d, ligne : %d\n", grille, colonne, ligne);
        return -1; // Retourner -1 pour indiquer une entrée invalide
    }

    // Calculer la position linéaire
    pos = (grille - 1) * 10 + ligne * 3 + colonne;
    printf("Position renvoyée : %d \n", pos);

    return pos;
}



int isOverSuperMorpion(super_morpion *sm) {
    // Parcourir chaque grille du super-morpion
    for (int i = 0; i < 9; i++) {
        // Parcourir chaque case de la grille courante
        for (int j = 0; j < 9; j++) {
            // Si une case est vide, le jeu n'est pas encore terminé
            if (sm->g[i][j] == -1) {
                return 0; // Retourner 0 indique que le jeu n'est pas terminé
            }
        }
    }
    
    // Si toutes les cases de toutes les grilles sont remplies, le jeu est terminé
    return 1; // Retourner 1 indique que le jeu est terminé
}

void showSuperMorpion(super_morpion *sm) {
    printf("État du Super Morpion :\n");
    for (int row = 0; row < 3; row++) { // Pour chaque ligne de grilles
        for (int line = 0; line < 3; line++) { // Pour chaque ligne dans la grille
            for (int grid = 0; grid < 3; grid++) { // Pour chaque grille sur la ligne
                // Calculez l'index de la grille dans le super morpion
                int gridIndex = row * 3 + grid;
                // Affichez la ligne correspondante de cette grille
                for (int col = 0; col < 3; col++) {
                    int cell = sm->g[gridIndex][line * 3 + col];
                    if (cell == -1) printf(". ");
                    else if (cell == ROND) printf("O ");
                    else if (cell == CROIX) printf("X ");
                }
                printf("| "); // Séparateur de grille
            }
            printf("\n");
        }
        printf("------|-------|------\n"); // Séparateur de ligne de grilles
    }
}

void updateCadranPrev(int pos){
	cadranprev = pos;
}
