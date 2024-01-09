#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <limits.h>
#include "negamax.h"

int main(int argc, char* argv[]){
	int secondsleft;
	printf("Temps restant: ");
	scanf("%d", &secondsleft);
    	time_t start_time = time(NULL);
    	
	super_morpion sm1 = toSuperMorpion(str);
	int i=0;
	while (str[i] != ' '){
		i++;
	}
	char a = str[i+2];
	int grilleAJouer = a - '0';
	childNode node;
	node.sm  = sm1;
	node.dernierePosition = grilleAJouer;
	showSuperMorpion(&sm1);

	int profondeur = 5;
	childNode result;
	result = getBestMove(&sm1,profondeur,1,node.dernierePosition);
	showSuperMorpion(&result.sm);
	int pos = convCoup(result.dernierePosition);
	printf("%d",pos);
	return 0;
}

