#include "../grille/Struct.h"
#include "../grille/Grille.h"
#include "TorpilleurAttaquer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void Jouer_Calculer_Portee(int eJoueurAdverse, t_coordonnee cTorpilleur[], int eNumero_Torpilleur,t_portee gPortee[N][M], int N_Torpilleur){
	//Fonction qui permet de stocker dans la grille gPortee[N][M] les cases où le torpilleur selectionne a la possibilite d'attaquer
	int eObstacle;
	int eToucher;
	int i, j;
	for(i = 0; i < N; i++){
		for(j = 0; j < M; j++){
			gPortee[i][j] = Hors_Portee;
		}
	}
	int x = cTorpilleur[eNumero_Torpilleur].x;
	int y = cTorpilleur[eNumero_Torpilleur].y;
	for(i = x - 1; i < x +2; i++){
		if(i >= 0 && i < N){
			for(j = y - 1; j < y +2; j++){
				if(j >= 0 && j < M){
					Grille_lire_obstacle(i, j, eJoueurAdverse, &eObstacle);
					Grille_lire_toucher(i, j, eJoueurAdverse, &eToucher);
					if(eObstacle == Aucun_o && eToucher == Non){
						gPortee[i][j] = Portee;
					}
				}
			}
		}
	}
}

void Jouer_Afficher_Portee(t_portee gPortee[N][M]){
	printw("\n");
	int i, j;	
	for(i = 0; i < N; i++){
		printw("\n");
		for(j = 0; j < M; j++){
				printw("%i ", gPortee[i][j]);
		}
	}
	printw("\n");
	refresh();
}

int Jouer_Attaque_Possible(t_portee gPortee[N][M]){
	//Fonction qui permmet de determiner si l'attaque est possible c'est à dire si le torpilleur a bien une case où il peut attaquer
	int i, j;	
	for(i = 0; i < N; i++){
		for(j = 0; j < M; j++){
			if(gPortee[i][j]){
				return 1;
			}
		}
	}
	return 0;
}

void Jouer_Init_Curseur(t_portee gPortee[N][M], t_coordonnee *cCurseur){
	int i, j;
	int bPortee;
	if(gPortee[cCurseur->x][cCurseur->y] == Hors_Portee){
		for(i = 0; i < N ; i++){
			for(j = 0; j < M; j++){
				bPortee = gPortee[i][j];
				if(bPortee){
					cCurseur->x = i;
					cCurseur->y = j;
				}
			}
		}
	}
}


void Jouer_Deplacer_Curseur(t_portee gPortee[N][M], t_coordonnee *cCurseur){
	int eSaisie;
	t_direction dDirection;
	printw("\nVeuillez selectionner la direction dans laquelle deplacer le curseur (Haut = 0, Bas = 1, Gauche = 2, Droite = 3):");
	refresh();
	scanw("%i", &eSaisie);
	while(eSaisie < 0 || eSaisie > 3){
		printw("\nNumero de direction incorrect, veuiller entrez un numero a nouveau (Haut = 0, Bas = 1, Gauche = 2, Droite = 3):");
		refresh();
		scanw("%i", &eSaisie);
	}
	int x = cCurseur->x, y = cCurseur->y;
	dDirection = eSaisie;
	if(dDirection == Haut){
		x--;
		while(gPortee[x][y] == Hors_Portee && x > 0){
			x--;
		}
	}
	if(dDirection == Bas){
		x++;
		while(gPortee[x][y] == Hors_Portee && x < N){
			x++;
		}
	}
	if(dDirection == Droite){
		y++;
		while(gPortee[x][y] == Hors_Portee && y < M){
			y++;
		}
	}
	if(dDirection == Gauche){
		y--;
		while(gPortee[x][y] == Hors_Portee && y > 0){
			y--;
		}
	}
	if(gPortee[x][y] == Portee){
		cCurseur->x = x;
		cCurseur->y = y;
	}
}

int Jouer_Stringtonum(char *v,int *res){
    int bNum=1;
    int i;
    *res=0;
    for(i=0;i<strlen(v);i++)
        bNum=bNum && isdigit(v[i]);
    if(bNum==1){
        *res=atoi(v);
    }
    return bNum;
}

/*void Jouer_Choisir_Attaque(t_portee gPortee[N][M], t_coordonnee *cCurseur,int N_Torpilleur){
	//Fonction qui permet de choisir les coordonne a attaquer manuellement.
	char sx[20], sy[20];
	int x, y;
	int bCoordonneValide = 0;
	printw("\nVeuillez saisir les coordonnées x et y de votre attaque :");
	refresh();
        scanw("%s",sx);
        scanw("%s",sy);
	while(!bCoordonneValide){
		if(Jouer_Stringtonum(sx,&x) && Jouer_Stringtonum(sy,&y)){
			if(gPortee[x][y] == Portee){
				cCurseur->x = x;
				cCurseur->y = y;
				bCoordonneValide = 1;
			}
		}
		if(!bCoordonneValide){
			printw("\nCoordonnes invalides, veuillez saisir les coordonnées x et y de votre attaque :");
			refresh();
      			scanw("%s",sx);
  		      	scanw("%s",sy);
		}
	}
}*/


void Jouer_Choisir_Attaque(int eJoueur, int eNumero_Torpilleur, t_portee gPortee[N][M], t_coordonnee *cCurseur,int N_Torpilleur){
	int ech;
	int bValider = 0;
	printw("\nVeuillez selectionner votre torpilleur a l'aide des fleches haut, bas, gauche et droite :");
	refresh();
	clear();
	Portee_torpilleur_afficher(gPortee,eJoueur,cCurseur->x, cCurseur->y);
	refresh();
	while(bValider == 0){
		timeout(-1);
		ech = getch();
		switch(ech){
			case 68:
				if(gPortee[cCurseur->x][cCurseur->y-1] == Portee){
					cCurseur->y--;
				}
				clear();
				Portee_torpilleur_afficher(gPortee,eJoueur,cCurseur->x, cCurseur->y);
				break;
			case 67:
				if(gPortee[cCurseur->x][cCurseur->y+1] == Portee){
					cCurseur->y++;
				}
				clear();
				Portee_torpilleur_afficher(gPortee,eJoueur,cCurseur->x, cCurseur->y);
				break;
			case 65:
				if(gPortee[cCurseur->x-1][cCurseur->y] == Portee){
					cCurseur->x--;
				}
				clear();
				Portee_torpilleur_afficher(gPortee,eJoueur,cCurseur->x, cCurseur->y);
				break;
			case 66:
				if(gPortee[cCurseur->x+1][cCurseur->y] == Portee){
					cCurseur->x++;
				}
				clear();
				Portee_torpilleur_afficher(gPortee,eJoueur,cCurseur->x, cCurseur->y);
				break;
			case 10:
				bValider = 1;
				break;
		}
	}
}




