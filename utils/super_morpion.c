#include "super_morpion.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
static int fileCounter = 0;
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

void playSuperMorpion(super_morpion *sm, int pos) {
  assert(pos <= 88 && pos >= 0);
  if (cadranprev == -1) {
    cadranprev = (pos / 10); // Numéro du cadran
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
  char fileName[30], pngFileName[30], command[100];

  // Créer un nom de fichier unique pour le fichier DOT et le fichier PNG
  snprintf(fileName, sizeof(fileName),
           "./super_morpion_image/super_morpion%d.dot", fileCounter);
  snprintf(pngFileName, sizeof(pngFileName),
           "./super_morpion_image/super_morpion%d.png", fileCounter);

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
           "dot %s -Tpng -o ./super_morpion_image/super_morpion%d.png",
           fileName, fileCounter);
  system(command);

  fileCounter++; // Incrémenter le compteur pour la prochaine image
}

int isWinSuperMorpion(super_morpion sm) {
  morpion grille0 = newMorpion();
  grille0.trait = sm.trait;
  memcpy(grille0.g, sm.g[0], 9);

  morpion grille1 = newMorpion();
  grille1.trait = sm.trait;
  memcpy(grille1.g, sm.g[1], 9);

  morpion grille2 = newMorpion();
  grille2.trait = sm.trait;
  memcpy(grille2.g, sm.g[2], 9);

  morpion grille3 = newMorpion();
  grille3.trait = sm.trait;
  memcpy(grille3.g, sm.g[3], 9);

  morpion grille4 = newMorpion();
  grille4.trait = sm.trait;
  memcpy(grille4.g, sm.g[4], 9);

  morpion grille5 = newMorpion();
  grille5.trait = sm.trait;
  memcpy(grille5.g, sm.g[5], 9);

  morpion grille6 = newMorpion();
  grille6.trait = sm.trait;
  memcpy(grille6.g, sm.g[6], 9);

  morpion grille7 = newMorpion();
  grille7.trait = sm.trait;
  memcpy(grille7.g, sm.g[7], 9);

  morpion grille8 = newMorpion();
  grille8.trait = sm.trait;
  memcpy(grille8.g, sm.g[8], 9);

  if (abs(isWin(grille0)) == 1 && abs(isWin(grille1)) == 1 &&
      abs(isWin(grille2)) == 1)
    return sm.trait * -1;
  if (abs(isWin(grille3)) == 1 && abs(isWin(grille4)) == 1 &&
      abs(isWin(grille5)) == 1)
    return sm.trait * -1;
  if (abs(isWin(grille6)) == 1 && abs(isWin(grille7)) == 1 &&
      abs(isWin(grille8)) == 1)
    return sm.trait * -1;
  if (abs(isWin(grille0)) == 1 && abs(isWin(grille3)) == 1 &&
      abs(isWin(grille6)) == 1)
    return sm.trait * -1;
  if (abs(isWin(grille1)) == 1 && abs(isWin(grille4)) == 1 &&
      abs(isWin(grille7)) == 1)
    return sm.trait * -1;
  if (abs(isWin(grille2)) == 1 && abs(isWin(grille5)) == 1 &&
      abs(isWin(grille8)) == 1)
    return sm.trait * -1;
  if (abs(isWin(grille0)) == 1 && abs(isWin(grille4)) == 1 &&
      abs(isWin(grille8)) == 1)
    return sm.trait * -1;
  if (abs(isWin(grille2)) == 1 && abs(isWin(grille4)) == 1 &&
      abs(isWin(grille6)) == 1)
    return sm.trait * -1;

  return 0;
}