#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <limits.h>
#include "negamax.h"

int main(int argc, char* argv[]){

	int secondsleft = atoi(argv[2]);
	
	char* FEN = argv[1];
	printf("Lu : %s \n", FEN);

    	
	super_morpion sm1 = toSuperMorpion(FEN);
	showSuperMorpion(&sm1);
	generateSuperMorpionImage(sm1);
	//printf("Trait : %d \n", sm1.trait);

	childNode node;
	node.sm  = sm1;
	int i;
	while(FEN[i] != ' ') i++;
	int lastMove = (FEN[i+1]-48)*10+FEN[i+2]-48;
	//printf("Last Move : %d \n", lastMove);
	node.dernierePosition = invConvCoup(lastMove);
	//printf("Le dernier coup est : %d \n", node.dernierePosition);
	//showSuperMorpion(&sm1);
	
	int profondeur = 5;
	
	/*
	if(secondsleft >= 120) profondeur = 5;
	if(secondsleft >= 60 && secondsleft < 120 ) profondeur = 5;
	if(secondsleft <= 30) profondeur = 5;
	if(secondsleft < 15) profondeur = 5;
	*/
	
	//printf("Profondeur choisie : %d \n", profondeur);
	
	childNode result;
	result = getBestMove(&sm1,profondeur,1,node.dernierePosition);
	//showSuperMorpion(&result.sm);
	int pos = convCoup(result.dernierePosition);
	printf("%d \n",result.dernierePosition);
	printf("%d \n",pos);
	
	return pos;
}

