// Structure pour représenter un enfant avec son état de jeu et la dernière position jouée
typedef struct {
    super_morpion sm;  // L'état du jeu de l'enfant
    int dernierePosition;  // La dernière position jouée pour cet enfant
} childNode;

// Déclaration des prototypes de fonctions
int minimax(childNode node, int depth, int traitOrdi);
childNode * nodeChildren(super_morpion *node, int dernierePosition, int *childrenCount);
int isTerminal(super_morpion *node);
childNode getBestMove(super_morpion *node, int depth, int traitOrdi, int dernierePosition);