#include <stdio.h>
#include "./utils/super_morpion.h"

// int main(int argc, char ** argv){
/*
	super_morpion sm = newSuperMorpion();
	generateSuperMorpionImage(sm);
	playSuperMorpion(&sm,84);
	generateSuperMorpionImage(sm);
*/
	/*
	grille test = {CROIX, CROIX, CROIX, ROND, ROND, ROND, ROND, CROIX, CROIX};
	morpion test2;
	test2.trait = ROND;
	
	printf("L'élément 5 de la grille de test est : %d \n", test[4]);
	printf("Le trait est au : %d \n", test2.trait);
	char play[] = "1o3x1xo x";
	morpion M = toMorpion(play);
	printMorpion(M);
	printf("La valeur de la case 1 est : %d", M.g[1]);
	printf("Le jeu est au %d \n",M.trait);
	
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
	*/
	
        int main(){
        morpion M = newMorpion();
        int move;
        int moveCount = 0;

        while(!isWin(M) && moveCount < 9){  
        printMorpion(M);  
        printf("Player %d's turn. Enter your move (0-8): ", M.trait+1);
        scanf("%d", &move);
        playMorpion(&M, move); 
        generateMorpionImage(M);  
        moveCount ++;
    }

        printMorpion(M);
        if (isWin(M)){
        	printf("Game over - Player %d win \n", 1-M.trait+1);
        } else {
        	printf("Game over - It's a draw \n");
        }
	
    return 0;
}

