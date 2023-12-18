#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "morpion.h"
static int fileCounter = 0;

morpion newMorpion(){
	morpion M = {{-1,-1,-1,-1,-1,-1,-1,-1,-1}, ROND};
	return M;
}

void printMorpion(morpion M){
	int i;
	printf("- - - - -  \n");
	
	for(i = 0; i<9;i++){
		if(M.g[i]==ROND){
			printf(" O ");
		}
		if(M.g[i] == CROIX){
			printf(" X ");
		}
		if(M.g[i] == -1){
			printf(" . ");
		}
		if(i%3==2){
			printf("\n");
		}
	}
	printf("- - - - -  \n");
}

void playMorpion(morpion * M, int pos){
	assert(pos <= 8 && pos >= 0);
	
	if(M->g[pos] == ROND || M->g[pos] == CROIX){ //On vérifie que la position n'a pas déjà été jouée
		printf("Position déjà jouée, merci de rejouer \n");
		return;
	}
	
	M->g[pos] = M->trait;
	if(M->trait == ROND){
		M->trait = CROIX;
	}
	else{
		M->trait = ROND;
	}
}

int isWin(morpion M){
	if(M.trait == ROND){
		if(M.g[0] == CROIX && M.g[1] == CROIX && M.g[2] == CROIX){
			return 1;
		}
		if(M.g[3] == CROIX && M.g[4] == CROIX && M.g[5] == CROIX){
			return 1;
		}
		if(M.g[6] == CROIX && M.g[7] == CROIX && M.g[8] == CROIX){
			return 1;
		}
		if(M.g[0] == CROIX && M.g[3] == CROIX && M.g[6] == CROIX){
			return 1;
		}
		if(M.g[1] == CROIX && M.g[4] == CROIX && M.g[7] == CROIX){
			return 1;
		}
		if(M.g[2] == CROIX && M.g[5] == CROIX && M.g[8] == CROIX){
			return 1;
		}
		if(M.g[4] == CROIX && M.g[6] == CROIX && M.g[2] == CROIX){
			return 1;
		}
		if(M.g[4] == CROIX && M.g[0] == CROIX && M.g[8] == CROIX){
			return 1;
		}
		return 0;
	}
	if(M.trait == CROIX){
		if(M.g[0] == ROND && M.g[1] == ROND && M.g[2] == ROND){
			return -1;
		}
		if(M.g[3] == ROND && M.g[4] == ROND && M.g[5] == ROND){
			return -1;
		}
		if(M.g[6] == ROND && M.g[7] == ROND && M.g[8] == ROND){
			return -1;
		}
		if(M.g[0] == ROND && M.g[3] == ROND && M.g[6] == ROND){
			return -1;
		}
		if(M.g[1] == ROND && M.g[4] == ROND && M.g[7] == ROND){
			return -1;
		}
		if(M.g[2] == ROND && M.g[5] == ROND && M.g[8] == ROND){
			return -1;
		}
		if(M.g[4] == ROND && M.g[6] == ROND && M.g[2] == ROND){
			return -1;
		}
		if(M.g[4] == ROND && M.g[0] == ROND && M.g[8] == ROND){
			return -1;
		}
		return 0;
	}
	return 0;
}


/*void generateMorpionImage(const morpion M) {
    int i;
    char fileName[30], pngFileName[30], command[100];

    // Créer un nom de fichier unique pour le fichier DOT et le fichier PNG
    snprintf(fileName, sizeof(fileName), "morpion%d.dot", fileCounter);
    snprintf(pngFileName, sizeof(pngFileName), "morpion%d.png", fileCounter);

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
    for (i = 0; i<9; i++){
	if(M.g[i]==ROND){
			fprintf(file, "<TD bgcolor=\"white\">O</TD> \n");
	}
	if(M.g[i] == CROIX){
			fprintf(file, "<TD bgcolor=\"white\">X</TD> \n");
	}
	if(M.g[i] == -1){
			fprintf(file, "<TD bgcolor=\"white\">.</TD> \n");
	}
	if(i%3==2){
			fprintf(file, "</TR> \n");
			fprintf(file, "<TR> \n");
	}
    }
    
    fprintf(file, "<TD bgcolor=\"red\" colspan=\"3\">label</TD></TR> \n");
    fprintf(file, "</TABLE> \n");
    fprintf(file,">]; \n");
    fprintf(file, "}\n");
    fclose(file);
    snprintf(command, sizeof(command), "dot %s -Tpng -o morpion%d.png",fileName, fileCounter);
    system(command);

    fileCounter++;  // Incrémenter le compteur pour la prochaine image
}*/

void generateMorpionImage(const morpion M) {
    static char previousFileName[30] = "";
    char fileName[30], pngFileName[30], command[200];


    if (previousFileName[0] != '\0') {
        snprintf(command, sizeof(command), "rm %s", previousFileName);
        system(command);
    }


    snprintf(fileName, sizeof(fileName), "morpion%d.dot", fileCounter);
    snprintf(pngFileName, sizeof(pngFileName), "morpion%d.png", fileCounter);

    FILE *file = fopen(fileName, "w");
    if (file == NULL) {
        printf("Erreur : Impossible d'ouvrir le fichier %s.\n", fileName);
        return;
    }

    fprintf(file, "digraph {\n");
    fprintf(file, " a0 [shape=none label=<\n");
    fprintf(file, "<TABLE border=\"0\" cellspacing=\"10\" cellpadding=\"10\" style=\"rounded\" bgcolor=\"black\"> \n");
    fprintf(file, "<TR> \n");
    for (i = 0; i<9; i++){
	if(M.g[i]==ROND){
			fprintf(file, "<TD bgcolor=\"white\">O</TD> \n");
	}
	if(M.g[i] == CROIX){
			fprintf(file, "<TD bgcolor=\"white\">X</TD> \n");
	}
	if(M.g[i] == -1){
			fprintf(file, "<TD bgcolor=\"white\">.</TD> \n");
	}
	if(i%3==2){
			fprintf(file, "</TR> \n");
			fprintf(file, "<TR> \n");
	}
    }
    
    fprintf(file, "<TD bgcolor=\"red\" colspan=\"3\">label</TD></TR> \n");
    fprintf(file, "</TABLE> \n");
    fprintf(file,">]; \n");
    fprintf(file, "}\n");
    fclose(file);

    snprintf(command, sizeof(command), "dot %s -Tpng -o %s && rm %s", fileName, pngFileName, fileName);
    system(command);

    strncpy(previousFileName, fileName, sizeof(previousFileName));

    fileCounter++; 
}
