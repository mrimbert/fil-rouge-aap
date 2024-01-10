#include <stdio.h>
#include <stdlib.h>
#include "../utils/morpion.h"
#include <string.h>
#include <limits.h> //Pour ajouter les infinis

int minimax(morpion node, int traitOrdi, int test);
int isTerminal(morpion node); //Détecte si un noeud est terminal et renvoie 1 si c'est le cas
morpion * nodeChild(morpion node);
int eval(morpion M, int trait); //Renvoie la valeur de la grille de morpion 1 si victoire du joueur au trait, -1 si victoire de l'adversaire, 0 si égalité


int main(int argc, char ** argv){
	morpion grille_init = toMorpion(argv[1]);
	printf("digraph {\n");
	minimax(grille_init, grille_init.trait, -1);
	printf("}\n");
}


int isTerminal(morpion node){
	int i;
	if(abs(isWin(node))==1) return 1;
	for(i=0; i<9; i++){
		if(node.g[i] == -1) return 0;
	}
	return 1;
}


int minimax(morpion node, int traitOrdi, int test){ //On souhaite atteindre les noeuds terminaux, notre algorithme minimax ne prend donc pas d'argument de profondeur
	
	int numMere = 0;
	int val = 0;
	int i;
	if (isTerminal(node) == 1){
		if(traitOrdi == node.trait) numMere = generateGrilleImage(node, 0);
		else numMere = generateGrilleImage(node, 1);
		val = eval(node, traitOrdi);
		valeurMorpion(numMere, val);
		if(test != -1) generateLinkMorpion(test, numMere);
		return val;
	}
	
	
	if(traitOrdi == node.trait){
		val = INT_MIN;
		numMere = generateGrilleImage(node, 0);
		if(test != -1) generateLinkMorpion(test, numMere);
		morpion * child = nodeChild(node);
		for (i=0; i<9; i++){
			if(memcmp(child[i].g,newMorpion().g, 9*sizeof(int))){
				val = max(val, minimax(child[i], traitOrdi, numMere));
				valeurMorpion(numMere, val);
			}
		}

	} else {
		val = INT_MAX;
		numMere = generateGrilleImage(node, 1);
		if(test != -1) generateLinkMorpion(test, numMere);
		morpion * child = nodeChild(node);
		for (i=0; i<9; i++){
			if(memcmp(child[i].g,newMorpion().g, 9*sizeof(int))){
				val = min(val, minimax(child[i], traitOrdi, numMere));
				valeurMorpion(numMere, val);

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

int eval(morpion M, int trait){
	if(trait == CROIX && isWin(M) == 1) return 1;
	if(trait == CROIX && isWin(M) == -1) return -1;
	if(trait == ROND && isWin(M)== 1) return -1;
	if(trait == ROND && isWin(M) == -1) return 1;
	return 0;
}
