//
//  Placement_bateau.c
//
//
//  Created by Zerbane Mehdi on 27/11/2015.
//
//
#include "../grille/Outil.h"
#include "../grille/Grille.h"
#include "../grille/Struct.h"
#include "Placement_obstacle.h"
#include "../Affichage/include/afficher.h"

t_plateau grille;

int bStringtonum(char *v,int *res){ /*Fonction qui convertis une chaine de caractères en int si la chaine de caractère est un int*/
    int eNum=1;
    int i;
    *res=0;
    for(i=0;i<strlen(v);i++)
        eNum=eNum && isdigit(v[i]);
    if(eNum==1){
        *res=atoi(v); //On convertis la chaine en int
    }
    return eNum;
}
/****************************************************************************/
/****************************************************************************/
/****************************************************************************/
int verif_presence(t_bateau bateau,int i,int j,int eChoix_sens,int eNum_grille){ /*Fonction qui regarde si là où l'on souhaite placer le bateau il y a dejà un bateau ou un obstacle*/

    int eCompteur=0,eResultat_b=0,eResultat_o=0,eResultat_t=0;
    if(eChoix_sens==1){
	    while(eCompteur<bateau){
		Grille_lire_bateau(i,j+eCompteur,eNum_grille,&eResultat_b); //On regarde si il y a un bateau
 		Grille_lire_obstacle(i,j+eCompteur,eNum_grille,&eResultat_o); //On regarde si il y a un obstacle
		Grille_lire_torpilleur(i,j+eCompteur,eNum_grille,&eResultat_t); //On regarde si il y a un torpilleur
		if(eResultat_b!=0 || eResultat_o!=0 || eResultat_t!=0)return 0; // Si il y a quelque chose on return 0
	        eCompteur++;
	   }
   }
    else if(eChoix_sens==2){
	while(eCompteur<bateau){
		Grille_lire_bateau(eCompteur+i,j,eNum_grille,&eResultat_b); //On regarde si il y a un bateau
		Grille_lire_obstacle(eCompteur+i,j,eNum_grille,&eResultat_o); //On regarde si il y a un obstacle
		Grille_lire_torpilleur(eCompteur+i,j,eNum_grille,&eResultat_t); //On regarde si il y a un torpilleur
		if(eResultat_b!=0 || eResultat_o!=0 || eResultat_t!=0)return 0; // Si il y a quelque chose on return 0
	        eCompteur++;
	   }

   }
	return 1; //Sinon on return 1
}
/****************************************************************************/
/****************************************************************************/
/****************************************************************************/
int Assez_de_place(t_bateau bateau, int i,int j,int eChoix_sens,int eNum_grille){ /*Fonction qui regarde si il y a assez de place pour placer un bateau*/
	if(eChoix_sens==1){
		return (j+bateau-1<N); 
	}
	else if(eChoix_sens==2){
		return (i+bateau-1<M);
	}
	return 0;
}
/****************************************************************************/
/****************************************************************************/
/****************************************************************************/
void Placer_grillebateau(t_bateau bateau, int i,int j,int eNum_grille,int eChoix_sens){ /*On place sur la grille le bateau*/
	int eCompteur=0;
	if(eChoix_sens==1){
		while(eCompteur<bateau){
			Grille_ecrire_bateau(i,j+eCompteur,eNum_grille,bateau);
			eCompteur++;
		}
	}else if(eChoix_sens==2){
		while(eCompteur<bateau){
			Grille_ecrire_bateau(i+eCompteur,j,eNum_grille,bateau);
			eCompteur++;
		}
	}
}
/****************************************************************************/
/****************************************************************************/
/****************************************************************************/
void Enlever_grillebateau(t_bateau bateau, int i,int j,int eNum_grille,int eChoix_sens){ /*Fonction qui supprime un bateau d'une grille*/
	int eCompteur=0,eBateau=0,eObstacle=0;
	if(eChoix_sens==1){
		while(eCompteur<bateau){
			Grille_lire_bateau(i,j+eCompteur,eNum_grille,&eBateau); // On regarde si il y a un bateau
 			Grille_lire_obstacle(i,j+eCompteur,eNum_grille,&eObstacle); //On regarde si il y a un bateau
			if(eBateau==bateau && eObstacle==0)Grille_ecrire_bateau(i,j+eCompteur,eNum_grille,Aucun_b); //On supprime le bateau
			eCompteur++;
		}
	}else if(eChoix_sens==2){
		while(eCompteur<bateau){
			Grille_lire_bateau(i+eCompteur,j,eNum_grille,&eBateau);
 			Grille_lire_obstacle(i+eCompteur,j,eNum_grille,&eObstacle);
			if(eBateau==bateau && eObstacle==0)Grille_ecrire_bateau(i+eCompteur,j,eNum_grille,Aucun_b);
			eCompteur++;
		}
	}
}
/****************************************************************************/
/****************************************************************************/
/****************************************************************************/
void Enlever_grillebateau2(int eNum_grille){ /*Fonction qui supprime des bateaux d'une grille*/
	int i,j,eObstacle=0;
	if(eNum_grille==2){
		for(i=0;i<N;i++){
			for(j=0;j<M;j++){
				Grille_lire_obstacle(i,j,eNum_grille,&eObstacle);
				if((grille.grille2[i][j].bateau==Sous_Marin || grille.grille2[i][j].bateau==Destroyer || grille.grille2[i][j].bateau==Porte_Avion || grille.grille2[i][j].torpilleur==Present) && !eObstacle){
			 grille.grille2[i][j].bateau=Aucun_b; 
				grille.grille2[i][j].torpilleur=0;
				}

			}
		}
	}else if(eNum_grille==1){
		for(i=0;i<N;i++){
			for(j=0;j<M;j++){
				Grille_lire_obstacle(i,j,eNum_grille,&eObstacle);
				if((grille.grille1[i][j].bateau==Sous_Marin || grille.grille1[i][j].bateau==Destroyer || grille.grille1[i][j].bateau==Porte_Avion || grille.grille1[i][j].torpilleur==Present) && !eObstacle){
			 grille.grille1[i][j].bateau=Aucun_b; 
				grille.grille1[i][j].torpilleur=0;
				}

			}
		}
	}
	
}
/****************************************************************************/
/****************************************************************************/
/****************************************************************************/
void Placer_bateau_auto(int eNum_grille,int eNb_torpilleur,int eNb_sous_m,int eNb_Port_A,int eNb_Dest){ /*Fonction qui place aléatoirement des bateaux*/
	int eCompteur=0,eChoix_sens,i,j,eOk=0,eNb=0,eValide=0,eChoix,compteur=0;
	char sC[20];
	clear();
	srand(time(NULL));
	do{
	    compteur=0;
	    for(eCompteur=0;eCompteur!=1;eCompteur++){
		//Sous_Marin
		do{
			while(compteur!=eNb_sous_m){
			    	eOk=0;
				i=uHasard(N);
				j=uHasard(M);
			    	if(bCroit(0,i,N-1) && bCroit(0,j,M-1)){
						eChoix_sens=uHasard(2);
						if(verif_presence(Sous_Marin,i,j,eChoix_sens,eNum_grille) && Assez_de_place(Sous_Marin,i,j,eChoix_sens,eNum_grille)){
							Placer_grillebateau(Sous_Marin, i,j,eNum_grille,eChoix_sens);
							eOk=1;
							compteur++;
						}            
			    	}

			}
       		}while(!eOk);
	 	eOk=0;
		compteur=0;
		//Destroyer
		do{
			while(compteur!=eNb_Dest){
				eOk=0;
				i=uHasard(N);
				j=uHasard(M);
			    if(bCroit(0,i,N-1) && bCroit(0,j,M-1)){
				eChoix_sens=uHasard(2);
					if(verif_presence(Destroyer,i,j,eChoix_sens,eNum_grille) && Assez_de_place(Destroyer,i,j,eChoix_sens,eNum_grille)){
						Placer_grillebateau(Destroyer, i,j,eNum_grille,eChoix_sens);
						eOk=1;
						compteur++;
					}
			    }
			}
		}while(!eOk);
        	eOk=0;
		compteur=0;
		//Porte_Avion
		do{
			while(compteur!=eNb_Port_A){
				eOk=0;
				i=uHasard(N);
				j=uHasard(M);
			    if(bCroit(0,i,N-1) && bCroit(0,j,M-1)){
				eChoix_sens=uHasard(2);
					if(verif_presence(Porte_Avion,i,j,eChoix_sens,eNum_grille) && Assez_de_place(Porte_Avion,i,j,eChoix_sens,eNum_grille)){
						Placer_grillebateau(Porte_Avion, i,j,eNum_grille,eChoix_sens);
						eOk=1;
						compteur++;
					}                    
			    }
			}
		}while(!eOk);
		eOk=0;
		eNb=0;
		//Torpilleur(s)
		while(eNb!=eNb_torpilleur){
			eOk=0;
			do{
				i=uHasard(N);
				j=uHasard(M);
				if(bCroit(0,i,N-1) && bCroit(0,j,M-1)){		          
				    eChoix_sens=uHasard(2);
					if(verif_presence(Present,i,j,eChoix_sens,eNum_grille) && Assez_de_place(Present,i,j,eChoix_sens,eNum_grille)){
						Grille_ecrire_torpilleur(i,j,eNum_grille,Present);
						eOk=1;
						eNb++;	
					}		            
			    	}
			}while(!eOk);

		}
	 }
		Grille_perso_afficher(eNum_grille);
		    printw("Etes vous satisfait de vos bateaux ?? (Oui:1) : ");
		    refresh();
		    echo();
		    scanw("%s",sC);
		   noecho();
		    if(bStringtonum(sC,&eChoix)){
		        if(eChoix==1)eValide=1; 
				else{
					eValide=0;
					Enlever_grillebateau2(eNum_grille);
					clear();
				}
		    }else  Enlever_grillebateau2(eNum_grille);
		
	}while(!eValide);
}

/****************************************************************************/
/****************************************************************************/
/****************************************************************************/

int Changement_colonne(char * v,int *pRes){
	 if(strcmp(v,"A")==0 || strcmp(v,"a")==0){
	 	*pRes=0;
	 	return 1;
	 }
	 else if(strcmp(v,"B")==0 || strcmp(v,"b")==0){
		*pRes=1;
	 	return 1;	 
	 }
	 else if(strcmp(v,"C")==0 || strcmp(v,"c")==0){
	 	*pRes=2;
	 	return 1;
	 }
	 else if(strcmp(v,"D")==0 || strcmp(v,"d")==0){
	 	*pRes=3;
	 	return 1;
	 }
	 else if(strcmp(v,"E")==0 || strcmp(v,"e")==0){
	 	*pRes=4;
	 	return 1;
	 }
	 else if(strcmp(v,"F")==0 || strcmp(v,"f")==0){
	 	*pRes=5;
	 	return 1;
	 }
	 else if(strcmp(v,"G")==0 || strcmp(v,"g")==0){
	 	*pRes=6;
	 	return 1;
	 }
	 else if(strcmp(v,"H")==0 || strcmp(v,"h")==0){
	 	*pRes=7;
	 	return 1;
	 }
	 else if(strcmp(v,"I")==0 || strcmp(v,"i")==0){
	 	*pRes=8;
	 	return 1;
	 }
	 else if(strcmp(v,"J")==0 || strcmp(v,"j")==0){
	 	*pRes=9;
	 	return 1;
	 }
	 else return 0;
}
/****************************************************************************/
/****************************************************************************/
/****************************************************************************/

void Placer_bateau_manuelle(int eNum_grille,int eNb_torpilleur,int eNb_sous_m,int eNb_Port_A,int eNb_Dest){ /*Fonction qui place manuellement des bateaux*/
    int eCompteur=0,eChoix_sens=0,i=0,j=0,eOk=0,eChoix=0,eValide=0,eNb_t=0;
    char sI[20];
    char sJ[20];
    char sC[20];
	clear();
    Grille_perso_afficher(eNum_grille);
  
		printw("Vous allez rentrer le Sous_Marin\n");
		refresh();
        do{
	    while(eCompteur!=eNb_sous_m){
		    eOk=0; //Variable qui vérifie si le bateau a été placer
		    eChoix=0;
		    printw("Veuillez rentrer les coordonnées i et j de depart pour placer le bateau n°%i: ",eCompteur+1);
		    refresh();
			echo();
		    scanw("%s",sI); //On entre les coordonnées en chaine de caractères
		    scanw("%s",sJ);
			noecho();
		     if(bStringtonum(sI,&i) && Changement_colonne(sJ,&j)){ //On transforme la chaine sI en int sur la variable i, et on entre une colonne en lettre et on la renvoi en int sur j
		         if(bCroit(0,i,N)){
		            printw("Dans quelle sens souhaitez vous le placé ? 1 Horizontal , 2 Vertical\t : ");
		            refresh();
				echo();
		            scanw("%i",&eChoix_sens);
				noecho();
		            if(bCroit(1,eChoix_sens,2)){         
							if(verif_presence(Sous_Marin,i,j,eChoix_sens,eNum_grille) && Assez_de_place(Sous_Marin,i,j,eChoix_sens,eNum_grille)){ //On vérifié si il y a dejà un bateau à l'endroit ou on va placer notre bateau, et on vérifie si il y a la place pour le mettre
								Placer_grillebateau(Sous_Marin, i,j,eNum_grille,eChoix_sens); //Si oui on place le bateau
								eOk=1;
							}
		            }
		    	}
		     }
		    clear();
		    Grille_perso_afficher(eNum_grille); //On affiche la grille pour visualiser notre bateau
		    printw("Etes vous satisfait de votre choix ? Oui:1 \t Non:0 \n");
		    refresh();
			echo();
		    scanw("%s",sC);
			noecho();
		    if(bStringtonum(sC,&eChoix)){ //On convertie en int sC si dans la chaine de caractères il y a que un entier
		        if(eChoix==1 && eOk==1){
				eValide=1; 
				eCompteur++;
			}  //Variable qui vérifie si l'utilisateur est d'accord avec sa position et si le bateau a été placé
			else{
				eValide=0;
				Enlever_grillebateau(Sous_Marin, i,j,eNum_grille,eChoix_sens); //Sinon on supprime le bateau 
			}
		    }else  Enlever_grillebateau(Sous_Marin, i,j,eNum_grille,eChoix_sens);
		}
        }while(!eValide);

 	eOk=0;
	clear();
	eCompteur=0;
	Grille_perso_afficher(eNum_grille); //On affiche la grille pour visualiser notre bateau
	printw("Vous allez placer le Destroyer\n");
	refresh();
        do{
		while(eCompteur!=eNb_Dest){
		    printw("Veuillez rentrer les coordonnées i et j pour placer le bateau n°%i: ",eCompteur+1);
		    refresh();
			echo();
		    scanw("%s",sI);
		    scanw("%s",sJ);
			noecho();
		    if(bStringtonum(sI,&i) && Changement_colonne(sJ,&j)){ //On transforme la chaine sI en int sur la variable i, et on entre une colonne en lettre et on la renvoi en int sur j
		        if(bCroit(0,i,N)){
		            printw("Dans quelle sens souhaitez vous le placé ? 1 Horizontal , 2 Vertical\t : ");
		            refresh();
				echo();
		            scanw("%i",&eChoix_sens);
				noecho();
		            if(bCroit(1,eChoix_sens,2)){
		            	printw("%i pour i et %i pour j \n",i,j);
		            	refresh();
							if(verif_presence(Destroyer,i,j,eChoix_sens,eNum_grille) && Assez_de_place(Destroyer,i,j,eChoix_sens,eNum_grille)){ //On vérifié si il y a dejà un bateau à l'endroit ou on va placer notre bateau, et on vérifie si il y a la place pour le mettre
						    Placer_grillebateau(Destroyer, i,j,eNum_grille,eChoix_sens); //On place le bateau sur la grille si les conditions sont validées
								eOk=1;
							}
			  			 }
					}
		    	}  
		clear();
		    Grille_perso_afficher(eNum_grille); //On affiche la grille pour visualiser notre bateau
				printw("Etes vous satisfait de votre choix ? Oui:1 \t Non:0 \n");
				refresh();
			echo();
		    scanw("%s",sC);
			noecho();
		    if(bStringtonum(sC,&eChoix)){
		        if(eChoix==1 && eOk==1){
				eValide=1;
				eCompteur++;
			} 
			else{
				eValide=0;
				Enlever_grillebateau(Destroyer, i,j,eNum_grille,eChoix_sens); //On l'enlève sinon
			}
		    }else  Enlever_grillebateau(Destroyer, i,j,eNum_grille,eChoix_sens);
		}
        }while(!eValide);
	clear();
	eCompteur=0;
	Grille_perso_afficher(eNum_grille); //On affiche la grille pour visualiser notre bateau
	printw("Vous allez placer le Porte_Avion\n");   
        eOk=0;
        do{
		while(eCompteur!=eNb_Port_A){
		    refresh();
		    printw("Veuillez rentrer les coordonnées i et j pour placer le bateau n°%i : ",eCompteur+1);
		    refresh();
		    echo();
		    scanw("%s",sI);
		    scanw("%s",sJ);
			noecho();
		    if(bStringtonum(sI,&i) && Changement_colonne(sJ,&j)){
		        if(bCroit(0,i,N)){
		            printw("Dans quelle sens souhaitez vous le placé ? 1 Horizontal , 2 Vertical\t : ");
		            refresh();
				echo();
		            scanw("%i",&eChoix_sens);
			noecho();
		            if(bCroit(1,eChoix_sens,2)){
							if(verif_presence(Porte_Avion,i,j,eChoix_sens,eNum_grille)&& Assez_de_place(Porte_Avion,i,j,eChoix_sens,eNum_grille)){//On vérifié si il y a dejà un bateau à l'endroit ou on va placer notre bateau, et on vérifie si il y a la place pour le mettre
						    Placer_grillebateau(Porte_Avion,i,j,eNum_grille,eChoix_sens); //Si les conditions sont validées on place le bateau
								eOk=1;
							}
		             }
		        }
		    }
	clear();
		    Grille_perso_afficher(eNum_grille); //On affiche la grille pour visualiser notre bateau
				printw("Etes vous satisfait de votre choix ? Oui:1 \t Non:0 \n");
		refresh();
			echo();
	
		    scanw("%s",sC);
			noecho();
		    if(bStringtonum(sC,&eChoix)){
		        if(eChoix==1 && eOk==1){
				eValide=1;
				eCompteur++;
			}
					else{
						eValide=0;
						Enlever_grillebateau(Porte_Avion,i,j,eNum_grille,eChoix_sens);
					}
		    }else  Enlever_grillebateau(Porte_Avion,i,j,eNum_grille,eChoix_sens);
		}
        }while(!eValide);
        Grille_perso_afficher(eNum_grille);
		eOk=0;
		eCompteur=0;
		clear();
		Grille_perso_afficher(eNum_grille); //On affiche la grille pour visualiser notre bateau
		refresh();
		while(eCompteur!=eNb_torpilleur){ //Tant qu'on a pas le nombre de torpilleur souhaiter
			do{
			    eOk=0;
			    printw("Vous allez rentrer le torpilleur n°%i \n",eCompteur+1);
			    printw("Veuillez rentrer les coordonnées i et j de depart pour placer le bateau : ");
			    refresh();
				echo();
			    scanw("%s",sI);
			    scanw("%s",sJ);
				noecho();
			    if(bStringtonum(sI,&i) && Changement_colonne(sJ,&j)){
				    if(bCroit(0,i,N)){
						if(verif_presence(Present,i,j,eChoix_sens,eNum_grille)){
							Grille_ecrire_torpilleur(i,j,eNum_grille,Present);
							eOk=1;
						}
				    }
			    }
	clear();
	    Grille_perso_afficher(eNum_grille); //On affiche la grille pour visualiser notre bateau
				printw("Etes vous satisfait de votre choix ? Oui:1 \t Non:0 \n");
				refresh();
			echo();
	            scanw("%s",sC);
			noecho();
	            if(bStringtonum(sC,&eChoix)){
	                if(eChoix==1 && eOk==1)eValide=1;
					else{
						eValide=0;
						Enlever_grillebateau(Present,i,j,eNum_grille,eChoix_sens);
					}
	            }else  Enlever_grillebateau(Present,i,j,eNum_grille,eChoix_sens);
	        }while(!eValide);
			eCompteur++;	
		}
    
	clear();
	Grille_perso_afficher(eNum_grille);
}
/****************************************************************************/
/****************************************************************************/
/****************************************************************************/
int init_grille(void){ /*Fonction qui initialise completement la grille et qui demande à l'utilisateur de placé les bateaux*/
	char sChoix[20];
	char sT[20];
	char sConfig[20];
	int eChoix=0,eValide=1,eNb_torpilleurs=0,eNumJ=1,eConfig=1,eNb_sous_m=1,eNb_Dest=1,eNb_Port_A=1;
	Grille_init(); //On initialise la grille avec tout à 0
	placer_obstacle(); //On place les obstacles sur les grilles
	do{
		printw("\nCombien de Torpilleur souhaitez-vous (J%i) et (J%i) ?",eNumJ,eNumJ+1);
		refresh();
		echo();
		scanw("%s",sT);
		noecho();
	}while(!bStringtonum(sT,&eNb_torpilleurs) || (eNb_torpilleurs<=0 || eNb_torpilleurs>5)); //Tant qu'on a pas un nombres de torpilleurs en int on continue, et tant qu'on a pas un nombre de torpilleurs entre 1 et 5 inclus
	printw("Configuration de la partie :\n\n\t 1 bateau de chaque : 1\n\t Choisir son nombre de bateaux : 2\n");
	refresh();
	echo();
	scanw("%s",sConfig);
	noecho();
	while(bStringtonum(sConfig,&eConfig) && eValide){
			if(eConfig==1){
				eNb_sous_m=1;
				eNb_Dest=1;
				eNb_Port_A=1;
				eValide=0;
			}
			else if(eConfig==2){
				clear();
				printw("Choix en configuration : \n");
				printw("Combien de Sous-Marin souhaitez vous ? ");
				refresh();
				echo();
				scanw("%i",&eNb_sous_m);
				noecho();
				printw("Combien de Destroyer souhaitez vous ? ");
				refresh();
				echo();
				scanw("%i",&eNb_Dest);
				noecho();
				printw("Combien de Porte-Avion souhaitez vous ? ");
				refresh();
				echo();
				scanw("%i",&eNb_Port_A);
				noecho();
				eValide=0;
			}
			else{
				printw("Merci d'entrer un chiffre correct\n");	
				refresh();
				echo();			
				scanw("%s",&sConfig);
				noecho();

			}
	}
	clear();
	while(!eValide || eNumJ!=3){
		clear();
		printw("\n\nPlacé automatique (J%i) : 1 \n\nPlacé manuelle (J%i): 2\n\n",eNumJ,eNumJ);
		printw("Choix : ");
		refresh();
		echo();
		scanw("%s",sChoix);
		noecho();


		if(bStringtonum(sChoix,&eChoix)){ //Si dans choix on a seulement 1 entier on renvoie l'entier dans Choix
				if(eChoix==1){
					Placer_bateau_auto(eNumJ,eNb_torpilleurs,eNb_sous_m,eNb_Port_A,eNb_Dest); //On place automatique les bateaux sur les grilles des joueurs
					clear();
					eValide=1;
					eNumJ++;
				}
				else if(eChoix==2){
					Placer_bateau_manuelle(eNumJ,eNb_torpilleurs,eNb_sous_m,eNb_Port_A,eNb_Dest);
					clear();
					eValide=1;
					eNumJ++;
				}					
		}
	}

	return eNb_torpilleurs;
}
