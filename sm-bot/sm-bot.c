#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <limits.h>
#include "negamax.h"

int main(int argc, char* argv[]){

	int secondsleft = atoi(argv[4]);
	
	char* FEN = argv[1];
	//printf("Lu : %s \n", FEN);
	char* lastMove = argv[2];
	//printf("Lu : %s \n", lastMove);
	char* trait = argv[3];
	//printf("Lu : %s \n", trait);
    	
	super_morpion sm1 = toSuperMorpion(FEN, trait);
	//printf("Trait : %d \n", sm1.trait);

	childNode node;
	node.sm  = sm1;
	node.dernierePosition = invConvCoup(atoi(lastMove));
	//printf("Le dernier coup est : %d \n", node.dernierePosition);
	//showSuperMorpion(&sm1);
	
	int profondeur;
	
	
	if(secondsleft >= 120) profondeur = 5;
	if(secondsleft >= 60 && secondsleft < 120 ) profondeur = 5;
	if(secondsleft <= 30) profondeur = 5;
	if(secondsleft < 15) profondeur = 5;
	
	//printf("Profondeur choisie : %d \n", profondeur);
	
	childNode result;
	result = getBestMove(&sm1,profondeur,1,node.dernierePosition);
	//showSuperMorpion(&result.sm);
	int pos = convCoup(result.dernierePosition);
	printf("%d \n",result.dernierePosition);
	printf("%d \n",pos);
	return pos;
}

