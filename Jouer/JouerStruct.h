#ifndef STRUCTURE_JOUER
#define STRUCTURE_JOUER

#define N_Torpilleur 2

typedef struct {int x;int y;} t_coordonnee;
typedef enum{Haut, Bas, Gauche, Droite}t_direction;
typedef enum{Hors_Portee, Portee} t_portee;

#endif