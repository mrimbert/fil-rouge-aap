#define CROIX 1
#define ROND 0

typedef int grille[9];

typedef struct {
	grille g;
	int trait;
} morpion;

typedef struct{
	grille g[9];
	int trait;
} super_morpion;

