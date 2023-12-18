#include <stdio.h>
#include "morpion.h"

//int main(int argc, char ** argv){
	/*
	grille test = {CROIX, CROIX, CROIX, ROND, ROND, ROND, ROND, CROIX, CROIX};
	morpion test2;
	test2.trait = ROND;
	
	printf("L'élément 5 de la grille de test est : %d \n", test[4]);
	printf("Le trait est au : %d \n", test2.trait);
	*/
	
	/*morpion M = newMorpion();
	printMorpion(M);
	playMorpion(&M, 0);
	playMorpion(&M, 1);
	playMorpion(&M, 3);
	playMorpion(&M, 5);
	playMorpion(&M, 6);
	printMorpion(M);
	generateMorpionImage(M);
	printf("Est-ce que quelqu'un a gagné ? %d \n", isWin(M));*/
	
	
        /*int main(){
        morpion M = newMorpion();
        int move;
        int currentPlayer = 0;  // 0 for player 1, 1 for player 2

        while(!isWin(M)){  // Check if the game is over
        printMorpion(M);  // Display the current state of the game
        printf("Player %d's turn. Enter your move (0-8): ", currentPlayer + 1);
        scanf("%d", &move);
        playMorpion(&M, move);  // Update the game state with the new move
        generateMorpionImage(M);  // Generate an image of the current game state
        currentPlayer = 1 - currentPlayer;  // Switch player
    }

        printMorpion(M);  // Display the final state of the game
        printf("Game over!\n");

    return 0;
}*/

int main(){
    morpion M = newMorpion();
    int move;
    int currentPlayer = 0;  
    int moveCount = 0;    

    while(!isWin(M) && moveCount < 9){
        printMorpion(M); 
        printf("Player %d's turn. Enter your move (0-8): ", currentPlayer + 1);
        scanf("%d", &move);
        playMorpion(&M, move); 
        generateMorpionImage(M);
        currentPlayer = 1 - currentPlayer;
        moveCount++;  
    }

    printMorpion(M);
    if (isWin(M)) {
        printf("Player %d wins!\n", 1 - currentPlayer); 
    } else {
        printf("Game over! It's a draw.\n");
    }

    return 0;
}
