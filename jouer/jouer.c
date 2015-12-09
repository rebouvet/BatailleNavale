#include "../grille/Grille.h"
#include "TorpilleurDeplacer.h"
#include "TorpilleurChoisir.h"
#include "TorpilleurAttaquer.h"
#include <stdio.h>
#include <stdlib.h>

void Jouer_init_temporaire(){
	int eJoueur = 1;
	Grille_init();
	Grille_ecrire_torpilleur(0,0, eJoueur, Present);
	Grille_ecrire_torpilleur(7,7, eJoueur, Present);
	Grille_ecrire_bateau(0,0, 2, 3);
	Grille_ecrire_obstacle(7,6, eJoueur, Oui);
	Grille_ecrire_obstacle(5,5, 2, Oui);
}

void Jouer_Changer_Joueur(int *eJoueur){
	if(*eJoueur == 1){
		*eJoueur = 2;
	}
	else {
		*eJoueur = 1;
	}
}

void Jouer_Choisir(int eJoueur,t_coordonnee *pcTorpilleur,int *peNumero_Torpilleur){
	Jouer_Trouver_Torpilleur(eJoueur, pcTorpilleur);
	Jouer_Afficher_Torpilleur(pcTorpilleur);
	Jouer_Selectionner_Torpilleur(peNumero_Torpilleur);
	Jouer_Afficher_Torpilleur_Selectionne(*peNumero_Torpilleur);
}

void Jouer_Deplacer(int eJoueur,t_coordonnee *pcTorpilleur,int *peNumero_Torpilleur){
	t_direction dDirection;
	int bValide = 0;
	while(!bValide){
		Jouer_Choisir_Direction(&dDirection);
		bValide = Jouer_Deplacement_Valide(eJoueur,dDirection,*peNumero_Torpilleur, pcTorpilleur);
		if(!bValide){
			printf("\nDirection invalide (Presence d'un torpilleur ou d'un obstacle ou hors carte)");
		}
	}
	Jouer_Deplacer_Torpilleur(eJoueur,dDirection,*peNumero_Torpilleur, pcTorpilleur);
	Jouer_Trouver_Torpilleur(eJoueur, pcTorpilleur);
	Jouer_Afficher_Torpilleur(pcTorpilleur);
}

void Jouer_Attaquer(int eJoueur,t_coordonnee *pcTorpilleur,int *peNumero_Torpilleur){
	t_portee gPortee[N][M];
	t_coordonnee cCurseur;
	int bAttaque_Possible;
	int eJoueurAdverse = eJoueur;
	Jouer_Changer_Joueur(&eJoueurAdverse);
	
	Jouer_Calculer_Portee(eJoueur, pcTorpilleur, *peNumero_Torpilleur, gPortee); // /!\Limites !!!!
	Jouer_Afficher_Portee(gPortee);
	bAttaque_Possible = Jouer_Attaque_Possible(gPortee);
	if(bAttaque_Possible){
		Jouer_Choisir_Attaque(gPortee, &cCurseur);
		Grille_ecrire_toucher(cCurseur.x,cCurseur.y, eJoueurAdverse, Oui);
		
	}
	else{
		printf("\nAttaque impossible HAHAHAHAHAH");
	}
}

int Jouer_Gagnant(int eJoueur){
	Jouer_Changer_Joueur(&eJoueur);
	int eBateau, eToucher;
	int bGagnant = 1;
	int i, j;
	for(i=0; i < N; i++){
		for(j=0; j < M; j++){
			Grille_lire_bateau(i,j, eJoueur,&eBateau);
			Grille_lire_toucher(i,j, eJoueur,&eToucher);
			if(eBateau && eToucher == Non){
				bGagnant = 0;
			}
		}
	}
	return bGagnant;
}


void Jouer_Partie(){
	int eJoueur = 0;
	t_coordonnee cTorpilleur[N_Torpilleur];
	int eNumero_Torpilleur;
	int bGagnant = 0;
	
	while(!bGagnant){
		Jouer_Changer_Joueur(&eJoueur);
		Jouer_Choisir(eJoueur, cTorpilleur, &eNumero_Torpilleur);
		Jouer_Deplacer(eJoueur, cTorpilleur, &eNumero_Torpilleur);
		Jouer_Attaquer(eJoueur, cTorpilleur, &eNumero_Torpilleur);
		bGagnant = Jouer_Gagnant(eJoueur);
	}
	printf("\nLe joueur %i a gagne !", eJoueur);
}

/*int main(){
	Jouer_init_temporaire(); //Temporaire

	Jouer_Partie();
	printf("\n");
	
	return 1;
}*/