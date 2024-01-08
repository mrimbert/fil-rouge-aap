#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <limits.h>
#include "super_morpion.h"

int main(){
    	char str[100]; 
    	printf("Chaine de caractere: ");
	fgets(str, sizeof(str), stdin);
	int secondsleft;
	printf("Temps restant: ");
	scanf("%d", &secondsleft);
    	time_t start_time = time(NULL);
    	
	super_morpion sm = toSuperMorpion(str);
	int i=0;
	while (str[i] != ' '){
		i++;
	}
	char a = str[i+2];
	int grilleAJouer = a - '0';
	showSuperMorpion(&sm);
	

	int alpha = INT_MIN;
	int beta = INT_MAX;
	int profondeur = 2;
	EvalResult result = negaMax(sm, grilleAJouer, profondeur, alpha, beta, 1);
	printf("Coup: %d\n", result.meilleureGrille);
	return 0;
}

