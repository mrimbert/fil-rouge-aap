#include <stdio.h>
#include "morpion.h"

int main(int argc, char ** argv){
	/*
	grille test = {CROIX, CROIX, CROIX, ROND, ROND, ROND, ROND, CROIX, CROIX};
	morpion test2;
	test2.trait = ROND;
	
	printf("L'élément 5 de la grille de test est : %d \n", test[4]);
	printf("Le trait est au : %d \n", test2.trait);
	*/
	
	morpion M = newMorpion();
	printMorpion(M);
	playMorpion(&M, 0);
	playMorpion(&M, 1);
	playMorpion(&M, 3);
	playMorpion(&M, 5);
	playMorpion(&M, 6);
	printMorpion(M);
	generateMorpionImage(M);
	printf("Est-ce que quelqu'un a gagné ? %d \n", isWin(M));
	
	return 0;

}
