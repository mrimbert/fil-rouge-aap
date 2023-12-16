#include <stdio.h>
#include "morpion.h"

int main(int argc, char ** argv){
	
	grille test = {CROIX, CROIX, CROIX, ROND, ROND, ROND, ROND, CROIX, CROIX};
	morpion test2;
	test2.trait = ROND;
	
	printf("L'élément 5 de la grille de test est : %d \n", test[4]);
	printf("Le trait est au : %d \n", test2.trait);
	return 0;

}
