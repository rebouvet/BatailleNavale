#ifndef TORPILLEUR_CHOIX
#define TORPILLEUR_CHOIX

#include "JouerStruct.h"
#include "include/Struct.h"

void Jouer_Trouver_Torpilleur(int eJoueur, t_coordonnee cBateau[N_Torpilleur]);
void Jouer_Afficher_Torpilleur(t_coordonnee cTorpilleur[N_Torpilleur]);
void Jouer_Selectionner_Torpilleur(int *peNumero_Torpilleur);
void Jouer_Afficher_Torpilleur_Selectionne(int eNumero_Torpilleur);

#endif