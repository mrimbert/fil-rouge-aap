#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "super_morpion.h"
static int fileCounter = 0;

super_morpion newSuperMorpion(){
	super_morpion sm = {{{-1,-1,-1,-1,-1,-1,-1,-1,-1},{-1,-1,-1,-1,-1,-1,-1,-1,-1},{-1,-1,-1,-1,-1,-1,-1,-1,-1},{-1,-1,-1,-1,-1,-1,-1,-1,-1},{-1,-1,-1,-1,-1,-1,-1,-1,-1},{-1,-1,-1,-1,-1,-1,-1,-1,-1},{-1,-1,-1,-1,-1,-1,-1,-1,-1},{-1,-1,-1,-1,-1,-1,-1,-1,-1},{-1,-1,-1,-1,-1,-1,-1,-1,-1}},ROND};
	return sm;
}

void playSuperMorpion(super_morpion * sm, int pos){
	assert(pos <= 88 && pos >= 0);
	int i = (pos/10); //Numéro du cadran
	int j = (pos%10); //Position dans le cadran
	
	if(sm->g[i][j] == ROND || sm->g[i][j] == CROIX){ //On vérifie que la position n'a pas déjà été jouée
		printf("Position déjà jouée, merci de rejouer \n");
		return;
	}
	
	sm->g[i][j] = sm->trait;
	if(sm->trait == ROND){
		sm->trait = CROIX;
	}
	else{
		sm->trait = ROND;
	}
}


void generateSuperMorpionImage(super_morpion sm){
    int i;
    int j;
    char fileName[30], pngFileName[30], command[100];

    // Créer un nom de fichier unique pour le fichier DOT et le fichier PNG
    snprintf(fileName, sizeof(fileName), "./super_morpion_image/super_morpion%d.dot", fileCounter);
    snprintf(pngFileName, sizeof(pngFileName), "./super_morpion_image/super_morpion%d.png", fileCounter);

    FILE *file = fopen(fileName, "w");
    if (file == NULL) {
        printf("Erreur : Impossible d'ouvrir le fichier %s.\n", fileName);
        return;
    }

     // Écriture du contenu DOT représentant le morpion dans le fichier
    fprintf(file, "digraph {\n");
    fprintf(file, " a0 [shape=none label=<\n");
    fprintf(file, "<TABLE border=\"0\" cellspacing=\"10\" cellpadding=\"10\" style=\"rounded\" bgcolor=\"black\"> \n");
            fprintf(file, "<TR> \n");
    fprintf(file,"<TD bgcolor=\"black\"> \n");
    fprintf(file, "<TABLE border=\"0\" cellspacing=\"10\" cellpadding=\"10\" style=\"rounded\" bgcolor=\"white\"> \n");
        fprintf(file, "<TR> \n");
    for (i = 0; i<9; i++){
    	for(j = 0; j<9; j++){
		if(sm.g[i][j]==ROND){
				fprintf(file, "<TD bgcolor=\"white\">O</TD> \n");
		}
		if(sm.g[i][j] == CROIX){
				fprintf(file, "<TD bgcolor=\"white\">X</TD> \n");
		}
		if(sm.g[i][j] == -1){
				fprintf(file, "<TD bgcolor=\"white\">.</TD> \n");
		}
		if(j%3==2){
				fprintf(file, "</TR> \n");
				if(j!=8) {fprintf(file, "<TR> \n"); }
		}
    }
    fprintf(file, "</TABLE> \n");
	fprintf(file, "</TD> \n");
	if(i%3==2 && i != 8){
		fprintf(file, "</TR> \n");
		fprintf(file, "<TR> \n");
		
	}
	   if(i != 8){
	    fprintf(file,"<TD bgcolor=\"white\"> \n");
		fprintf(file, "<TABLE border=\"0\" cellspacing=\"10\" cellpadding=\"10\" style=\"rounded\" bgcolor=\"white\"> \n");
		        fprintf(file, "<TR> \n");
		        }
   }
   fprintf(file, "</TR>");
    fprintf(file, "</TABLE>");
   fprintf(file, ">];");
    fprintf(file, "}\n");
    fclose(file);
    snprintf(command, sizeof(command), "dot %s -Tpng -o ./super_morpion_image/super_morpion%d.png",fileName, fileCounter);
    system(command);

    fileCounter++;  // Incrémenter le compteur pour la prochaine image
}

