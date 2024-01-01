#include <stdio.h>
#include <stdlib.h>
#include "./utils/morpion.h"
#include <string.h>
#include <limits.h> //Pour ajouter les infinis

int minimax(morpion node, int traitOrdi);
int isTerminal(morpion node); //Détecte si un noeud est terminal et renvoie 1 si c'est le cas
morpion * nodeChild(morpion node);

int main(int argc, char ** argv){
	morpion grille_init = toMorpion(argv[1]);
	printMorpion(grille_init);
	morpion * test = nodeChild(grille_init);
}


int isTerminal(morpion node){
	int i;
	if(abs(isWin(node))==1) return 1;
	for(i=0; i<9; i++){
		if(node.g[i] == -1) return 0;
	}
	return 1;
}


int minimax(morpion node, int traitOrdi){ //On souhaite atteindre les noeuds terminaux, notre algorithme minimax ne prend donc pas d'argument de profondeur
	int val = 0;
	int i;
	
	if (isTerminal(node) == 1){
		return val;
	}
	
	morpion * child = nodeChild(node);
	
	if(traitOrdi == node.trait){
		val = INT_MIN;
		for (i=0; i<9; i++){
			if(memcmp(child[i].g,newMorpion().g, 9*sizeof(int))){
				val = max(val, minimax(child[i], traitOrdi));
			}
		}

	} else {
		val = INT_MAX;
		for (i=0; i<9; i++){
			if(memcmp(child[i].g,newMorpion().g, 9*sizeof(int))){
				val = min(val, minimax(child[i], traitOrdi));
			}
		}
		
	}
	
	return val;
}

morpion * nodeChild(morpion node){
	morpion * list = malloc(9*sizeof(morpion));
	morpion temp = newMorpion();
	temp.trait = 1-node.trait;
	memcpy(temp.g, node.g, sizeof(temp.g));
	int i;
	for (i=0; i<9; i++){
		if(node.g[i] == -1){
			temp.g[i] = node.trait;
			list[i] = temp;
			temp.g[i] = -1;
		} else {
			list[i] = newMorpion();
		}
	}
	
	return list;
}
