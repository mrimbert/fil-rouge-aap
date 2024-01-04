#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "morpion.h"
static int fileCounter = 0;
static int morpionCounter = 0;

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


morpion toMorpion(char * play){
	morpion M = newMorpion();
	int i = 0;
	int decalage = 0;
	while(play[i] != ' '){
		if(play[i] == 'x' || play[i] == 'X'){
			M.g[i+decalage] = CROIX;
			//printf("Position %d \n", i+decalage);
		} 
		if(play[i] == 'o' || play[i] == 'O'){
			M.g[i+decalage] = ROND;
			//printf("Position %d \n", i+decalage);
		}
		//printf("On a : %c\n", play[i]);
		if(play[i] <= 56) {
			decalage += play[i]-49;
			//printf("Decalage = %d \n", decalage);
		}
		i++;
	}
	if(play[i+1] == 'o'){
		M.trait = ROND;
	}
	if(play[i+1] == 'x'){
		M.trait = CROIX;
	}
	return M;
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


void generateMorpionImage(const morpion M) {
    int i;
    char fileName[30], pngFileName[30], command[100];

    // Créer un nom de fichier unique pour le fichier DOT et le fichier PNG
    snprintf(fileName, sizeof(fileName), "./morpion_image/morpion%d.dot", fileCounter);
    snprintf(pngFileName, sizeof(pngFileName), "./morpion_image/morpion%d.png", fileCounter);

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
    snprintf(command, sizeof(command), "dot %s -Tpng -o ./morpion_image/morpion%d.png",fileName, fileCounter);
    system(command);

    fileCounter++;  // Incrémenter le compteur pour la prochaine image
}

int generateGrilleImage(const morpion M, int state){
    int i;
    
     // Écriture du contenu DOT représentant le morpion sur la sortie standard (donc la console)
    printf(" m%d [shape=none label=<\n", morpionCounter);
    printf("<TABLE border=\"0\" cellspacing=\"10\" cellpadding=\"10\" style=\"rounded\" bgcolor=\"black\"> \n");
    printf("<TR> \n");
    for (i = 0; i<9; i++){
	if(M.g[i]==ROND){
			printf("<TD bgcolor=\"white\">O</TD> \n");
	}
	if(M.g[i] == CROIX){
			printf("<TD bgcolor=\"white\">X</TD> \n");
	}
	if(M.g[i] == -1){
			printf("<TD bgcolor=\"white\">.</TD> \n");
	}
	if(i%3==2){
			printf("</TR> \n");
			printf("<TR> \n");
	}
    }
    
    if (state==1){
    	    printf("<TD bgcolor=\"red\" colspan=\"3\">m_%d</TD></TR> \n", morpionCounter);
    }
    if (state == 0){
    	   printf("<TD bgcolor=\"green\" colspan=\"3\">m_%d</TD></TR> \n", morpionCounter);
    }
    printf("</TABLE> \n");
    printf(">]; \n");
    int prev = morpionCounter;
    morpionCounter++;
    
    return prev;
}

void generateLinkMorpion(int num_mere, int num_fille){
	printf("m%d -> m%d[label=\"Coup\"] \n", num_mere, num_fille);
}

void valeurMorpion(int num, int val){
	printf("m%d[xlabel=%d] \n", num, val);
}


int max(int a, int b){
	if(a>= b) return a;
	return b; 
}

int min(int a, int b){
	if(a>= b) return b;
	return a; 
}

int getCounter(){
	return morpionCounter;
}

// Vérifie si une grille 3x3 dans une structure morpion est complète
int isOver(morpion m) {
    for (int i = 0; i < 9; i++) {
        if (m.g[i] == -1) { // Si une case est vide, la grille n'est pas complète
            return 0;
        }
    }
    return 1; // Toutes les cases sont remplies
}
